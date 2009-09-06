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

#include "dataitem.h"
#include "functionitem.h"
#include "storage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


DECLARE_STATIC_STC(functionitem)

functionitem::functionitem()
{
	init(-1,-1);
}

functionitem::functionitem(int button_id, int page)
{
	init(button_id,page);
}

void functionitem::init(int button_id, int page)
{
	p_stor_name = wxT("functionitem");
	
	p_id_map[wxT("id")] = 1;
	p_id_map[wxT("button_id")] = 2;
	p_id_map[wxT("page")] = 3;
	p_id_map[wxT("name")] = 4;
	p_id_map[wxT("name2")] = 5;
	p_id_map[wxT("connection_type")] = 6;
	p_id_map[wxT("switching")] = 7;
	p_id_map[wxT("overlay")] = 8;
	p_id_map[wxT("timebase")] = 9;
	p_id_map[wxT("timer")] = 10;
	p_id_map[wxT("stage_orientated")] = 11;
	p_id_map[wxT("pos_changeable")] = 12;
	p_id_map[wxT("speed_group")] = 13;
	p_id_map[wxT("connection_type_int")] = 14;
	p_id_map[wxT("switching_int")] = 15;
	p_id_map[wxT("overlay_int")] = 16;
	p_id_map[wxT("stage_orientated_int")] = 17;
	p_id_map[wxT("pos_changeable_int")] = 18;
	p_id_map[wxT("speed_group_int")] = 19;
	
	p_dont_show_map[1] = true;
	p_dont_show_map[2] = true;
	p_dont_show_map[3] = true;
	p_dont_show_map[14] = true;
	p_dont_show_map[15] = true;
	p_dont_show_map[16] = true;
	p_dont_show_map[17] = true;
	p_dont_show_map[18] = true;
	p_dont_show_map[19] = true;
	
	
	p_dont_save_map[6] = true;
	p_dont_save_map[7] = true;
	p_dont_save_map[8] = true;
	p_dont_save_map[11] = true;
	p_dont_save_map[12] = true;
	p_dont_save_map[13] = true;
	
	p_id = get_max_id(storage::list_functionitem,wxT("id")) + 1;
	
	p_page = page;
	p_button_id = button_id;

	p_name = wxT("");
	p_name2 = wxT("");
	p_connection_type = T_STRAIGHT;	
	p_switching = true;
	p_overlay = false;
	p_stage_orientated = false;
	p_pos_changeable = false;
	
	p_timebase = 1;
	p_timer = 0;
	
	p_speed_group = -1;
	
	map_connection_type[wxT("Straight")] = T_STRAIGHT;
	map_connection_type[wxT("Fast Straight")] = T_FASTSTRAIGHT;
	map_connection_type[wxT("Points")] = T_POINTS;
	map_connection_type[wxT("Circle")] = T_CIRCLE;
	
	map_bool[wxT("true")] = true;
	map_bool[wxT("false")] = false;
	
	own_speed_fader = false;
	active = false;
	active_timer = 0;
	for(int i = 0; i < DMX_CHNLS; i++)
	{
		mask[i] = false;
		active_mask[i] = false;
	}
	
	speed = (int)(60/SPEED_MULTIPLICATOR);
	step = 0;
	preview_step = -1;
	
	storage::list_functionitem.push_back(this);
}

functionitem::~functionitem()
{
	while(!list_dataitem.empty()) 
		delete *list_dataitem.begin();
	
	storage::list_functionitem.remove(this);
}

void functionitem::save(wxFile& file)
{
	storage_item::save_main(file);
	storage::save(file, list_dataitem);
	storage_item::save_end(file);
}

void functionitem::load(wxFile& file)
{
	wxString parm = storage_item::load_main(file);
	while(parm != wxT(""))
	{
		if(parm == wxT("dataitem"))
		{
			dataitem* item = new dataitem(this);
			item->load(file);
		}

		parm = storage_item::load_main(file);
	}

	update_spline();
}

void functionitem::copy_to(deskitem* ditem, int page)
{
	functionitem* fitem = new functionitem(ditem->get_button_id(), page);
	
	//copy config, but not id,button_id,page
	for(int i = 4;i <= get_num_all_params();i++)
	{
		if(should_save(i))
			if(get_s_param(i) != wxT(""))
				fitem->storage_item::set_param(get_param_name(i), get_s_param(i));
	}
	
	storageitemlist::iterator it;
	for(it = list_dataitem.begin();it != list_dataitem.end();it++)
	{
		dataitem*  ditem = new dataitem(fitem);
		
		for(int i = 1;i <= (*it)->get_num_all_params();i++)
		{
			if((*it)->should_save(i))
				if((*it)->get_s_param(i) != wxT(""))
					ditem->storage_item::set_param((*it)->get_param_name(i), (*it)->get_s_param(i));
		}
	}
}

