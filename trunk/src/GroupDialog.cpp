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

#include "GroupDialog.h"
#include "storage.h"


GroupDialog::GroupDialog(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxDialog(parent, id, title, pos, size, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxTHICK_FRAME)
{
    grid_group = new mywxGrid(this, -1);
    button_close = new wxButton(this, wxID_CLOSE, wxT("&Close"));
    button_add = new wxButton(this, wxID_NEW, wxT("&Add"));
    button_delete = new wxButton(this, wxID_DELETE, wxT("&Delete"));
	
    set_properties();
    do_layout();

	grid_group->set_list(&storage::list_groupitem,new_groupitem,NULL);
}


void GroupDialog::set_properties()
{
    SetTitle(wxT("Groups"));
    SetSize(wxSize(400, 400));
}


void GroupDialog::do_layout()
{
    wxBoxSizer* sizer_1 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_2 = new wxBoxSizer(wxHORIZONTAL);
	sizer_2->Add(button_add, 0, 0, 0);
	sizer_2->Add(button_delete, 0, 0, 0);
    sizer_2->Add(button_close, 0, 0, 0);
    sizer_1->Add(grid_group, 1, wxEXPAND, 0);
    sizer_1->Add(sizer_2, 0, wxALIGN_RIGHT, 0);
    SetAutoLayout(true);
    SetSizer(sizer_1);
    Layout();
}

BEGIN_EVENT_TABLE(GroupDialog, wxDialog)
	EVT_BUTTON(wxID_CLOSE, GroupDialog::OnClose)
	EVT_BUTTON(wxID_NEW, GroupDialog::OnNew)
	EVT_BUTTON(wxID_DELETE, GroupDialog::OnDelete)
END_EVENT_TABLE()

void GroupDialog::OnClose(wxCommandEvent& event)
{
	Close();
}

void GroupDialog::OnNew(wxCommandEvent& event)
{
	grid_group->append();
}

void GroupDialog::OnDelete(wxCommandEvent& event)
{
	grid_group->delete_selected();
}
