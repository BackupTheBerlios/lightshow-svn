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

#include "valueitem.h"
#include "storage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


DECLARE_STATIC_STC(valueitem)

void new_valueitem(void* param)
{
	valueitem* item = new valueitem((projectorchannelitem*)param);
}

valueitem::valueitem(projectorchannelitem* pcitem) :
	p_parent(pcitem)
{
	p_stor_name = wxT("valueitem");
	
	p_id_map[wxT("name")] = 1;		//wxString
	p_id_map[wxT("value")] = 2;		//int
	
	p_editable_map[1] = true;
	p_editable_map[2] = true;
	
	p_column_width[1] = 200;
	p_column_width[2] = 100;
	
	p_name = wxT("New Value");
	p_value = 0;
	
	p_parent->list_valueitem.push_back(this);
}

valueitem::~valueitem()
{
	p_parent->list_valueitem.remove(this);
}

wxString valueitem::get_s_param(int id)
{
	switch(id)
	{
		case 1:
			return p_name;
		case 2:
			return storage::int_to_str(p_value);
		default:
			return wxT("");
	}
}

bool valueitem::possible_param(int id,wxString value)
{
	if(id == 2)
	{
		int i = storage::str_to_int(value);
		if(i < 0 || i > 255) return false;
	}
	return true;
}

bool valueitem::set_param(int id,wxString value)
{
	if(!possible_param(id,value)) return false;
	switch(id)
	{
		case 1:
			p_name = value;
			return true;
		case 2:
			p_value = storage::str_to_int(value);
			return true;
		default:
			return false;
	}	
}