void functionitem::move_to(deskitem* ditem, int page)
{
	p_page = page;
	p_button_id = ditem->get_button_id();
}

void functionitem::delete_deps()
{
	//TODO faderitems durchgehen und evtl löschen
}

wxString functionitem::get_param_map(int id)
{
	switch(id)
	{
	case 6:
		return param_map_to_string(&map_connection_type);
	case 7:
	case 8:
	case 11:
	case 12:
		return param_map_to_string(&map_bool);
	case 13:
		return storage::list_to_string(storage::list_groupitem,wxT("name"));
	default:
		return wxT("");
	}
}

wxString functionitem::get_s_param(int id)
{
	switch(id)
	{
		case 1:
			return storage::int_to_str(p_id);
		case 2:
			return storage::int_to_str(p_button_id);
		case 3:
			return storage::int_to_str(p_page);
		case 4:
			return p_name;
		case 5:
			return p_name2;
		case 6:
			return param_map_lookup(&map_connection_type,p_connection_type);
		case 7:
			return param_map_lookup(&map_bool,p_switching);
		case 8:
			return param_map_lookup(&map_bool,p_overlay);
		case 9:
			return storage::double_to_str(p_timebase);
		case 10:
			return storage::double_to_str(p_timer);
		case 11:
			return param_map_lookup(&map_bool,p_stage_orientated);
		case 12:
			return param_map_lookup(&map_bool,p_pos_changeable);
		case 13:
			return storage::list_lookup(storage::list_groupitem,wxT("id"),storage::int_to_str(p_speed_group),wxT("name"));
		case 14:
			return storage::int_to_str(p_connection_type);
		case 15:
			return storage::bool_to_str(p_switching);
		case 16:
			return storage::bool_to_str(p_overlay);
		case 17:
			return storage::bool_to_str(p_stage_orientated);
		case 18:
			return storage::bool_to_str(p_pos_changeable);
		case 19:
			return storage::int_to_str(p_speed_group);
		default:
			return wxT("");
	}
}

bool functionitem::set_param(int id,wxString value)
{
	int t;
	wxString str;
	
	switch(id)
	{
		case 1:
			p_id = storage::str_to_int(value);
			return true;
		case 2:
			p_button_id = storage::str_to_int(value);
			return true;
		case 3:
			p_page = storage::str_to_int(value);
			return true;
		case 4:
			p_name = value;
			return true;
		case 5:
			p_name2 = value;
			return true;
		case 6:
			t = map_connection_type[value];
			if(t != 0)
			{
				p_connection_type = t;
				update_spline();
				return true;
			}
			else return false;
		case 7:
			p_switching = (map_bool[value]!=0);
			return true;
		case 8:
			p_overlay = (map_bool[value]!=0);
			return true;
		case 9:
			p_timebase = storage::str_to_double(value);
			return true;
		case 10:
			p_timer = storage::str_to_double(value);
			return true;
		case 11:
			p_stage_orientated = (map_bool[value]!=0);
			return true;
		case 12:
			p_pos_changeable = (map_bool[value]!=0);
			return true;
		case 13:
			str = storage::list_lookup(storage::list_groupitem,wxT("name"),value,wxT("id"));
			if(str != wxT(""))
			{
				p_speed_group = storage::str_to_int(str);
				return true;
			}
		case 14:
			p_connection_type = storage::str_to_int(value);
			return true;
		case 15:
			p_switching = storage::str_to_bool(value);
			return true;
		case 16:
			p_overlay = storage::str_to_bool(value);
			return true;
		case 17:
			p_stage_orientated = storage::str_to_bool(value);
			return true;
		case 18:
			p_pos_changeable = storage::str_to_bool(value);
			return true;
		case 19:
			p_speed_group = storage::str_to_int(value);
			return true;
		default:
			return false;
	}	
}

