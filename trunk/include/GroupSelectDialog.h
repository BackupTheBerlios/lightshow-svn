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

#ifndef GROUPSELECTDIALOG_H
#define GROUPSELECTDIALOG_H

#include "prec.h"

#include "mywxGrid.h"

class GroupSelectDialog: public wxDialog {
public:
    GroupSelectDialog(wxWindow* parent, int id, const wxString& title, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=wxDEFAULT_DIALOG_STYLE);
	void SetItem(deskitem* item, int page);

private:
    void set_properties();
    void do_layout();
	
	void OnClose(wxCommandEvent& event);
	void OnAdd(wxCommandEvent& event);
	void OnDelete(wxCommandEvent& event);
	DECLARE_EVENT_TABLE()

protected:
    mywxGrid* grid_groupselect;
    wxButton* button_close;
    wxButton* button_add;
    wxButton* button_delete;
};


#endif // GROUPSELECTDIALOG_H
