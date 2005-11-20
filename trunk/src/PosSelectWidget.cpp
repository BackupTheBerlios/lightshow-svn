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

#include "PosSelectWidget.h"

PosSelectWidget::PosSelectWidget(wxWindow* parent, wxWindowID id) : wxWindow(parent, id)
{
	p_fitem = NULL;
}

PosSelectWidget::~PosSelectWidget()
{
}

BEGIN_EVENT_TABLE(PosSelectWidget, wxWindow)
	EVT_PAINT(PosSelectWidget::OnPaint)
	EVT_MOUSE_EVENTS(PosSelectWidget::OnMouseEvent)
END_EVENT_TABLE()

void PosSelectWidget::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);
	Draw(dc);
}

void PosSelectWidget::OnMouseEvent(wxMouseEvent& event)
{
	if(event.ButtonUp())
		GetParent()->Refresh();
	else if(event.Dragging() || event.Button(wxMOUSE_BTN_ANY))
	{
		if(p_fitem)
		{
			int winh, winw;
			GetClientSize(&winw,&winh);

			wxClientDC dc(this);
			wxPoint pos = event.GetLogicalPosition(dc);
			
			dataitem * ditem = p_fitem->get_dataitem(p_cur_row);
			if(ditem)
			{
				if((winw-14) != 0)
				{
					int x = (int)(255 - (pos.x - 7)/(double)(winw-14) * 255);
					if(x >= 0 && x <= 255)
						ditem->set_value(p_pan_channel,x);
				}
				if((winh-14) != 0)
				{
					int y = (int)(255 - (pos.y - 7)/(double)(winw-14) * 255);
					if(y >= 0 && y <= 255)
						ditem->set_value(p_tilt_channel,y);
				}
			}

			Refresh();
		}
	}
}

void PosSelectWidget::SetItem(functionitem* fitem, int channel, int row)
{
	p_fitem = fitem;
	p_cur_row = row;
	
	p_pan_channel = -1;
	p_tilt_channel = -1;
	
	if(!p_fitem) return;
		
	channelitem* citem = storage::channelitem_for_channel(channel);
	if(citem)
	{
		projectoritem* pitem = storage::projectoritem_for_channelitem(citem);
		if(pitem)
		{
			for(int i = 1; i <= pitem->get_num_channels();i++)
			{
				projectorchannelitem* pcitem = storage::projectorchannelitem_for_subchannel(pitem, i);
				if(pcitem)
				{
					if(pcitem->get_type() == projectorchannelitem::T_PAN)
						p_pan_channel = citem->get_start_channel() + i - 2;
					else if(pcitem->get_type() == projectorchannelitem::T_TILT)
						p_tilt_channel = citem->get_start_channel() + i - 2;
				}
			}
		}
	}
	
	if(p_pan_channel == -1 || p_tilt_channel == -1)
	{
		p_fitem = NULL;
	}

	Refresh();
}

void PosSelectWidget::Draw(wxDC& dc)
{
	dc.BeginDrawing();

	dc.SetBackground(*wxWHITE_BRUSH);
	dc.Clear();

	int winh, winw;
	GetClientSize(&winw,&winh);
	
	if(p_fitem)
	{
		for(int i = 0; i < p_fitem->get_num_rows();i++)
		{
			for(double d = 0.0; d <= 0.9; d += 0.1)
			{
				int size = POINT_SMALL;
				
				if(d == 0.0)
				{
					size = POINT_LARGE;
					if(i == p_cur_row)
					{
						dc.SetPen(*wxRED_PEN);
						dc.SetBrush(*wxRED_BRUSH);
					}
					else
					{
						dc.SetPen(*wxBLACK_PEN);
						dc.SetBrush(*wxBLACK_BRUSH);
					}
				}
				else
				{
					dc.SetPen(*wxGREY_PEN);
					dc.SetBrush(*wxGREY_BRUSH);
				}
				
				int x = (int)((255 - p_fitem->get_value(p_pan_channel,i+d))/255.0 * (winw - 14) + 7);
				int y = (int)((255 - p_fitem->get_value(p_tilt_channel,i+d))/255.0 * (winh - 14) + 7);
				
				dc.DrawCircle(x,y,size);
			}
		}
	}	
	
	dc.EndDrawing();
}
