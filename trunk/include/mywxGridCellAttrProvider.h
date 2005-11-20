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

//From the newgrid sample of wxWidgets

#include "storage_item.h"
#include "mywxGridCellEditors.h"


class mywxGridCellAttrProvider : public wxGridCellAttrProvider
{
public:
    mywxGridCellAttrProvider();
    virtual ~mywxGridCellAttrProvider();
	void set_list(storageitemlist* slist);

    virtual wxGridCellAttr *GetAttr(int row, int col,  wxGridCellAttr::wxAttrKind  kind) const;

protected:
	mywxGridCellTextEditor m_cellTextEditor;
    wxGridCellAttr *m_attrForOddRows;
	wxGridCellAttr *m_attrForOddRowsRO;
	wxGridCellAttr *m_attr;
	wxGridCellAttr *m_attrRO;
	storageitemlist* p_list;
};

class mywxGridCellAttrProviderChnl : public mywxGridCellAttrProvider
{
public:
    mywxGridCellAttrProviderChnl();
    virtual ~mywxGridCellAttrProviderChnl();

    virtual wxGridCellAttr *GetAttr(int row, int col,  wxGridCellAttr::wxAttrKind  kind) const;

private:
    wxGridCellAttr *m_attrForEmptyRows;
	wxGridCellAttr *m_attrForEmptyRowsRO;

};
