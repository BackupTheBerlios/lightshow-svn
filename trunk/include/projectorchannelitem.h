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

#ifndef __PROJECTORCHANNELITEM_HH
#  define __PROJECTORCHANNELITEM_HH

#include "storage_item.h"
#include "projectoritem.h"

class projectorchannelitem : public storage_item
{
public:
	projectorchannelitem(projectoritem* parent);
	virtual ~projectorchannelitem();
	void save(wxFile& file);
	void load(wxFile& file);
	void delete_deps();

	bool is_less(storage_item& b);

	wxString get_s_param(int id);
	inline wxString get_s_param(wxString id) { return storage_item::get_s_param(id); };

	bool set_param(int id,wxString value);

	int get_type() { return p_type; };
	int get_channel() { return p_channel; };
	bool set_channel(int channel) { p_channel = channel; return true; };
	wxString get_name() { return p_name; };


	wxString get_param_map(int id);

	bool change_channel(unsigned int new_channel);

	enum
	{
		T_PAN = 1,
		T_TILT,
		T_CONTINOUS,
		T_VALUE
	};

	storageitemlist list_valueitem;
private:
	int p_channel;
	wxString p_name;
	int p_type;

	simap map_type;
	projectoritem* p_parent;
	
#include "storage_items_common.h"

};

void new_projectorchannelitem(void* param);

#endif //__PROJECTORCHANNELITEM_HH
