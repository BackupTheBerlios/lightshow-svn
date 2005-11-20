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

#ifndef PATGENPLUGIN_H
#define PATGENPLUGIN_H

#include "wx/wx.h"

//functionality used from the plugin, supported by the app
class patgen_app_interface : wxObject
{
public:
};

//functionality used from app, supported by the plugin
class patgen_plugin : public wxObject
{
public:
	virtual wxString get_name() = 0;
	virtual int get_type() = 0;
	virtual wxString get_state() { return wxT("Started"); };
	void set_interf(patgen_app_interface* interf) { p_interf = interf; };
	
	virtual bool init() = 0;
	virtual void exit() = 0;
	virtual void config() {};
	
protected:
	patgen_app_interface* p_interf;
};

typedef patgen_plugin* (*getpatgenplugintype)();

#endif // PATGENPLUGIN_H
