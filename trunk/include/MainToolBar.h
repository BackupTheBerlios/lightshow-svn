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

#ifndef MAINTOOLBAR_H
#define MAINTOOLBAR_H

#include "prec.h"

enum
{
	IDM_SHOW_DESK = 100,
	IDM_SHOW_DESK_SETUP,
	IDM_SHOW_FUNCTION_SETUP,
	IDM_IO_SETUP,
	IDM_GROUP_SETUP,
	IDM_CHANNEL_SETUP,
	IDM_LIBRARY,
	IDM_DMX_PATCH,
	IDM_SETUP_OUTPUT
};


class MainToolBar: public wxToolBar {
public:
    MainToolBar(wxWindow* parent, int id, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=wxTB_HORIZONTAL);

private:
    void set_properties();
    void do_layout();

protected:
};


#endif // MAINTOOLBAR_H
