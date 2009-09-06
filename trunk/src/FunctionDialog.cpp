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

#include "FunctionDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



FunctionDialog::FunctionDialog(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxDialog(parent, id, title, wxPoint(10,10), size, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER)
{
	p_fitem = NULL;
	storage::setuping = true;

	//first create these to get correct Z-order
	staticbox_1 = new wxStaticBoxSizer(wxHORIZONTAL, this, wxT("Value/Position"));
	staticbox_2 = new wxStaticBoxSizer(wxHORIZONTAL, this, wxT("Properties"));
	
    grid_data = new mywxGrid(this, wxID_MYGRID);
    text_channel_name = new wxTextCtrl(this, -1, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    button_close = new wxButton(this, wxID_CLOSE, wxT("&Close"));
    slider_pos = new wxSlider(this, wxID_MYSLIDER, 255, 0, 255, wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL);
    static_line_3 = new wxStaticLine(this, -1, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL);
    select_pos = new PosSelectWidget(this, -1);
    label_2 = new wxStaticText(this, -1, wxT(""));
    grid_properties = new mywxGrid(this, -1);
    static_line_2 = new wxStaticLine(this, -1);
	
	button_add = new wxButton(this, 7040, wxT("Add"));
    button_delete = new wxButton(this, 7041, wxT("Delete"));

    set_properties();
    do_layout();
}

FunctionDialog::~FunctionDialog()
{
	storage::setuping = false;
	if(p_fitem)
		p_fitem->disable_preview();
}

void FunctionDialog::set_properties()
{
    SetTitle(wxT("Function Setup"));
	SetSize(wxSize(900, 700));
    select_pos->SetSize(wxSize(200, 200));
    grid_properties->SetSize(wxSize(300, 200));
}


void FunctionDialog::do_layout()
{
    wxBoxSizer* sizer_1 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_3 = new wxBoxSizer(wxHORIZONTAL);
	
    sizer_1->Add(grid_data, 1, wxEXPAND | wxFIXED_MINSIZE, 0);
	
	sizer_3->Add(text_channel_name, 1, wxEXPAND, 0);
	sizer_3->Add(button_add, 0, 0, 0);
	sizer_3->Add(button_delete, 0, 0, 0);
    sizer_1->Add(sizer_3, 0, wxEXPAND, 0);

    staticbox_1->Add(slider_pos, 0, wxEXPAND, 0);
    staticbox_1->Add(static_line_3, 0, wxEXPAND, 0);
    staticbox_1->Add(select_pos, 0, wxEXPAND, 0);
    
	sizer_2->Add(staticbox_1, 0, wxEXPAND, 0);
    sizer_2->Add(label_2, 1, wxEXPAND, 0);
    
	staticbox_2->Add(grid_properties, 1, wxEXPAND | wxFIXED_MINSIZE, 0);
    sizer_2->Add(staticbox_2, 1, wxEXPAND, 0);
    
	sizer_1->Add(sizer_2, 0, wxEXPAND, 0);
    sizer_1->Add(static_line_2, 0, wxEXPAND, 0);
    sizer_1->Add(button_close, 0, wxALIGN_RIGHT, 2);
    SetAutoLayout(true);
    SetSizer(sizer_1);
    Layout();
}

BEGIN_EVENT_TABLE(FunctionDialog, wxDialog)
	EVT_BUTTON(wxID_CLOSE, FunctionDialog::OnClose)
	EVT_GRID_CMD_SELECT_CELL(wxID_MYGRID, FunctionDialog::OnGridSelect)
	EVT_COMMAND_SCROLL(wxID_MYSLIDER, FunctionDialog::OnScroll)
	EVT_BUTTON(7040, FunctionDialog::OnCmd)
	EVT_BUTTON(7041, FunctionDialog::OnCmd)
END_EVENT_TABLE()

void FunctionDialog::OnClose(wxCommandEvent& event)
{
	Close();
}

void FunctionDialog::OnCmd(wxCommandEvent& event)
{
	switch(event.GetId())
	{
		case 7040:
			grid_data->append();
			break;
		case 7041:
			grid_data->delete_selected();
			break;
		default:
			event.Skip();
	}
}

void FunctionDialog::OnGridSelect(wxGridEvent& event)
{
	text_channel_name->Clear();
	text_channel_name->AppendText(storage::channel_name_long(event.GetCol()+1));
	
	if(p_fitem) p_fitem->enable_preview(event.GetRow());
	
	select_pos->SetItem(p_fitem, event.GetCol()+1, event.GetRow());
	
	//let wxGrid do the rest
	event.Skip();
}

void FunctionDialog::OnScroll(wxScrollEvent& event)
{
	if(p_fitem)
	{
		dataitem * ditem = p_fitem->get_dataitem(grid_data->GetGridCursorRow());
		if(ditem)
		{
			ditem->set_value(grid_data->GetGridCursorCol(),255-event.GetPosition());
		}

		Refresh();
	}
}

void FunctionDialog::SetItem(deskitem* item, int page)
{
	p_fitem = storage::functionitem_for_deskitem(item,page,true);
	if(p_fitem == NULL)
	{
		p_fitem = new functionitem(item->get_button_id(),page);
	}

	p_fitem->deactivate(true);
	
	grid_data->set_list(&p_fitem->list_dataitem,new_dataitem,p_fitem);
	grid_properties->set_item(p_fitem);
}
