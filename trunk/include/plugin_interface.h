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

#ifndef __PLUGIN_INTERFACE_HH
#  define __PLUGIN_INTERFACE_HH

#include "../plugins/include/io_plugin.h"
#include "../plugins/include/patgen_plugin.h"

class io_plugin_interface
{
public:
	io_plugin_interface();

	static void key_state_change(int id,bool down);
	static void slider_pos_change(int id, int pos, bool flash);
	static void xy_change(int x, int y, bool relative);

	io_app_interface interf;
	
private:
	static void RefreshDesk();
};

#endif // __PLUGIN_INTERFACE_HH
