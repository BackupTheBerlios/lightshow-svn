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

#ifndef FUNCTIONDIALOG_H
#define FUNCTIONDIALOG_H

#include "prec.h"

#include "PosSelectWidget.h"
#include "mywxGrid.h"
#include "storage.h"

class FunctionDialog: public wxDialog {
public:
    FunctionDialog(wxWindow* parent, int id, const wxString& title, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=wxDEFAULT_DIALOG_STYLE);
	virtual ~FunctionDialog();
	void SetItem(deskitem* item, int page);

private:
    void set_properties();
    void do_layout();

	enum
	{
		wxID_MYGRID = 5300,
		wxID_MYSLIDER
	};

	void OnClose(wxCommandEvent& event);
	void OnGridSelect(wxGridEvent& event);
	void OnScroll(wxScrollEvent& event);
	void OnCmd(wxCommandEvent& event);


	DECLARE_EVENT_TABLE()

protected:
	wxStaticBoxSizer* staticbox_1;
	wxStaticBoxSizer* staticbox_2;
    mywxGrid* grid_data;
    wxTextCtrl* text_channel_name;
    wxButton* button_close;
    wxSlider* slider_pos;
    PosSelectWidget* select_pos;
    wxStaticText* label_2;
    mywxGrid* grid_properties;
    wxStaticLine* static_line_2;
    wxStaticLine* static_line_3;
	wxButton* button_add;
    wxButton* button_delete;


	functionitem* p_fitem;
};


#endif // FUNCTIONDIALOG_H
