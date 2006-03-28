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


#include "ConfigDialog.h"
#include <wx/config.h>


ConfigDialog::ConfigDialog(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxDialog(parent, id, title, pos, size, wxDEFAULT_DIALOG_STYLE)
{
#ifdef __WXMSW__
    label_1 = new wxStaticText(this, -1, wxT("\nThe MiniDMX Adapter is connected to:\n"));
    choice_1 = new wxChoice(this, -1);
#else
    label_1 = new wxStaticText(this, -1, wxT("\nThe MiniDMX Adapter is connected to:\n(for example '/dev/ttyS1')\n"));
    choice_1 = new wxTextCtrl(this, -1);
#endif
    button_1 = new wxButton(this, wxID_CLOSE, wxT("&Close"));

    set_properties();
    do_layout();
}

ConfigDialog::~ConfigDialog()
{
	wxConfig config(wxT("LightShowPlugins"));

#ifdef __WXMSW__
	config.Write(wxT("mini_dmx_plugin/serial_port"),choice_1->GetStringSelection());	
#else
	config.Write(wxT("mini_dmx_plugin/serial_port"),choice_1->GetValue());	
#endif
}

void ConfigDialog::set_properties()
{
	SetTitle(wxT("MiniDMX Configuration"));
	wxConfig config(wxT("LightShowPlugins"));
	
#ifdef __WXMSW__
	DWORD cbNeeded = 0;
	DWORD dwPorts = 0;
	EnumPorts(NULL, 1, NULL, 0, &cbNeeded, &dwPorts);
	
	BYTE* pPorts = (BYTE*) malloc(cbNeeded);

	BOOL bSuccess = EnumPorts(NULL, 1, pPorts, cbNeeded, &cbNeeded, &dwPorts);
	if (bSuccess)
	{
		PORT_INFO_1* pPortInfo = (PORT_INFO_1*) pPorts;
		for (DWORD i=0; i<dwPorts; i++)
		{
			wxString pn(pPortInfo->pName);
			if(pn.StartsWith(wxT("COM")))
				choice_1->Append(pn.BeforeFirst(wxT(':')));
			
			pPortInfo++;
		}
	}

	free(pPorts);

	choice_1->SetStringSelection(config.Read(wxT("mini_dmx_plugin/serial_port")));
#else
	choice_1->SetValue(config.Read(wxT("mini_dmx_plugin/serial_port")));	
#endif
}


void ConfigDialog::do_layout()
{
    wxBoxSizer* sizer_1 = new wxBoxSizer(wxVERTICAL);
    sizer_1->Add(label_1, 1, wxEXPAND|wxFIXED_MINSIZE, 10);
    sizer_1->Add(choice_1, 0, wxALIGN_CENTER_HORIZONTAL|wxFIXED_MINSIZE, 0);
    sizer_1->Add(button_1, 0, wxALIGN_RIGHT|wxFIXED_MINSIZE, 0);
    SetAutoLayout(true);
    SetSizer(sizer_1);
	Fit();
    Layout();
}

BEGIN_EVENT_TABLE(ConfigDialog, wxDialog)
	EVT_BUTTON(wxID_CLOSE, ConfigDialog::OnClose)
END_EVENT_TABLE()

void ConfigDialog::OnClose(wxCommandEvent& event)
{
	Close();
}
