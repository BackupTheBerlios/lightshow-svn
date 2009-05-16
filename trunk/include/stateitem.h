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

#ifndef __STATEITEM_HH
#  define __STATEITEM_HH

#include "storage_item.h"
#include "projectoritem.h"

#define MAX_DEV_CHNLS 20

class stateitem : public storage_item
{
public:
	stateitem(projectoritem* pitem,int state);
	stateitem(projectoritem* pitem);
	void init(int state);
	virtual ~stateitem();

	int get_num_params();

	wxString get_s_param(int id);
	
	bool single_select() { return true; };
	bool possible_param(int id,wxString value);
	bool set_param(int id,wxString value);

	enum
	{
		STATE_ON = 0,
		STATE_OFF,
		STATE_HIGHLITE
	};

	unsigned char get_value(int index);
	bool get_mask(int index);

	int get_state() { return p_state; };

private:
	projectoritem* p_parent;
	int p_state;
	unsigned char p_data[MAX_DEV_CHNLS];
	bool p_mask[MAX_DEV_CHNLS];
	
#include "storage_items_common.h"

};

#endif //__STATEITEM_HH
