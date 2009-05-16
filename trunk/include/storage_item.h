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

#ifndef __STORAGE_ITEM_HH
#  define __STORAGE_ITEM_HH

#include "prec.h"

typedef map<wxString,int> simap;
typedef map<int,bool> ibmap;
typedef map<int,int> iimap;

//for storage::list_xyz
class storage_item;
typedef list<storage_item*> storageitemlist;

class storage_item
{
public:
	storage_item();
	virtual ~storage_item();

	virtual void save(wxFile& file);
	void save_main(wxFile& file);
	void save_end(wxFile& file);
	virtual void load(wxFile& file);
	wxString load_main(wxFile& file);

	virtual void delete_deps() {};
		
	virtual bool is_less(storage_item& b);

	virtual wxString get_param_name(int id);
	int get_param_id(wxString id);
	virtual int get_num_params() { return gp_id_map()->size()-gp_dont_show_map()->size(); };
	virtual int get_num_all_params() { return gp_id_map()->size(); };
	int real_id_for_virtual_id(int id);
	int real_id_for_virtual_id(wxString id) { return real_id_for_virtual_id(get_param_id(id)); };
	
	virtual bool should_show(unsigned int id);
	bool should_show(wxString id) { return should_show(get_param_id(id)); };
	virtual bool can_edit(int id);
	bool can_edit(wxString id) { return can_edit(get_param_id(id)); };

	virtual bool should_save() { return true; };
	virtual bool should_save(int id);
	bool should_save(wxString id) { return should_save(get_param_id(id)); };
	
	int get_column_width(int id);
	int get_column_width(wxString id) { return get_column_width(get_param_id(id)); };
	void set_column_width(int id, int width);
	virtual void delete_param(int id) { };
	virtual bool single_select() { return false; };
//	virtual bool can_drag_drop() { return false; };
//	virtual bool can_copy_paste() { return false; };

	virtual wxString get_s_param(int id) = 0;
	wxString get_s_param(wxString id) { return get_s_param(get_param_id(id)); };
	int get_i_param(int id);
	int get_i_param(wxString id) { return get_i_param(get_param_id(id)); };
	bool get_b_param(int id);
	bool get_b_param(wxString id) { return get_b_param(get_param_id(id)); };
	double get_d_param(int id);
	double get_d_param(wxString id) { return get_d_param(get_param_id(id)); };

	virtual wxString get_param_map(int id) { return wxT(""); };
	wxString get_param_map(wxString id) { return get_param_map(get_param_id(id)); };

	static wxString param_map_lookup(simap* smap,int search);
	static wxString param_map_to_string(simap* smap);
	static int get_max_id(storageitemlist& slist,wxString param);
	static int get_max_button_id();

	virtual bool set_param(int id,wxString value) = 0;
	bool set_param(wxString id,wxString value) { return set_param(get_param_id(id),value); };
	bool set_param(int id,int value);
	bool set_param(wxString id,int value) { return set_param(get_param_id(id),value); };
	bool set_param(int id,bool value);
	bool set_param(wxString id,bool value) { return set_param(get_param_id(id),value); };
	bool set_param(int id,double value);
	bool set_param(wxString id,double value) { return set_param(get_param_id(id),value); };

public:
	virtual wxString* gp_stor_name() = 0;
	virtual simap* gp_id_map() = 0;
	virtual ibmap* gp_dont_show_map() = 0;
	virtual ibmap* gp_editable_map() = 0;
	virtual ibmap* gp_dont_save_map() = 0;
	virtual iimap* gp_column_width() = 0;

};

struct storage_item_sort
{
	bool operator()(storage_item* x, storage_item* y) const
	{ 
		return y->is_less(*x);
	}
};

#endif // __STORAGE_ITEM_HH
