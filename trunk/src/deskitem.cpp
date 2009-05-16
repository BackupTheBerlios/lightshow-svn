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

#include "deskitem.h"
#include "storage.h"

DECLARE_STATIC_STC(deskitem)

deskitem::deskitem()
{
	init(T_FUNCTION);
}

deskitem::deskitem(int type)
{
	init(type);
}

void deskitem::init(int type)
{
	p_stor_name = wxT("deskitem");

	p_id_map[wxT("pos_x")] = 1;
	p_id_map[wxT("pos_y")] = 2;
	p_id_map[wxT("id")] = 3;
	p_id_map[wxT("type_int")] = 4;
	p_id_map[wxT("button_id_int")] = 5;
	p_id_map[wxT("fader_id_int")] = 6;
	p_id_map[wxT("page_id_int")] = 7;
	
	p_dont_save_map[3] = true;
	
	p_type = type;
	
	p_pos_x = 0;
	p_pos_y = 0;
	
	p_fader_id = 0;
	p_button_id = 0;
	p_page_id = 0;
	
	switch(type)
	{
	case T_FADER:
		p_fader_id = get_max_id(storage::list_deskitem,wxT("fader_id_int")) + 1;
		break;
	case T_PAGE:
		p_page_id = get_max_id(storage::list_deskitem,wxT("page_id_int")) + 1;		
	case T_FUNCTION:
	case T_GROUP:
		p_button_id = get_max_id(storage::list_deskitem,wxT("button_id_int")) + 1;
		break;
	}
	
	pos = 0;
	
	storage::list_deskitem.push_back(this);
}

deskitem::~deskitem()
{
	storage::list_deskitem.remove(this);
}

void deskitem::delete_deps()
{
	// wenn page löschen auch alles durchgehen
	//TODO function bzw faderitems durchgehen und evtl löschen
	// grouplist richtig löschen
}

wxString deskitem::get_s_param(int id)
{
	switch(id)
	{
		case 1:
			return storage::int_to_str(p_pos_x);
		case 2:
			return storage::int_to_str(p_pos_y);
		case 3:
			return storage::int_to_str(get_id());	
		case 4:
			return storage::int_to_str(p_type);
		case 5:
			return storage::int_to_str(p_button_id);
		case 6:
			return storage::int_to_str(p_fader_id);
		case 7:
			return storage::int_to_str(p_page_id);
	}

	return wxT("");
}

bool deskitem::set_param(int id,wxString value)
{
	switch(id)
	{
		case 1:
			p_pos_x = storage::str_to_int(value);
			return true;
		case 2:
			p_pos_y = storage::str_to_int(value);
			return true;
		case 3: //TODO assure unique ids
			set_id(storage::str_to_int(value));
			return true;
		case 4:
			p_type = storage::str_to_int(value);
			return true;
		case 5:
			p_button_id = storage::str_to_int(value);
			return true;
		case 6:
			p_fader_id = storage::str_to_int(value);
			return true;
		case 7:
			p_page_id = storage::str_to_int(value);
			return true;
		default:
			return false;
	}	
}

int deskitem::get_id()
{
	return p_type == T_FADER ? p_fader_id : p_button_id; 
}

void deskitem::set_id(int id)
{
	//TODO assure unique ids
	switch(p_type)
	{
	case T_FADER:
		p_fader_id = id;
	case T_GROUP:
	case T_PAGE:
	case T_FUNCTION:
		p_button_id = id;
	}
}
