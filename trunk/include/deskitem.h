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

#ifndef __DESKITEM_HH
#  define __DESKITEM_HH

#include "storage_item.h"

class deskitem : public storage_item
{
public:
	deskitem();
	deskitem(int type);
	void init(int type);
	virtual ~deskitem();

	void delete_deps();

	wxString get_s_param(int id);
	
	bool set_param(int id,wxString value);

	int get_fader_id() { return p_fader_id; };
	int get_button_id() { return p_button_id; };
	int get_type() { return p_type; };
	int get_page_id() { return p_page_id; };
	int get_pos_x() { return p_pos_x; };
	int get_pos_y() { return p_pos_y; };
	void set_pos_x(int x) { p_pos_x = x; };
	void set_pos_y(int y) { p_pos_y = y; };
	int get_id();
	void set_id(int id);


	//deskitem types
	enum
	{
		T_GROUP = 1,
		T_PAGE,
		T_FUNCTION,
		T_FADER
	};

	int pos; // if we are a fader

private:
	int p_type;
	int p_pos_x;
	int p_pos_y;
	int p_button_id;
	int p_fader_id;
	int p_page_id;
	
#include "storage_items_common.h"

};

#endif //__DESKITEM_HH
