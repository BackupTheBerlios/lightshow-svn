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

#include "LoadTypeDialog.h"
#include "storage.h"


LoadTypeDialog::LoadTypeDialog(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxDialog(parent, id, title, pos, size, wxDEFAULT_DIALOG_STYLE)
{
    label_4 = new wxStaticText(this, -1, wxT("Choose what to do:"));
    label_5 = new wxStaticText(this, -1, wxT("Desk"));
    radio_btn_desk_load = new wxRadioButton(this, IDR_DESK_LOAD, wxT("Load"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
    radio_btn_desk_keep = new wxRadioButton(this, IDR_DESK_KEEP, wxT("Keep"));
    radio_btn_desk_clear = new wxRadioButton(this, IDR_DESK_CLEAR, wxT("Clear"));
    label_6 = new wxStaticText(this, -1, wxT("Channels"));
    radio_btn_channels_load = new wxRadioButton(this, IDR_CHANNELS_LOAD, wxT("Load"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
    radio_btn_channels_keep = new wxRadioButton(this, IDR_CHANNELS_KEEP, wxT("Keep"));
    radio_btn_channels_clear = new wxRadioButton(this, IDR_CHANNELS_CLEAR, wxT("Clear"));
    label_7 = new wxStaticText(this, -1, wxT("Functions"));
    radio_btn_functions_load = new wxRadioButton(this, IDR_FUNCTIONS_LOAD, wxT("Load"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
    radio_btn_functions_keep = new wxRadioButton(this, IDR_FUNCTIONS_KEEP, wxT("Keep"));
    radio_btn_functions_clear = new wxRadioButton(this, IDR_FUNCTIONS_CLEAR, wxT("Clear"));
    button_close = new wxButton(this, wxID_CLOSE, wxT("&Close"));
    button_ok = new wxButton(this, wxID_OK, wxT("&OK"));

    set_properties();
    do_layout();

	p_clear = 0;
	p_load = LOADSAVE_DESK | LOADSAVE_CHANNEL | LOADSAVE_FUNKTION;
}


BEGIN_EVENT_TABLE(LoadTypeDialog, wxDialog)
    EVT_RADIOBUTTON(IDR_DESK_LOAD, LoadTypeDialog::OnDeskLoad)
    EVT_RADIOBUTTON(IDR_DESK_KEEP, LoadTypeDialog::OnDeskKeep)
    EVT_RADIOBUTTON(IDR_DESK_CLEAR, LoadTypeDialog::OnDeskClear)
    EVT_RADIOBUTTON(IDR_CHANNELS_LOAD, LoadTypeDialog::OnChannelsLoad)
    EVT_RADIOBUTTON(IDR_CHANNELS_KEEP, LoadTypeDialog::OnChannelsKeep)
    EVT_RADIOBUTTON(IDR_CHANNELS_CLEAR, LoadTypeDialog::OnChannelsClear)
    EVT_RADIOBUTTON(IDR_FUNCTIONS_LOAD, LoadTypeDialog::OnFunctionsLoad)
    EVT_RADIOBUTTON(IDR_FUNCTIONS_KEEP, LoadTypeDialog::OnFunctionsKeep)
    EVT_RADIOBUTTON(IDR_FUNCTIONS_CLEAR, LoadTypeDialog::OnFunctionsClear)
    EVT_BUTTON(wxID_CLOSE, LoadTypeDialog::OnClose)
    EVT_BUTTON(wxID_OK, LoadTypeDialog::OnOK)
END_EVENT_TABLE();


void LoadTypeDialog::OnDeskLoad(wxCommandEvent &event)
{
	p_clear &= ~LOADSAVE_DESK;
	p_load |= LOADSAVE_DESK;

    radio_btn_channels_load->Enable();
    radio_btn_channels_keep->Disable();
	if(radio_btn_channels_keep->GetValue())
	{
		radio_btn_channels_load->SetValue(1);
		OnChannelsLoad(event);
	}
    radio_btn_channels_clear->Enable();
    radio_btn_functions_load->Enable();
    radio_btn_functions_keep->Disable();
	if(radio_btn_functions_keep->GetValue())
	{
		radio_btn_functions_load->SetValue(1);
		OnFunctionsLoad(event);
	}
    radio_btn_functions_clear->Enable();
}

void LoadTypeDialog::OnDeskKeep(wxCommandEvent &event)
{
	p_clear &= ~LOADSAVE_DESK;
	p_load &= ~LOADSAVE_DESK;

    radio_btn_channels_load->Enable();
    radio_btn_channels_keep->Enable();
    radio_btn_channels_clear->Enable();
    radio_btn_functions_load->Enable();
    radio_btn_functions_keep->Enable();
    radio_btn_functions_clear->Enable();
}

void LoadTypeDialog::OnDeskClear(wxCommandEvent &event)
{
	p_clear |= LOADSAVE_DESK | LOADSAVE_FUNKTION;
	p_load &= ~(LOADSAVE_DESK | LOADSAVE_FUNKTION);

    radio_btn_channels_load->Enable();
    radio_btn_channels_keep->Enable();
    radio_btn_channels_clear->Enable();
    radio_btn_functions_load->Disable();
    radio_btn_functions_keep->Disable();
    radio_btn_functions_clear->SetValue(1);	
}

void LoadTypeDialog::OnChannelsLoad(wxCommandEvent &event)
{
	p_clear &= ~LOADSAVE_CHANNEL;
	p_load |= LOADSAVE_CHANNEL;

   	radio_btn_functions_load->Enable();
    radio_btn_functions_keep->Disable();
	if(radio_btn_functions_keep->GetValue())
	{
		radio_btn_functions_load->SetValue(1);
		OnFunctionsLoad(event);
	}
    radio_btn_functions_clear->Enable();	
}

void LoadTypeDialog::OnChannelsKeep(wxCommandEvent &event)
{
	p_clear &= ~LOADSAVE_CHANNEL;
	p_load &= ~LOADSAVE_CHANNEL;

    radio_btn_functions_load->Enable();
    radio_btn_functions_keep->Enable();
    radio_btn_functions_clear->Enable();
}

void LoadTypeDialog::OnChannelsClear(wxCommandEvent &event)
{
	p_clear |= LOADSAVE_CHANNEL;
	p_load &= ~LOADSAVE_CHANNEL;

    radio_btn_functions_load->Disable();
    radio_btn_functions_keep->Disable();
    radio_btn_functions_clear->SetValue(1);
}
void LoadTypeDialog::OnFunctionsLoad(wxCommandEvent &event)
{
	p_clear &= ~LOADSAVE_FUNKTION;
	p_load |= LOADSAVE_FUNKTION;
}

void LoadTypeDialog::OnFunctionsKeep(wxCommandEvent &event)
{
	p_clear &= ~LOADSAVE_FUNKTION;
	p_load &= ~LOADSAVE_FUNKTION;
}

void LoadTypeDialog::OnFunctionsClear(wxCommandEvent &event)
{
	p_clear |= LOADSAVE_FUNKTION;
	p_load &= ~LOADSAVE_FUNKTION;
}

void LoadTypeDialog::OnClose(wxCommandEvent &event)
{
	EndModal(wxID_CLOSE);
}

void LoadTypeDialog::OnOK(wxCommandEvent &event)
{
	EndModal(wxID_OK);
}

void LoadTypeDialog::set_properties()
{
    SetTitle(wxT("Choose what to load"));
    SetSize(wxSize(358, 234));
    radio_btn_desk_load->SetValue(1);
    radio_btn_channels_load->SetValue(1);
    radio_btn_functions_load->SetValue(1);
}


void LoadTypeDialog::do_layout()
{
    wxBoxSizer* sizer_1 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_2 = new wxBoxSizer(wxHORIZONTAL);
    wxGridSizer* grid_sizer_1 = new wxGridSizer(3, 4, 0, 0);
    sizer_1->Add(label_4, 0, wxADJUST_MINSIZE, 0);
    grid_sizer_1->Add(label_5, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxADJUST_MINSIZE, 0);
    grid_sizer_1->Add(radio_btn_desk_load, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxADJUST_MINSIZE, 0);
    grid_sizer_1->Add(radio_btn_desk_keep, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxADJUST_MINSIZE, 0);
    grid_sizer_1->Add(radio_btn_desk_clear, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxADJUST_MINSIZE, 0);
    grid_sizer_1->Add(label_6, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxADJUST_MINSIZE, 0);
    grid_sizer_1->Add(radio_btn_channels_load, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxADJUST_MINSIZE, 0);
    grid_sizer_1->Add(radio_btn_channels_keep, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxADJUST_MINSIZE, 0);
    grid_sizer_1->Add(radio_btn_channels_clear, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxADJUST_MINSIZE, 0);
    grid_sizer_1->Add(label_7, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxADJUST_MINSIZE, 0);
    grid_sizer_1->Add(radio_btn_functions_load, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxADJUST_MINSIZE, 0);
    grid_sizer_1->Add(radio_btn_functions_keep, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxADJUST_MINSIZE, 0);
    grid_sizer_1->Add(radio_btn_functions_clear, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxADJUST_MINSIZE, 0);
    sizer_1->Add(grid_sizer_1, 1, wxEXPAND, 0);
    sizer_2->Add(button_close, 0, wxADJUST_MINSIZE, 0);
    sizer_2->Add(button_ok, 0, wxADJUST_MINSIZE, 0);
    sizer_1->Add(sizer_2, 0, wxALIGN_RIGHT, 0);
    SetAutoLayout(true);
    SetSizer(sizer_1);
    Layout();
}

