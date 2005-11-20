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

#include "channelitem.h"
#include "storage.h"

simap channelitem::map_type;

void new_channelitem(void* param)
{
	channelitem* item = new channelitem();
}

channelitem::channelitem()
{
	init(-1);
}

channelitem::channelitem(int start_channel)
{
	init(start_channel);
}

void channelitem::init(int start_channel)
{
	p_stor_name = wxT("channelitem");
	
	p_id_map[wxT("start_channel")] = 1;
	p_id_map[wxT("name")] = 2;
	p_id_map[wxT("type")] = 3;
	p_id_map[wxT("group")] = 4;
	p_id_map[wxT("proj_type")] = 5;
	p_id_map[wxT("top_left_x")] = 6;
	p_id_map[wxT("top_left_y")] = 7;
	p_id_map[wxT("bottom_left_x")] = 8;
	p_id_map[wxT("bottom_left_y")] = 9;
	p_id_map[wxT("top_right_x")] = 10;
	p_id_map[wxT("top_right_y")] = 11;
	p_id_map[wxT("bottom_right_x")] = 12;
	p_id_map[wxT("bottom_right_y")] = 13;
	p_id_map[wxT("start_channel_int")] = 14;
	p_id_map[wxT("type_int")] = 15;
	p_id_map[wxT("group_int")] = 16;
	p_id_map[wxT("num_channels")] = 17;
	p_id_map[wxT("proj_type_int")] = 18;
	
	p_dont_show_map[6] = true;
	p_dont_show_map[7] = true;
	p_dont_show_map[8] = true;
	p_dont_show_map[9] = true;
	p_dont_show_map[10] = true;
	p_dont_show_map[11] = true;
	p_dont_show_map[12] = true;
	p_dont_show_map[13] = true;
	p_dont_show_map[14] = true;
	p_dont_show_map[15] = true;
	p_dont_show_map[16] = true;
	p_dont_show_map[17] = true;
	p_dont_show_map[18] = true;
				
	p_dont_save_map[1] = true;
	p_dont_save_map[3] = true;
	p_dont_save_map[4] = true;
	p_dont_save_map[5] = true;
	p_dont_save_map[17] = true;
	
	p_editable_map[1] = true;
	p_editable_map[2] = true;
	p_editable_map[3] = true;
	p_editable_map[4] = true;
	p_editable_map[5] = true;
	
	p_column_width[1] = 100;
	p_column_width[2] = 200;
	p_column_width[3] = 150;
	p_column_width[4] = 150;
	p_column_width[5] = 150;
	
	
	map_type[wxT("Konventional")] = T_KONV;
	map_type[wxT("Miscellaneous")] = T_MISC;
	map_type[wxT("Projector")] = T_PROJ;
	
	p_name = wxT("New Channelitem");
	p_type = T_KONV;
	p_proj_type = wxT("");
	p_group = -1;
	
	p_top_left[0] = 0;
	p_top_left[1] = 0;
	p_bottom_left[0] = 255;
	p_bottom_left[1] = 0;
	p_top_right[0] = 0;
	p_top_right[1] = 255;
	p_bottom_right[0] = 255;
	p_bottom_right[1] = 255;

	p_invert_pan = false;
	p_invert_tilt = false;
	
	p_start_channel = get_next_free_channel();
	
	active = true;

	//do not store if not engou free channels
	//TODO howto delete us?
	if(p_start_channel != -1)
		storage::list_channelitem.push_back(this);
}

channelitem::~channelitem()
{
	storage::list_channelitem.remove(this);
}

void channelitem::delete_deps()
{
	//TODO alles wie immer
}

wxString channelitem::get_param_map(int id)
{
	switch(id)
	{
		case 3:
			return param_map_to_string(&map_type);
		case 4:
			return storage::list_to_string(storage::list_groupitem,wxT("name"));
		case 5:
			if(p_type != T_PROJ) return wxT("");
			return storage::list_to_string(storage::list_projectoritem,wxT("name"));
		default:
			return wxT("");				
	}
}

