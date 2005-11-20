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

//
// File: OutputDrawWindow.cpp
// Created by: User <Email>
// Created on: Sun Sep  5 17:01:44 2004
//
#include "OutputDrawWindow.h"
#include "storage.h"

OutputDrawWindow::OutputDrawWindow(wxWindow* parent, wxWindowID id) : wxScrolledWindow(parent, id)
{	
	p_refresh_pending = false;
}

OutputDrawWindow::~OutputDrawWindow()
{
}

BEGIN_EVENT_TABLE(OutputDrawWindow, wxScrolledWindow)
	EVT_PAINT(OutputDrawWindow::OnPaint)
	EVT_SIZE(OutputDrawWindow::OnSize)
	EVT_ERASE_BACKGROUND(OutputDrawWindow::OnEraseBackground)
END_EVENT_TABLE()

void OutputDrawWindow::OnPaint(wxPaintEvent& event)
{
#ifdef __WXMSW__
	wxBufferedPaintDC dc(this);
#else
	wxPaintDC dc(this);
#endif
	
	DoPrepareDC(dc);
	DrawOutput(dc);
	
	p_refresh_pending = false;
}

void OutputDrawWindow::RefreshOutput()
{
	if(!p_refresh_pending)
	{
		p_refresh_pending = true;
		Refresh();
	}
}


void OutputDrawWindow::OnEraseBackground(wxEraseEvent& event)
{
#ifdef __WXMSW__
	event.Skip(false);
	//do noting -> windows non flicker
#endif
}

void OutputDrawWindow::OnSize(wxSizeEvent& event)
{
	int winh, winw;
	GetClientSize(&winw,&winh);	

	int page = ((winw - 30) / 25) + 1;
	if(page) // prevent null division at initial sizing
	{
		int x,y;
		GetViewStart(&x,&y);
		SetScrollbars(0, winh, 0, DMX_CHNLS / page + 1, 0, y);
	}

	Refresh();

	event.Skip();
}

void OutputDrawWindow::DrawOutput(wxDC& dc)
{
	dc.BeginDrawing();

//	dc.SetBackground(*wxBLACK_BRUSH);
	dc.SetPen(*wxGREY_PEN);
	dc.SetTextForeground(*wxWHITE);
	dc.SetBrush(*wxBLACK_BRUSH);
//	dc.Clear();
	
	int winh, winw;

	//Because Clear isnt working on full area
	GetVirtualSize(&winw,&winh);
	dc.DrawRectangle(-1,-1,winw+2,winh+2);

	GetClientSize(&winw,&winh);

	int page = ((winw - 30) / 25) + 1;

	int x = 0;
	int y = 0;

	for(int i = 0;i < DMX_CHNLS;i++)
	{
		y = i / page * winh;
		x = (i%page * 25) + 5;

		//DMX data bar
		dc.SetBrush(*wxBLUE_BRUSH);

		int height = (int) (((winh - 25) / 255.0) * storage::DMX[i]);
		if(height != 0)
			dc.DrawRectangle(x, y + winh - 20 - height, 20, height);

		//Channel text      
		wxString channel = storage::int_to_str(i+1);

		if ((i % 2) == 0)
		{
			dc.DrawText(channel, x - 2, y + winh - 20);
		}
		else
		{
			dc.DrawText(channel,x - 2, y + winh - 15);
		}
	}

	dc.EndDrawing();
}
