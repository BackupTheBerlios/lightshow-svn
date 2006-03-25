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

#include "MainFrame.h"
#include "LibraryDialog.h"
#include "DMXPatchDialog.h"
#include "GroupDialog.h"
#include "ChannelDialog.h"
#include "IOSetupDialog.h"
#include "SaveTypeDialog.h"
#include "LoadTypeDialog.h"


//---- Event Class -------------------------------------
DEFINE_EVENT_TYPE(mywxMAINFRAME_REFRESH_EVENT);

IMPLEMENT_DYNAMIC_CLASS(MainFrameRefreshEvent, wxCommandEvent)

MainFrameRefreshEvent::MainFrameRefreshEvent(int id, int what) : 
wxCommandEvent(mywxMAINFRAME_REFRESH_EVENT, id), p_what(what)
{
	p_force_common = false;
}

MainFrameRefreshEvent::MainFrameRefreshEvent(const MainFrameRefreshEvent &event) 
{
	this->m_eventType = event.m_eventType;
	this->m_id = event.GetId();
	this->p_what = event.GetWhat();
	this->p_force_common = event.GetForceCommon();
}
//---- Event Class END-------------------------------------


MainFrame::MainFrame(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxFrame(parent, id, title, pos, size, wxDEFAULT_FRAME_STYLE | wxMAXIMIZE)
{
    window_1 = new wxSplitterWindow(this, -1);
    sizer_1 = new wxBoxSizer(wxVERTICAL);
    main_draw_window = new MainDrawWindow(window_1, -1);
    output_draw_window = new OutputDrawWindow(window_1, -1);

	main_tool_bar = new MainToolBar(this,-1);
	desk_setup_tool_bar = new DeskSetupToolBar(this,-1);
	
	status_bar = new wxStatusBar(this,-1);

    set_properties();
    do_layout();
    
    main_draw_window->SetFocus();
}

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_TOOL_RANGE(IDM_MENU,IDM_SETUP_OUTPUT,MainFrame::OnMainToolBar)
	EVT_TOOL_RANGE(IDDS_ADD_GROUP,IDDS_DELETE,MainFrame::OnDeskSetupToolBar)
	EVT_MF_REFRESH(MainFrame::RefreshEvent)
	EVT_KEY_DOWN(MainFrame::OnKeyDown)
	EVT_KEY_UP(MainFrame::OnKeyUp)
	EVT_MENU(wxID_EXIT,MainFrame::OnQuit)
	EVT_MENU(IDM_FILE_LOAD,MainFrame::OnLoad)
	EVT_MENU(IDM_FILE_SAVE,MainFrame::OnSave)
	EVT_MENU(IDM_FILE_ADD_LIBRARY,MainFrame::OnAddLibrary)
END_EVENT_TABLE()

void MainFrame::set_properties()
{
    SetTitle(wxT("LightShow"));
    SetSize(wxSize(800, 600));
	window_1->SetSashGravity(1.0);
	p_prev_size = -1;

    // create the menu
    file_menu.Append(IDM_FILE_LOAD, wxT("&Load\tCtrl-L"), wxT("Load"));
    file_menu.Append(IDM_FILE_SAVE, wxT("&Save\tCtrl-S"), wxT("Save"));
	file_menu.AppendSeparator();
	file_menu.Append(IDM_FILE_ADD_LIBRARY, wxT("&Add Library File\tCtrl-A"), wxT("Open a File and add the Contents to the Library"));
	file_menu.AppendSeparator();
    file_menu.Append(wxID_EXIT, wxT("&Quit\tCtrl-Q"), wxT("Quit"));
}

void MainFrame::do_layout()
{
	sizer_1->Add(main_tool_bar, 0, wxEXPAND | wxBOTTOM, 2);
	sizer_1->Add(desk_setup_tool_bar, 0, wxEXPAND | wxBOTTOM, 2);
	sizer_1->Show(desk_setup_tool_bar,false);
    window_1->SplitHorizontally(main_draw_window, output_draw_window, 442);
	window_1->SetMinimumPaneSize(50);
    sizer_1->Add(window_1, 1, wxEXPAND, 0);
	sizer_1->Add(status_bar, 0, wxEXPAND, 0);
    SetSizer(sizer_1);
	Layout();
}

void MainFrame::ShowDeskSetupToolBar(bool show)
{
	sizer_1->Show(desk_setup_tool_bar,show);
	Layout();
}

void MainFrame::RefreshEvent(MainFrameRefreshEvent& event)
{
	if(event.GetWhat() == MainFrameRefreshEvent::OUTPUT)
		output_draw_window->RefreshOutput();
	else if(event.GetWhat() == MainFrameRefreshEvent::DESK)
		main_draw_window->RefreshDesk(event.GetForceCommon());
}

void MainFrame::OnQuit(wxCommandEvent& event)
{
	Close();
}

void MainFrame::OnLoad(wxCommandEvent& event)
{
	wxMessageDialog mdlg(this,wxT("Do you want to Save your data before loading?"),wxT("Save?"),wxCANCEL|wxYES_NO);
	int ret = mdlg.ShowModal();

	if(ret == wxID_CANCEL) return;
	if(ret == wxID_YES)
	{
		wxFileDialog dlg(this,wxT("Choose File to save to"),wxT(""),wxT(""),wxT("LightShow File (*.ls)|*.ls"),wxSAVE);
		if(dlg.ShowModal() == wxID_OK)
			storage::save(dlg.GetPath());	
	}

	LoadTypeDialog tdlg(this,-1,wxT("Choose what to load"));
	if(tdlg.ShowModal() == wxID_OK)
	{
		storage::clear(tdlg.GetClear() | tdlg.GetLoad());
		//check if we need to load anything
		if(tdlg.GetLoad())
		{
			wxFileDialog dlg(this,wxT("Choose File to load"),wxT(""),wxT(""),wxT("LightShow File (*.ls)|*.ls"),wxOPEN | wxFILE_MUST_EXIST);
			if(dlg.ShowModal() == wxID_OK)
				storage::load(dlg.GetPath(),tdlg.GetLoad());	
		}
	}


	main_draw_window->RefreshDesk(true);
}

void MainFrame::OnSave(wxCommandEvent& event)
{
	SaveTypeDialog tdlg(this,-1,wxT("Choose what to save"));
	if(tdlg.ShowModal() == wxID_OK)
	{
		//check if we need to save anything
		if(!tdlg.GetSave()) return;

		wxFileDialog dlg(this,wxT("Choose File to save to"),wxT(""),wxT(""),wxT("LightShow File (*.ls)|*.ls"),wxSAVE);
		if(dlg.ShowModal() == wxID_OK)
			storage::save(dlg.GetPath(),tdlg.GetSave());	
	}
}

void MainFrame::OnAddLibrary(wxCommandEvent& event)
{
	wxFileDialog dlg(this,wxT("Choose File to add to Library"),wxT(""),wxT(""),wxT("Library File (*.ls)|*.ls"),wxOPEN | wxFILE_MUST_EXIST);
	if(dlg.ShowModal() == wxID_OK)
		storage::load(dlg.GetPath(),LOADSAVE_LIBRARY);		
}

void MainFrame::OnKeyDown(wxKeyEvent& event)
{
	//maybe our plugins want to do someting if a key gets pressed
	if(!storage::setuping)
		storage::send_key_to_plugin(event.GetKeyCode(), true);		
}

void MainFrame::OnKeyUp(wxKeyEvent& event)
{
	//maybe our plugins want to do someting if a key gets released
	if(!storage::setuping)
		storage::send_key_to_plugin(event.GetKeyCode(), false);
}			

void MainFrame::OnMainToolBar(wxCommandEvent& event)
{
	if(event.GetId() == IDM_MENU)
	{
		PopupMenu(&file_menu);
	}
	else if(event.GetId() == IDM_IO_SETUP)
	{
		IOSetupDialog dlg(this,-1,wxT("IO Setup"));
		dlg.Centre();
		dlg.ShowModal();
	}
	else if(event.GetId() == IDM_GROUP_SETUP)
	{
		GroupDialog dlg(this,-1,wxT("Group Setup"));
		dlg.Centre();
		dlg.ShowModal();
	}
	else if(event.GetId() == IDM_CHANNEL_SETUP)
	{
		ChannelDialog dlg(this,-1,wxT("Channel Setup"));
		dlg.Centre();
		dlg.ShowModal();
	}
	else if(event.GetId() == IDM_LIBRARY)
	{
		LibraryDialog dlg(this,-1,wxT("Library"));
		dlg.Centre();
		dlg.ShowModal();
	}
	else if(event.GetId() == IDM_DMX_PATCH)
	{
		DMXPatchDialog dlg(this,-1,wxT("DMX Patch"));
		dlg.Centre();
		dlg.ShowModal();
	}
	else if(event.GetId() == IDM_SETUP_OUTPUT)
	{
		storage::setup = event.IsChecked();
	}
	else
		main_draw_window->OnMainToolBar(event);
}

void MainFrame::OnDeskSetupToolBar(wxCommandEvent& event)
{
	main_draw_window->OnDeskSetupToolBar(event);
}

void MainFrame::SetStatusText(wxString& text)
{
	status_bar->SetStatusText(text);
}