void functionitem::activate(bool hard)
{
	//Determine if we should activate or reactivate the function
	if(!active || hard)
	{
		active = true;
		step = 0;
	}
	else
	{
		if(p_overlay)
			active = false;
		else if(p_switching)
		{
			bool doit = true;
			bool all_mask[DMX_CHNLS];
			
			int i;
			for(i = 0;i < DMX_CHNLS;i++)
				all_mask[i] = mask[i];
			
			//Use Only Active Projectors
			storage::group_filter(all_mask);
			
			for(i = 0;i < DMX_CHNLS;i++)
			{
				if(all_mask[i] != active_mask[i])
				{
					doit = false;
					break;
				}
			}
			
			if(doit) active = false;
		}
	}

	//if it is deactivated go home
	if(!active) return;
	
	bool update_mask[DMX_CHNLS];

	int i;
	for(i = 0;i < DMX_CHNLS;i++)
		active_mask[i] = mask[i];
	
	//Use Only Active Projectors
	storage::group_filter(active_mask);

	for(i = 0;i < DMX_CHNLS;i++)
		update_mask[i] = active_mask[i];
	
	//Konv. Channels use HTP (highest, not latest value)
	storage::konventional_filter(update_mask);

	//Update Masks For All Functions execpt this
	storage::update_function_masks(update_mask,this);
}

void functionitem::deactivate(bool hard)
{
	if(hard)
		active = false;
	else if(!p_switching)
		active = false;
}

bool functionitem::get_active()
{
	return active;
}

void functionitem::get_active_mask(bool* mask)
{
	for(int i = 0;i < DMX_CHNLS;i++)
		mask[i] = active_mask[i];
}

void functionitem::set_speed(int new_speed)
{
	speed = new_speed;
}

void functionitem::update_mask(bool* mask,bool overlay,bool switching)
{
	if(!active) return;
	if(p_overlay != overlay) return;
	if(p_switching != switching) return;
		
	bool act = false;
	for(int i = 0;i < DMX_CHNLS;i++)
	{
		active_mask[i] = active_mask[i] && !mask[i];

		if(active_mask[i]) act = true;
	}
	
	if(!act) active = false;
}

void functionitem::do_step(double new_step)
{
	if(new_step < 0) //SingleStep
		step = (int)(step + 1);
	else
		step = new_step;
}

unsigned char functionitem::get_value(int channel, double step)
{
	unsigned char value = 0;
	
	if(!mask[channel]) return value;

	unsigned int ai = (int)step;
	unsigned int bi = (int)step + 1;
	if(bi > list_dataitem.size()-1) bi = 0;
	
	dataitem* d1 = get_dataitem(ai);
	dataitem* d2 = get_dataitem(bi);
	
	double pos = step - ai;
	
	unsigned char a = d1->get_value(channel);
	unsigned char b = d2->get_value(channel);

	if(d2->step(channel))
		value = a;
	else
	{
		switch(p_connection_type)
		{
		case T_STRAIGHT:
			value = (unsigned char)(a-(pos*a)+(pos*b));
			break;
		case T_FASTSTRAIGHT:
			if(pos < 0.3) value = a;
			else if(pos > 0.7) value = b;
			else value = (unsigned char)(a-(((pos-0.3)/0.4)*a)+(((pos-0.3)/0.4)*b));
			break;
		case T_POINTS:
			if(storage::xfade[channel] != 0)
			{
				double pos2 = 255.0/storage::xfade[channel] * ( pos - 1.0 ) + 1;
				if(pos2 < 0) pos2 = 0;
				value = (unsigned char)(a-(pos2*a)+(pos2*b));
			}
			else
			{
				value = a;
			}
			break;
		case T_CIRCLE:
			value = interpolate(channel, ai, pos);
			break;
		}
	}
	
	return value;
}


void functionitem::run(int what)
{
	if(what == R_PREVIEW)
	{
		if(preview_step >= (int)list_dataitem.size())
			preview_step = -1;

		if(preview_step == -1) return;

		storage::highlite(mask);
		
		for(int i = 0;i < DMX_CHNLS;i++)
		{	
			if(!mask[i]) continue;
			
			storage::DMX[i] = get_value(i,preview_step);
		}		
				
		if(p_stage_orientated)
			stage();
		return;
	}

	if(what == R_ON) return;	
	
	if(!active) return;
	
	if((what == R_SW_OV || what == R_PB_OV))
	{
		if(!p_overlay) return;
	}
	else if(p_overlay) return;
		
	if((what == R_PB || what == R_PB_OV))
	{
		if(p_switching) return;
	}
	else if(!p_switching) return;
		
	//Calculate Next Step Nr.
	if(p_timer != 0)
	{
		step += (120/2400.0)*p_timebase;
		if(step >= list_dataitem.size()-1)
		{
			step = list_dataitem.size()-1; //Use last Step
			
			if(active_timer > p_timer) //Just Started
				active_timer = 0;

			active_timer += speed/(2400.0/SPEED_MULTIPLICATOR);
			
			if(active_timer > p_timer) //Timer is elapsed
				step = 0;
		}
	}
	else
	{
		step += (speed/(2400.0/SPEED_MULTIPLICATOR))*p_timebase;
		if(step >= list_dataitem.size())
			step = 0;
	}
	
	for(int i = 0;i < DMX_CHNLS;i++)
	{
		if(!active_mask[i]) continue;

		unsigned char value = get_value(i,step);
		
		if(p_overlay) storage::DMX[i] = value;
		else storage::DMX[i] = (storage::DMX[i] < value) ? value : storage::DMX[i];
	}
	
	if(p_stage_orientated)
		stage();
}

