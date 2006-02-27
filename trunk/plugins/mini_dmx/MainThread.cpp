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


#include "MainThread.h"
#include <wx/config.h>

#define P_BLKSTART	0x5A
#define P_BLKEND	0xA5
#define P_DMXOUT96	0xA0
#define P_DMXOUT512 0xA2
#define P_ACK		0xC1
#define P_ERROR     0xC0

#define USE512 0

MainThread::MainThread() : wxThread()
{
}

MainThread::~MainThread()
{
}

void MainThread::Output(int count, unsigned char* channels)
{
	p_data = channels;
	p_count = count;
}

wxString MainThread::GetState()
{
	return p_state;
}

MainThread::ExitCode MainThread::Entry()
{
	p_data = NULL;
	p_state = wxT("started");

#ifdef __WXMSW__
	MSWLoop();
#else
	NIXLoop();
#endif

	return 0;
}



#ifdef __WXMSW__

void MainThread::MSWLoop()
{
	wxConfig config(wxT("LightShow"));

	wxString port = config.Read(wxT("mini_dmx_plugin/serial_port"),wxT("COM1"));

	DCB dcb;
	DWORD asd;
	int fSuccess;
	HANDLE hCom;
	int i;
	unsigned char ack;

	hCom = CreateFile(port.fn_str(),GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

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

	fSuccess = GetCommState(hCom,&dcb);

	if(!fSuccess)
	{
		CloseHandle(hCom);
		p_state = wxT("error GetComState: ") + port;
		while(!TestDestroy())
			Sleep(1000);
		return;
	}

	dcb.fDtrControl = DTR_CONTROL_DISABLE;
	dcb.fRtsControl = RTS_CONTROL_ENABLE;
	dcb.BaudRate = 115200;
	dcb.ByteSize = 8;
	dcb.Parity = NOPARITY;
	dcb.StopBits = ONESTOPBIT;

	fSuccess = SetCommState(hCom,&dcb);

	if(!fSuccess)
	{
		CloseHandle(hCom);
		p_state = wxT("error SetComState: ") + port;
		while(!TestDestroy())
			Sleep(1000);
		return;
	}

	COMMTIMEOUTS cto;

	cto.ReadIntervalTimeout = 100;
	cto.ReadTotalTimeoutConstant = 100;
	cto.ReadTotalTimeoutMultiplier = 100;
	cto.WriteTotalTimeoutConstant = 100;
	cto.WriteTotalTimeoutMultiplier = 100;

	SetCommTimeouts(hCom,&cto);

#ifdef USE512
	unsigned char data[515];
	data[0] = P_BLKSTART;
	data[1] = P_DMXOUT512;
	data[514] = P_BLKEND;
#else
	unsigned char data[99];
	data[0] = P_BLKSTART;
	data[1] = P_DMXOUT96;
	data[98] = P_BLKEND;
#endif	
				
	while(!TestDestroy())
	{
		Sleep(5);

		if(p_data == NULL) continue;

#ifdef USE512
		for(i = 0; i < 512;i++)
#else
		for(i = 0; i < 96;i++)
#endif
		{
			if(i < p_count)
				data[i+2] = p_data[i];
		}
		
		PurgeComm(hCom, PURGE_RXCLEAR);
#ifdef USE512
		WriteFile(hCom,data,515,&asd,NULL);
#else
		WriteFile(hCom,data,99,&asd,NULL);
#endif
		ReadFile(hCom,&ack,1,&asd,NULL);
		if(asd == 1 && ack == P_BLKSTART)
		{
			ReadFile(hCom,&ack,1,&asd,NULL);
			if(asd == 1 && ack == P_ACK)
			{
				ReadFile(hCom,&ack,1,&asd,NULL);
				if(asd == 1 && ack == P_BLKEND)
				{
					p_state = wxT("running");
					continue;
				}
			}
			else if(asd == 1 && ack == P_ERROR)
			{
				ReadFile(hCom,&ack,1,&asd,NULL);
				if(asd == 1 && ack == P_BLKEND)
				{
					p_state = wxT("error");
					continue;
				}
			}
		}

		p_state = wxT("failure");
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
	wxConfig config(wxT("LightShow"));

	wxString port = config.Read(wxT("mini_dmx_plugin/serial_port"),wxT("/dev/ttyS1"));	

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
	tio.c_cc[VMIN] = 0;
	tio.c_cc[VTIME] = 5;
	tcflush(fd, TCIFLUSH);
	tcsetattr(fd,TCSANOW,&tio);
	
	int i;
	
	i = TIOCM_RTS;
	ioctl(fd, TIOCMBIS, &i);
	i = TIOCM_DTR;
	ioctl(fd, TIOCMBIC, &i);
	
	int res;
#ifdef USE512
	unsigned char data[515];
	data[0] = P_BLKSTART;
	data[1] = P_DMXOUT512;
	data[514] = P_BLKEND;
#else
	unsigned char data[99];
	data[0] = P_BLKSTART;
	data[1] = P_DMXOUT96;
	data[98] = P_BLKEND;
#endif
	unsigned char ack;
				
	while(!TestDestroy())
	{
		Sleep(5);

		if(p_data == NULL) continue;

#ifdef USE512
		for(i = 0; i < 512;i++)
#else
		for(i = 0; i < 96;i++)
#endif
		{
			if(i < p_count)
				data[i+2] = p_data[i];
		}

		tcflush(fd, TCIFLUSH);

#ifdef USE512
		write(fd,data,515);
#else
		write(fd,data,99);
#endif

		res = read(fd,&ack,1);
		if(res == 1 && ack == P_BLKSTART)
		{
			res = read(fd,&ack,1);
			if(res == 1 && ack == P_ACK)
			{
				res = read(fd,&ack,1);
				if(res == 1 && ack == P_BLKEND)
				{
					p_state = wxT("running");
					continue;
				}
			}
			else if(res == 1 && ack == P_ERROR)
			{
				res = read(fd,&ack,1);
				if(res == 1 && ack == P_BLKEND)
				{
					p_state = wxT("error");
					continue;
				}
			}
 
		}

		p_state = wxT("failure");
	}
	
	close(fd);
}
#endif // ifndef __WXMSW__
