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


#include <wx/grid.h>
#include "mywxGrid.h"

//---- Event Class -------------------------------------
DEFINE_EVENT_TYPE(mywxGRID_CHANGE_EVENT);

IMPLEMENT_DYNAMIC_CLASS(mywxGridChangeEvent, wxCommandEvent)

mywxGridChangeEvent::mywxGridChangeEvent(int id, int type, int row) : 
	wxCommandEvent(mywxGRID_CHANGE_EVENT, id), p_type(type), p_row(row)
{
	
}

mywxGridChangeEvent::mywxGridChangeEvent(const mywxGridChangeEvent &event) 
{
	this->m_eventType = event.m_eventType;
	this->m_id = event.GetId();
}

bool mywxGridChangeEvent::IsAppend()
{
	return (p_type == T_APPEND);
}

bool mywxGridChangeEvent::IsDelete()
{
	return (p_type == T_DELETE);
}

int mywxGridChangeEvent::GetRow()
{
	return p_row;
}
//---- Event Class END-------------------------------------

mywxGrid::mywxGrid(wxWindow* parent, wxWindowID id) : 
wxGrid(parent, id, wxDefaultPosition, wxDefaultSize, wxWANTS_CHARS, wxPanelNameStr)
{
	p_list = NULL;
	p_item = NULL;
	p_new = NULL;
	p_new_param = NULL;

	SetColLabelSize(20);
	SetRowLabelSize(0);	
	SetGridLineColour(*wxBLACK);

	p_table_base_list.set_parent(this);
	p_table_base_chnl_list.set_parent(this);
	
	RegisterDataType(mywxGRID_VALUE_STRING, new wxGridCellStringRenderer, new mywxGridCellTextEditor);
	RegisterDataType(mywxGRID_VALUE_CHOICE, new wxGridCellStringRenderer, new mywxGridCellChoiceEditor);
}

mywxGrid::~mywxGrid()
{
	DisableCellEditControl();
}

BEGIN_EVENT_TABLE(mywxGrid, wxGrid)
	EVT_KEY_DOWN(mywxGrid::OnKeyDown)
	EVT_GRID_CELL_LEFT_CLICK(mywxGrid::OnCellLeftClick)
END_EVENT_TABLE()

void mywxGrid::OnKeyDown(wxKeyEvent &event)
{
	switch(event.GetKeyCode())
	{
		case WXK_RETURN:
		case WXK_NUMPAD_ENTER:
			DisableCellEditControl();
			MoveCursorDown(false);
			break;
		case WXK_DELETE:
			delete_selected();
			break;
		case WXK_INSERT:
			append();
			break;
		default:
			event.Skip(); // Send Event to wxGrid::
			break;
	}
}

void mywxGrid::OnCellLeftClick(wxGridEvent& event)
{
	if(p_list)
	{
		if(!p_list->empty())
		{
			storage_item* s = *(p_list->begin());
			//Good way to display Editor on single click, but don't need to handle all the selection stuff
			if(s->single_select())
				SetCurrentCell( wxGridCellCoords(event.GetRow(), event.GetCol()));
		}
	}
	event.Skip();
}

void mywxGrid::update()
{
	if(p_list)
		if(!p_list->empty())
		{
			storage_item* s = *(p_list->begin());
			for(int i = 0;i < s->get_num_params();i++)
			{
				SetColSize(i,s->get_column_width(s->real_id_for_virtual_id(i)));
			}
			
			if(s->single_select())
			{
				SetRowLabelSize(10);
				SetSelectionMode(wxGrid::wxGridSelectCells);
			}
			else
			{
				SetRowLabelSize(0);
				SetSelectionMode(wxGrid::wxGridSelectRows);
			}
		}
}

void mywxGrid::append()
{
	if(p_new == NULL) return;
		
	p_new(p_new_param);
	AppendRows(); //does noting but notify the displays
	mywxGridChangeEvent event(GetId(), mywxGridChangeEvent::T_APPEND);
	ProcessEvent(event);
}

void mywxGrid::delete_selected()
{
	if(GetSelectionMode() == wxGrid::wxGridSelectRows)
	{
		wxGridCellCoordsArray seltl = GetSelectionBlockTopLeft();
		while(seltl.GetCount() > 0)
		{
			DeleteRows(seltl[0].GetRow());
			mywxGridChangeEvent event(GetId(), mywxGridChangeEvent::T_DELETE,seltl[0].GetRow());
			ProcessEvent(event);
			seltl = GetSelectionBlockTopLeft();
		}

		wxGridCellCoordsArray sel = GetSelectedCells();
		while(sel.GetCount() > 0)
		{
			DeleteRows(sel[0].GetRow());
			mywxGridChangeEvent event(GetId(), mywxGridChangeEvent::T_DELETE,sel[0].GetRow());
			ProcessEvent(event);
			sel = GetSelectedCells();
		}
	}
	
	wxArrayInt sel = GetSelectedRows();
	while(sel.GetCount() > 0)
	{
		DeleteRows(sel[0]);
		mywxGridChangeEvent event(GetId(), mywxGridChangeEvent::T_DELETE,sel[0]);
		ProcessEvent(event);
		sel = GetSelectedRows();
	}
	
}

void mywxGrid::set_list(storageitemlist* slist,void(*create_new)(void*),void* parm)
{
	p_list = slist;
	p_new = create_new;
	p_new_param = parm;

	if(p_list)
		if(p_list->empty())
			append();

	p_table_base_list.set_list(slist);
	
	m_rowHeights.Empty();
    	m_rowBottoms.Empty();
	m_colWidths.Empty();
	m_colRights.Empty();
    
	SetTable(&p_table_base_list);

	update();
	ForceRefresh();
}

void mywxGrid::set_channel_list()
{
	p_list = &storage::list_channelitem;
	p_new = new_channelitem;
	p_new_param = NULL;

	if(p_list)
		if(p_list->empty())
			append();

	p_table_base_chnl_list.init();
	
	m_rowHeights.Empty();
    	m_rowBottoms.Empty();
	m_colWidths.Empty();
	m_colRights.Empty();

	SetTable(&p_table_base_chnl_list);

	update();
	ForceRefresh();
}

void mywxGrid::set_item(storage_item* sitem,void(*create_new)(void*),void* parm)
{
	p_item = sitem;
	p_new = create_new;
	p_new_param = parm;
	
	p_table_base_item.set_item(sitem);

	m_rowHeights.Empty();
    	m_rowBottoms.Empty();
	m_colWidths.Empty();
	m_colRights.Empty();

	SetTable(&p_table_base_item);
	SetSelectionMode(wxGrid::wxGridSelectRows);

	SetColSize(0,130);
	SetColSize(1,150);
	
	ForceRefresh();
}
