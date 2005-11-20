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


#ifndef IOSETUPDIALOG_H
#define IOSETUPDIALOG_H

#include "prec.h"

class IOSetupDialog: public wxDialog {
public:
    IOSetupDialog(wxWindow* parent, int id, const wxString& title, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=wxDEFAULT_DIALOG_STYLE);
	~IOSetupDialog();

private:
    void set_properties();
    void do_layout();

	DECLARE_EVENT_TABLE()

	void OnClose(wxCommandEvent& event);
	void OnConfig(wxCommandEvent& event);
	void OnRefresh(wxTimerEvent& event);
	void OnActivate(wxListEvent& event);

protected:
    wxListCtrl* list_ctrl_plugins;
    wxButton* button_config;
    wxButton* button_close;
	wxTimer* timer;
};


#endif // IOSETUPDIALOG_H
