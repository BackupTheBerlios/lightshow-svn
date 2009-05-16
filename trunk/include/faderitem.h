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

#ifndef __FADERITEM_HH
#  define __FADERITEM_HH

#include "storage_item.h"
#include "functionitem.h"

class faderitem : public storage_item
{
public:
	faderitem();
	faderitem(int fader_id,int page);
	void init(int fader_id,int page);
	virtual ~faderitem();

	void delete_deps();
	void move_to(deskitem* fitem, int page);
	void copy_to(deskitem* fitem, int page);

	wxString get_param_map(int id);

	wxString get_s_param(int id);
	inline wxString get_s_param(wxString id) { return storage_item::get_s_param(id); }; 

	bool set_param(int id,wxString value);

	wxString get_name() { return p_name; };
	wxString get_name2() { return p_name2; };
	int get_type() { return p_type; };
	int get_page() { return p_page; };
	int get_fader_id() { return p_fader_id; };

	//deskitem types
	enum
	{
		T_MASTER = 1,
		T_SPEED = 2,
		T_FADE = 4,
		T_XFADE = 8,
		T_GROUP = 16,
		T_FUNCTION = 32
	};
	
	void changed();
	void tab();
	void tab_release();
	void off_toggle();
	void run(int what);
	int get_active_pos();
	void set_active_pos(int pos);
	
private:
	simap map_type;

	int active_pos;	
	bool active_tab;
	bool active_zero;
	int prev_pos;
	bool flash;
	wxLongLong last_tab;
	int tab_list[10];
	int tab_count;
	int tab_pos;

private:
	int p_fader_id;
	int p_page;

	wxString p_name;
	wxString p_name2;
	int p_type;

	int p_group;
	int p_function;
	bool p_own_function;
	
#include "storage_items_common.h"

};

#endif //__FADERITEM_HH
