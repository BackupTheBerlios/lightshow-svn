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

#ifndef IOPLUGIN_H
#define IOPLUGIN_H

#include "wx/wx.h"

//functionality used from the plugin, supported by the app
struct io_app_interface
{
public:
	void (*key_state_change)(int id,bool down);
	void (*slider_pos_change)(int id, int pos, bool flash);
	void (*xy_change)(int x, int y, bool relative);
};

enum
{
	T_PLUGIN_OUTPUT = 1,
	T_PLUGIN_INPUT = 2
};

//functionality used from app, supported by the plugin
class io_plugin
{
public:
	//returns the name of the plugin
	virtual wxString get_name() = 0;
	//returns T_PLUGIN_OUTPUT or T_PLUGIN_INPUT or a combination of both
	virtual int get_type() = 0;
	//returns a free to choose status text
	virtual wxString get_state() { return wxT("Started"); };
	
	//called by the GUI:
	void set_interf(io_app_interface interf) { p_interf = interf; };
	virtual bool init() = 0;
	virtual void exit() = 0;
	virtual void config() {};
	
	//output
	//called 40 times per second to output the DMX data
	virtual void output(int count, unsigned char* channels) {};

	//input
	//array of the states of the key-leds, called when the state changes
	virtual void set_key_leds(int count, bool* state) {};
	//gets called if a key state at the pc-keyboard has changes 
	virtual void pc_key_change(int key, bool down) {};
	
protected:
	io_app_interface p_interf;
};

typedef io_plugin* (*getioplugintype)();

#endif // IOPLUGIN_H
