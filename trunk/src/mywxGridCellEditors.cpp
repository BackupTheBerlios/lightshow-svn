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

#include "prec.h"
#include "mywxGridCellEditors.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//---------------------------------------------------------
mywxGridCellChoiceEditor::mywxGridCellChoiceEditor() : 
									wxGridCellChoiceEditor(0,NULL,true)
{
}

bool mywxGridCellChoiceEditor::IsAcceptedKey(wxKeyEvent& event)
{
	if(event.m_keyCode == WXK_SPACE) return true;
	
	if(event.m_keyCode == WXK_CONTROL) return false;
	if(event.m_keyCode == WXK_SHIFT) return false;

	return wxGridCellChoiceEditor::IsAcceptedKey(event);
}

void mywxGridCellChoiceEditor::BeginEdit(int row, int col, wxGrid* grid)
{
	p_sel_single = grid->GetSelectedCells();
	p_sel_topleft = grid->GetSelectionBlockTopLeft();
	p_sel_bottomright = grid->GetSelectionBlockBottomRight();
	
	wxGridCellChoiceEditor::BeginEdit(row,col,grid);
}

bool mywxGridCellChoiceEditor::EndEdit(int row, int col, wxGrid* grid, const wxString &oldval, wxString *newval)
{
	if(wxGridCellChoiceEditor::EndEdit(row,col,grid,oldval,newval))
	{
		if(grid->GetSelectionMode() == wxGrid::wxGridSelectRows) return true;

		wxString newtext = grid->GetCellValue(row,col);
			
		unsigned int i;	
		for(i = 0;i < p_sel_single.GetCount();i++)
		{
			grid->SetCellValue(p_sel_single[i].GetRow(),p_sel_single[i].GetCol(),newtext);
		}

		for(i = 0;i < p_sel_topleft.GetCount();i++)
		{
			for(int j = p_sel_topleft[i].GetRow();j <= p_sel_bottomright[i].GetRow();j++)
			{
				for(int k = p_sel_topleft[i].GetCol();k <= p_sel_bottomright[i].GetCol();k++)
				{
					grid->SetCellValue(j,k,newtext);
				}
			}
		}
		return true;
	}
	return false;
}

//---------------------------------------------------------
void mywxGridCellTextEditor::Create(wxWindow* parent, wxWindowID id, wxEvtHandler* evtHandler)
{
    m_control = new wxTextCtrl(parent, id, wxEmptyString,
                               wxDefaultPosition, wxDefaultSize
#ifdef __WXMSW__
                               , wxTE_PROCESS_TAB | wxTE_AUTO_SCROLL | wxTE_PROCESS_ENTER
#endif
                              );

    wxGridCellEditor::Create(parent, id, evtHandler);
}

bool mywxGridCellTextEditor::IsAcceptedKey(wxKeyEvent& event)
{
	if(event.m_keyCode == WXK_SPACE) return true;
	
	return wxGridCellTextEditor::IsAcceptedKey(event);
}

void mywxGridCellTextEditor::StartingKey(wxKeyEvent& event)
{
	if(event.m_keyCode == WXK_SPACE) return;

	wxGridCellTextEditor::StartingKey(event);
}

void mywxGridCellTextEditor::BeginEdit(int row, int col, wxGrid* grid)
{
	p_sel_single = grid->GetSelectedCells();
	p_sel_topleft = grid->GetSelectionBlockTopLeft();
	p_sel_bottomright = grid->GetSelectionBlockBottomRight();
	
	wxGridCellTextEditor::BeginEdit(row,col,grid);
}

bool mywxGridCellTextEditor::EndEdit(int row, int col, wxGrid* grid, const wxString &oldval, wxString *newval)
{
	if(wxGridCellTextEditor::EndEdit(row,col,grid,oldval,newval))
	{
		if(grid->GetSelectionMode() == wxGrid::wxGridSelectRows) return true;

		wxString newtext = grid->GetCellValue(row,col);
			
		unsigned int i;	
		for(i = 0;i < p_sel_single.GetCount();i++)
		{
			grid->SetCellValue(p_sel_single[i].GetRow(),p_sel_single[i].GetCol(),newtext);
		}

		for(i = 0;i < p_sel_topleft.GetCount();i++)
		{
			for(int j = p_sel_topleft[i].GetRow();j <= p_sel_bottomright[i].GetRow();j++)
			{
				for(int k = p_sel_topleft[i].GetCol();k <= p_sel_bottomright[i].GetCol();k++)
				{
					grid->SetCellValue(j,k,newtext);
				}
			}
		}
		return true;
	}
	return false;
}
