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

#ifndef _MYWXGRIDCELLEDITORS_H_
#define _MYWXGRIDCELLEDITORS_H_

#include <wx/grid.h>

/*****************************************************************************
*  These Editor Classes change the value of all selected Cells and
*  are using the 'Space' Key to begin the editing
******************************************************************************/

class mywxGridCellChoiceEditor : public wxGridCellChoiceEditor
{
public:
	mywxGridCellChoiceEditor();
	
	virtual bool IsAcceptedKey(wxKeyEvent& event);
	virtual void BeginEdit(int row, int col, wxGrid* grid);
	virtual bool EndEdit(int row, int col, wxGrid* grid);
	
private:
	wxGridCellCoordsArray p_sel_single;
	wxGridCellCoordsArray p_sel_topleft;
	wxGridCellCoordsArray p_sel_bottomright;
};

class mywxGridCellTextEditor : public wxGridCellTextEditor
{
public:
	virtual void Create(wxWindow* parent, wxWindowID id, wxEvtHandler* evtHandler);

	virtual bool IsAcceptedKey(wxKeyEvent& event);
	virtual void StartingKey(wxKeyEvent& event);
	virtual void BeginEdit(int row, int col, wxGrid* grid);
	virtual bool EndEdit(int row, int col, wxGrid* grid);

private:
	wxGridCellCoordsArray p_sel_single;
	wxGridCellCoordsArray p_sel_topleft;
	wxGridCellCoordsArray p_sel_bottomright;
};

#endif //_MYWXGRIDCELLEDITORS_H_
