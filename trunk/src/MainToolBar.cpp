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

// -*- C++ -*- generated by wxGlade 0.3.3 on Fri Sep  3 20:20:11 2004

#include "MainToolBar.h"

#ifdef __WXMAC__
#  include "../bitmaps/text/menu.xpm"
#  include "../bitmaps/text/desk.xpm"
#  include "../bitmaps/text/desk_setup.xpm"
#  include "../bitmaps/text/function_setup.xpm"
#  include "../bitmaps/text/io_setup.xpm"
#  include "../bitmaps/text/group_setup.xpm"
#  include "../bitmaps/text/channel_setup.xpm"
#  include "../bitmaps/text/library.xpm"
#  include "../bitmaps/text/dmx_patch.xpm"
#  include "../bitmaps/text/setup_output.xpm"
#endif

MainToolBar::MainToolBar(wxWindow* parent, int id, const wxPoint& pos, const wxSize& size, long style):
    wxToolBar(parent, id, pos, size, wxTB_FLAT | wxTB_TEXT | wxTB_NOICONS)
{
    set_properties();
    do_layout();
}


void MainToolBar::set_properties()
{
#ifdef __WXMAC__
	SetToolBitmapSize(wxSize(96, 24));
    AddTool(IDM_MENU, wxT("Menu"), wxBitmap(menu_xpm), wxNullBitmap, wxITEM_NORMAL, wxT(""), wxT(""));
	AddSeparator();
    AddTool(IDM_SHOW_DESK, wxT("Desk"), wxBitmap(desk_xpm), wxNullBitmap, wxITEM_RADIO, wxT(""), wxT(""));
    AddTool(IDM_SHOW_DESK_SETUP, wxT("Desk Setup"), wxBitmap(desk_setup_xpm), wxNullBitmap, wxITEM_RADIO, wxT(""), wxT(""));
    AddTool(IDM_SHOW_FUNCTION_SETUP, wxT("Function Setup"), wxBitmap(function_setup_xpm), wxNullBitmap, wxITEM_RADIO, wxT(""), wxT(""));
    AddSeparator();
    AddTool(IDM_IO_SETUP, wxT("IO Setup"), wxBitmap(io_setup_xpm), wxNullBitmap, wxITEM_NORMAL, wxT(""), wxT(""));
    AddTool(IDM_GROUP_SETUP, wxT("Group Setup"), wxBitmap(group_setup_xpm), wxNullBitmap, wxITEM_NORMAL, wxT(""), wxT(""));
    AddTool(IDM_CHANNEL_SETUP, wxT("Channel Setup"), wxBitmap(channel_setup_xpm), wxNullBitmap, wxITEM_NORMAL, wxT(""), wxT(""));
    AddTool(IDM_LIBRARY, wxT("Library"), wxBitmap(library_xpm), wxNullBitmap, wxITEM_NORMAL, wxT(""), wxT(""));
    AddTool(IDM_DMX_PATCH, wxT("DMX Patch"), wxBitmap(dmx_patch_xpm), wxNullBitmap, wxITEM_NORMAL, wxT(""), wxT(""));
    AddSeparator();
    AddTool(IDM_SETUP_OUTPUT, wxT("Setup Output"), wxBitmap(setup_output_xpm), wxNullBitmap, wxITEM_CHECK, wxT(""), wxT(""));
#else
    AddTool(IDM_MENU, wxT("Menu"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxT(""), wxT(""));
	AddSeparator();
    AddTool(IDM_SHOW_DESK, wxT("Desk"), wxNullBitmap, wxNullBitmap, wxITEM_RADIO, wxT(""), wxT(""));
    AddTool(IDM_SHOW_DESK_SETUP, wxT("Desk Setup"), wxNullBitmap, wxNullBitmap, wxITEM_RADIO, wxT(""), wxT(""));
    AddTool(IDM_SHOW_FUNCTION_SETUP, wxT("Function Setup"), wxNullBitmap, wxNullBitmap, wxITEM_RADIO, wxT(""), wxT(""));
    AddSeparator();
    AddTool(IDM_IO_SETUP, wxT("IO Setup"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxT(""), wxT(""));
    AddTool(IDM_GROUP_SETUP, wxT("Group Setup"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxT(""), wxT(""));
    AddTool(IDM_CHANNEL_SETUP, wxT("Channel Setup"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxT(""), wxT(""));
    AddTool(IDM_LIBRARY, wxT("Library"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxT(""), wxT(""));
    AddTool(IDM_DMX_PATCH, wxT("DMX Patch"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxT(""), wxT(""));
    AddSeparator();
    AddTool(IDM_SETUP_OUTPUT, wxT("Setup Output"), wxNullBitmap, wxNullBitmap, wxITEM_CHECK, wxT(""), wxT(""));
#endif
	
    Realize();
}


void MainToolBar::do_layout()
{
}
