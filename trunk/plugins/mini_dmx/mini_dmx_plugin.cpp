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
#include "mini_dmx_plugin.h"

#include <wx/wx.h>

IMPLEMENT_APP_NO_MAIN(wxDLLApp)

bool wxDLLApp::OnInit()
{
	return true;
}

bool mini_dmx_plugin::init()
{
	::wxInitialize();

	p_thread = new MainThread();
	p_thread->Create();
	p_thread->Run();

	return true;
}

void mini_dmx_plugin::exit()
{
	p_thread->Delete();

	::wxUninitialize();
}

void mini_dmx_plugin::config()
{
	ConfigDialog dlg(NULL,-1,wxT("MiniDMX Configuration"));
	dlg.ShowModal();

	p_thread->Delete();
	p_thread = new MainThread();
	p_thread->Create();
	p_thread->Run();
}

void mini_dmx_plugin::output(int count, unsigned char* channels)
{
	p_thread->Output(count,channels);
}
	
extern "C"
{
	io_plugin* get_io_plugin()
	{
		return (io_plugin*) new mini_dmx_plugin();
	}
}
