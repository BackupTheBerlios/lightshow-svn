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

DECLARE_STATIC_STC(configitem)

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
	p_id_map[wxT("page_color")] = 9;
	p_id_map[wxT("function_color")] = 10;
	p_id_map[wxT("function_otherpage_color")] = 11;
	p_id_map[wxT("function_pb_color")] = 12;
	p_id_map[wxT("function_pb_otherpage_color")] = 13;
	p_id_map[wxT("group_color")] = 14;
	p_id_map[wxT("fade_color")] = 15;
	p_id_map[wxT("fader_button_color")] = 16;
	p_id_map[wxT("fader_active_color")] = 17;
	p_id_map[wxT("led_on_color")] = 18;
	p_id_map[wxT("led_off_color")] = 19;
	p_id_map[wxT("border_color")] = 20;
	p_id_map[wxT("border_highlite_color")] = 21;
	p_id_map[wxT("background_color")] = 22;
	p_id_map[wxT("text_color")] = 23;
	p_id_map[wxT("text_fader_color")] = 24;
	p_id_map[wxT("text_font_size")] = 25;
	p_id_map[wxT("rounds_size")] = 26;
	
	
	p_draw_scale = 1.0;
	p_button_height = 55;
	p_button_width = 55;
	p_fader_height = 205;
	p_fader_width = 55;
	p_fader_button_height = 55;
	p_translucent_buttons = false;
	p_translucent_fader = true;
	p_font_size = 10;
	p_rounds_size = 5;
	
	unsigned char color[16][3] = {	{149,207,99}, {98,147,147}, {98,147,147},
									{103,204,204}, {103,204,204}, {98,150,98},
									{201,207,98}, {150,156,46}, {100,154,101},
									{255,0,0}, {100,0,0}, {150,150,150},
									{200,200,200}, {0,0,0}, {0,0,0},
									{0,0,0} };

	for(int i = 0; i < 16; i++)
		for(int j = 0; j < 3; j++)
			p_color[i][j] = color[i][j];
}

configitem::~configitem()
{
}

wxString configitem::get_s_param(int id)
{
	if(id > 8 && id < 25)
		return storage::rgb_to_str(p_color[id-9]);
	
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
		case 25:
			return storage::int_to_str(p_font_size);
		case 26:
			return storage::int_to_str(p_rounds_size);
		default:
			return wxT("");
	}
}

bool configitem::set_param(int id,wxString value)
{
	if(id > 8 && id < 25)
		return storage::str_to_rgb(value,p_color[id-9]);
	
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
		case 25:
			p_font_size = storage::str_to_int(value);
			return true;
		case 26:
			p_rounds_size = storage::str_to_int(value);
			return true;
		default:
			return false;
	}	
}
