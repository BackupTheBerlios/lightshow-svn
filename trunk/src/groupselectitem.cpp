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

#include "groupselectitem.h"
#include "storage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


DECLARE_STATIC_STC(groupselectitem)

void new_group_in_groupselectitem(void* param)
{
	groupselectitem* item = (groupselectitem*) param;
	item->new_group();
}

groupselectitem::groupselectitem()
{
	init(-1,-1);
}

groupselectitem::groupselectitem(int button_id, int page)
{
	init(button_id,page);
}

void groupselectitem::init(int button_id, int page)
{
	p_stor_name = wxT("groupselectitem");
	
	p_id_map[wxT("id")] = 1;
	p_id_map[wxT("button_id")] = 2;
	p_id_map[wxT("page")] = 3;
	p_id_map[wxT("name")] = 4;
	
	p_dont_show_map[1] = true;
	p_dont_show_map[2] = true;
	p_dont_show_map[3] = true;
	
	p_editable_map[4] = true;	
	
	active = true;

	p_id = get_max_id(storage::list_groupselectitem,wxT("id")) + 1;
	
	p_button_id = button_id;
	p_page = page;

	storage::list_groupselectitem.push_back(this);
}

groupselectitem::~groupselectitem()
{
	storage::list_groupselectitem.remove(this);
}

bool groupselectitem::should_show(unsigned int id)
{
	if(id < 5)
		return !p_dont_show_map[id];
	else
		return ((id % 2) == 1);
}

bool groupselectitem::can_edit(int id)
{
	if(id < 5)
		return p_editable_map[id];
	else
		return ((id % 2) == 1);
}

bool groupselectitem::should_save(int id)
{
	if(id < 5)
		return !p_dont_save_map[id];
	else
		return ((id % 2) == 0);
}

wxString groupselectitem::get_param_name(int id)
{
	if(id < 5)
		return param_map_lookup(&p_id_map,id);
	else
		return wxT("group");
}

int groupselectitem::get_num_params()
{
	return group_list.size()+1;
}

int groupselectitem::get_num_all_params()
{
	return group_list.size()*2+4;
}

void groupselectitem::new_group()
{
	int size = group_list.size();
	
	group_list.push_back(-1);
}

void groupselectitem::delete_param(int id)
{
	if(id < 5) return;
	
	//delete data
	vector<int>::iterator it = group_list.begin();
	for(int i = 1; i+5 < id; i += 2)
	{
		if(it == group_list.end()) return;
		it++;
	}
	
	if(it != group_list.end())
		group_list.erase(it);
	
	//TODO what if chn active state = false while deleting?
}

wxString groupselectitem::get_param_map(int id)
{
	//View
	if(id >= 5 && ((id % 2) == 1))
	{
		return storage::list_to_string_compare(storage::list_channelitem,wxT("name"),wxT("type_int"),storage::int_to_str(channelitem::T_PROJ));
	}
	
	return wxT("");
}

wxString groupselectitem::get_s_param(int id)
{
	switch(id)
	{
		case 1:
			return storage::int_to_str(p_id);
		case 2:
			return storage::int_to_str(p_button_id);
		case 3:
			return storage::int_to_str(p_page);
		case 4:
			return p_name;
	}
	
	//View
	if(id >= 5 && ((id % 2) == 1))
	{
		return storage::list_lookup(storage::list_channelitem,wxT("start_channel_int"),storage::int_to_str(group_list[(id-5)/2]),wxT("name"));
	}
	
	//Save
	if(id >= 5 && ((id % 2) == 0))
	{
		return storage::int_to_str(group_list[(id-5)/2]);
	}
	
	return wxT("");
}
	
bool groupselectitem::set_param(int id,wxString value)
{
	//printf("%d %w\n",id,value.c_str());
	switch(id)
	{
		case 1:
			p_id = storage::str_to_int(value);
			return true;
		case 2:
			p_button_id = storage::str_to_int(value);
			return true;
		case 3:
			p_page = storage::str_to_int(value);
			return true;
		case 4:
			p_name = value;
			return true;
	}
	
	//View
	if(id >= 5 && id % 2 == 1)
	{
		wxString str = storage::list_lookup(storage::list_channelitem,wxT("name"),value,wxT("start_channel_int"));

		group_list[(id-5)/2] = storage::str_to_int(str);
		return true;
	}
	
	//Load
	if(id == -1)
	{
		new_group();

		group_list[group_list.size()-1] = storage::str_to_int(value);
		
		return true;
	}

	return false;
}

void groupselectitem::activate(bool down)
{
	if(down) 
	{
		//deactivate all channelitems that are controlled by groupselectitems 
		storage::update_channelitems_active();
	}
	else
	{
		active = true;

		for(unsigned int i = 0; i < group_list.size();i++)
		{
			channelitem* citem = storage::channelitem_for_channel(group_list[i]);
			if(citem)
				citem->activate(true);
		}
	
		storage::update_groupselectitems_active();
	}
}

void groupselectitem::toggle()
{
	active = !active;
	
	for(unsigned int i = 0; i < group_list.size();i++)
	{
		channelitem* citem = storage::channelitem_for_channel(group_list[i]);
		if(citem)
			citem->activate(active);
	}
	
	storage::update_groupselectitems_active();	
}

bool groupselectitem::get_active()
{
	return active;
}

void groupselectitem::update_active(bool act)
{
	if(act)
	{	//called from storage::update_groupselectitems_active to update our state
		for(unsigned int i = 0; i < group_list.size();i++)
		{
			channelitem* citem = storage::channelitem_for_channel(group_list[i]);
			if(citem)
			{
				if(!citem->get_active())
				{
					active = false;
					return;
				}
			}
		}
		active = true;
	}
	else
	{	//called from storage::update_channelitems_active to deactivate all channelitems that are controlled by us
		for(unsigned int i = 0; i < group_list.size();i++)
		{
			channelitem* citem = storage::channelitem_for_channel(group_list[i]);
			if(citem)
			{
				citem->activate(false);
			}
		}
	}
}
