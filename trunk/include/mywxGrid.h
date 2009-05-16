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


#ifndef _MYWXGRID_H_
#define _MYWXGRID_H_

#define mywxGRID_VALUE_STRING wxT("MYSTRING")
#define mywxGRID_VALUE_CHOICE wxT("MYCHOICE")

#include "mywxGridTableBase.h"

//---- Event Class -------------------------------------
DECLARE_EVENT_TYPE(mywxGRID_CHANGE_EVENT, 7777)

#define EVT_GRID_CHANGE(fn) \
    DECLARE_EVENT_TABLE_ENTRY( \
	mywxGRID_CHANGE_EVENT, wxID_ANY, wxID_ANY, \
	(wxObjectEventFunction)(wxEventFunction)&fn, \
	(wxObject *) NULL \
    ),
	
class mywxGridChangeEvent : public wxCommandEvent 
{
public:
    mywxGridChangeEvent(int id = 0,int type = T_APPEND, int row = -1);
    mywxGridChangeEvent(const mywxGridChangeEvent &event);
    virtual wxEvent *Clone() const {return new mywxGridChangeEvent(*this);};
	
    DECLARE_DYNAMIC_CLASS(mywxGridChangeEvent)
	
	bool IsAppend();
	bool IsDelete();
	int GetRow();
	
	enum
	{
		T_APPEND,
		T_DELETE
	};

private:
	int p_type;
	int p_row;
};
//---- Event Class END-----------------------------------

class mywxGrid : public wxGrid
{
public:
	mywxGrid(wxWindow* parent, wxWindowID id);
	virtual ~mywxGrid();
	void set_list(storageitemlist* slist,void(*create_new)(void*) = NULL,void* parm = NULL);
	void set_item(storage_item* sitem,void(*create_new)(void*) = NULL,void* parm = NULL);
	void set_channel_list();
	void append(bool first = false);
	void delete_selected();
	void update();

private:
	void OnKeyDown(wxKeyEvent& event); 
	void OnCellLeftClick(wxGridEvent& event);
	void OnCellColSize(wxGridSizeEvent& event);

	DECLARE_EVENT_TABLE() 
	mywxGridTableBaseList p_table_base_list;
	mywxGridTableBaseChnlList p_table_base_chnl_list;
	mywxGridTableBaseItem p_table_base_item;
	storageitemlist* p_list;
	storage_item* p_item;
	void (*p_new)(void *);
	void* p_new_param;
	
};

#endif	//_MYWXGRID_H_
