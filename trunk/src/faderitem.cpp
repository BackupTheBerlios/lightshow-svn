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


#include "functionitem.h"
#include "faderitem.h"
#include "storage.h"

faderitem::faderitem()
{
	init(-1,-1);
}

faderitem::faderitem(int fader_id,int page)
{
	init(fader_id,page);
}

void faderitem::init(int fader_id,int page)
{
	p_stor_name = wxT("faderitem");

	p_id_map[wxT("fader_id")] = 1;
	p_id_map[wxT("page")] = 2;
	p_id_map[wxT("name")] = 3;
	p_id_map[wxT("name2")] = 4;
	p_id_map[wxT("type")] = 5;
	p_id_map[wxT("group")] = 6;
	p_id_map[wxT("function")] = 7;
	p_id_map[wxT("type_int")] = 8;
	p_id_map[wxT("group_int")] = 9;
	p_id_map[wxT("function_int")] = 10;
	p_id_map[wxT("own_function")] = 11;
	
	p_dont_show_map[1] = true;
	p_dont_show_map[2] = true;
	p_dont_show_map[8] = true;
	p_dont_show_map[9] = true;
	p_dont_show_map[10] = true;
	p_dont_show_map[11] = true;
	
	p_dont_save_map[5] = true;
	p_dont_save_map[6] = true;
	p_dont_save_map[7] = true;
	
	p_editable_map[3] = true;
	p_editable_map[4] = true;
	p_editable_map[5] = true;
	p_editable_map[6] = true;
	p_editable_map[7] = true;
	
	map_type[wxT("Master for Group")] = T_MASTER | T_GROUP;
	map_type[wxT("Master for Function")] = T_MASTER | T_FUNCTION;
	map_type[wxT("Speed for Group")] = T_SPEED | T_GROUP;
	map_type[wxT("Speed for Function")] = T_SPEED | T_FUNCTION;
	map_type[wxT("Fade for Function")] = T_FADE | T_FUNCTION;
	map_type[wxT("XFade for Group")] = T_XFADE | T_GROUP;
	map_type[wxT("XFade for Function")] = T_XFADE | T_FUNCTION;
	map_type[wxT("Global Scene XFade")] = T_XFADE;
	
	wxString p_name = wxT("");
	wxString p_name2 = wxT("");
	p_type = T_MASTER | T_GROUP;

	p_fader_id = fader_id;
	p_page = page;
	
	p_group = -1;
	p_function = -1;

	p_own_function = false;

	//ACTIVE
	active_pos = 0;
	prev_pos = 0;
	flash = false;
	tab_count = 0;
	tab_pos = 0;
	active_tab = false;
	active_zero = false;

	storage::list_faderitem.push_back(this);
}

faderitem::~faderitem()
{
	storage::list_faderitem.remove(this);
}

void faderitem::delete_deps()
{
}

wxString faderitem::get_param_map(int id)
{
	switch(id)
	{
		case 5:
			return param_map_to_string(&map_type);
		case 6:
			if(p_type & T_GROUP)
				return storage::list_to_string(storage::list_groupitem,wxT("name"));
			else
				return wxT("");
		case 7:
			if(p_type & T_FUNCTION)
				return storage::list_to_string(storage::list_functionitem,wxT("name"));
			else
				return wxT("");
	}
	
	return wxT("");
}

wxString faderitem::get_s_param(int id)
{
	switch(id)
	{
		case 1:
			return storage::int_to_str(p_fader_id);
		case 2:
			return storage::int_to_str(p_page);
		case 3:
			return p_name;
		case 4:
			return p_name2;
		case 5:
			return param_map_lookup(&map_type,p_type);
		case 6:
			if(p_type & T_GROUP)
				return storage::list_lookup(storage::list_groupitem,wxT("id"),storage::int_to_str(p_group),wxT("name"));
			else
				return wxT("");
		case 7:
			if(p_type & T_FUNCTION)
				return storage::list_lookup(storage::list_functionitem,wxT("id"),storage::int_to_str(p_function),wxT("name"));
			else
				return wxT("");
		case 8:
			return storage::int_to_str(p_type);
		case 9:
			return storage::int_to_str(p_group);
		case 10:
			return storage::int_to_str(p_function);
		case 11:
			return storage::bool_to_str(p_own_function);
		default:
			return wxT("");
	}
}

