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

#include "projectorchannelitem.h"
#include "projectoritem.h"
#include "valueitem.h"
#include "storage_item.h"
#include "storage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

DECLARE_STATIC_STC(projectorchannelitem)


void new_projectorchannelitem(void* param)
{
	projectorchannelitem* item = new projectorchannelitem((projectoritem*)param);
}


projectorchannelitem::projectorchannelitem(projectoritem* parent) :
p_parent(parent)
{
	p_stor_name = wxT("projectorchannelitem");
	
	p_id_map[wxT("channel")] = 1;
	p_id_map[wxT("name")] = 2;
	p_id_map[wxT("type")] = 3;
	p_id_map[wxT("type_int")] = 4;
	p_id_map[wxT("channel_int")] = 5;
	
	p_dont_show_map[4] = true;
	p_dont_show_map[5] = true;
	
	p_dont_save_map[1] = true;
	p_dont_save_map[3] = true;
	
	p_editable_map[1] = true;
	p_editable_map[2] = true;
	p_editable_map[3] = true;
	
	p_column_width[1] = 65;
	p_column_width[2] = 200;
	p_column_width[3] = 160;
	
	p_channel = p_parent->list_projectorchannelitem.size() + 1;
	p_name = wxT("New Channel");
	p_type = 4;
	
	map_type[wxT("Pan")] = T_PAN;
	map_type[wxT("Tilt")] = T_TILT;
	map_type[wxT("Continous")] = T_CONTINOUS;
	map_type[wxT("Value")] = T_VALUE;
		
	p_parent->list_projectorchannelitem.push_back(this);
}

projectorchannelitem::~projectorchannelitem()
{
	while(!list_valueitem.empty())
		delete *list_valueitem.begin();
	
	p_parent->list_projectorchannelitem.remove(this);
}

void projectorchannelitem::save(wxFile& file)
{
	storage_item::save_main(file);
	storage::save(file, list_valueitem);
	storage_item::save_end(file);
}

void projectorchannelitem::load(wxFile& file)
{
	wxString parm = storage_item::load_main(file);
	while(parm != wxT(""))
	{
		if(parm == wxT("valueitem"))
		{
			valueitem* item = new valueitem(this);
			item->load(file);
		}

		parm = storage_item::load_main(file);
	}
}

bool projectorchannelitem::is_less(storage_item& b)
{
	projectorchannelitem* pcitem = (projectorchannelitem*)&b;
	return (p_channel > pcitem->get_channel());
}

void projectorchannelitem::delete_deps()
{
	//TODO wie immer
}

wxString projectorchannelitem::get_s_param(int id)
{
	switch(id)
	{
		case 1:
		case 5:
			return storage::int_to_str(p_channel);
		case 2:
			return p_name;
		case 3:
			return param_map_lookup(&map_type,p_type);
		case 4:
			return storage::int_to_str(p_type);
		default:
			return wxT("");
	}
}

bool projectorchannelitem::change_channel(unsigned int new_channel)
{
	if(new_channel > p_parent->list_projectorchannelitem.size())
		return false;
	
	storageitemlist::iterator it;
	
	for(it = p_parent->list_projectorchannelitem.begin();it != p_parent->list_projectorchannelitem.end();it++)
	{
		projectorchannelitem* pcitem = (projectorchannelitem*)*it;

		if(pcitem->get_channel() == new_channel)
		{
			if(!pcitem->set_channel(p_channel))
				return false;
			else
			{
				p_channel = new_channel;

#ifndef __VISUALC__ //VSC++ doesn't support sort
				p_parent->list_projectorchannelitem.sort(storage_item_sort());
#endif

				return true;
			}
		}
	}
	
	return false;
}
	
bool projectorchannelitem::set_param(int id,wxString value)
{
	int t;
	
	switch(id)
	{
		case 1:
			return change_channel(storage::str_to_int(value));
		case 2:
			p_name = value;
			return true;
		case 3:
			t = map_type[value];
			if(t != 0)
			{
				p_type = t;
				return true;
			}
			else return false;
		case 4:
			t = storage::str_to_int(value);
			if(param_map_lookup(&map_type,t) != wxT(""))
			{
				p_type = t;
				return true;
			}
			else
				return false;
		case 5:
			p_channel = storage::str_to_int(value);
			return true;
		default:
			return false;
	}
}

wxString projectorchannelitem::get_param_map(int id)
{
	if(id == 3)
	{
		return storage_item::param_map_to_string(&map_type);
	}

	return wxT("");
}
