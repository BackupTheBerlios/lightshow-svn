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

#include "LibraryDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


LibraryDialog::LibraryDialog(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxDialog(parent, id, title, pos, size, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER)
{
    label_1 = new wxStaticText(this, -1, wxT("Devices"));
    grid_devices = new mywxGrid(this, IDG_DEVICES);
    static_line_7 = new wxStaticLine(this, -1, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL);
    label_5 = new wxStaticText(this, -1, wxT(""));
    static_line_3 = new wxStaticLine(this, -1);
    static_line_4 = new wxStaticLine(this, -1);
    label_4 = new wxStaticText(this, -1, wxT("States"));
    grid_states = new mywxGrid(this, IDG_STATES);
    button_close = new wxButton(this, wxID_CLOSE, wxT("&Close"));
    static_line_5 = new wxStaticLine(this, -1);
    label_2 = new wxStaticText(this, -1, wxT("Channels"));
    grid_channels = new mywxGrid(this, IDG_CHANNELS);
    static_line_6 = new wxStaticLine(this, -1, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL);
    label_3 = new wxStaticText(this, -1, wxT("Values"));
    grid_values = new mywxGrid(this, IDG_VALUES);

	button_device_add = new wxButton(this, 7010, wxT("Add"));
    button_device_delete = new wxButton(this, 7011, wxT("Delete"));
	button_channel_add = new wxButton(this, 7020, wxT("Add"));
    button_channel_delete = new wxButton(this, 7021, wxT("Delete"));
	button_value_add = new wxButton(this, 7030, wxT("Add"));
    button_value_delete = new wxButton(this, 7031, wxT("Delete"));

    set_properties();
    do_layout();
	
	p_proj_item = NULL;
	p_proj_chn_item = NULL;

	grid_devices->set_list(&storage::list_projectoritem,new_projectoritem,NULL);
}


void LibraryDialog::set_properties()
{
    SetTitle(wxT("Library"));
    SetSize(wxSize(863, 682));
}


void LibraryDialog::do_layout()
{
    wxBoxSizer* sizer_1 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_4 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_7 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_6 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_8 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_3 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_5 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_9 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* sizer_10 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* sizer_11 = new wxBoxSizer(wxHORIZONTAL);
			
	sizer_5->Add(label_1, 0, 0, 0);
    sizer_5->Add(grid_devices, 1, wxEXPAND | wxFIXED_MINSIZE, 0);
	sizer_9->Add(button_device_add, 0, 0, 0);
	sizer_9->Add(button_device_delete, 0, 0, 0);
	sizer_5->Add(sizer_9, 0, wxALIGN_RIGHT, 0);
    sizer_3->Add(sizer_5, 1, wxEXPAND, 0);
    sizer_3->Add(static_line_7, 0, wxEXPAND, 0);
    sizer_3->Add(label_5, 0, wxEXPAND, 0);
	sizer_1->Add(sizer_3, 1, wxEXPAND, 0);
    sizer_1->Add(static_line_3, 0, wxEXPAND, 0);
    
	sizer_6->Add(label_2, 0, 0, 0);
    sizer_6->Add(grid_channels, 1, wxEXPAND | wxFIXED_MINSIZE, 0);
	sizer_10->Add(button_channel_add, 0, 0, 0);
	sizer_10->Add(button_channel_delete, 0, 0, 0);
	sizer_6->Add(sizer_10, 0, wxALIGN_RIGHT, 0);
    sizer_4->Add(sizer_6, 1, wxEXPAND, 0);
    sizer_4->Add(static_line_6, 0, wxEXPAND, 0);
    sizer_7->Add(label_3, 0, 0, 0);
    sizer_7->Add(grid_values, 1, wxEXPAND | wxFIXED_MINSIZE, 0);
	sizer_11->Add(button_value_add, 0, 0, 0);
	sizer_11->Add(button_value_delete, 0, 0, 0);
	sizer_7->Add(sizer_11, 0, wxALIGN_RIGHT, 0);
    sizer_4->Add(sizer_7, 1, wxEXPAND, 0);
    sizer_1->Add(sizer_4, 1, wxEXPAND, 0);
    sizer_1->Add(static_line_4, 0, wxEXPAND, 0);
    
	sizer_8->Add(label_4, 0, 0, 0);
    sizer_8->Add(grid_states, 1, wxEXPAND | wxFIXED_MINSIZE, 0);
    sizer_1->Add(sizer_8, 1, wxEXPAND, 0);
    sizer_1->Add(static_line_5, 0, wxEXPAND, 0);
    
	sizer_1->Add(button_close, 0, wxALIGN_RIGHT, 0);
    SetAutoLayout(true);
    SetSizer(sizer_1);
    Layout();
}

BEGIN_EVENT_TABLE(LibraryDialog, wxDialog)
	EVT_GRID_CELL_LEFT_CLICK(LibraryDialog::OnClick)
	EVT_GRID_CHANGE(LibraryDialog::OnChange)
	EVT_BUTTON(wxID_CLOSE, LibraryDialog::OnClose)
	EVT_BUTTON(7010, LibraryDialog::OnCmd)
	EVT_BUTTON(7011, LibraryDialog::OnCmd)
	EVT_BUTTON(7020, LibraryDialog::OnCmd)
	EVT_BUTTON(7021, LibraryDialog::OnCmd)
	EVT_BUTTON(7030, LibraryDialog::OnCmd)
	EVT_BUTTON(7031, LibraryDialog::OnCmd)
END_EVENT_TABLE()

void LibraryDialog::OnClose(wxCommandEvent& event)
{
	Close();
}

void LibraryDialog::OnCmd(wxCommandEvent& event)
{
	switch(event.GetId())
	{
		case 7010:
			grid_devices->append();
			break;
		case 7011:
			grid_devices->delete_selected();
			break;
		case 7020:
			grid_channels->append();
			break;
		case 7021:
			grid_channels->delete_selected();
			break;
		case 7030:
			grid_values->append();
			break;
		case 7031:
			grid_values->delete_selected();
			break;
		default:
			event.Skip();
	}
}

void LibraryDialog::OnClick(wxGridEvent& event)
{
	int row = event.GetRow();
	switch(event.GetId())
	{
	case IDG_DEVICES:
		p_proj_item = (projectoritem*) storage::storage_item_for_row(&storage::list_projectoritem,row);

		grid_channels->set_list(NULL);
		grid_states->set_list(NULL);
		grid_values->set_list(NULL);

		if(p_proj_item != NULL)
		{
			grid_channels->set_list(&p_proj_item->list_projectorchannelitem,new_projectorchannelitem,p_proj_item);
			grid_states->set_list(&p_proj_item->list_stateitem);
		}
		break;
	case IDG_CHANNELS:
		if(p_proj_item != NULL)
		{
			p_proj_chn_item = (projectorchannelitem*) storage::storage_item_for_row(&p_proj_item->list_projectorchannelitem,row);
			grid_values->set_list(NULL);
			
			if(p_proj_chn_item->get_type() == projectorchannelitem::T_VALUE)
				grid_values->set_list(&p_proj_chn_item->list_valueitem,new_valueitem,p_proj_chn_item);
		}
		break;
	}
	event.Skip();
}

void LibraryDialog::OnChange(mywxGridChangeEvent& event)
{
	if(event.GetId() == IDG_DEVICES)
	{
		if(event.IsDelete())
		{
			p_proj_item = NULL;
			grid_channels->set_list(NULL);
			grid_values->set_list(NULL);
			grid_states->set_list(NULL);
		}
	}
	else if(event.GetId() == IDG_CHANNELS)
	{
		if(grid_states->GetTable())
		{
			if(event.IsAppend())
				grid_states->GetTable()->AppendCols();
			else if(event.IsDelete())
				grid_states->GetTable()->DeleteCols(0);
		}
		
		if(event.IsDelete())
		{
			p_proj_chn_item = NULL;
			grid_values->set_list(NULL);
		}
	}
}
