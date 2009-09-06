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

#include "OutputDrawWindow.h"
#include "storage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


OutputDrawWindow::OutputDrawWindow(wxWindow* parent, wxWindowID id) : wxScrolledWindow(parent, id)
{	
	p_refresh_pending = 0;
	p_page = 1;
}

OutputDrawWindow::~OutputDrawWindow()
{
}

BEGIN_EVENT_TABLE(OutputDrawWindow, wxScrolledWindow)
	EVT_PAINT(OutputDrawWindow::OnPaint)
	EVT_SIZE(OutputDrawWindow::OnSize)
	EVT_ERASE_BACKGROUND(OutputDrawWindow::OnEraseBackground)
	EVT_KEY_DOWN(OutputDrawWindow::OnKeyDown)
	EVT_KEY_UP(OutputDrawWindow::OnKeyUp)
END_EVENT_TABLE()

void OutputDrawWindow::OnPaint(wxPaintEvent& event)
{
	p_refresh_pending = 0;

#ifdef __WXGTK__
	wxPaintDC dc(this);
#else
	wxBufferedPaintDC dc(this);
#endif

	DoPrepareDC(dc);
	DrawOutput(dc);
}

void OutputDrawWindow::RefreshOutput()
{
	if(p_refresh_pending++ == 2)
		Refresh();
}

void OutputDrawWindow::OnEraseBackground(wxEraseEvent& event)
{
	//do noting -> no flicker
}

void OutputDrawWindow::OnKeyDown(wxKeyEvent& event)
{
	event.ResumePropagation(2);
	event.Skip(); //MainFrame Handles This
}

void OutputDrawWindow::OnKeyUp(wxKeyEvent& event)
{
	event.ResumePropagation(2);
	event.Skip(); //MainFrame Handles This
}

void OutputDrawWindow::OnSize(wxSizeEvent& event)
{
	int winh, winw;
	GetClientSize(&winw,&winh);
	
	//prevent error at initial sizeing
	if((winw <= 0) || (winh <= 0))
		return;

	p_page = ((winw - 30) / 25) + 1;

	int x,y;
	GetViewStart(&x,&y);
	SetScrollbars(0, winh, 0, DMX_CHNLS / p_page + 1, 0, y);

	DrawInitialOutput();
	RefreshOutput();

	event.Skip();
}

void OutputDrawWindow::DrawInitialOutput()
{
	int winh, winw;

	GetClientSize(&winw,&winh);

	wxBitmap memory_dc_bitmap(winw, winh * (DMX_CHNLS / p_page + 1));
	wxMemoryDC memory_dc;
	
	memory_dc.SelectObject(memory_dc_bitmap);
	
	memory_dc.SetBackground(*wxBLACK_BRUSH);
	memory_dc.SetTextForeground(*wxWHITE);
	memory_dc.Clear();
	
	
	int x = 0;
	int y = 0;
	
	for(int i = 0;i < DMX_CHNLS;i++)
	{
		y = i / p_page * winh;
		x = (i % p_page * 25) + 5;
		
		//Channel text      
		wxString channel = storage::int_to_str(i+1);
		
		if ((i % 2) == 0)
			memory_dc.DrawText(channel, x - 2, y + winh - 20);
		else
			memory_dc.DrawText(channel,x - 2, y + winh - 15);
	}
	
	memory_dc.SelectObject(wxNullBitmap);
	
	p_background = memory_dc_bitmap;
	
}

void OutputDrawWindow::DrawOutput(wxDC& dc)
{	
	int winh, winw;
	GetClientSize(&winw,&winh);
	
	dc.DrawBitmap(p_background, 0, 0);

	dc.SetPen(*wxGREY_PEN);
	dc.SetBrush(*wxBLUE_BRUSH);

	int x = 0;
	int y = 0;

	for(int i = 0;i < DMX_CHNLS;i++)
	{
		y = i / p_page * winh;
		x = (i % p_page * 25) + 5;

		//DMX data bar
		int height = (int) (((winh - 25) / 255.0) * storage::DMX[i]);
		if(height != 0)
			dc.DrawRectangle(x, y + winh - 20 - height, 20, height);
	}
}
