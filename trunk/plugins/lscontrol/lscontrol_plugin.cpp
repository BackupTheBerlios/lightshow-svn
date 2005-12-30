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
#include "ConfigDialog.h"
#include "lscontrol_plugin.h"

#include <wx/wx.h>

IMPLEMENT_APP_NO_MAIN(wxDLLApp)

bool wxDLLApp::OnInit()
{
	return true;
}

bool lscontrol_plugin::init()
{
	p_thread = new MainThread();
	p_thread->Create();
	p_thread->set_interf(p_interf);
	p_thread->Run();

	return true;
}

void lscontrol_plugin::exit()
{
	p_thread->Delete();
}

void lscontrol_plugin::config()
{
	ConfigDialog dlg(NULL,-1,wxT("LSControl Desk Configuration"));
	dlg.ShowModal();

	p_thread->Delete();
	p_thread = new MainThread();
	p_thread->Create();
	p_thread->set_interf(p_interf);
	p_thread->Run();
}

void lscontrol_plugin::set_key_leds(int count, bool* state)
{
	int i;
	for(i = 1;i < 14;i++)
	{
		p_thread->dataout[i] = 63;
	}

	for(i = 0;i < count;i++)
	{
		if(i == 78) break;
		if(state[i])
		{
			p_thread->dataout[(i/6)+1] -= (int)pow(2,i%6);
		}
	}
}

void lscontrol_plugin::output(int count, unsigned char* channels)
{
	for(int i = 0;i < count;i++)
	{
		if(i == 70) break;
		p_thread->dataout[i+14] = channels[i];
	}
}
	
extern "C"
{
	io_plugin* get_io_plugin()
	{
		return (io_plugin*) new lscontrol_plugin();
	}
}
