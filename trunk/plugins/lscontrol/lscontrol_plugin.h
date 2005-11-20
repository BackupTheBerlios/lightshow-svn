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


#ifndef MINIDMXPLUGIN_H
#define MINIDMXPLUGIN_H

#include "wx/wx.h"


class wxDLLApp : public wxApp
{
	bool OnInit();
};

class lscontrol_plugin : public io_plugin
{
public:
	wxString get_name() { return wxT("LSControl"); };
	int get_type() { return T_PLUGIN_OUTPUT | T_PLUGIN_INPUT; };
	wxString get_state() { return p_thread->GetState(); };

	
	bool init();
	void exit();
	void config();
	
	//output
	virtual void output(int count, unsigned char* channels);
	virtual void set_key_leds(int count, bool* state);
	
private:
	unsigned char* p_data;
	int p_count;
	
	MainThread* p_thread;
};

extern "C"
{
	WXEXPORT io_plugin* get_io_plugin();
}

#endif // MINIDMXPLUGIN_H