wxString channelitem::get_s_param(int id)
{
	switch(id)
	{
	case 1:
		return storage::int_to_str(p_start_channel);
	case 2:
		return p_name;
	case 3:
		return param_map_lookup(&map_type,p_type);
	case 4:
		return storage::list_lookup(storage::list_groupitem, wxT("id"), storage::int_to_str(p_group), wxT("name"));
	case 5:
		if(p_type == T_PROJ)
			return p_proj_type;
		else 
			return wxT("");
	case 6:
		return storage::int_to_str(p_top_left[0]);
	case 7:
		return storage::int_to_str(p_top_left[1]);
	case 8:
		return storage::int_to_str(p_bottom_left[0]);
	case 9:
		return storage::int_to_str(p_bottom_left[1]);
	case 10:
		return storage::int_to_str(p_top_right[0]);
	case 11:
		return storage::int_to_str(p_top_right[1]);
	case 12:
		return storage::int_to_str(p_bottom_right[0]);
	case 13:
		return storage::int_to_str(p_bottom_right[1]);
	case 14:
		return storage::int_to_str(p_start_channel);
	case 15:
		return storage::int_to_str(p_type);
	case 16:
		return storage::int_to_str(p_group);
	case 17:
		return storage::int_to_str(get_num_channels());
	case 18:
		return p_proj_type;
	}
	
	return wxT("");
}
	
bool channelitem::set_param(int id,wxString value)
{
	int t;
	wxString str;
	
	switch(id)
	{
	case 1:
		t = storage::str_to_int(value);
		if(is_channel_free(t,get_num_channels()))
		{
			p_start_channel = t;
			return true;
		}
		else return false;
	case 2:
		p_name = value;
		return true;
	case 3:
		t = map_type[value];
		if(t == 0) return false;
		
		if(t == T_PROJ)
		{
			p_proj_type = wxT("");
		}

		p_type = t;
		return true;
	case 4:
		str = storage::list_lookup(storage::list_groupitem,wxT("name"),value,wxT("id"));
		if(str != wxT(""))
		{
			p_group = storage::str_to_int(str);
			return true;
		}
		return false;
	case 5:
		{
			if(p_type != T_PROJ) return false;
			wxString str_num = storage::list_lookup(storage::list_projectoritem, wxT("name"), value, wxT("num_channels"));
			int num = storage::str_to_int(str_num);
			if(is_channel_free(p_start_channel,num,this))
			{
				p_proj_type = value;
				return true;
			}
		}
		return false;
	case 6:
		p_top_left[0] = storage::str_to_int(value);
		return true;
	case 7:
		p_top_left[1] = storage::str_to_int(value);
		return true;
	case 8:
		p_bottom_left[0] = storage::str_to_int(value);
		return true;
	case 9:
		p_bottom_left[1] = storage::str_to_int(value);
		return true;
	case 10:
		p_top_right[0] = storage::str_to_int(value);
		return true;
	case 11:
		p_top_right[1] = storage::str_to_int(value);
		return true;
	case 12:
		p_bottom_right[0] = storage::str_to_int(value);
		return true;
	case 13:
		p_bottom_right[1] = storage::str_to_int(value);
		return true;
	case 14:
		p_start_channel = storage::str_to_int(value);
		return true;
	case 15:
		p_type = storage::str_to_int(value);
		return true;
	case 16:
		p_group = storage::str_to_int(value);
		return true;
	//case 17: // ReadOnly
	case 18:
		p_proj_type = value;
	default:
		return false;		
	}
}

int channelitem::get_num_channels()
{
	if(p_type != T_PROJ) return 1;

	if(p_proj_type == wxT("")) return 1;
	
	wxString str = storage::list_lookup(storage::list_projectoritem, wxT("name"),
										p_proj_type, wxT("num_channels"));
	return storage::str_to_int(str);
}

/*static*/ bool channelitem::is_channel_free(int start, int num,channelitem* me)
{
	storageitemlist::iterator it;
	for(it = storage::list_channelitem.begin();it != storage::list_channelitem.end();it++)
	{
		if(*it == me) continue;

		int it_start = (*it)->get_i_param(wxT("start_channel"));
		int it_num = (*it)->get_i_param(wxT("num_channels"));
		
		bool before = (start+num-1 < it_start);
		bool after = (start > it_start+it_num-1);
		
		//printf("%d %d %d %d b:%d a:%d\n",start,num,it_start,it_num,before,after);
		
		if(!before && !after) return false;
	}
	
	return true;
}

/*static*/ int channelitem::get_next_free_channel()
{
	for(int i = 1;i <= DMX_CHNLS;i++)
		if(is_channel_free(i)) return i;
			
	wxLogError(wxT("Not enough free channels!"));
			   
	return -1;
}

void channelitem::activate(bool act)
{
	active = act;
}

bool channelitem::get_active()
{
	return active;
}

void channelitem::get_mask(bool* mask)
{
	for(int i = p_start_channel;i < p_start_channel+get_num_channels();i++)
		mask[i-1] = true;
}

void channelitem::mask(bool* mask)
{
	//reset mask if we aren't active
	if(active) return;
	
	for(int i = p_start_channel;i < p_start_channel+get_num_channels();i++)
		mask[i-1] = false;
}
