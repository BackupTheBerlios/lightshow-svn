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

#include "storage.h"

#include <wx/tokenzr.h>
#include <wx/dir.h>
#include <wx/filename.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////
// Static Declarations
/////////////////////////////////////////////////////////////////////////////////////////////////////

configitem storage::config;
int storage::page = 1;
int storage::DMX[DMX_CHNLS];
int storage::xfade[DMX_CHNLS];
bool storage::setup = false;
bool storage::setuping = false;

//plugin interfaces
io_plugin_interface storage::io_plugin_interf;


//lists
storageitemlist storage::list_groupitem;
storageitemlist storage::list_patchitem;
storageitemlist storage::list_deskitem;
storageitemlist storage::list_groupselectitem;
storageitemlist storage::list_channelitem;
storageitemlist storage::list_projectoritem;
storageitemlist storage::list_functionitem;
storageitemlist storage::list_faderitem;
vector<io_plugin*> storage::list_io_plugins;
vector<patgen_plugin*> storage::list_patgen_plugins;
vector<wxDynamicLibrary*> storage::list_dyn_libs;


void storage::init()
{
	//init some data
	int i;
	for(i = 0;i < DMX_CHNLS;i++)
	{
		xfade[i] = 0;
		DMX[i] = 0;
	}
}

void storage::load_plugins()
{
	wxString filename;
	wxString ext = wxDynamicLibrary::CanonicalizeName(wxT("*"),wxDL_MODULE);

	//TODO /usr/share/etc on linux?
	wxString path = wxGetCwd() + wxT("/Plugins");
	
	wxDir dir(path);
	
	if(!dir.IsOpened())
	{
		wxLogError(wxT("Plugin Directory [ %s ] not found!"),path.c_str());
		return;
	}
	
	wxString file;
	
	//TODO implement in wxDynamicLibrary and use Mac-Functions to determine the path out of the Info.plist
	bool cont = dir.GetFirst(&filename, ext, wxDIR_FILES);

	while(cont)
	{
		file = path + wxT("/") + filename;
		wxDynamicLibrary* lib = new wxDynamicLibrary(file);
		if(lib->IsLoaded())
		{
			bool save = false;
			
			if(lib->HasSymbol(wxT("get_io_plugin")))
			{
				getioplugintype get_io_plug = (getioplugintype) lib->GetSymbol(wxT("get_io_plugin"));
				if(get_io_plug != NULL)
				{
					save = true;
					list_io_plugins.push_back(get_io_plug());
				}
			}
			
			if(lib->HasSymbol(wxT("get_genpat_plugin")))
			{
				getpatgenplugintype get_patgen_plug = (getpatgenplugintype) lib->GetSymbol(wxT("get_genpat_plugin"));
				if(get_patgen_plug != NULL)
				{
					save = true;
					list_patgen_plugins.push_back(get_patgen_plug());
				}
			}
			
			if(save)
			{
				wxLogVerbose(wxT("Loaded %s"),filename.c_str());
				list_dyn_libs.push_back(lib);
			}
		}
		cont = dir.GetNext(&filename);
	}
	
	//Start Plugins
	for(unsigned int i = 0;i < list_io_plugins.size();i++)
	{
		list_io_plugins[i]->set_interf(io_plugin_interf.interf);
		list_io_plugins[i]->init();
	}
}

void storage::exit()
{
	//delete data
	while(!list_faderitem.empty())
		delete *list_faderitem.begin();
	while(!list_functionitem.empty())
		delete *list_functionitem.begin();
	while(!list_groupitem.empty())
		delete *list_groupitem.begin();
	while(!list_patchitem.empty())
		delete *list_patchitem.begin();
	while(!list_deskitem.empty())
		delete *list_deskitem.begin();
	while(!list_groupselectitem.empty())
		delete *list_groupselectitem.begin();
	while(!list_channelitem.empty())
		delete *list_channelitem.begin();
	while(!list_projectoritem.empty())
		delete *list_projectoritem.begin();
}