bool faderitem::set_param(int id,wxString value)
{
	int t;
	wxString str;
	switch(id)
	{
		case 1:
			p_fader_id = storage::str_to_int(value);
			return true;
		case 2:
			p_page = storage::str_to_int(value);
			return true;
		case 3:
			p_name = value;
			return true;
		case 4:
			p_name2 = value;
			return true;
		case 5:
			t = map_type[value];
			if(t != 0)
			{
				p_type = map_type[value];
				return true;
			}
			return false;
		case 6:
			str = storage::list_lookup(storage::list_groupitem,wxT("name"),value,wxT("id"));
			if(str != wxT(""))
			{
				p_group = storage::str_to_int(str);
				return true;
			}
			return false;
		case 7:
			str = storage::list_lookup(storage::list_functionitem,wxT("name"),value,wxT("id"));
			if(str != wxT(""))
			{
				p_function = storage::str_to_int(str);
				return true;
			}
			return false;
		case 8:
			p_type = storage::str_to_int(value);
			return true;
		case 9:
			p_group = storage::str_to_int(value);
			return true;
		case 10:
			p_function = storage::str_to_int(value);
			return true;
		case 11:
			p_own_function = storage::str_to_bool(value);
			return true;
		default:
			return false;
	}	
}

void faderitem::copy_to(deskitem* ditem, int page)
{
	faderitem* nfitem = new faderitem(ditem->get_fader_id(), page);
	
	//copy config, but not fader_id,page
	for(int i = 3;i <= get_num_all_params();i++)
	{
		if(should_save(i))
			if(get_s_param(i) != wxT(""))
				nfitem->storage_item::set_param(get_param_name(i), get_s_param(i));
	}
}

void faderitem::move_to(deskitem* ditem, int page)
{
	p_page = page;
	p_fader_id = ditem->get_fader_id();
}

void faderitem::changed()
{
	functionitem* fitem = storage::functionitem_for_id(p_function);

	//TODO own function
	//function (de)activate
	if(((p_type & T_FUNCTION) || (p_type & T_FADE)))
	{
		if(fitem != NULL)
		{
			if(active_pos > 5)
				fitem->activate(true);
			else
				fitem->deactivate(true);
		}
	}

	//SingleFunction Fade
	if(p_type & T_FADE)
	{
		if(fitem != NULL)
		{
			fitem->set_speed(0);
			fitem->do_step(1-active_pos/255.0);
		}
	}

	//SpeedFader
	if(p_type & T_SPEED)
	{
		int speed = active_pos;
		if(speed < 5) speed = 0;

		if(p_type & T_FUNCTION)
		{
			if(fitem != NULL)
				fitem->set_speed(speed);
		}
		else if(p_type & T_GROUP)
		{
			storageitemlist::iterator it;
			for(it = storage::list_functionitem.begin();it != storage::list_functionitem.end();it++)
			{
				fitem = (functionitem*)*it;
				if(fitem->get_speed_group() == p_group)
				{
					fitem->set_speed(speed);
				}	
			}
		}
	}

	//XFader
	if(p_type & T_XFADE)
	{
		bool mask[DMX_CHNLS];
		int i;
		for(i = 0;i < DMX_CHNLS;i++)
			mask[i] = false;

		if(p_type & T_FUNCTION)
		{
			functionitem* fitem;
			fitem = storage::functionitem_for_id(p_function);
			
			if(fitem != NULL)
				fitem->get_active_mask(mask);
		}
		else if(p_type & T_GROUP)
		{
			for(int i = 0;i < DMX_CHNLS;i++)
			mask[i] = false;

			storageitemlist::iterator it;
			for(it = storage::list_channelitem.begin();it != storage::list_channelitem.end();it++)
			{
				channelitem* citem = (channelitem*)*it;
				if(citem->get_group() == p_group)
				{
					citem->get_mask(mask);
				}	
			}
		}

		for(i = 0;i < DMX_CHNLS;i++)
		{
			if(mask[i])
			{
				storage::xfade[i] = active_pos;
			}
		}

	}
}

