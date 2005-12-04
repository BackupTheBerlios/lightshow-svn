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

#include "GroupSelectDialog.h"


GroupSelectDialog::GroupSelectDialog(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxDialog(parent, id, title, pos, size, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxTHICK_FRAME)
{
    grid_groupselect = new mywxGrid(this, -1);
    button_close = new wxButton(this, wxID_CLOSE, wxT("&Close"));
    button_add = new wxButton(this, wxID_NEW, wxT("&Add"));
    button_delete = new wxButton(this, wxID_DELETE, wxT("&Delete"));
	
    set_properties();
    do_layout();
}


void GroupSelectDialog::set_properties()
{
    SetTitle(wxT("Group Select Setup"));
    SetSize(wxSize(400, 500));
}


void GroupSelectDialog::do_layout()
{
    wxBoxSizer* sizer_1 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_2 = new wxBoxSizer(wxHORIZONTAL);
    sizer_1->Add(grid_groupselect, 1, wxEXPAND, 0);
	sizer_2->Add(button_add, 0, 0, 0);
	sizer_2->Add(button_delete, 0, 0, 0);
    sizer_2->Add(button_close, 0, 0, 0);
	sizer_1->Add(sizer_2, 0, wxALIGN_RIGHT, 0);
    SetAutoLayout(true);
    SetSizer(sizer_1);
    Layout();
}

BEGIN_EVENT_TABLE(GroupSelectDialog, wxDialog)
	EVT_BUTTON(wxID_CLOSE, GroupSelectDialog::OnClose)
	EVT_BUTTON(wxID_NEW, GroupSelectDialog::OnAdd)
	EVT_BUTTON(wxID_DELETE, GroupSelectDialog::OnDelete)
END_EVENT_TABLE()

void GroupSelectDialog::OnClose(wxCommandEvent& event)
{
	Close();
}

void GroupSelectDialog::OnAdd(wxCommandEvent& event)
{
	grid_groupselect->append();
}

void GroupSelectDialog::OnDelete(wxCommandEvent& event)
{
	grid_groupselect->delete_selected();
}

void GroupSelectDialog::SetItem(deskitem* item,int page)
{
	groupselectitem* gsitem = storage::groupselectitem_for_deskitem(item,page,true);
	if(gsitem == NULL)
	{
		gsitem = new groupselectitem(item->get_button_id(),page);
	}
	
	grid_groupselect->set_item(gsitem,new_group_in_groupselectitem,gsitem);
}
