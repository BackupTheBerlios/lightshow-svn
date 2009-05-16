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

#ifndef __GROUPSELECTITEM_HH
#  define __GROUPSELECTITEM_HH

#include "storage_item.h"
#include <vector>

class groupselectitem : public storage_item
{
public:
	groupselectitem();
	groupselectitem(int button_id, int page);
	void init(int button_id, int page);
	virtual ~groupselectitem();
		
	bool should_show(unsigned int id);
	bool can_edit(int id);
	bool should_save(int id);
	wxString get_param_name(int id);
	int get_num_params();
	int get_num_all_params();
	
	wxString get_param_map(int id);
	wxString get_s_param(int id);
	inline wxString get_s_param(wxString id) { return storage_item::get_s_param(id); }; 

	bool set_param(int id,wxString value);

	int get_page() { return p_page; };
	int get_button_id() { return p_button_id; };
	wxString get_name() { return p_name; };
	
	void new_group();
	void delete_param(int id);
	
	vector<int> group_list;
	
	void activate(bool down = true);
	void toggle();
	bool get_active();
	
	void update_active(bool act = true);
	
private:
	bool active;
	int p_id;
	int p_button_id;
	int p_page;
	wxString p_name;
	
#include "storage_items_common.h"

};

void new_group_in_groupselectitem(void* param);

#endif //__GROUPSELECTITEM_HH
