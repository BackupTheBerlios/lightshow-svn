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

#ifndef _POSSELECTWIDGET_H_
#define _POSSELECTWIDGET_H_

#include "prec.h"
#include "storage.h"

#define POINT_SMALL 2
#define POINT_LARGE 5

class PosSelectWidget : public wxWindow
{

public:
	PosSelectWidget(wxWindow* parent, wxWindowID id);
	 ~PosSelectWidget();

	void SetItem(functionitem* fitem, int channel, int row);


protected:
	void Draw(wxDC& dc);
	
	void OnPaint(wxPaintEvent& event);
	void OnMouseEvent(wxMouseEvent& event);

	DECLARE_EVENT_TABLE()

private:
	functionitem* p_fitem;
	int p_pan_channel;
	int p_tilt_channel;
	int p_cur_row;
};


#endif	//_POSSELECTWIDGET_H_
