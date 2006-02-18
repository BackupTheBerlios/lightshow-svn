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

#ifndef __FUCTIONITEM_HH
#  define __FUCTIONITEM_HH

#include "storage_item.h"
#include "storage.h"
#include "prec.h"

//Speed to Steps: BPM : 60 : 40 = steps per 25ms

class dataitem;

class functionitem : public storage_item
{
	friend class dataitem;
	
public:
	functionitem();
	functionitem(int button_id, int page);
	void init(int button_id, int page);
	virtual ~functionitem();
	void save(wxFile& file);
	void load(wxFile& file);

	void delete_deps();

	wxString get_param_map(int id);

	wxString get_s_param(int id);
	inline wxString get_s_param(wxString id) { return storage_item::get_s_param(id); };
	
	bool set_param(int id,wxString value);

	bool get_switching() { return p_switching; };
	bool get_overlay() { return p_overlay; };
	wxString get_name() { return p_name; };
	wxString get_name2() { return p_name2; };
	int get_page() { return p_page; };
	int get_button_id() { return p_button_id; };
	int get_speed_group() { return p_speed_group; };
	int get_id() { return p_id; };

	//connection types
	enum
	{
		T_STRAIGHT = 1,
		T_FASTSTRAIGHT,
		T_POINTS,
		T_CIRCLE
	};

	storageitemlist list_dataitem;

	void activate(bool hard = false);
	void deactivate(bool hard = false);
	bool get_active();
	void set_speed(int new_speed);
	
	void run(int what);
	void do_step(double new_step = -1);
	
	void enable_preview(int step);
	void disable_preview();
	
	void update_mask(bool* mask,bool overlay,bool switching);
	void get_active_mask(bool* mask);

	int get_num_rows();
	unsigned char get_value(int row, double step);
	dataitem* get_dataitem(int index);
	
	void copy_to(deskitem* ditem, int page);
	void move_to(deskitem* ditem, int page);

	void update_spline();

private:
	unsigned char interpolate(int channel, int step, double pos);
	void stage();

	bool active;
	int speed;
	bool own_speed_fader;
	bool mask[DMX_CHNLS];
	bool active_mask[DMX_CHNLS];
	double active_timer;

	typedef vector<double> vdt;
	map<int,vdt> spline_a;
	map<int,vdt> spline_b;
	map<int,vdt> spline_c;
	map<int,vdt> spline_d;

	double step;
	int preview_step;

private:
	int p_id;

	int p_button_id;
	int p_page;

	wxString p_name;
	wxString p_name2;
	int p_connection_type;	
	bool p_switching;
	bool p_overlay;

	double p_timebase;
	double p_timer;
	bool p_stage_orientated;
	bool p_pos_changeable;
	
	int p_speed_group;

	simap map_bool;
	simap map_connection_type;
};

#endif //__FUCTIONITEM_HH
