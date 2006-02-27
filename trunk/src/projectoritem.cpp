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

#include "projectoritem.h"
#include "projectorchannelitem.h"
#include "stateitem.h"
#include "storage.h"

void new_projectoritem(void* param)
{
	projectoritem* pitem = new projectoritem();
	stateitem* sitem = new stateitem(pitem,stateitem::STATE_ON);
	sitem = new stateitem(pitem,stateitem::STATE_OFF);
	sitem = new stateitem(pitem,stateitem::STATE_HIGHLITE);
}

projectoritem::projectoritem()
{
	p_stor_name = wxT("projectoritem");
	
	p_id_map[wxT("name")] = 1;
	p_id_map[wxT("num_channels")] = 2;

	p_editable_map[1] = true;
	
	p_dont_show_map[2] = true;
	
	p_dont_save_map[2] = true;
	
	p_column_width[1] = 200;
	
	p_name = wxT("New Device");
	
	storage::list_projectoritem.push_back(this);
}

projectoritem::~projectoritem()
{		
	while(!list_stateitem.empty())
		delete *list_stateitem.begin();
	
	while(!list_projectorchannelitem.empty())
		delete *list_projectorchannelitem.begin();

	storage::list_projectoritem.remove(this);
}

void projectoritem::save(wxFile& file)
{
	storage_item::save_main(file);
	storage::save(file, list_projectorchannelitem);
	storage::save(file, list_stateitem);
	storage_item::save_end(file);
}

void projectoritem::load(wxFile& file)
{
	wxString parm = storage_item::load_main(file);
	while(parm != wxT(""))
	{
		if(parm == wxT("projectorchannelitem"))
		{
			projectorchannelitem* item = new projectorchannelitem(this);
			item->load(file);
		}
		else if(parm == wxT("stateitem"))
		{
			stateitem* item = new stateitem(this);
			item->load(file);
		}
		
		parm = storage_item::load_main(file);
	}
	
	if(list_stateitem.size() != 3)
	{
		//TODO find missing state and add it
	}
}

void projectoritem::delete_deps()
{
	//TODO auch von zugehoeringen channels und states debs deleten
}

wxString projectoritem::get_s_param(int id)
{
	switch(id)
	{
		case 1:
			return p_name;
		case 2:
			return storage::int_to_str(get_num_channels());
		default:
			return wxT("");
	}
}

bool projectoritem::set_param(int id,wxString value)
{	
	switch(id)
	{
		case 1:
			p_name = value;
			return true;
		//case 2: // ReadOnly: Cannot be set
		default:
			return false;
	}
}

void projectoritem::run(int start_channel, int pos, int what)
{
	stateitem *on = storage::stateitem_for_state(this,stateitem::STATE_ON);
	stateitem *off = storage::stateitem_for_state(this,stateitem::STATE_OFF);

	if(!on || !off) return;

	for(int i = 0; i < get_num_channels(); i++)
	{
		if(on->get_mask(i) && off->get_mask(i))
		{
			if((pos < 5 && what == R_SW_OV) || (pos >= 5 && what == R_ON))
			{
				unsigned int a = on->get_value(i);
				unsigned int b = off->get_value(i);
				storage::DMX[start_channel+i-1] = (unsigned char)(b-(pos/255.0*b)+(pos/255.0*a));
			}
		}
		else
		{
			if(pos < 127 && what == R_SW_OV)
			{
				if(off->get_mask(i))
					storage::DMX[start_channel+i-1] = off->get_value(i);
			}
			else if(what == R_ON)
			{
				if(on->get_mask(i))
					storage::DMX[start_channel+i-1] = on->get_value(i);
			}
		}
	}
}

void projectoritem::highlite(int start_channel)
{
	stateitem *hl = storage::stateitem_for_state(this,stateitem::STATE_HIGHLITE);

	if(!hl) return;

	for(int i = 0; i < get_num_channels(); i++)
	{
		if(hl->get_mask(i))
		{
			storage::DMX[start_channel+i-1] = hl->get_value(i);
		}
	}
}
