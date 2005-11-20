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

#ifndef LIBRARYDIALOG_H
#define LIBRARYDIALOG_H

#include "prec.h"

#include "mywxGrid.h"
#include "storage.h"

enum
{
	IDG_DEVICES = 500,
	IDG_CHANNELS,
	IDG_VALUES,
	IDG_STATES
};

class LibraryDialog: public wxDialog {
public:
    LibraryDialog(wxWindow* parent, int id, const wxString& title, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=wxDEFAULT_DIALOG_STYLE);

private:
    void set_properties();
    void do_layout();

	void OnClick(wxGridEvent& event);
	void OnChange(mywxGridChangeEvent& event);
	void OnClose(wxCommandEvent& event);
	DECLARE_EVENT_TABLE()

	projectoritem* p_proj_item;
	projectorchannelitem* p_proj_chn_item;

protected:
    wxStaticText* label_1;
    mywxGrid* grid_devices;
    wxStaticLine* static_line_7;
    wxStaticText* label_5;
    wxStaticLine* static_line_3;
    wxStaticLine* static_line_4;
    wxStaticText* label_4;
    mywxGrid* grid_states;
    wxButton* button_close;
    wxStaticLine* static_line_5;
    wxStaticText* label_2;
    mywxGrid* grid_channels;
    wxStaticLine* static_line_6;
    wxStaticText* label_3;
    mywxGrid* grid_values;
};


#endif // LIBRARYDIALOG_H
