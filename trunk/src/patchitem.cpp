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

#include "patchitem.h"
#include "storage.h"

DECLARE_STATIC_STC(patchitem)

vector<int> patchitem::p_patch(DMX_CHNLS,-1);

patchitem::patchitem()
{
	p_stor_name = wxT("patchitem");
	
	p_id_map[wxT("programm_channel")] = 1;
	p_id_map[wxT("channel_name")] = 2;
	p_id_map[wxT("output_channel")] = 3;
	p_id_map[wxT("output_channel_int")] = 4;
	
	p_dont_show_map[4] = true;
	
	p_dont_save_map[2] = true;
	p_dont_save_map[3] = true;

	p_editable_map[1] = false;
	p_editable_map[2] = false;
	p_editable_map[3] = true;
	
	p_column_width[1] = 150;
	p_column_width[2] = 300;
	p_column_width[3] = 100;

	//get first unused channel number
	int chn = 0;
	do {
		chn++;
	} while (get_patch(chn) != -1);
	
	p_programm_channel = chn;
	p_output_channel = chn;

	if(chn <= DMX_CHNLS)
	{
		p_patch[p_programm_channel-1] = p_output_channel;
	
		storage::list_patchitem.push_back(this);
	}
	else
	{
		for(int i = 0;i < DMX_CHNLS;i++)
			wxLogVerbose(wxT("%d - %d"),i+1,p_patch[i]);
		//TODO delete this ?? any problems?
		wxLogError(wxT("THIS MAY NOT HAPPEN until there is a solution (patchitem > 512)"));
		exit(0);
	}
}

patchitem::~patchitem()
{
	p_patch[p_programm_channel-1] = -1;
	storage::list_patchitem.remove(this);
}

int patchitem::get_patch(int channel)
{
	if(channel > DMX_CHNLS) return -1;
	return p_patch[channel-1];
}

bool patchitem::should_save()
{
	return (p_programm_channel != p_output_channel);
}

wxString patchitem::get_s_param(int id)
{
	switch(id)
	{
		case 1:
			return storage::int_to_str(p_programm_channel);
		case 2:
			return storage::channel_name_long(p_programm_channel);
		case 3:
		case 4:
			return storage::int_to_str(p_output_channel);
		default:
			return wxT("");
	}
}


bool patchitem::change_channel(int new_channel)
{
	storageitemlist::iterator it;
	
	for(it = storage::list_patchitem.begin();it != storage::list_patchitem.end();it++)
	{
		patchitem* pitem = (patchitem*)*it;
		if(pitem->get_output_channel() == new_channel)
		{
			if(!pitem->set_output_channel(p_output_channel))
				return false;
			else
			{
				p_output_channel = new_channel;
				return true;
			}
		}
	}
	
	return false;
}
	
bool patchitem::set_param(int id,wxString value)
{
	switch(id)
	{
		case 1:
			p_patch[p_programm_channel-1] = -1;
			p_programm_channel = storage::str_to_int(value);
			p_patch[p_programm_channel-1] = p_output_channel;
			return true;
		case 3:
			if(change_channel(storage::str_to_int(value)))
			{
				p_patch[p_programm_channel-1] = p_output_channel;
				return true;
			}
			else 
				return false;
		case 4:
			return set_output_channel(storage::str_to_int(value));
		default:
			return false;
	}
}

bool patchitem::set_output_channel(int channel)
{
	p_output_channel = channel;
	p_patch[p_programm_channel-1] = p_output_channel;

	return true;
}

