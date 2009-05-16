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

#ifndef __GROUPITEM_HH
#  define __GROUPITEM_HH

#include "storage_item.h"

class groupitem : public storage_item
{
public:
	groupitem();
	virtual ~groupitem();

	void delete_deps();

	wxString get_s_param(int id);
	
	bool set_param(int id,wxString value);

private:
	int p_id;
	wxString p_name;
	
#include "storage_items_common.h"

};

void new_groupitem(void* param);

#endif //__GROUPITEM_HH
