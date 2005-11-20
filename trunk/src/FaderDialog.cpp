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

#include "FaderDialog.h"


FaderDialog::FaderDialog(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxDialog(parent, id, title, pos, size, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxTHICK_FRAME)
{
    grid_fader = new mywxGrid(this, -1);
    button_close = new wxButton(this, wxID_CLOSE, wxT("&Close"));

    set_properties();
    do_layout();
}


void FaderDialog::set_properties()
{
    SetTitle(wxT("FaderSetup"));
    SetSize(wxSize(400, 400));
}


void FaderDialog::do_layout()
{
    wxBoxSizer* sizer_1 = new wxBoxSizer(wxVERTICAL);
    sizer_1->Add(grid_fader, 1, wxEXPAND, 0);
    sizer_1->Add(button_close, 0, wxALIGN_RIGHT, 0);
    SetAutoLayout(true);
    SetSizer(sizer_1);
    Layout();
}

BEGIN_EVENT_TABLE(FaderDialog, wxDialog)
	EVT_BUTTON(wxID_CLOSE, FaderDialog::OnClose)
END_EVENT_TABLE()

void FaderDialog::OnClose(wxCommandEvent& event)
{
	Close();
}

void FaderDialog::SetItem(deskitem* item, int page)
{
	faderitem* fitem = storage::faderitem_for_deskitem(item,page,true);
	if(fitem == NULL)
	{
		fitem = new faderitem(item->get_fader_id(),page);
	}
	
	grid_fader->set_item(fitem);
}
