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

#include "ChannelDialog.h"
#include "storage.h"


ChannelDialog::ChannelDialog(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxDialog(parent, id, title, pos, size, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER)
{
    grid_channels = new mywxGrid(this, -1);
    button_properties = new wxButton(this, wxID_PROPERTIES, wxT("&Properties"));
    button_close = new wxButton(this, wxID_CLOSE, wxT("&Close"));
    button_add = new wxButton(this, wxID_NEW, wxT("&Add"));
    button_delete = new wxButton(this, wxID_DELETE, wxT("&Delete"));

    set_properties();
    do_layout();
	
	grid_channels->set_channel_list();
}


void ChannelDialog::set_properties()
{
    SetTitle(wxT("Channels"));
    SetSize(wxSize(779, 600));
}


void ChannelDialog::do_layout()
{
    wxBoxSizer* sizer_2 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_4 = new wxBoxSizer(wxHORIZONTAL);
    sizer_2->Add(grid_channels, 1, wxEXPAND, 0);
	sizer_4->Add(button_add, 0, 0, 0);
	sizer_4->Add(button_delete, 0, 0, 0);
    sizer_4->Add(button_properties, 0, 0, 0);
    sizer_4->Add(button_close, 0, 0, 0);
    sizer_2->Add(sizer_4, 0, wxALIGN_RIGHT, 0);
    SetAutoLayout(true);
    SetSizer(sizer_2);
    Layout();
}

BEGIN_EVENT_TABLE(ChannelDialog, wxDialog)
	EVT_BUTTON(wxID_CLOSE, ChannelDialog::OnClose)
	EVT_BUTTON(wxID_NEW, ChannelDialog::OnNew)
	EVT_BUTTON(wxID_DELETE, ChannelDialog::OnDelete)
END_EVENT_TABLE()

void ChannelDialog::OnClose(wxCommandEvent& event)
{
	Close();
}

void ChannelDialog::OnNew(wxCommandEvent& event)
{
	grid_channels->append();
}

void ChannelDialog::OnDelete(wxCommandEvent& event)
{
	grid_channels->delete_selected();
}
