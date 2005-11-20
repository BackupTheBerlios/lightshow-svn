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

#ifndef __VALUEITEM_HH
#  define __VALUEITEM_HH

#include "storage_item.h"
#include "projectorchannelitem.h"

class valueitem : public storage_item
{
public:
	valueitem(projectorchannelitem* pcitem);
	virtual ~valueitem();

	wxString get_s_param(int id);
	
	bool possible_param(int id,wxString value);
	bool set_param(int id,wxString value);

private:
	projectorchannelitem* p_parent;
	wxString p_name;
	int p_value;
};

void new_valueitem(void* param);

#endif //__VALUEITEM_HH
