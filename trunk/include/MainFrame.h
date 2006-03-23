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

#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "prec.h"

#include "MainDrawWindow.h"
#include "OutputDrawWindow.h"
#include "MainToolBar.h"
#include "DeskSetupToolBar.h"

//---- Event Class -------------------------------------
DECLARE_EVENT_TYPE(mywxMAINFRAME_REFRESH_EVENT, 7778)

#define EVT_MF_REFRESH(fn) \
DECLARE_EVENT_TABLE_ENTRY( \
						   mywxMAINFRAME_REFRESH_EVENT, wxID_ANY, wxID_ANY, \
						   (wxObjectEventFunction)(wxEventFunction)&fn, \
						   (wxObject *) NULL \
						   ),

class MainFrameRefreshEvent : public wxCommandEvent 
{
public:
	enum
	{
		DESK,
		OUTPUT
	};
	
    MainFrameRefreshEvent(int id = 0, int what = OUTPUT);
    MainFrameRefreshEvent(const MainFrameRefreshEvent &event);
	
    virtual wxEvent *Clone() const {return new MainFrameRefreshEvent(*this);};
	
    DECLARE_DYNAMIC_CLASS(MainFrameRefreshEvent)
		
	int GetWhat() const { return p_what; };
	void SetForceCommon(bool force_common) { p_force_common = force_common; };
	bool GetForceCommon() const { return p_force_common; };

private:
	int p_what;
	bool p_force_common;
};
//---- Event Class END-----------------------------------


enum
{
	IDS_OUTPUTDRAW_SCROLLBAR = 300
};

class MainFrame: public wxFrame {
public:
    MainFrame(wxWindow* parent, int id, const wxString& title, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=wxDEFAULT_FRAME_STYLE);

	void ShowDeskSetupToolBar(bool show = true);
	void SetStatusText(wxString& text);

private:
	void set_properties();
	void do_layout();

	void OnMainToolBar(wxCommandEvent& event);
	void OnDeskSetupToolBar(wxCommandEvent& event);
	
	void RefreshEvent(MainFrameRefreshEvent& event);
	
	DECLARE_EVENT_TABLE()

protected:
	void OnKeyDown(wxKeyEvent& event);
	void OnKeyUp(wxKeyEvent& event);

	MainDrawWindow* main_draw_window;
	OutputDrawWindow* output_draw_window;
	wxSplitterWindow* window_1;
	wxBoxSizer* sizer_1;
	
	MainToolBar* main_tool_bar;
	DeskSetupToolBar* desk_setup_tool_bar;

	wxStatusBar* status_bar;
	
	int p_prev_size;
};


#endif // MAINFRAME_H
