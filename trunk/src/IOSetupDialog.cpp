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


#include "IOSetupDialog.h"
#include "storage.h"

IOSetupDialog::IOSetupDialog(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxDialog(parent, id, title, pos, size, wxDEFAULT_DIALOG_STYLE)
{
    list_ctrl_plugins = new wxListCtrl(this, wxID_VIEW_LIST, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxSUNKEN_BORDER);
    button_config = new wxButton(this, wxID_PROPERTIES, wxT("C&onfiguration"));
    button_close = new wxButton(this, wxID_CLOSE, wxT("&Close"));

    set_properties();
    do_layout();
	
	//Add Colums to List
	list_ctrl_plugins->InsertColumn(0,wxT("Name"),wxLIST_FORMAT_LEFT,100);
	list_ctrl_plugins->InsertColumn(1,wxT("Type"),wxLIST_FORMAT_LEFT,100);
	list_ctrl_plugins->InsertColumn(2,wxT("Status"),wxLIST_FORMAT_LEFT,150);
	
	//Add Items to List
	for(unsigned int i = 0;i < storage::list_io_plugins.size();i++)
	{
		list_ctrl_plugins->InsertItem(i,storage::list_io_plugins[i]->get_name());
		
		wxString str = wxT("");
		
		if(storage::list_io_plugins[i]->get_type() & T_PLUGIN_INPUT)
			str += wxT("Input");
		
		if(storage::list_io_plugins[i]->get_type() & T_PLUGIN_OUTPUT)
		{
			if(str != wxT(""))
				str += wxT("/");
			str += wxT("Output");
		}

		list_ctrl_plugins->SetItem(i,1,str);
		list_ctrl_plugins->SetItem(i,2,storage::list_io_plugins[i]->get_state());
	}

	timer = new wxTimer(this,wxID_REFRESH);
	timer->Start(500);
}

IOSetupDialog::~IOSetupDialog()
{
	timer->Stop();
	delete timer;
}


void IOSetupDialog::set_properties()
{
    SetTitle(wxT("IO Setup"));
    SetSize(wxSize(400, 400));
}

void IOSetupDialog::do_layout()
{
    wxBoxSizer* sizer_1 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_2 = new wxBoxSizer(wxHORIZONTAL);
    sizer_1->Add(list_ctrl_plugins, 1, wxEXPAND, 0);
    sizer_2->Add(button_config, 0, 0, 0);
    sizer_2->Add(button_close, 0, 0, 0);
    sizer_1->Add(sizer_2, 0, wxALIGN_RIGHT, 0);
    SetAutoLayout(true);
    SetSizer(sizer_1);
    Layout();
}

BEGIN_EVENT_TABLE(IOSetupDialog, wxDialog)
	EVT_BUTTON(wxID_CLOSE, IOSetupDialog::OnClose)
	EVT_BUTTON(wxID_PROPERTIES, IOSetupDialog::OnConfig)
	EVT_TIMER(wxID_REFRESH, IOSetupDialog::OnRefresh)
	EVT_LIST_ITEM_ACTIVATED(wxID_VIEW_LIST, IOSetupDialog::OnActivate)
END_EVENT_TABLE()

void IOSetupDialog::OnClose(wxCommandEvent& event)
{
	Close();
}

void IOSetupDialog::OnConfig(wxCommandEvent& event)
{
	int item = -1;

    item = list_ctrl_plugins->GetNextItem(item,wxLIST_NEXT_ALL,wxLIST_STATE_SELECTED);
    if ( item != -1 )

	storage::list_io_plugins[item]->config();
}

void IOSetupDialog::OnRefresh(wxTimerEvent& event)
{
	//Refresh the status msgs
	for(unsigned int i = 0;i < storage::list_io_plugins.size();i++)
	{
		list_ctrl_plugins->SetItem(i,2,storage::list_io_plugins[i]->get_state());
	}
}

void IOSetupDialog::OnActivate(wxListEvent& event)
{
	int item = event.GetIndex();
	storage::list_io_plugins[item]->config();
}

