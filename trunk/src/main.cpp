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
#include "main.h"
#include "MainFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_APP(LightShowApp)

bool LightShowApp::OnInit()
{
//	_CrtSetBreakAlloc(330609);

	wxLog *logger = new wxLogStderr();
	logger->SetVerbose();
	wxLog *old_log = wxLog::SetActiveTarget( logger );
	if(old_log) 
		delete old_log;
	
	storage::init();
	storage::load();
	
	p_thread = new FunctionThread(this);
	p_thread->Create();
	p_thread->SetPriority(WXTHREAD_MAX_PRIORITY);
	
    wxInitAllImageHandlers();
	
    MainFrame* main_frame = new MainFrame(0, -1, wxT(""));
    SetTopWindow(main_frame);

	storage::load_plugins();

	p_thread->Run();
    main_frame->Show();

    return true;
}

int LightShowApp::OnExit()
{
	storage::save();

	p_thread->End();
	p_thread->Wait();

	storage::unload_plugins();

	delete p_thread;

	storage::clear();

	return 0;
}
