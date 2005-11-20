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
#include "mywxGridCellAttrProvider.h"
#include "storage.h"


mywxGridCellAttrProvider::mywxGridCellAttrProvider()
{
	p_list = NULL;
	
    m_attrForOddRows = new wxGridCellAttr;
    m_attrForOddRows->SetBackgroundColour(*wxLIGHT_GREY);
	
	m_attrForOddRowsRO = new wxGridCellAttr;
	m_attrForOddRowsRO->SetBackgroundColour(*wxLIGHT_GREY);
	m_attrForOddRowsRO->SetReadOnly();
	
	m_attr = new wxGridCellAttr;
	
	m_attrRO = new wxGridCellAttr;
	m_attrRO->SetReadOnly();
}

mywxGridCellAttrProvider::~mywxGridCellAttrProvider()
{
}

void mywxGridCellAttrProvider::set_list(storageitemlist* slist)
{
	p_list = slist;
}


wxGridCellAttr *mywxGridCellAttrProvider::GetAttr(int row, int col,
                           wxGridCellAttr::wxAttrKind  kind /* = wxGridCellAttr::Any */) const
{
    wxGridCellAttr *attr = wxGridCellAttrProvider::GetAttr(row, col, kind);
	
	bool RO = false;
	if(col == 0) RO = true; // Default first Cell to RO, others to Editable
		
	if ( p_list ) 
		if ( !p_list->empty() ) 
			RO = !(*p_list->begin())->can_edit((*p_list->begin())->real_id_for_virtual_id(col));

	if ( !attr )
	{
		if ( RO )
		{
			if ( row % 2 ) attr = m_attrForOddRowsRO;
			else  attr = m_attrRO;
		}
		else
		{
			if ( row % 2 ) attr = m_attrForOddRows;
			else attr = m_attr;
		}

		attr->IncRef();
	}
	else
	{
		if ( (row % 2 && !attr->HasBackgroundColour()) || (RO && !attr->IsReadOnly()) )
		{
			wxGridCellAttr *attrNew = attr->Clone();
			attr->DecRef();
			attr = attrNew;
			
			if ( row % 2 ) attr->SetBackgroundColour(*wxLIGHT_GREY);
				
			if ( RO ) attr->SetReadOnly();
		}
	}

    return attr;
}

////////////////////////////////////////////////////////////////////////////////////////////
// mywxGridCellAttrProviderChnl
////////////////////////////////////////////////////////////////////////////////////////////
mywxGridCellAttrProviderChnl::mywxGridCellAttrProviderChnl() : mywxGridCellAttrProvider()
{
	p_list = NULL;
	
    m_attrForEmptyRows = new wxGridCellAttr;
    m_attrForEmptyRows->SetBackgroundColour(*wxGREEN);
	
	m_attrForEmptyRowsRO = new wxGridCellAttr;
	m_attrForEmptyRowsRO->SetBackgroundColour(*wxGREEN);
	m_attrForEmptyRowsRO->SetReadOnly();
}

mywxGridCellAttrProviderChnl::~mywxGridCellAttrProviderChnl()
{
}

wxGridCellAttr *mywxGridCellAttrProviderChnl::GetAttr(int row, int col,
                           wxGridCellAttr::wxAttrKind  kind /* = wxGridCellAttr::Any */) const
{
    wxGridCellAttr *attr = wxGridCellAttrProvider::GetAttr(row, col, kind);
	
	bool RO = true;
	bool grey = false;
	bool free = false;

	channelitem* citem = storage::channelitem_for_channel(row+1);

	if(citem)
	{
		if( citem->get_start_channel() != row+1 )
			grey = true;
		else
			RO = !citem->can_edit(citem->real_id_for_virtual_id(col));
	}
	else
		free = true;

	if ( !attr )
	{
		if ( RO )
		{
			if ( grey ) attr = m_attrForOddRowsRO;
			else if ( free ) attr = m_attrForEmptyRowsRO;
			else  attr = m_attrRO;
		}
		else
		{
			if ( grey ) attr = m_attrForOddRows;
			else if ( free ) attr = m_attrForEmptyRows;
			else attr = m_attr;
		}

		attr->IncRef();
	}
	else
	{
		if ( ((grey || free) && !attr->HasBackgroundColour()) || (RO && !attr->IsReadOnly()) )
		{
			wxGridCellAttr *attrNew = attr->Clone();
			attr->DecRef();
			attr = attrNew;
			
			if ( grey ) attr->SetBackgroundColour(*wxLIGHT_GREY);
			if ( free ) attr->SetBackgroundColour(*wxGREEN);
			if ( RO ) attr->SetReadOnly();
		}
	}

    return attr;
}