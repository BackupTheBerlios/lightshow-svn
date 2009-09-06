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


#include "FunctionThread.h"
#include "MainFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


FunctionThread::FunctionThread(wxApp* app) : wxThread(wxTHREAD_JOINABLE)
{
	p_app = app;
	end = false;
}

FunctionThread::~FunctionThread()
{
}

void FunctionThread::End()
{
	end = true;
}

FunctionThread::ExitCode FunctionThread::Entry()
{
	wxLongLong time_now,time_old,elapsed,wait;
	storageitemlist::iterator it;
	
	wait = 25;
	
	while(!end)
	{
		//Wait for 25ms to elapse
		do
		{
			Sleep(1);
			time_now = ::wxGetLocalTimeMillis();
			elapsed = time_now - time_old;
		}while(elapsed < wait);

		time_old = time_now;
		
		//printf("%d\n",elapsed.GetLo());
		
		if(elapsed < 50)
			wait = 25 - (elapsed - wait);
		else
			wait = 25;
		
		for(int i = 0;i < DMX_CHNLS;i++)
		{
			storage::DMX[i] = 0;
		}
		
		//If setuping - run only prewiews of functions
		if(storage::setup && storage::setuping)
		{
			for(it = storage::list_functionitem.begin();it != storage::list_functionitem.end();it++)
			{
				functionitem* item = (functionitem*)*it;
				item->run(R_PREVIEW);
			}
			
			Output();
			continue;
		}
		
		//--------RunFunctions---------------------------
		//1st Switched Functions + FaderFkt (no Overlay)
		//  XFade
		//2nd Switched Functions + FaderFkt Overlay
		//  MasterFader
		//3rd PushButton Functions (no Overlay)
		//  XFade2
		//4th PushButton Functions Overlay
		for(int run = R_ON;run <= R_PB_OV;run++)
		{
			for(it = storage::list_functionitem.begin();it != storage::list_functionitem.end();it++)
			{
				functionitem* item = (functionitem*)*it;
				item->run(run);
			}
		
			for(it = storage::list_faderitem.begin();it != storage::list_faderitem.end();it++)
			{
				faderitem* item = (faderitem*)*it;
				item->run(run);
			}
		}

		Output();

	}

	return 0;
}

void FunctionThread::Output()
{	
	unsigned int i;
	for(i = 0;i < DMX_CHNLS;i++)
	{
		int d = patchitem::get_patch(i+1);
		if(d != -1)
			DMXout[d-1] = storage::DMX[i];
	}

	for(i = 0;i < storage::list_io_plugins.size();i++)
		storage::list_io_plugins[i]->output(DMX_CHNLS,DMXout);
	
	MainFrame* mfr = (MainFrame*)p_app->GetTopWindow();
	if(mfr) 
	{
		MainFrameRefreshEvent* evt = new MainFrameRefreshEvent(-1);
		mfr->GetEventHandler()->QueueEvent(evt);
	}
}
