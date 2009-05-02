/***************************************************************************
 *  LightShow - control software for DMX512 lighting fixtures
 *
 *  Copyright (C) 2005  Thorsten Baumhoefer
 *  totob(at)totosoft.de
 *
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 ***************************************************************************/


#include "../include/io_plugin.h"
#include "MainThread.h"
#include <wx/config.h>


MainThread::MainThread() : wxThread()
{
	dataout[0] = 255;

	for(int j = 0;j < 78;j++)
	{
		prevstate[j] = false;
		if(j < 24)
		{
			prevpos[j] = 0;
			prevflash[j] = false;
		}
	}
}

MainThread::~MainThread()
{
}

wxString MainThread::GetState()
{
	return p_state;
}

MainThread::ExitCode MainThread::Entry()
{
	p_state = wxT("started");

#ifdef __WXMSW__
	MSWLoop();
#else
	NIXLoop();
#endif

	return 0;
}

void MainThread::process()
{
	unsigned char parity = 0;
	for(int j = 0;j < 39;j++)
	{
		parity += datain[j];
	}
	
	if(datain[39] != parity) 
	{
		p_state = wxT("failure");
		return;
	}

	p_state = wxT("running");
	
	int i;
	for(i = 15; i < 39;i++)
	{
		if(datain[i] > prevpos[i-15]+2 || datain[i] < prevpos[i-15]-2)
		{
			bool flash = false;
			int pos = datain[i];
			
			if(datain[i] > 250)
			{
				if(prevpos[i-15] < 240)
				{
					flash = true;
					prevflash[i-15] = true;
				}
			}
			else
			{
				if(prevflash[i-15])
				{
					prevflash[i-15] = false;
					pos = -1;
				}
			}
			
			prevpos[i-15] = datain[i];
			
			if(!TestDestroy()) p_interf.slider_pos_change(i-14,pos,flash);
		}
	}
	
	if(TestDestroy()) return;
	
	for(i = 0; i < 78;i++)
	{
		bool down = true;
		if((datain[i/6] & (int)(1<<i%6)) == (1<<i%6)) down = false;
		
		
		if(prevstate[i] != down)
		{
			if(!TestDestroy()) p_interf.key_state_change(i+1, down);
			prevstate[i] = down;
		}
	}
	

	/*
	//TODO pos verarbeiten datain[13] + [14]
	datain[13] = 63 - datain[13];
	
	int prevxy[2];
	int xycount = 0;
	
	prevxy[0] = 127;
	prevxy[1] = 127;
	
	
	if(abso)
	{
		  int x = (datain[14] - upper_left_x) / (double)(down_right_x - upper_left_x) * 255;
		  int y = (datain[13] - down_right_y) / (double)(upper_left_y - down_right_y) * 255;
		  
		  if((prevxy[0] != x) || (prevxy[1] != y))
		  {
			  prevxy[0] = x;
			  prevxy[1] = y;
			  
			  in.SetXY(x,y,FALSE);
		  }
	}
	else
	{
		  int x = 0;
		  int y = 0;
		  
		  if(datain[14] > middle_x + 10)
			  x = (datain[14] - middle_x + 10) / (double)(down_right_x - middle_x + 10) * 8;
		  else if(datain[14] < middle_x - 10)
			  x = ((datain[14] - upper_left_x) / (double)(middle_x - 2 - upper_left_x) * 8) - 8;
		  
		  if(datain[13] > middle_y + 10)
			  y = (datain[13] - middle_y + 10) / (double)(upper_left_y - middle_y + 10) * 8;
		  else if(datain[13] < middle_y - 10)
			  y = ((datain[13] - down_right_y) / (double)(middle_y - 2 - down_right_y) * 8) - 8;
		  
		  in.SetXY(x,y,TRUE);
		  
	}
	*/
			  
}

void MainThread::calc_parity()
{
	unsigned char parity = 0;
	
	for(int j = 1;j < 84;j++)
	{
		parity += dataout[j];
	}
	
	dataout[84] = parity;	
}

#ifdef __WXMSW__

