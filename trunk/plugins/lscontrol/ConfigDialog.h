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

#include <wx/wx.h>
#include <wx/image.h>

#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

class ConfigDialog: public wxDialog {
public:

    ConfigDialog(wxWindow* parent, int id, const wxString& title, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=wxDEFAULT_DIALOG_STYLE);
	~ConfigDialog();

private:
    void set_properties();
    void do_layout();

	void OnClose(wxCommandEvent& event);
	DECLARE_EVENT_TABLE()


protected:
    wxStaticText* label_1;
    wxTextCtrl* choice_1;
    wxButton* button_1;
};


#endif // CONFIGDIALOG_H
