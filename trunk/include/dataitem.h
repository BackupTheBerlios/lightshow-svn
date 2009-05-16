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

#ifndef __DATAITEM_HH
#  define __DATAITEM_HH

#include "storage_item.h"
#include "functionitem.h"
#include "storage.h"

class functionitem;

class dataitem : public storage_item
{
public:
	dataitem(functionitem* parent);
	virtual ~dataitem();

	bool single_select() { return true; };
	bool can_copy_paste() { return true; };
	bool can_new() { return true; };
	bool can_delete() { return true; };

	void delete_deps();
	
	wxString get_s_param(int id);
	
	wxString get_param_name(int id);
	wxString get_param_map(int id);
	
	bool set_param(int id,wxString value);
	
	unsigned char get_value(int index);
	void set_value(int index, unsigned char value);
	bool step(int index);

private:
	functionitem* p_parent;
	unsigned char p_data[DMX_CHNLS];
	bool p_step[DMX_CHNLS];
	
#include "storage_items_common.h"

};

void new_dataitem(void* param);

#endif //__DATAITEM_HH