void storage::unload_plugins()
{
	//Stop Plugins
	unsigned int i;
	for(i = 0;i < list_io_plugins.size();i++)
		list_io_plugins[i]->exit();	
	
	//UnLoad Plugins
	//---------------
	for(i = 0;i < list_io_plugins.size();i++)
		delete list_io_plugins[i];	
	for(i = 0;i < list_dyn_libs.size();i++)
		delete list_dyn_libs[i];	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// Load and Save
/////////////////////////////////////////////////////////////////////////////////////////////////////

void storage::load()
{
	load_single_files(wxT("Library"));

	wxFile file(wxT("data.ls"));
	if(!file.IsOpened()) return;
		
	load(file);

	file.Close();
}

void storage::save()
{
	save_single_files(list_projectoritem, wxT("Library"));

	wxFile file(wxT("data.ls"),wxFile::write);
	if(!file.IsOpened()) return;
		
	save(file);

	file.Close();
}
	
void storage::load(wxFile& file, int what)
{
	wxString parm,val;
	int stat = load_parse(file,parm,val);
	while(stat != LOADPARSE_EOF)
	{
		storage_item* item = NULL;
		
		if(stat != LOADPARSE_START)
		{
			wxString msg = wxT("Ignored ") + parm + wxT(" while loading.");
			wxLogVerbose(msg);
			break;
		}

		if(what & LOADSAVE_DESK)
		{
			if(parm == wxT("configitem"))
				config.load(file);
			else if(parm == wxT("deskitem"))
				item = new deskitem();
			else if(parm == wxT("projectoritem"))
				item = new projectoritem();
		}
		if(what & LOADSAVE_CHANNEL)
		{
			if(parm == wxT("groupitem"))
				item = new groupitem();
			else if(parm == wxT("patchitem"))
				item = new patchitem();
			else if(parm == wxT("groupselectitem"))
				item = new groupselectitem();
			else if(parm == wxT("channelitem"))
				item = new channelitem();
		}
		if(what & LOADSAVE_FUNKTION)
		{
			if(parm == wxT("functionitem"))
				item = new functionitem();
			else if(parm == wxT("faderitem"))
				item = new faderitem();
		}
		
		if(item != NULL)
			item->load(file);
		else
			if(parm != wxT("configitem"))
			{
				wxString msg = wxT("Ignored ") + parm + wxT(" while loading.");
				wxLogVerbose(msg);
			}

		stat = load_parse(file,parm,val);
	}

	while( list_patchitem.size() < DMX_CHNLS)
		patchitem* p = new patchitem();
}

void storage::load_single_files(wxString path)
{
	wxString filename;
	wxString ext = wxT("*.ls");

	//TODO /usr/share/etc on linux?
	wxString cpath = wxGetCwd() + wxT("/") + path;
	
	wxDir dir(cpath);
	
	if(!dir.IsOpened())
	{
		wxLogError(wxT("Load: Directory [ %s ] not found!"),cpath.c_str());
		return;
	}
	
	wxString fullpath;
	
	//TODO implement in wxDynamicLibrary and use Mac-Functions to determine the path out of the Info.plist
	bool cont = dir.GetFirst(&filename, ext, wxDIR_FILES);

	while(cont)
	{
		fullpath = path + wxT("/") + filename;
			
		wxFile file(fullpath);
		if(!file.IsOpened()) return;
			
		load(file);

		file.Close();

		cont = dir.GetNext(&filename);
	}
	
}

void storage::save(wxFile& file, int what)
{
	if(what & LOADSAVE_DESK)
	{
		config.save(file);
		save(file, list_deskitem);
	}
	
	if(what & LOADSAVE_CHANNEL)
	{
		save(file, list_groupitem);
		save(file, list_patchitem);
		save(file, list_groupselectitem);
		save(file, list_channelitem);
	}

	if(what & LOADSAVE_FUNKTION)
	{
		save(file, list_functionitem);
		save(file, list_faderitem);
	}
}

void storage::save(wxFile& file, storageitemlist& slist)
{
	storageitemlist::iterator it;
	for(it = slist.begin();it != slist.end();it++)
	{
		(*it)->save(file);
	}
}

void storage::save_single_files(storageitemlist& slist, wxString path)
{
	path += wxT("/");

	storageitemlist::iterator it;
	for(it = slist.begin();it != slist.end();it++)
	{
		wxString name = (*it)->get_s_param(wxT("name"));
		wxFile file(path + name + wxT(".ls"),wxFile::write);
		if(!file.IsOpened())
		{
			wxLogError(wxT("Could not save Library item: ") + name + wxT("."));
			continue;
		}
		
		(*it)->save(file);
		
		file.Close();
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Functions
/////////////////////////////////////////////////////////////////////////////////////////////////////

int storage::str_to_int(wxString s)
{
	long i;
	if(!s.ToLong(&i)) i = -1;
	return (int)i;
}

bool storage::str_to_bool(wxString s)
{
	bool b = (str_to_int(s)!=0);
	return b;
}

double storage::str_to_double(wxString s)
{
	double d = -1;
	s.ToDouble(&d);
	return d;
}

bool storage::str_to_rgb(wxString s,unsigned char* rgb)
{
	if(s.Length() != 6 || !rgb)
		return false;
	
	for(int i = 0;i < 3;i++)
	{
		long l;
		if(! s.Mid(i*2,2).ToLong(&l,16))
			return false;
		rgb[i] = (unsigned char)l;
	}
	return true;
}

/*
void storage::str_to_list(wxString s,list<int>& l)
{
	l.clear();
	wxStringTokenizer tkz(s, wxT(","));
	while ( tkz.HasMoreTokens() )
	{
    	wxString token = tkz.GetNextToken();
		l.push_back(str_to_int(token));
	}
}
*/

wxString storage::int_to_str(int i)
{
	return wxString::Format(wxT("%d"),i);
}

wxString storage::bool_to_str(bool b)
{
	return int_to_str(b);
}

wxString storage::double_to_str(double d)
{
	return wxString::Format(wxT("%.2f"),d);
}

wxString storage::rgb_to_str(unsigned char* rgb)
{
	if(!rgb)
		return wxT("");
	
	return wxString::Format(wxT("%02X%02X%02X"),rgb[0],rgb[1],rgb[2]);
}

/*wxString storage::list_to_str(list<int>& l)
{
	wxString str = wxT("");
	
	list<int>::iterator it;
	for(it = l.begin();it != l.end();it++)
	{
		if(it != l.begin()) str += wxT(",");
		str += int_to_str(*it);
	}
	
	return str;
}*/

storage_item* storage::storage_item_for_row(storageitemlist* slist,int row)
{
	storageitemlist::iterator it;
	it = slist->begin();
	for(int i = 0;i < row;i++)
	{
		if(it == slist->end()) return NULL;
		it++;
	}
	return *it;
}

wxString storage::list_lookup(storageitemlist& slist, wxString searchparam, wxString value, wxString returnparam)
{
	storageitemlist::iterator it;
	for(it = slist.begin();it != slist.end();it++)
	{
		if((*it)->get_s_param(searchparam) == value)  return (*it)->get_s_param(returnparam);
	}
	
	return wxT("");
}

wxString storage::list_to_string(storageitemlist& slist, wxString param)
{
	wxString str = wxT("");

	storageitemlist::iterator it;
	for(it = slist.begin();it != slist.end();it++)
	{
		if(it != slist.begin()) str += wxT(",");
		str += (*it)->get_s_param(param);
	}
	
	return str;
}

wxString storage::list_to_string_compare(storageitemlist& slist, wxString returnparam, wxString sparam, wxString value)
{
	wxString str = wxT("");

	storageitemlist::iterator it;
	for(it = slist.begin();it != slist.end();it++)
	{
		if((*it)->get_s_param(sparam) == value)
		{
			if(it != slist.begin()) str += wxT(",");
			str += (*it)->get_s_param(returnparam);
		}
	}
	
	return str;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// Load Helper Functions
/////////////////////////////////////////////////////////////////////////////////////////////////////

wxString storage::load_get_line(wxFile& file)
{
	wxString str = wxT("");
	char buf;

	while(!file.Eof())
	{
		int pos = file.Read(&buf,1);
		if(pos != 1) break;
		if(buf == '\n') break;
					
		str += buf;
	}
	return str;
}

int storage::load_parse(wxFile& file, wxString& param, wxString& value)
{
	param = wxT("");
	value = wxT("");
	
	wxString inp = load_get_line(file);
	if(inp == wxT(""))
		return LOADPARSE_EOF;
	
	inp = inp.AfterFirst('<');
	param = inp.BeforeFirst('>');
	if(param.StartsWith(wxT("/"),&param))
		return LOADPARSE_END;
	
	inp = inp.AfterFirst('>');
	value = inp.BeforeFirst('<');
	
	inp = inp.AfterFirst('<');
	inp = inp.BeforeFirst('>');
	
	if(value == wxT("") && inp == wxT("") && param != wxT(""))
		return LOADPARSE_START;
	else
		return LOADPARSE_VALUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// Item Helper Functions
/////////////////////////////////////////////////////////////////////////////////////////////////////
/*
storage_item* storage::xxx_for_deskitem(storageitemlist& slist,wxString param,deskitem* item,int page, bool setup)
{
	do
	{
		int b_id = item->get_id();
		storageitemlist::iterator it;
		for(it = slist.begin();it != slist.end();it++)
		{
			if((*it)->get_i_param(param) == b_id && (*it)->get_i_param(wxT("page")) == page)
				return *it;
		}
	}
	while (!setup && --page);
	
	return NULL;
}
*/

groupselectitem* storage::groupselectitem_for_deskitem(deskitem* item,int page, bool setup)
{
	int b_id = item->get_id();
	groupselectitem* gitem;
	
	do
	{
		storageitemlist::iterator it;
		for(it = list_groupselectitem.begin();it != list_groupselectitem.end();it++)
		{
			gitem = (groupselectitem*)*it;
			if(gitem->get_button_id() == b_id && gitem->get_page() == page)
				return gitem;
		}
	}
	while (--page);
	//transparency everytime
	
	return NULL;
}

functionitem* storage::functionitem_for_deskitem(deskitem* item,int page, bool setup)
{
	setup = setup || !config.get_translucent_buttons();

	int b_id = item->get_id();
	functionitem* fitem;
	
	do
	{
		storageitemlist::iterator it;
		for(it = list_functionitem.begin();it != list_functionitem.end();it++)
		{
			fitem = (functionitem*)*it;
			if(fitem->get_button_id() == b_id && fitem->get_page() == page)
				return fitem;
		}
	}
	while (!setup && --page);
	
	return NULL;
}

faderitem* storage::faderitem_for_deskitem(deskitem* item,int page, bool setup)
{
	setup = setup || !config.get_translucent_fader();

	int b_id = item->get_id();
	faderitem* fitem;
	
	do
	{
		storageitemlist::iterator it;
		for(it = list_faderitem.begin();it != list_faderitem.end();it++)
		{
			fitem = (faderitem*)*it;
			if(fitem->get_fader_id() == b_id && fitem->get_page() == page)
				return fitem;
		}
	}
	while (!setup && --page);
	
	return NULL;
}

deskitem* storage::deskitem_for_position(int x, int y, int w, int h)
{
	double draw_scale = storage::config.get_draw_scale();

	int relx = (int)((x/(double)w)*1000*draw_scale);
	int rely = (int)((y/(double)h)*1000*draw_scale);

	storageitemlist::iterator it;
	for(it = storage::list_deskitem.begin();it != storage::list_deskitem.end();it++)
	{
		deskitem* item = (deskitem*)*it;
		
		int x = item->get_pos_x();
		int y = item->get_pos_y();
		
		if(item->get_type() == deskitem::T_FADER)
		{
			if((relx > x) && (relx < x+storage::config.get_fader_width()) && (rely > y) && \
				(rely < y+storage::config.get_fader_height()+storage::config.get_fader_button_height()))
				return item;
		}
		else
		{
			if((relx > x) && (relx < x+storage::config.get_button_width()) && (rely > y) && \
				(rely < y+storage::config.get_button_height()))
				return item;
		}
	}
	
	return NULL;
}

deskitem* storage::deskitem_for_id(int id, bool fader)
{
	storageitemlist::iterator it;
	for(it = storage::list_deskitem.begin();it != storage::list_deskitem.end();it++)
	{
		deskitem* ditem = (deskitem*)*it;
		if(fader)
		{
			if(ditem->get_fader_id() == id)
				return ditem;
		}
		else
		{
			if(ditem->get_button_id() == id)
				return ditem;
		}
	}
	return NULL;	
}

/*
storage_item* storage::xxx_for_xxx(storageitemlist& slist, wxString searchparam, wxString comparevalue)
{
	storageitemlist::iterator it;
	for(it = slist.begin();it != slist.end();it++)
	{
		if((*it)->get_s_param(searchparam) == comparevalue)
			return *it;
	}
	return NULL;
}
*/

channelitem* storage::channelitem_for_channel(int channel)
{
	storageitemlist::iterator it;
	for(it = list_channelitem.begin();it != list_channelitem.end();it++)
	{
		channelitem* citem = (channelitem*)*it;

		int it_start = citem->get_start_channel();
		int it_num = citem->get_num_channels();
		
		if(channel >= it_start && channel <= it_start+it_num-1)
			return citem;
	}
	return NULL;
}

projectoritem* storage::projectoritem_for_channelitem(channelitem* item)
{
	if(!item) return NULL;
		
	if(item->get_type() != channelitem::T_PROJ) return NULL;
	
	wxString name = item->get_proj_type();
		
	storageitemlist::iterator it;
	projectoritem* pitem;
	for(it = list_projectoritem.begin();it != list_projectoritem.end();it++)
	{
		pitem = (projectoritem*)*it;
		if(pitem->get_name() == name)
			return pitem;
	}
	return NULL;
}

projectorchannelitem* storage::projectorchannelitem_for_subchannel(projectoritem* item, int subchannel)
{
	if(!item) return NULL;
	
	storageitemlist::iterator it;
	projectorchannelitem* pitem;
	for(it = item->list_projectorchannelitem.begin();it != item->list_projectorchannelitem.end();it++)
	{
		pitem = (projectorchannelitem*)*it;
		if(pitem->get_channel() == subchannel)
			return pitem;
	}
	return NULL;
}

stateitem* storage::stateitem_for_state(projectoritem* item, int state)
{
	if(!item) return NULL;

	storageitemlist::iterator it;
	stateitem* sitem;
	for(it = item->list_stateitem.begin();it != item->list_stateitem.end();it++)
	{
		sitem = (stateitem*)*it;
		if(sitem->get_state() == state)
			return sitem;
	}
	return NULL;
}

functionitem* storage::functionitem_for_id(int id)
{
	storageitemlist::iterator it;
	functionitem* fitem;
	for(it = list_functionitem.begin();it != list_functionitem.end();it++)
	{
		fitem = (functionitem*)*it;
		if(fitem->get_id() == id)
			return fitem;
	}
	return NULL;
}


wxString storage::channel_name_long(int id)
{
	wxString name;
	channelitem* citem = storage::channelitem_for_channel(id);
	if(citem)
	{
		name = citem->get_name();
		projectoritem* pitem = storage::projectoritem_for_channelitem(citem);
		if(pitem)
		{
			name += wxT(" [") + pitem->get_name() + wxT("]");
			int subchannel = id - citem->get_start_channel() + 1;
			projectorchannelitem* pcitem = storage::projectorchannelitem_for_subchannel(pitem,subchannel);
			if(pcitem)
			{
				name += wxT(" (") + pcitem->get_name() + wxT(")");
			}
		}
		return name;
	}	
	
	return storage::int_to_str(id);	
}

wxString storage::channel_name(int id)
{
	wxString name;
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
				name = pcitem->get_name();
				return name;
			}
		}
		name = citem->get_name();
		return name;
	}	
	
	return storage::int_to_str(id);	
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
// Run Functions
/////////////////////////////////////////////////////////////////////////////////////////////////////

void storage::group_filter(bool* mask)
{
	storageitemlist::iterator it;
	for(it = list_channelitem.begin();it != list_channelitem.end();it++)
	{
		channelitem* citem = (channelitem*)*it;
		citem->mask(mask);
	}
}

void storage::konventional_filter(bool* mask)
{
	storageitemlist::iterator it;
	for(it = list_channelitem.begin();it != list_channelitem.end();it++)
	{
		channelitem* citem = (channelitem*)*it;
		if(citem->get_type() == channelitem::T_KONV)
		{
			int it_start = citem->get_start_channel();
			int it_num = citem->get_num_channels();
		
			for(int channel = it_start;channel <= it_start+it_num-1;channel++)
				mask[channel-1] = false;
		}
	}
}

void storage::highlite(bool* mask)
{
	storageitemlist::iterator it;
	for(it = list_channelitem.begin();it != list_channelitem.end();it++)
	{
		channelitem* citem = (channelitem*)*it;
		if(citem->get_type() == channelitem::T_PROJ)
		{
			int it_start = citem->get_start_channel();
			int it_num = citem->get_num_channels();
			
			for(int channel = it_start;channel <= it_start+it_num-1;channel++)
			{
				if(mask[channel-1])
				{
					projectoritem* pitem = projectoritem_for_channelitem(citem);
					if(pitem)
					{
						pitem->highlite(it_start);
					}
					break;
				}
			}
		}
	}	
}

void storage::update_function_masks(bool* mask,functionitem* act_item)
{
	bool overlay = act_item->get_overlay();
	bool switching = act_item->get_switching();
	
	storageitemlist::iterator it;
	for(it = list_functionitem.begin();it != list_functionitem.end();it++)
	{
		functionitem* item = (functionitem*)*it;
		
		if(item != act_item)
			item->update_mask(mask,overlay,switching);
	}
}

void storage::update_groupselectitems_active()
{
	storageitemlist::iterator it;
	for(it = list_groupselectitem.begin();it != list_groupselectitem.end();it++)
	{
		groupselectitem* gitem = (groupselectitem*)*it;
		gitem->update_active(true);
	}
}

void storage::update_channelitems_active()
{
	storageitemlist::iterator it;
	for(it = list_groupselectitem.begin();it != list_groupselectitem.end();it++)
	{
		groupselectitem* gitem = (groupselectitem*)*it;
		gitem->update_active(false);
	}
}

unsigned int storage::get_max_desk_button_id()
{
	unsigned int id = 0;
	storageitemlist::iterator it;
	for(it = list_deskitem.begin();it != list_deskitem.end();it++)
	{
		deskitem* ditem = (deskitem*)*it;
		if(ditem->get_button_id() > id)
			id = ditem->get_button_id();
	}
	return id;
}

void storage::update_key_led_states()
{
	unsigned int count = storage::get_max_desk_button_id();
	bool* on = (bool*)malloc(count * sizeof(bool));
	
	functionitem* function_item = NULL;
	groupselectitem* group_item = NULL;

	unsigned int i;
	for(i = 0; i < count;i++)
	{
		on[i] = false;

		deskitem* ditem = storage::deskitem_for_id(i+1);
		if(ditem)
		{
			switch(ditem->get_type())
			{
			case deskitem::T_GROUP:
				group_item = storage::groupselectitem_for_deskitem(ditem,storage::page);
				if(group_item != NULL)
					on[i] = group_item->get_active();
				break;
			case deskitem::T_PAGE:
				if(ditem->get_page_id() == storage::page)
					on[i] = true;
				break;
			case deskitem::T_FUNCTION:
				function_item = storage::functionitem_for_deskitem(ditem,storage::page);
				if(function_item != NULL)
					on[i] = function_item->get_active();
				break;
			}
		}
	}
	
	//Plugin Output
	for(i = 0;i < list_io_plugins.size();i++)
	{
		list_io_plugins[i]->set_key_leds(count, on);
	}
	
	delete on;
}
