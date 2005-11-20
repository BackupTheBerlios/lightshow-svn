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


#include "plugin_interface.h"
#include "storage.h"

#include "main.h"
#include "MainFrame.h"

io_plugin_interface::io_plugin_interface()
{
	interf.key_state_change = &key_state_change;
	interf.slider_pos_change = &slider_pos_change;
	interf.xy_change = &xy_change;
}

void io_plugin_interface::key_state_change(int id,bool down)
{
	deskitem* ditem = storage::deskitem_for_id(id);
	if(!ditem) return;
	
	if(ditem->get_type() == deskitem::T_PAGE)
	{
		storage::page = ditem->get_page_id();
	}
	else if(ditem->get_type() == deskitem::T_FUNCTION)
	{
		functionitem* fitem = storage::functionitem_for_deskitem(ditem,storage::page);
		if(fitem)
		{
			if(down)
				fitem->activate();
			else
				fitem->deactivate();
		}
	}
	else if(ditem->get_type() == deskitem::T_GROUP)
	{
		groupselectitem* gitem = storage::groupselectitem_for_deskitem(ditem,storage::page);
		if(gitem)
		{
			gitem->activate(down);
		}
	}
	
	RefreshDesk();	
}

void io_plugin_interface::slider_pos_change(int id, int pos, bool flash)
{
	deskitem* ditem = storage::deskitem_for_id(id,true);
	
	if(!ditem) return;
		
	//hw pos
	if(!flash && pos != -1)
		ditem->pos = pos;
	
	faderitem* fitem = storage::faderitem_for_deskitem(ditem,storage::page);
	if(fitem)
	{
		if(flash)
		{
			fitem->tab();
		}
		else
		{
			fitem->tab_release();
			if(pos != -1)
				fitem->set_active_pos(pos);
		}
	}
		
	RefreshDesk();	
}

void io_plugin_interface::xy_change(int x, int y, bool relative)
{
	
	RefreshDesk();
}

void io_plugin_interface::RefreshDesk()
{	
	storage::update_key_led_states();
	
	MainFrame* mfr = (MainFrame*)::wxGetApp().GetTopWindow();
	if(mfr) mfr->RefreshDesk();	
}
