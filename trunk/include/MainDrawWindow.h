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

#ifndef _MAINDRAWWINDOW_H_
#define _MAINDRAWWINDOW_H_

#include "prec.h"
#include "storage.h"

enum
{
	STATE_DESK,
	STATE_DESK_SETUP,
	STATE_FUNCTION_SETUP
};

enum
{
	DESKSETUP_ADD_FKT,
	DESKSETUP_ADD_FADER,
	DESKSETUP_ADD_PAGE,
	DESKSETUP_ADD_GROUP,
	DESKSETUP_MOVE,
	DESKSETUP_CHANGE_NUM,
	DESKSETUP_DELETE,
};

class MainDrawWindow : public wxWindow
{

public:
	MainDrawWindow(wxWindow* parent, wxWindowID id);
	 ~MainDrawWindow();

	void OnMainToolBar(wxCommandEvent& event);
	void OnDeskSetupToolBar(wxCommandEvent& event);

	void RefreshDesk(bool force_common = false);

protected:
	void DrawDesk(wxDC& dc);
	void DrawCommon();
	
	void SetStatusText(wxString text);
	
	void OnPaint(wxPaintEvent& event);
	void OnSize(wxSizeEvent& event);
	void OnKeyDown(wxKeyEvent& event);
	void OnKeyUp(wxKeyEvent& event);
	void OnMouseEvent(wxMouseEvent& event);
	void OnEraseBackground(wxEraseEvent& event);
	
	DECLARE_EVENT_TABLE()	
		
	int p_state;
	int p_desksetup_state;
	deskitem* p_selected_item;
	deskitem* p_hover_item;
	functionitem* p_floating_item;
	faderitem* p_floating_fader;
	int p_change_num;
	
	wxBitmap p_draw_common;

	wxBrush p_page_brush;
	wxBrush p_function_brush;
	wxBrush p_function_otherpage_brush;
	wxBrush p_function_pb_brush;
	wxBrush p_function_pb_otherpage_brush;
	wxBrush p_group_brush;
	wxBrush p_fader_brush;
	wxBrush p_fader_button_brush;
	wxBrush p_fader_active_brush;
	
	wxBrush p_led_on_brush;
	wxBrush p_led_off_brush;
	
	wxPen p_border_pen;
	wxPen p_border_highlite_pen;
	
	wxBrush p_background_brush;
	wxColor p_text_color;
	wxColor p_text_infader_color;
	wxFont* p_text_font;
	
	wxCursor* p_delete_cursor;
	wxCursor* p_move_cursor;
	wxCursor* p_copy_cursor;
	wxCursor* p_hand_cursor;

};


#endif	//_MAINDRAWWINDOW_H_
