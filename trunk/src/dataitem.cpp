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
#include "storage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

DECLARE_STATIC_STC(dataitem)

void new_dataitem(void* param)
{
	dataitem* item = new dataitem((functionitem*)param);
}

dataitem::dataitem(functionitem* parent) :
p_parent(parent)
{
	p_stor_name = wxT("dataitem");
	
	dataitem* prev = NULL;
	if(!p_parent->list_dataitem.empty())
	{
		prev = (dataitem*)p_parent->list_dataitem.back();
	}
	
	for(int i = 0;i < DMX_CHNLS;i++)
	{
		//1...DMX_CHNLS : View
		p_id_map[storage::int_to_str(i+1)] = i+1;
		p_editable_map[i+1] = true;
		p_dont_save_map[i+1] = true;
		
		//DMX_CHNLS+1...2*DMX_CHNLS : Save
		p_id_map[storage::int_to_str(i+1) + wxT("_int")] = i+DMX_CHNLS+1;
		p_dont_show_map[i+DMX_CHNLS+1] = true;
		
		if(prev)
		{
			p_step[i] = prev->step(i);
			p_data[i] = prev->get_value(i);
		}
		else
		{
			p_step[i] = false;
			p_data[i] = 0;
		}
	}

	p_parent->list_dataitem.push_back(this);
}

dataitem::~dataitem()
{
	p_parent->list_dataitem.remove(this);
}

void dataitem::delete_deps()
{
	//TODO halt
}

wxString dataitem::get_param_map(int id)
{
	channelitem* citem = storage::channelitem_for_channel(id);
	if(citem)
	{
		projectoritem* pitem = storage::projectoritem_for_channelitem(citem);
		if(pitem)
		{
			int subchannel = id - citem->get_start_channel() + 1;
			projectorchannelitem* pcitem = storage::projectorchannelitem_for_subchannel(pitem,subchannel);
			if(pcitem)
			{
				if(pcitem->get_type() == projectorchannelitem::T_VALUE)
				{
					return storage::list_to_string(pcitem->list_valueitem,wxT("name"));
				}
			}
		}
	}	
	return wxT("");
}

wxString dataitem::get_param_name(int id)
{
	if(id > DMX_CHNLS) return storage_item::get_param_name(id);

	return storage::channel_name(id);	
}

wxString dataitem::get_s_param(int id)
{
	if(id < 1 || id > 2*DMX_CHNLS) return wxT("");
		
	//Save
	if(id > DMX_CHNLS)
		if(p_parent->mask[id-DMX_CHNLS-1])
		{
			if(!p_step[id-DMX_CHNLS-1])
				return storage::int_to_str(p_data[id-DMX_CHNLS-1]);
			else
				return storage::int_to_str(-p_data[id-DMX_CHNLS-1]);
		}
		else return wxT("");
		
	//View
	if(!p_parent->mask[id-1]) return wxT("");

	wxString str;

	if(!p_step[id-1])
		str = wxT("");
	else
		str = wxT("-");
		
	channelitem* citem = storage::channelitem_for_channel(id);
	if(citem)
	{
		projectoritem* pitem = storage::projectoritem_for_channelitem(citem);
		if(pitem)
		{
			int subchannel = id - citem->get_start_channel() + 1;
			projectorchannelitem* pcitem = storage::projectorchannelitem_for_subchannel(pitem,subchannel);
			if(pcitem)
			{
				if(pcitem->get_type() == projectorchannelitem::T_VALUE)
				{
					wxString str2 = storage::list_lookup(pcitem->list_valueitem,wxT("value"),storage::int_to_str(p_data[id-1]),wxT("name"));
					if(str2 != wxT(""))
					{
						str += str2;
						return str;
					}
				}
			}
		}
	}	
		
	str += storage::int_to_str(p_data[id-1]);
	return str;
}
	
bool dataitem::set_param(int id,wxString value)
{
	if(id < 1 || id > 2*DMX_CHNLS) return false;

	//Values starting with a '-' have special meaning
	bool step = false;
	if(value.StartsWith(wxT("-"),&value)) //removes the '-' if it exists
		step = true;
		
	int val = storage::str_to_int(value);
	
	//Load
	if(id > DMX_CHNLS)
	{
		if(val == -1)
		{
			p_data[id-DMX_CHNLS-1] = 0;
		}
		else
		{
			p_data[id-DMX_CHNLS-1] = val;
			p_step[id-DMX_CHNLS-1] = step;
			p_parent->mask[id-DMX_CHNLS-1] = true;
		}
		return true;
	}
	
	//View
	//Empty
	if(value == wxT(""))
	{
		p_parent->mask[id-1] = false;
		return true;
	}
	
	//Valid Number
	if(val != -1)
	{
		set_value(id-1,val);
		p_step[id-1] = step;
		return true;
	}

	channelitem* citem = storage::channelitem_for_channel(id);
	if(citem)
	{
		projectoritem* pitem = storage::projectoritem_for_channelitem(citem);
		if(pitem)
		{
			int subchannel = id - citem->get_start_channel() + 1;
			projectorchannelitem* pcitem = storage::projectorchannelitem_for_subchannel(pitem,subchannel);
			if(pcitem)
			{
				if(pcitem->get_type() == projectorchannelitem::T_VALUE)
				{
					wxString str = storage::list_lookup(pcitem->list_valueitem,wxT("name"),value,wxT("value"));
					if(str != wxT(""))
					{
						set_value(id-1,storage::str_to_int(str));
						p_step[id-1] = step;
						return true;
					}
				}
			}
		}
	}		
	return false;
}

unsigned char dataitem::get_value(int index)
{
	if(index >= DMX_CHNLS || index < 0) return 0;
	
	return p_data[index];
}

void dataitem::set_value(int index, unsigned char value)
{
	if(index >= DMX_CHNLS || index < 0) return;
	
	p_data[index] = value;
	p_parent->mask[index] = true;
	p_parent->update_spline();
}


bool dataitem::step(int index)
{
	if(index >= DMX_CHNLS || index < 0) return false;

	return p_step[index];
}
