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

#ifndef __CHANNELITEM_HH
#  define __CHANNELITEM_HH

#include "storage_item.h"

class channelitem : public storage_item
{
public:
	channelitem();
	channelitem(int start_channel);
	void init(int start_channel);
	virtual ~channelitem();

	void delete_deps();
	wxString get_param_map(int id);

	wxString get_s_param(int id);
	inline wxString get_s_param(wxString id) { return storage_item::get_s_param(id); };

	bool set_param(int id,wxString value);

	int get_start_channel() { return p_start_channel; };
	int get_group() { return p_group; };
	int get_type() { return p_type; };
	wxString get_name() { return p_name; };
	wxString get_proj_type() { return p_proj_type; };

	int get_num_channels();

private:
	static int get_next_free_channel();
	static bool is_channel_free(int start, int num = 1,channelitem* me = NULL);

	static simap map_type;

public:
	enum
	{
		T_KONV = 1,
		T_MISC,
		T_PROJ
	};

	void get_mask(bool* mask);
	void mask(bool* mask);
	
	void activate(bool act = true);	
	bool get_active();
	
private:
	bool active;
	int p_start_channel;
	wxString p_name;
	int p_type;
	int p_group;
	wxString p_proj_type;
	
	int p_top_left[2];
	int p_bottom_left[2];
	int p_top_right[2];
	int p_bottom_right[2];

	bool p_invert_pan;
	bool p_invert_tilt;
};

void new_channelitem(void* param);


#endif //__CHANNELITEM_HH
