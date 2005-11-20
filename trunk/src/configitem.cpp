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

#include "configitem.h"
#include "storage.h"

configitem::configitem()
{
	p_stor_name = wxT("configitem");

	p_id_map[wxT("draw_scale")] = 1;
	p_id_map[wxT("button_width")] = 2;
	p_id_map[wxT("button_height")] = 3;
	p_id_map[wxT("fader_width")] = 4;
	p_id_map[wxT("fader_height")] = 5;
	p_id_map[wxT("fader_button_height")] = 6;
	p_id_map[wxT("translucent_buttons")] = 7;
	p_id_map[wxT("translucent_fader")] = 8;
	
	p_draw_scale = 1.0;
	p_button_height = 55;
	p_button_width = 55;
	p_fader_height = 205;
	p_fader_width = 55;
	p_fader_button_height = 55;
	p_translucent_buttons = false;
	p_translucent_fader = true;
}

configitem::~configitem()
{
}

wxString configitem::get_s_param(int id)
{
	switch(id)
	{
		case 1:
			return storage::double_to_str(p_draw_scale);
		case 2:
			return storage::int_to_str(p_button_width);
		case 3:
			return storage::int_to_str(p_button_height);
		case 4:
			return storage::int_to_str(p_fader_width);
		case 5:
			return storage::int_to_str(p_fader_height);
		case 6:
			return storage::int_to_str(p_fader_button_height);
		case 7:
			return storage::bool_to_str(p_translucent_buttons);
		case 8:
			return storage::bool_to_str(p_translucent_fader);
		default:
			return wxT("");
	}
}

bool configitem::set_param(int id,wxString value)
{
	switch(id)
	{
		case 1:
			p_draw_scale = storage::str_to_double(value);
			return true;
		case 2:
			p_button_width = storage::str_to_int(value);
			return true;
		case 3:
			p_button_height = storage::str_to_int(value);
			return true;
		case 4:
			p_fader_width = storage::str_to_int(value);
			return true;
		case 5:
			p_fader_height = storage::str_to_int(value);
			return true;
		case 6:
			p_fader_button_height = storage::str_to_int(value);
			return true;
		case 7:
			p_translucent_buttons = storage::str_to_bool(value);
			return true;
		case 8:
			p_translucent_fader = storage::str_to_bool(value);
			return true;
		default:
			return false;
	}	
}