void faderitem::tab()
{
	if((p_type & T_MASTER) || (p_type & T_FADE))
	{
		if(!active_tab)
		{
			prev_pos = active_pos;
			set_active_pos(255);
			active_tab = true;
		}
	}
	else if(p_type & T_SPEED)
	{
		wxLongLong now = ::wxGetLocalTimeMillis();
		wxLongLong diff = now - last_tab;
		long time = diff.GetLo();


		if(active_pos < 5)	//Single Step
		{
			functionitem* fitem;
			if(p_type & T_FUNCTION)
			{
				fitem = storage::functionitem_for_id(p_function);
				
				if(fitem != NULL)
					fitem->do_step();
			}
			else if(p_type & T_GROUP)
			{
				storageitemlist::iterator it;
				for(it = storage::list_functionitem.begin();it != storage::list_functionitem.end();it++)
				{
					fitem = (functionitem*)*it;
					if(fitem->get_speed_group() == p_group)
					{
						fitem->do_step();
					}	
				}
			}
		}
		else //Tab Sync
		{
			if(time > 240)
			{
				if(time < 2000)
				{
					tab_count++;
					tab_pos++;

					if(tab_count > 10) tab_count = 10;
					if(tab_pos > 10) tab_pos = 0;

					tab_list[tab_pos-1] = 60000/time;

					int speed = 0;
					for(int i = 0;i < tab_count;i++)
						speed += tab_list[i];

					speed /= tab_count;

					prev_pos = speed;
					set_active_pos(speed);
				}
				else
				{
					tab_count = 0;
					tab_pos = 0;
				}
			}
		}
	
		last_tab = now;
	}
}

void faderitem::tab_release()
{
	if(!((p_type & T_MASTER) || (p_type & T_FADE))) return;

	//Prevent ugly happenings
	if(active_tab && active_pos == 255)
		set_active_pos(prev_pos);

	active_tab = false;
}

void faderitem::off_toggle()
{
	if(!active_zero)
	{
		prev_pos = active_pos;
		set_active_pos(0);
	}
	else
	{
		set_active_pos(prev_pos);
	}
	active_zero = !active_zero;		
}

void faderitem::set_active_pos(int pos)
{
	if(active_pos == pos) return;
	active_pos = pos;
	changed();
}

int faderitem::get_active_pos()
{
	return active_pos;
}

void faderitem::run(int what)
{
	//MasterFader
	if(!(p_type & T_MASTER)) return;

	bool mask[DMX_CHNLS];
	int i;
	for(i = 0;i < DMX_CHNLS;i++)
		mask[i] = false;

	if(p_type & T_FUNCTION && what == R_PB_OV)
	{
		functionitem* fitem;
		fitem = storage::functionitem_for_id(p_function);
		
		if(fitem != NULL)
		{
			if(fitem->get_active())
				fitem->get_active_mask(mask);
		}
	}
	else if(p_type & T_GROUP && (what == R_SW_OV || what == R_ON))
	{
		storageitemlist::iterator it;
		for(it = storage::list_channelitem.begin();it != storage::list_channelitem.end();it++)
		{
			channelitem* citem = (channelitem*)*it;

			if(citem->get_group() == p_group)
			{
				if(citem->get_type() == channelitem::T_PROJ)
				{
					//Projectors need special master fader handling
					projectoritem* pitem = storage::projectoritem_for_channelitem(citem);
					if(pitem)
						pitem->run(citem->get_start_channel(),active_pos, what);
				}
				else if(what == R_SW_OV)
				{
					//TODO filter functions with own master fader
					//Or the mask with channels belonging to the group
					citem->get_mask(mask);
				}
			}
		}
	}

	double fakt = active_pos / 255.0;
	for(i = 0;i < DMX_CHNLS;i++)
	{
		if(mask[i])
		{
			storage::DMX[i] *= fakt;
		}
	}
}
