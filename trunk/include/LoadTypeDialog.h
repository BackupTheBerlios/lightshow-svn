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

#ifndef LOADTYPEDIALOG_H
#define LOADTYPEDIALOG_H

enum
{
	IDR_DESK_LOAD = 500,
	IDR_DESK_KEEP,
	IDR_DESK_CLEAR,
	IDR_CHANNELS_LOAD,
	IDR_CHANNELS_KEEP,
	IDR_CHANNELS_CLEAR,
	IDR_FUNCTIONS_LOAD,
	IDR_FUNCTIONS_KEEP,
	IDR_FUNCTIONS_CLEAR
};

class LoadTypeDialog: public wxDialog {
public:
    LoadTypeDialog(wxWindow* parent, int id, const wxString& title, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=wxDEFAULT_DIALOG_STYLE);
	int GetClear() { return p_clear; };
	int GetLoad() { return p_load; };

private:
    void set_properties();
    void do_layout();

	int p_clear;
	int p_load;

protected:
    wxStaticText* label_4;
    wxStaticText* label_5;
    wxRadioButton* radio_btn_desk_load;
    wxRadioButton* radio_btn_desk_keep;
    wxRadioButton* radio_btn_desk_clear;
    wxStaticText* label_6;
    wxRadioButton* radio_btn_channels_load;
    wxRadioButton* radio_btn_channels_keep;
    wxRadioButton* radio_btn_channels_clear;
    wxStaticText* label_7;
    wxRadioButton* radio_btn_functions_load;
    wxRadioButton* radio_btn_functions_keep;
    wxRadioButton* radio_btn_functions_clear;
    wxButton* button_close;
    wxButton* button_ok;

    DECLARE_EVENT_TABLE();

    void OnDeskLoad(wxCommandEvent &event);
    void OnDeskKeep(wxCommandEvent &event);
    void OnDeskClear(wxCommandEvent &event);
    void OnChannelsLoad(wxCommandEvent &event);
    void OnChannelsKeep(wxCommandEvent &event);
    void OnChannelsClear(wxCommandEvent &event);
    void OnFunctionsLoad(wxCommandEvent &event);
    void OnFunctionsKeep(wxCommandEvent &event);
    void OnFunctionsClear(wxCommandEvent &event);
    void OnClose(wxCommandEvent &event);
    void OnOK(wxCommandEvent &event);
};

#endif // LOADTYPEDIALOG_H
