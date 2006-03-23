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

#ifndef _OUTPUTDRAWWINDOW_H_
#define _OUTPUTDRAWWINDOW_H_

#include "prec.h"

class OutputDrawWindow : public wxScrolledWindow
{
public:
	OutputDrawWindow(wxWindow* parent, wxWindowID id);
	 ~OutputDrawWindow();

	void RefreshOutput();

protected:
	void DrawOutput(wxDC& dc);
	void DrawInitialOutput();
	
	void OnPaint(wxPaintEvent& event);
	void OnSize(wxSizeEvent& event);
	void OnEraseBackground(wxEraseEvent& event);
	void OnKeyDown(wxKeyEvent& event);
	void OnKeyUp(wxKeyEvent& event);

	DECLARE_EVENT_TABLE()

private:
	wxBitmap p_background;
	int p_page;
	bool p_refresh_pending;
};


#endif	//_OUTPUTDRAWWINDOW_H_
