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
#include "mywxGridTableBase.h"
#include "storage.h"

/////////////////////////////////////////////////////////////////////////////////
// Table Base List
/////////////////////////////////////////////////////////////////////////////////

mywxGridTableBaseList::mywxGridTableBaseList()
{
	p_list = NULL;
	p_parent = NULL;
	p_attrProvider = new mywxGridCellAttrProvider();
	SetAttrProvider(p_attrProvider);
}

void mywxGridTableBaseList::set_list(storageitemlist* slist)
{
	if(p_list != NULL)
	{
		//TODO Clean up?
	}
	
	p_list = slist;

#ifndef __VISUALC__ //VSC++ doesn't support sort
	if(p_list)
		p_list->sort(storage_item_sort());
#endif

	p_attrProvider->set_list(slist);
}

void mywxGridTableBaseList::set_parent(mywxGrid* parent)
{
	p_parent = parent;
}

bool mywxGridTableBaseList::AppendRows(size_t numRows)
{
	//appending done in mywxGrid, here only notify
	
	if ( GetView() )
    {
        wxGridTableMessage msg( this, wxGRIDTABLE_NOTIFY_ROWS_APPENDED, numRows );
        GetView()->ProcessTableMessage( msg );
    }
	
	return true;
}

bool mywxGridTableBaseList::DeleteRows(size_t pos, size_t numRows)
{
	if(!p_list) return false;
	storageitemlist::iterator it;
	it = p_list->begin();

	unsigned int i;
	for(i = 0;i < pos;i++)
	{
		if(it == p_list->end()) return false;
		it++;
	}
	
	for(i = 0;i < numRows;i++)
	{
		if(it == p_list->end()) return false;
		delete *it;
		it++;
	}
	
	if ( GetView() )
    {
        wxGridTableMessage msg( this, wxGRIDTABLE_NOTIFY_ROWS_DELETED, pos, numRows );
        GetView()->ProcessTableMessage( msg );
    }
	
	return true;
}

bool mywxGridTableBaseList::AppendCols(size_t numCols)
{
	//Only Notifing
	mywxGrid* grid = (mywxGrid*)GetView();
	if ( grid )
    {
        wxGridTableMessage msg( this, wxGRIDTABLE_NOTIFY_COLS_APPENDED, numCols );
        grid->ProcessTableMessage( msg );
		grid->update();
	}
	return true;
}

bool mywxGridTableBaseList::DeleteCols(size_t pos, size_t numCols)
{        	
	//Only Notifing
	mywxGrid* grid = (mywxGrid*)GetView();
	if ( grid )
    {
        wxGridTableMessage msg( this, wxGRIDTABLE_NOTIFY_COLS_DELETED, pos, numCols );
        grid->ProcessTableMessage( msg );
		grid->update();
	}
	return true;
}

int mywxGridTableBaseList::GetNumberRows()
{
	if(!p_list) return 0;

	return p_list->size();
}

int mywxGridTableBaseList::GetNumberCols()
{
	if(p_list) 
		if(!p_list->empty())
		{
			storage_item* s = *(p_list->begin());
			return s->get_num_params();
		}
	
	return 0;
}

bool mywxGridTableBaseList::IsEmptyCell( int row, int col )
{
	return false;
}

wxString mywxGridTableBaseList::GetColLabelValue( int col )
{
	if(p_list) 
		if(!p_list->empty())
		{
			storage_item* s = *(p_list->begin());
			return s->get_param_name(s->real_id_for_virtual_id(col));
		}
	
	return wxT("");
}

wxString mywxGridTableBaseList::GetTypeName( int row, int col )
{
	if(p_list)
	{
		storage_item* item = storage::storage_item_for_row(p_list,row);

		if(item)
		{
			int id = item->real_id_for_virtual_id(col);
			if(item->get_param_map(id) != wxT(""))
				return wxString::Format(wxT("%s:%s"), mywxGRID_VALUE_CHOICE, item->get_param_map(id).c_str());
		}
	}
		
	return mywxGRID_VALUE_STRING;
}

bool mywxGridTableBaseList::CanGetValueAs( int row, int col, const wxString& typeName )
{
    if ( typeName == wxGRID_VALUE_STRING )
        return true;
	if( typeName == mywxGRID_VALUE_STRING )
		return true;

	return false;    
}

bool mywxGridTableBaseList::CanSetValueAs( int row, int col, const wxString& typeName )
{
	return CanGetValueAs(row,col,typeName);
}

wxString mywxGridTableBaseList::GetValue( int row, int col )
{
	if(!p_list) return wxT("");
	
	storage_item* item = storage::storage_item_for_row(p_list,row);
	
	if(item == NULL) return wxT("");
	
	return item->get_s_param(item->real_id_for_virtual_id(col));
}

void mywxGridTableBaseList::SetValue( int row, int col, const wxString& value )
{
	if(!p_list) return;

	storage_item* item = storage::storage_item_for_row(p_list,row);
	if(item == NULL) return;
		
	item->set_param(item->real_id_for_virtual_id(col), value);

	if(p_parent)
		p_parent->Refresh();
}

/////////////////////////////////////////////////////////////////////////////////
// Table Base List Chnl (special version for channel view)
/////////////////////////////////////////////////////////////////////////////////

mywxGridTableBaseChnlList::mywxGridTableBaseChnlList()
{
	p_list = NULL;
	p_attrProvider = new mywxGridCellAttrProviderChnl();
	SetAttrProvider(p_attrProvider);
}

void mywxGridTableBaseChnlList::init()
{
	if(p_list != NULL)
	{
		//TODO Clean up?
	}
	
	p_list = &storage::list_channelitem;

#ifndef __VISUALC__ //VSC++ doesn't support sort
	if(p_list)
		p_list->sort(storage_item_sort());
#endif

	p_attrProvider->set_list(p_list);
}

