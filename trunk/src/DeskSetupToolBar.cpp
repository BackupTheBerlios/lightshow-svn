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

#include "DeskSetupToolBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#ifdef __WXMAC__
#  include "../bitmaps/text/add_group.xpm"
#  include "../bitmaps/text/add_page.xpm"
#  include "../bitmaps/text/add_function.xpm"
#  include "../bitmaps/text/add_fader.xpm"
#  include "../bitmaps/text/move.xpm"
#  include "../bitmaps/text/change_number.xpm"
#  include "../bitmaps/text/delete.xpm"
#else
#  include "../bitmaps/add.xpm"
#  include "../bitmaps/move.xpm"
#  include "../bitmaps/change_number.xpm"
#  include "../bitmaps/delete.xpm"
#endif

DeskSetupToolBar::DeskSetupToolBar(wxWindow* parent, int id, const wxPoint& pos, const wxSize& size, long style):
    wxToolBar(parent, id, pos, size, wxTB_FLAT | wxTB_DOCKABLE | wxTB_TEXT)
{
    set_properties();
    do_layout();
}


void DeskSetupToolBar::set_properties()
{
#ifdef __WXMAC__
	SetToolBitmapSize(wxSize(80, 24));
    AddTool(IDDS_ADD_GROUP, wxT("Group"), wxBitmap(add_group_xpm), wxNullBitmap, wxITEM_RADIO, wxT(""), wxT(""));
    AddTool(IDDS_ADD_PAGE, wxT("Page"), wxBitmap(add_page_xpm), wxNullBitmap, wxITEM_RADIO, wxT(""), wxT(""));
    AddTool(IDDS_ADD_FUNCTION, wxT("Function"), wxBitmap(add_function_xpm), wxNullBitmap, wxITEM_RADIO, wxT(""), wxT(""));
    AddTool(IDDS_ADD_FADER, wxT("Fader"), wxBitmap(add_fader_xpm), wxNullBitmap, wxITEM_RADIO, wxT(""), wxT(""));
#else
	SetToolBitmapSize(wxSize(32, 32));
    AddTool(IDDS_ADD_GROUP, wxT("Group"), wxBitmap(add_xpm), wxNullBitmap, wxITEM_RADIO, wxT(""), wxT(""));
    AddTool(IDDS_ADD_PAGE, wxT("Page"), wxBitmap(add_xpm), wxNullBitmap, wxITEM_RADIO, wxT(""), wxT(""));
    AddTool(IDDS_ADD_FUNCTION, wxT("Function"), wxBitmap(add_xpm), wxNullBitmap, wxITEM_RADIO, wxT(""), wxT(""));
    AddTool(IDDS_ADD_FADER, wxT("Fader"), wxBitmap(add_xpm), wxNullBitmap, wxITEM_RADIO, wxT(""), wxT(""));
#endif

    AddTool(IDDS_MOVE, wxT("Move"), wxBitmap(move_xpm), wxNullBitmap, wxITEM_RADIO, wxT(""), wxT(""));
    AddTool(IDDS_NUMBER, wxT("Number"), wxBitmap(change_number_xpm), wxNullBitmap, wxITEM_RADIO, wxT(""), wxT(""));
    AddTool(IDDS_DELETE, wxT("Delete"), wxBitmap(delete_xpm), wxNullBitmap, wxITEM_RADIO, wxT(""), wxT(""));
    Realize();
}


void DeskSetupToolBar::do_layout()
{
}
