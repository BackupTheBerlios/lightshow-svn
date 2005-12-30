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

#ifndef __STORAGE_HH
#  define __STORAGE_HH

#include "prec.h"

#define DMX_CHNLS 70
#define MAX_GROUPS 25

class deskitem;
class functionitem;

#include "configitem.h"
#include "dataitem.h"
#include "deskitem.h"
#include "channelitem.h"
#include "projectoritem.h"
#include "projectorchannelitem.h"
#include "valueitem.h"
#include "stateitem.h"
#include "patchitem.h"
#include "groupitem.h"
#include "groupselectitem.h"
#include "functionitem.h"
#include "faderitem.h"
#include "storage_item.h"

#include "../plugins/include/io_plugin.h"
#include "../plugins/include/patgen_plugin.h"

#include "plugin_interface.h"

enum
{
	LOADSAVE_DESK = 1,
	LOADSAVE_CHANNEL = 2,
	LOADSAVE_FUNKTION = 4
};

enum
{
	LOADPARSE_START,
	LOADPARSE_VALUE,
	LOADPARSE_END,
	LOADPARSE_EOF
};


enum
{
	R_ON = 1,
	R_SW,
	R_SW_OV,
	R_PB,
	R_PB_OV,
	R_PREVIEW
};

class storage
{
public:
	static void load();
	static void save();

	static void load_plugins();
	static void unload_plugins();
	
	static void load(wxFile& file, int what = LOADSAVE_DESK | LOADSAVE_CHANNEL | LOADSAVE_FUNKTION);
	static void save(wxFile& file, int what = LOADSAVE_DESK | LOADSAVE_CHANNEL | LOADSAVE_FUNKTION);

	static void save(wxFile& file, storageitemlist& slist);
	static void save_single_files(storageitemlist& slist, wxString path);
	static void load_single_files(wxString path);


	static void init();
	static void exit();

	//active
	static int DMX[DMX_CHNLS];
	static int xfade[DMX_CHNLS];
	static int xfade2[DMX_CHNLS][2];

	static bool xfade_active;

	static bool setup;
	static bool setuping;

	static int max_id;

	static int page;
	static int num_pages;

	static configitem config;
	static storageitemlist list_groupitem;
	static storageitemlist list_patchitem;
	static storageitemlist list_deskitem;
	static storageitemlist list_groupselectitem;
	static storageitemlist list_channelitem;
	static storageitemlist list_projectoritem;
	static storageitemlist list_functionitem;
	static storageitemlist list_faderitem;
	
	static vector<io_plugin*> list_io_plugins;
	static vector<patgen_plugin*> list_patgen_plugins;
	static vector<wxDynamicLibrary*> list_dyn_libs;
	
	//helper functions
	static int str_to_int(wxString s);
	static bool str_to_bool(wxString s);
	static double str_to_double(wxString s);
	static bool str_to_rgb(wxString s,unsigned char* rgb);
	static wxString int_to_str(int i);
	static wxString bool_to_str(bool b);
	static wxString double_to_str(double d);
	static wxString rgb_to_str(unsigned char* rgb);
	
	static storage_item* storage_item_for_row(storageitemlist* slist,int row);
	
	static wxString list_lookup(storageitemlist& slist, wxString searchparam, wxString value, wxString returnparam);
	static wxString list_to_string(storageitemlist& slist, wxString param);
	static wxString list_to_string_compare(storageitemlist& slist, wxString returnparam, wxString sparam, wxString value);

	//load helper functions
	static wxString load_get_line(wxFile& file);
	static int load_parse(wxFile& file, wxString& param, wxString& value);
	
	//item helper functions
	static groupselectitem* groupselectitem_for_deskitem(deskitem* item,int page, bool setup = false);
	static functionitem* functionitem_for_deskitem(deskitem* item,int page, bool setup = false);
	static faderitem* faderitem_for_deskitem(deskitem* item,int page, bool setup = false);
	static deskitem* deskitem_for_position(int x, int y, int w, int h);
	static deskitem* deskitem_for_id(int id, bool fader = false);
	
	
	static channelitem* channelitem_for_channel(int channel);
	static projectoritem* projectoritem_for_channelitem(channelitem* item);
	static projectorchannelitem* projectorchannelitem_for_subchannel(projectoritem* item, int subchannel);
	static stateitem* stateitem_for_state(projectoritem* item, int state);
	static functionitem* functionitem_for_id(int id);
	
	static wxString channel_name(int id);
	static wxString channel_name_long(int id);

	//run helper functions
	static void group_filter(bool* mask);
	static void konventional_filter(bool* mask);
	
	static void highlite(bool* mask);

	static void update_function_masks(bool* mask,functionitem* act_item);
	static void update_groupselectitems_active();
	static void update_channelitems_active();
	
	static void update_key_led_states();
	static void send_key_to_plugin(int key, bool down);

private:
	static io_plugin_interface io_plugin_interf;
		
	static unsigned int get_max_desk_button_id();

//	static storage_item* xxx_for_xxx(storageitemlist& slist, wxString searchparam, wxString comparevalue);
//	static storage_item* xxx_for_deskitem(storageitemlist& slist,wxString param,deskitem* item,int page, bool setup = false);

};

#endif // __STORAGE_HH
