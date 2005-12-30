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
//#include "ConfigDialog.h"
#include "keyboard_plugin.h"

#include <wx/wx.h>
#include <wx/config.h>


IMPLEMENT_APP_NO_MAIN(wxDLLApp)

bool wxDLLApp::OnInit()
{
	return true;
}

bool keyboard_plugin::init()
{
	p_state = wxT("Started");
	
	wxConfig config(wxT("LightShow"));
	config.SetPath(wxT("keyboard_plugin"));
	
	long b;
	long k;
	wxString str;
	long dummy;

	bool bCont = config.GetFirstEntry(str, dummy);
	while ( bCont ) 
	{
		if(config.Read(str,&k))
		{
			if(str.AfterFirst(wxT('_')).ToLong(&b))
			{
				p_key_map[k] = b;
			}
		}
 
		bCont = config.GetNextEntry(str, dummy);
  	}
  	 
	return true;
}

void keyboard_plugin::exit()
{
	wxConfig config(wxT("LightShow"));
	config.DeleteGroup(wxT("keyboard_plugin"));
	config.SetPath(wxT("keyboard_plugin"));
	
	map<int,int>::iterator it;
	for(it = p_key_map.begin(); it != p_key_map.end(); it++)
	{
		config.Write(wxString::Format(wxT("button_%d"),it->second),it->first);
	}
}

void keyboard_plugin::config()
{
/*	ConfigDialog dlg(NULL,-1,wxT("Keyboard Plugin Configuration"));
	dlg.ShowModal();
*/
}

void keyboard_plugin::pc_key_change(int key, bool down)
{
	if(p_key_map.find(key) != p_key_map.end())
	{
		p_interf.key_state_change(p_key_map[key],down);
	}
}

	
extern "C"
{
	io_plugin* get_io_plugin()
	{
		return (io_plugin*) new keyboard_plugin();
	}
}
