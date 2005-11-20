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

#include "stateitem.h"
#include "storage.h"

stateitem::stateitem(projectoritem* pitem,int state) :
p_parent(pitem)
{
	init(state);
}

stateitem::stateitem(projectoritem* pitem) :
p_parent(pitem)
{
	init(-1);
}

void stateitem::init(int state)
{
	p_stor_name = wxT("stateitem");
	
	p_id_map[wxT("state")] = 1;
	p_id_map[wxT("state_int")] = MAX_DEV_CHNLS+2;
	
	p_dont_show_map[MAX_DEV_CHNLS+2] = true;
	
	p_dont_save_map[1] = true;
	
	p_editable_map[1] = false;
	p_editable_map[MAX_DEV_CHNLS+2] = false;
	
	p_column_width[1] = 80;

	for(int i = 0; i < MAX_DEV_CHNLS;i++)
	{
		wxString name = wxT("chn ");
		name += storage::int_to_str(i+1);
		
		p_data[i] = 0;
		p_mask[i] = false;
		
		p_id_map[name] = 2+i;		//int
		p_editable_map[2+i] = true;
	}
	
	p_state = state;

	p_parent->list_stateitem.push_back(this);
}

stateitem::~stateitem()
{
	p_parent->list_stateitem.remove(this);
}

int stateitem::get_num_params()
{
	return p_parent->get_num_channels()+1;
}

wxString stateitem::get_s_param(int id)
{
	if(id == 1)
	{
		switch(p_state)
		{
			case STATE_ON:
				return wxT("ON");
			case STATE_OFF:
				return wxT("OFF");
			case STATE_HIGHLITE:
				return wxT("HIGHLITE");
			default:
				return wxT("");
		}
	}
	else if(id == MAX_DEV_CHNLS+2)
	{
		return storage::int_to_str(p_state);
	}
	else if(id < MAX_DEV_CHNLS+2)
	{
		if(p_mask[id - 2])
			return storage::int_to_str(p_data[id - 2]);
		else
			return wxT("");
	}

	return wxT("");
}

bool stateitem::possible_param(int id,wxString value)
{
	if(id > 1 && id < MAX_DEV_CHNLS+2)
	{
		int i = storage::str_to_int(value);
	
		if(i < -1 || i > 255) return false;		
	}
	
	return true;
}

bool stateitem::set_param(int id,wxString value)
{
	if(id == MAX_DEV_CHNLS+2)
	{
		p_state = storage::str_to_int(value);
		return true;
	}
	
	if(!possible_param(id,value)) return false;
		
	if(id > 1 && id < MAX_DEV_CHNLS+2)
	{
		int i = storage::str_to_int(value);
		if(i == -1)
		{
			p_mask[id - 2] = false;
			p_data[id - 2] = 0;
		}
		else
		{
			p_mask[id - 2] = true;
			p_data[id - 2] = i;
		}	
		return true;
	}
	
	return false;
}

unsigned char stateitem::get_value(int index)
{
	if(index < 0 || index > MAX_DEV_CHNLS-1) return 0;

	return p_data[index];
}

bool stateitem::get_mask(int index)
{
	if(index < 0 || index > MAX_DEV_CHNLS-1) return false;

	return p_mask[index];
}
