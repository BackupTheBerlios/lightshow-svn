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

#include "SaveTypeDialog.h"
#include "storage.h"

SaveTypeDialog::SaveTypeDialog(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxDialog(parent, id, title, pos, size, wxDEFAULT_DIALOG_STYLE)
{
    label_7 = new wxStaticText(this, -1, wxT("Desk"));
    checkbox_desk_save = new wxCheckBox(this, -1, wxT("Save"));
    label_8 = new wxStaticText(this, -1, wxT("Channels"));
    checkbox_channels_save = new wxCheckBox(this, -1, wxT("Save"));
    label_9 = new wxStaticText(this, -1, wxT("Functions"));
    checkbox_functions_save = new wxCheckBox(this, -1, wxT("Save"));
    button_close = new wxButton(this, wxID_CLOSE, wxT("&Close"));
    button_ok = new wxButton(this, wxID_OK, wxT("&OK"));

    set_properties();
    do_layout();

	p_save = 0;
}


BEGIN_EVENT_TABLE(SaveTypeDialog, wxDialog)
    EVT_BUTTON(wxID_CLOSE, SaveTypeDialog::OnClose)
    EVT_BUTTON(wxID_OK, SaveTypeDialog::OnOK)
END_EVENT_TABLE();


void SaveTypeDialog::OnClose(wxCommandEvent &event)
{
	p_save = 0;
	EndModal(wxID_CLOSE);
}


void SaveTypeDialog::OnOK(wxCommandEvent &event)
{
	p_save = checkbox_desk_save->GetValue() ? LOADSAVE_DESK : 0;
	p_save |= checkbox_channels_save->GetValue() ? LOADSAVE_CHANNEL : 0;
	p_save |= checkbox_functions_save->GetValue() ? LOADSAVE_FUNKTION : 0;
	EndModal(wxID_OK);
}

void SaveTypeDialog::set_properties()
{
    SetTitle(wxT("Choose what to save"));
    SetSize(wxSize(258, 134));
	
	checkbox_desk_save->SetValue(1);
	checkbox_channels_save->SetValue(1);
	checkbox_functions_save->SetValue(1);
}


void SaveTypeDialog::do_layout()
{
    wxBoxSizer* sizer_1 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_2 = new wxBoxSizer(wxHORIZONTAL);
    wxGridSizer* grid_sizer_1 = new wxGridSizer(3, 2, 0, 0);
    grid_sizer_1->Add(label_7, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxADJUST_MINSIZE, 0);
    grid_sizer_1->Add(checkbox_desk_save, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxADJUST_MINSIZE, 0);
    grid_sizer_1->Add(label_8, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxADJUST_MINSIZE, 0);
    grid_sizer_1->Add(checkbox_channels_save, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxADJUST_MINSIZE, 0);
    grid_sizer_1->Add(label_9, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxADJUST_MINSIZE, 0);
    grid_sizer_1->Add(checkbox_functions_save, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxADJUST_MINSIZE, 0);
    sizer_1->Add(grid_sizer_1, 1, wxEXPAND, 0);
    sizer_2->Add(button_close, 0, wxADJUST_MINSIZE, 0);
    sizer_2->Add(button_ok, 0, wxADJUST_MINSIZE, 0);
    sizer_1->Add(sizer_2, 0, wxEXPAND|wxALIGN_RIGHT, 0);
    SetAutoLayout(true);
    SetSizer(sizer_1);
    Layout();
}