bool mywxGridTableBaseChnlList::DeleteRows(size_t pos, size_t numRows)
{
	if(!p_list) return false;

	for(unsigned int i = pos+1;i < pos+1+numRows;i++)
	{
		channelitem* citem = storage::channelitem_for_channel(i);
		if(citem)
			delete citem;
	}
	
	if(GetView())
    {
        wxGridTableMessage msg( this, wxGRIDTABLE_NOTIFY_ROWS_DELETED, pos, numRows );
        GetView()->ProcessTableMessage( msg );
    }
	
	return true;
}

int mywxGridTableBaseChnlList::GetNumberRows()
{
	if(!p_list) return 0;
	return DMX_CHNLS;
}

wxString mywxGridTableBaseChnlList::GetTypeName( int row, int col )
{
	if(p_list)
	{
		channelitem* citem = storage::channelitem_for_channel(row+1);
	
		if(citem && row+1 == citem->get_start_channel())
		{
			int id = citem->real_id_for_virtual_id(col);
			if(citem->get_param_map(id) != wxT(""))
				return wxString::Format(wxT("%s:%s"), mywxGRID_VALUE_CHOICE, citem->get_param_map(id).c_str());
		}
	}
		
	return mywxGRID_VALUE_STRING;
}

wxString mywxGridTableBaseChnlList::GetValue( int row, int col )
{
	if(!p_list) return wxT("");
	
	channelitem* citem = storage::channelitem_for_channel(row+1);
	
	if(citem == NULL || row+1 != citem->get_start_channel())
	{
		if(col == 0)
			return storage::int_to_str(row+1);
		else 
			return wxT("");
	}
	
	return citem->get_s_param(citem->real_id_for_virtual_id(col));
}

void mywxGridTableBaseChnlList::SetValue( int row, int col, const wxString& value )
{
	if(!p_list) return;

	channelitem* citem = storage::channelitem_for_channel(row+1);
	
	if(citem == NULL || row+1 != citem->get_start_channel())
		return;
		
	citem->set_param(citem->real_id_for_virtual_id(col), value);

	if(p_parent)
		p_parent->Refresh();
}

/////////////////////////////////////////////////////////////////////////////////
// Table Base Item
/////////////////////////////////////////////////////////////////////////////////

mywxGridTableBaseItem::mywxGridTableBaseItem()
{
	p_item = NULL;
	p_attrProvider = new mywxGridCellAttrProvider();
	SetAttrProvider(p_attrProvider);
}

void mywxGridTableBaseItem::set_item(storage_item* sitem)
{
	if(p_item != NULL)
	{
		//TODO Clean up?
	}
	
	p_item = sitem;
}

int mywxGridTableBaseItem::GetNumberRows()
{
	if(!p_item) return 0;

	return p_item->get_num_params();
}

int mywxGridTableBaseItem::GetNumberCols()
{
	return 2;
}

bool mywxGridTableBaseItem::IsEmptyCell( int row, int col )
{
	return false;
}

wxString mywxGridTableBaseItem::GetColLabelValue( int col )
{
	switch(col)
	{
	case 0:
		return wxT("param");
	case 1:
		return wxT("value");
	default:
		return wxT("");	
	}
}

wxString mywxGridTableBaseItem::GetTypeName( int row, int col )
{
	if(p_item && col == 1)
	{
		int id = p_item->real_id_for_virtual_id(row);
		if(p_item->get_param_map(id) != wxT(""))
			return wxString::Format(wxT("%s:%s"), mywxGRID_VALUE_CHOICE, p_item->get_param_map(id).c_str());
	}
		
	return mywxGRID_VALUE_STRING;
}

bool mywxGridTableBaseItem::CanGetValueAs( int row, int col, const wxString& typeName )
{
    if ( typeName == wxGRID_VALUE_STRING )
        return true;
	if( typeName == mywxGRID_VALUE_STRING )
		return true;

	return false;    
}

bool mywxGridTableBaseItem::CanSetValueAs( int row, int col, const wxString& typeName )
{
	return CanGetValueAs(row,col,typeName);
}

wxString mywxGridTableBaseItem::GetValue( int row, int col )
{
	if(!p_item) return wxT("");
	
	int id = p_item->real_id_for_virtual_id(row);
	
	if(col == 0)
		return p_item->get_param_name(id);
	else if(col == 1)
		return p_item->get_s_param(id);

	return wxT("");
}

void mywxGridTableBaseItem::SetValue( int row, int col, const wxString& value )
{
	if(!p_item) return;

	if(col == 1)		
		p_item->set_param(p_item->real_id_for_virtual_id(row), value);
}

bool mywxGridTableBaseItem::AppendRows(size_t numRows)
{
	//appending done in mywxGrid, here only notify
	
	if ( GetView() )
    {
        wxGridTableMessage msg( this, wxGRIDTABLE_NOTIFY_ROWS_APPENDED, numRows );
        GetView()->ProcessTableMessage( msg );
    }
	
	return true;
}

bool mywxGridTableBaseItem::DeleteRows(size_t pos, size_t numRows)
{
	if(!p_item) return false;
	
	for(unsigned int i = 0;i < numRows;i++)
	{
		int id = p_item->real_id_for_virtual_id(i + pos);
		p_item->delete_param(id);
	}

	if ( GetView() )
    {
        wxGridTableMessage msg( this, wxGRIDTABLE_NOTIFY_ROWS_DELETED, pos, numRows );
        GetView()->ProcessTableMessage( msg );
    }
	
	return true;
}