void MainThread::MSWLoop()
{
	wxConfig* config = new wxConfig(wxT("LightShowPlugins"));

	wxString port = config->Read(wxT("lscontrol_plugin/serial_port"),wxT("COM1"));

	delete config;

	DCB dcb;
	BOOL fSuccess;
	HANDLE hCom;

	hCom = CreateFile( port.fn_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	
	if(hCom == INVALID_HANDLE_VALUE)
	{
		LPVOID lpMsgBuf;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,NULL,GetLastError(),MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),(LPTSTR) &lpMsgBuf,0,NULL );
		p_state = wxT("error opening [") + port + wxT("]: ") + (LPCTSTR)lpMsgBuf;
		LocalFree( lpMsgBuf );
		
		while(!TestDestroy())
			Sleep(1000);
		return;
	}
	
	// Omit the call to SetupComm to use the default queue sizes.
	// Get the current configuration.
	
	fSuccess = GetCommState(hCom, &dcb);
	
	if(!fSuccess)
	{
		CloseHandle(hCom);
		p_state = wxT("error GetComState: ") + port;
		while(!TestDestroy())
			Sleep(1000);
		return;
	}
	
	dcb.fDtrControl = DTR_CONTROL_DISABLE;
	dcb.fRtsControl = RTS_CONTROL_DISABLE;
	dcb.BaudRate = 115200;
	dcb.ByteSize = 8;
	dcb.Parity = NOPARITY;
	dcb.StopBits = ONESTOPBIT;
	
	fSuccess = SetCommState(hCom, &dcb);
	
	if(!fSuccess)
	{
		CloseHandle(hCom);
		p_state = wxT("error SetComState: ") + port;
		while(!TestDestroy())
			Sleep(1000);
		return;
	}
	
	DWORD asd;
	unsigned char buf;

	while(!TestDestroy())
	{
		asd = 0;
		buf = 0;

		do
		{
			ReadFile(hCom,&buf,1,&asd,NULL);
			Sleep(1);
		} while(!TestDestroy() && (buf != 255 || asd != 1));

		if(TestDestroy()) break;

		ReadFile(hCom,&datain[0],40,&asd,NULL);
		if(asd != 40) continue;

		calc_parity();

		WriteFile(hCom,&dataout[0],85,&asd,NULL);

		process();
	}

	CloseHandle(hCom);
}

#endif //ifdef __WXMSW__



#ifndef __WXMSW__

#include <termios.h>
#include <fcntl.h>
#include <sys/ioctl.h>

void MainThread::NIXLoop()
{
	wxConfig config(wxT("LightShowPlugins"));

	wxString port = config.Read(wxT("lscontrol_plugin/serial_port"),wxT("/dev/ttyS1"));	

	int fd = open(port.fn_str(), O_RDWR | O_NOCTTY);
	if (fd < 0)
	{
		p_state = wxT("error opening [") + port + wxT("]");
		while(!TestDestroy())
			Sleep(1000);
		return;
	}
				
	struct termios tio;
	tio.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
	tio.c_iflag = 0;
	tio.c_oflag = 0;
	tio.c_lflag = 0;
	tio.c_cc[VMIN] = 40;
	tio.c_cc[VTIME] = 5;
	tcflush(fd, TCIFLUSH);
	tcsetattr(fd,TCSANOW,&tio);
	
	int i;
	
	i = TIOCM_RTS;
	ioctl(fd, TIOCMBIC, &i);
	i = TIOCM_DTR;
	ioctl(fd, TIOCMBIC, &i);

	int res;
	unsigned char buf;

	while(!TestDestroy())
	{
		buf = 0;

		do
		{
			res = read(fd,&buf,1);
			Sleep(1);
		} while(!TestDestroy() && (buf != 255 || res != 1));

		if(TestDestroy()) break;

		res = read(fd,&datain[0],40);

		if(res != 40) continue;

		calc_parity();

		write(fd,&dataout[0],85);

		process();
	}
			
	close(fd);
}
#endif // ifndef __WXMSW__
