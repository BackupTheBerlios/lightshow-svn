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

#include "storage_item.h"
#include "storage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

storage_item::storage_item()
{
}

storage_item::~storage_item()
{
}

bool storage_item::is_less(storage_item &b)
{ 
	return false;
}

void storage_item::load(wxFile& file)
{
	wxString parm = load_main(file);
	if(parm != wxT(""))
	{
		wxString msg = wxT("Ignored ") + parm + wxT(" while loading ") + *gp_stor_name() + wxT(".");
		wxLogVerbose(msg);
	}
}

wxString storage_item::load_main(wxFile& file)
{
	wxString param,value;
	int stat = storage::load_parse(file,param,value);
	while(stat == LOADPARSE_VALUE)
	{
		set_param(param,value);
		stat = storage::load_parse(file,param,value);
	}
	if(stat == LOADPARSE_START)
		return param;
	else
		return wxT("");
}

void storage_item::save(wxFile& file)
{
	if(should_save())
	{
		save_main(file);
		save_end(file);
	}
}

void storage_item::save_main(wxFile& file)
{
	file.Write(wxT("<") + *gp_stor_name() + wxT(">\n"));
	
	for(int i = 1;i <= get_num_all_params();i++)
	{
		if(should_save(i))
			if(get_s_param(i) != wxT(""))
				file.Write(wxT("\t<") + get_param_name(i) + wxT(">") + get_s_param(i) + wxT("</") + get_param_name(i) + wxT(">\n"));
	}
}

void storage_item::save_end(wxFile& file)
{
	file.Write(wxT("</") + *gp_stor_name() + wxT(">\n"));
}

wxString storage_item::param_map_lookup(simap* smap,int search)
{
	simap::iterator it;
	for(it = smap->begin();it != smap->end();it++)
		if(it->second == search) return it->first;

	return wxT("");
}

wxString storage_item::param_map_to_string(simap* smap)
{
	wxString str = wxT("");
	
	simap::iterator it;
	for(it = smap->begin();it != smap->end();it++)
	{
		if(it != smap->begin()) str += wxT(",");
		str += it->first;
	}
	return str;
}

int storage_item::get_max_id(storageitemlist& slist,wxString param)
{
	int i = 0;
	storageitemlist::iterator it;
	for(it = slist.begin();it != slist.end();it++)
	{
		if((*it)->get_i_param(param) > i) i = (*it)->get_i_param(param);
	}
	return i;
}

wxString storage_item::get_param_name(int id)
{
	return param_map_lookup(gp_id_map(),id);
}

int storage_item::get_param_id(wxString id)
{
	simap::iterator it = gp_id_map()->find(id);
	if( it != gp_id_map()->end() )
		return it->second;
	else
		return -1;
}

bool storage_item::can_edit(int id)
{
	ibmap::iterator it = gp_editable_map()->find(id);
	if( it != gp_editable_map()->end() )
		return it->second;
	else
		return false;
}

bool storage_item::should_save(int id)
{
	ibmap::iterator it = gp_dont_save_map()->find(id);
	if( it != gp_dont_save_map()->end() )
		return !(it->second);
	else
		return true;
}

bool storage_item::should_show(unsigned int id)
{
	//even not in id map
//	if(param_map_lookup(&p_id_map,id) == wxT("")) return false;
	if(id > gp_id_map()->size()) return false;
	
	//should it be shown
	ibmap::iterator it = gp_dont_show_map()->find(id);
	if( it != gp_dont_show_map()->end() )
		return !(it->second);
	else
		return true;
}

int storage_item::real_id_for_virtual_id(int id)
{
	id++;
	int i = 0;
		
	do
	{
		i++;
		if(i == get_num_all_params()) break;
		if(should_show(i))
			id--;
	} while (id != 0);
	
	return i;
}

int storage_item::get_column_width(int id)
{
	iimap::iterator it = gp_column_width()->find(id);
	if(it != gp_column_width()->end())
		return it->second;
	else
		return 50;
}

void storage_item::set_column_width(int id, int width)
{
	(*gp_column_width())[id] = width;
}

//-----------------------------------------------------------------------------------------------

bool storage_item::set_param(int id,int value)
{
	return set_param(id,storage::int_to_str(value));
}

bool storage_item::set_param(int id,bool value)
{
	return set_param(id,storage::bool_to_str(value));
}

bool storage_item::set_param(int id,double value)
{
	return set_param(id,storage::double_to_str(value));
}

int storage_item::get_i_param(int id)
{
	return storage::str_to_int(get_s_param(id));
}

bool storage_item::get_b_param(int id)
{
	return storage::str_to_bool(get_s_param(id));
}

double storage_item::get_d_param(int id)
{
	return storage::str_to_double(get_s_param(id));
}