unsigned char functionitem::interpolate(int channel, int step, double pos)
{
	int v = (int)(spline_a[channel][step+1]*pos*pos*pos + spline_b[channel][step+1]*pos*pos + spline_c[channel][step+1]*pos + spline_d[channel][step+1]);
	
	if( v < 0) v = 0;
	else if(v > 255) v = 255;

	return v;
}

void functionitem::update_spline()
{
	if(p_connection_type != T_CIRCLE)
		return;

	int l = list_dataitem.size();
	int n = l + 2;
	
	vector<double> e;
	vector<double> u;
	vector<double> r;
	vector<double> k;

	e.resize(n+1);
	u.resize(n+1);
	r.resize(n+1);
	k.resize(n+1);

	double k_i_plus_1;

	for(int channel = 0;channel < DMX_CHNLS;channel++)
	{
		//only for used channels
		if(!mask[channel]) continue;

		//	l = count
		//	l-1,0,..,l-1,0,1
		//  n = count + 2
		//  0,1,..,n-2,n-1,n

		//  l = 0, 0, 0, 0
		//  n = 0, 1, 2, 3
		
		int i;
		for(i = 0;i < n;i++)
		{
			// first
			int j = i - 1;
			if(j == -1) j = l-1;
			if(j > l-1) j = j - l;
			if(j > l-1) j = l-1;

			//next
			int k = i;
			if(k > l-1) k = k - l;
			if(k > l-1) k = l-1;

			e[i] = 6.0*(get_dataitem(k)->get_value(channel)-get_dataitem(j)->get_value(channel));
		}
		
		u[0] = 4.0;
		r[0] = e[1] - e[0];
		
		for(i = 1;i < n-1;i++)
		{
			u[i] = 4.0 - 1.0/u[i-1];
			r[i] = (e[i+1]-e[i])-r[i-1]/u[i-1];
		}
		
		k[n] = 0;
		for(i = n-1;i > 0;i--)
		{
			k[i] = (r[i-1]-k[i+1])/u[i-1];
		}
		k[0] = 0;

		spline_d[channel].resize(n+1);
		spline_c[channel].resize(n+1);
		spline_b[channel].resize(n+1);
		spline_a[channel].resize(n+1);
		
		for(i = 0;i <= n;i++)
		{
			// first
			int j = i - 1;
			if(j == -1) j = l-1;
			if(j > l-1) j = j - l; 
			if(j > l-1) j = l-1;

			//next
			int m = i;
			if(m > l-1) m = m - l;
			if(m > l-1) m = l-1;

			if(i < n)
				k_i_plus_1 = k[i+1];
			else
				k_i_plus_1 = k[0];

			spline_d[channel][i] = get_dataitem(j)->get_value(channel);
			spline_c[channel][i] = (get_dataitem(m)->get_value(channel)-get_dataitem(j)->get_value(channel))-(2.0*k[i]+k_i_plus_1)/6.0;
			spline_b[channel][i] = k[i]/2.0;
			spline_a[channel][i] = (k_i_plus_1-k[i])/6.0;
		}
	}
}

void functionitem::stage()
{
	//TODO stage
}

dataitem* functionitem::get_dataitem(int index)
{
	storageitemlist::iterator it = list_dataitem.begin();
	
	for(int i = 0;i < index;i++)
		if(it != list_dataitem.end())
			it++;
		else 
			it--;
	
	return (dataitem*)*it;	
}

int functionitem::get_num_rows()
{
	return list_dataitem.size();
}

void functionitem::enable_preview(int step)
{
	if(step < (int)list_dataitem.size()) 
		preview_step = step;
}

void functionitem::disable_preview()
{
	preview_step = -1;
}
