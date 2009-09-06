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

#include "groupitem.h"
#include "storage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


DECLARE_STATIC_STC(groupitem)

void new_groupitem(void* param)
{
	groupitem* item = new groupitem();
}

groupitem::groupitem()
{
	p_stor_name = wxT("groupitem");
	
	p_id_map[wxT("id")] = 1;
	p_id_map[wxT("name")] = 2;
	
	p_dont_show_map[1] = true;

	p_editable_map[2] = true;
	
	p_column_width[2] = 300;
	
	p_id = get_max_id(storage::list_groupitem,wxT("id")) + 1;
	p_name = wxT("New Group");
	
	if(p_id < MAX_GROUPS)//Not good, memory leak if above MAX_GROUPS
		storage::list_groupitem.push_back(this);
}

groupitem::~groupitem()
{
	storage::list_groupitem.remove(this);
}

void groupitem::delete_deps()
{
	//TODO alles groupige löschen + alle ids herabsetzen ? 
}

wxString groupitem::get_s_param(int id)
{
	switch(id)
	{
		case 1:
			return storage::int_to_str(p_id);
		case 2:
			return p_name;
		default:
			return wxT("");
	}
}
	
bool groupitem::set_param(int id,wxString value)
{
	switch(id)
	{
		case 1:
			p_id = storage::str_to_int(value);
			return true;
		case 2:
			p_name = value;
			return true;
		default:
			return false;
	}
}
