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


#ifndef _MYWXTABLEBASE_H_
#define _MYWXTABLEBASE_H_

#include "storage.h"
#include "storage_item.h"

#include "mywxGridCellAttrProvider.h"

class mywxGrid;

class mywxGridTableBaseList : public wxGridTableBase
{
public:
    mywxGridTableBaseList();
	void set_list(storageitemlist* slist);
	void set_parent(mywxGrid* parent);

	virtual bool DeleteRows(size_t pos = 0, size_t numRows = 1);
	virtual bool AppendRows(size_t numRows = 1);
	bool AppendCols(size_t numCols = 1);
	bool DeleteCols(size_t pos = 0, size_t numCols = 1);

    virtual int GetNumberRows();
    virtual int GetNumberCols();
    virtual bool IsEmptyCell( int row, int col );
    virtual wxString GetValue( int row, int col );
    virtual void SetValue( int row, int col, const wxString& value );

    virtual wxString GetColLabelValue( int col );

    virtual wxString GetTypeName( int row, int col );
    virtual bool CanGetValueAs( int row, int col, const wxString& typeName );
    virtual bool CanSetValueAs( int row, int col, const wxString& typeName );

protected:
	storageitemlist* p_list;
	mywxGrid* p_parent;
	mywxGridCellAttrProvider* p_attrProvider;
};

class mywxGridTableBaseChnlList : public mywxGridTableBaseList
{
public:
    mywxGridTableBaseChnlList();
	void init();

	virtual bool DeleteRows(size_t pos = 0, size_t numRows = 1);
	
    virtual int GetNumberRows();
    virtual wxString GetValue( int row, int col );
    virtual void SetValue( int row, int col, const wxString& value );

    virtual wxString GetTypeName( int row, int col );

private:
	mywxGridCellAttrProviderChnl* p_attrProvider;
};

class mywxGridTableBaseItem : public wxGridTableBase
{
public:
    mywxGridTableBaseItem();
	void set_item(storage_item* sitem);

	virtual bool DeleteRows(size_t pos = 0, size_t numRows = 1);
	virtual bool AppendRows(size_t numRows = 1);

    virtual int GetNumberRows();
    virtual int GetNumberCols();
    virtual bool IsEmptyCell( int row, int col );
    virtual wxString GetValue( int row, int col );
    virtual void SetValue( int row, int col, const wxString& value );

    virtual wxString GetColLabelValue( int col );

    virtual wxString GetTypeName( int row, int col );
    virtual bool CanGetValueAs( int row, int col, const wxString& typeName );
    virtual bool CanSetValueAs( int row, int col, const wxString& typeName );

private:
	storage_item* p_item;
	mywxGridCellAttrProvider* p_attrProvider;
};

#endif	//_MYWXTABLEBASE_H_
