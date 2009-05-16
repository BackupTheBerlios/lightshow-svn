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

#ifndef __PROJECTORITEM_HH
#  define __PROJECTORITEM_HH

#include "storage_item.h"

class projectoritem : public storage_item
{
public:
	projectoritem();
	virtual ~projectoritem();
	void save(wxFile& file);
	void load(wxFile& file);

	void delete_deps();

	wxString get_s_param(int id);
	inline wxString get_s_param(wxString id) { return storage_item::get_s_param(id); };
	
	bool set_param(int id,wxString value);

	int get_num_channels() { return list_projectorchannelitem.size(); };
	wxString get_name() { return p_name; };

	void run(int start_channel, int pos, int what);
	void highlite(int start_channel);

	storageitemlist list_stateitem;
	storageitemlist list_projectorchannelitem;
private:
	wxString p_name;
	
#include "storage_items_common.h"

};

void new_projectoritem(void* param);

#endif //__PROJECTORITEM_HH
