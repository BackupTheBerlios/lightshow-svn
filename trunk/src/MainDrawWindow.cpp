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

#include "MainDrawWindow.h"
#include "MainFrame.h"
#include "MainToolBar.h"
#include "DeskSetupToolBar.h"
#include "FunctionDialog.h"
#include "FaderDialog.h"
#include "GroupSelectDialog.h"

#include "../bitmaps/cursor_move.xpm"
#include "../bitmaps/cursor_copy.xpm"
#include "../bitmaps/cursor_delete.xpm"

MainDrawWindow::MainDrawWindow(wxWindow* parent, wxWindowID id) : wxWindow(parent, id, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE)
{
	p_state = STATE_DESK;
	p_desksetup_state = DESKSETUP_ADD_GROUP;
	p_selected_item = NULL;
	p_hover_item = NULL;
	p_floating_item = NULL;
	p_floating_fader = NULL;
	p_refresh_pending = false;
	
	unsigned char* rgb;
	
	rgb = storage::config.get_color(configitem::PAGE);
	p_page_brush.SetColour(rgb[0],rgb[1],rgb[2]);
	rgb = storage::config.get_color(configitem::FUNCTION);
	p_function_brush.SetColour(rgb[0],rgb[1],rgb[2]);
	rgb = storage::config.get_color(configitem::FUNCTION_OTHERPAGE);
	p_function_otherpage_brush.SetColour(rgb[0],rgb[1],rgb[2]);
	rgb = storage::config.get_color(configitem::FUNCTION_PB);
	p_function_pb_brush.SetColour(rgb[0],rgb[1],rgb[2]);
	rgb = storage::config.get_color(configitem::FUNCTION_PB_OTHERPAGE);
	p_function_pb_otherpage_brush.SetColour(rgb[0],rgb[1],rgb[2]);
	rgb = storage::config.get_color(configitem::GROUP);
    p_group_brush.SetColour(rgb[0],rgb[1],rgb[2]);
	rgb = storage::config.get_color(configitem::FADER);
	p_fader_brush.SetColour(rgb[0],rgb[1],rgb[2]);
	rgb = storage::config.get_color(configitem::FADER_BUTTON);
	p_fader_button_brush.SetColour(rgb[0],rgb[1],rgb[2]);
	rgb = storage::config.get_color(configitem::FADER_ACTIVE);
	p_fader_active_brush.SetColour(rgb[0],rgb[1],rgb[2]);
	rgb = storage::config.get_color(configitem::LED_ON);
	p_led_on_brush.SetColour(rgb[0],rgb[1],rgb[2]);
	rgb = storage::config.get_color(configitem::LED_OFF);
	p_led_off_brush.SetColour(rgb[0],rgb[1],rgb[2]);
	rgb = storage::config.get_color(configitem::BORDER);
	p_border_pen.SetColour(rgb[0],rgb[1],rgb[2]);
	rgb = storage::config.get_color(configitem::BORDER_HIGHLITE);
	p_border_highlite_pen.SetColour(rgb[0],rgb[1],rgb[2]);
	rgb = storage::config.get_color(configitem::BACKGROUND);
	p_background_brush.SetColour(rgb[0],rgb[1],rgb[2]);
	rgb = storage::config.get_color(configitem::TEXT);
	p_text_color.Set(rgb[0],rgb[1],rgb[2]);
	rgb = storage::config.get_color(configitem::TEXT_FADER);
	p_text_infader_color.Set(rgb[0],rgb[1],rgb[2]);

	
/*	p_page_brush.SetColour(149,207,99);
	p_function_brush.SetColour(98,147,147);
	p_function_otherpage_brush.SetColour(98,147,147);
	p_function_pb_brush.SetColour(103,204,204);
	p_function_pb_otherpage_brush.SetColour(103,204,204);
    p_group_brush.SetColour(98,150,98);
	p_fader_brush.SetColour(201,207,98);
	p_fader_button_brush.SetColour(150,156,46);
	p_fader_active_brush.SetColour(100,154,101);
	
	p_led_on_brush.SetColour(255,0,0);
	p_led_off_brush.SetColour(100,0,0);
	
	p_border_pen.SetColour(150,150,150);
	p_border_highlite_pen.SetColour(200,200,200);
	
	p_background_brush.SetColour(0,0,0);
	p_text_color.Set(0,0,0);
	p_text_infader_color.Set(0,0,0);
*/	
	
	wxBitmap cursor_delete_bitmap(cursor_delete_xpm);
	wxImage cursor_delete_image = cursor_delete_bitmap.ConvertToImage();
	cursor_delete_image.SetOption(wxIMAGE_OPTION_CUR_HOTSPOT_X, 12);
	cursor_delete_image.SetOption(wxIMAGE_OPTION_CUR_HOTSPOT_Y, 9);
	
	wxBitmap cursor_move_bitmap(cursor_move_xpm);
	wxImage cursor_move_image = cursor_move_bitmap.ConvertToImage();
	cursor_move_image.SetOption(wxIMAGE_OPTION_CUR_HOTSPOT_X, 12);
	cursor_move_image.SetOption(wxIMAGE_OPTION_CUR_HOTSPOT_Y, 9);
	
	wxBitmap cursor_copy_bitmap(cursor_copy_xpm);
	wxImage cursor_copy_image = cursor_copy_bitmap.ConvertToImage();
	cursor_copy_image.SetOption(wxIMAGE_OPTION_CUR_HOTSPOT_X, 12);
	cursor_copy_image.SetOption(wxIMAGE_OPTION_CUR_HOTSPOT_Y, 9);
	
	
	p_delete_cursor = new wxCursor(cursor_delete_image);
	p_move_cursor = new wxCursor(cursor_move_image);
	p_copy_cursor = new wxCursor(cursor_copy_image);
	p_hand_cursor = new wxCursor(wxCURSOR_HAND);
	
	SetCursor(*p_hand_cursor);
}

MainDrawWindow::~MainDrawWindow()
{
	delete p_delete_cursor;
	delete p_move_cursor;
	delete p_copy_cursor;
	delete p_hand_cursor;
}

BEGIN_EVENT_TABLE(MainDrawWindow, wxWindow)
	EVT_PAINT(MainDrawWindow::OnPaint)
	EVT_KEY_DOWN(MainDrawWindow::OnKeyDown)
	EVT_KEY_UP(MainDrawWindow::OnKeyUp)
	EVT_MOUSE_EVENTS(MainDrawWindow::OnMouseEvent)
	EVT_ERASE_BACKGROUND(MainDrawWindow::OnEraseBackground)
END_EVENT_TABLE()

void MainDrawWindow::OnPaint(wxPaintEvent& event)
{
#ifdef __WXMSW__
	wxBufferedPaintDC dc(this);
#else
	wxPaintDC dc(this);
#endif

	p_refresh_pending = false;
	
	DrawDesk(dc);
}

void MainDrawWindow::OnEraseBackground(wxEraseEvent& event)
{
#ifdef __WXMSW__
	event.Skip(false);
	//do noting -> windows non flicker
#endif
}

void MainDrawWindow::RefreshDesk()
{
	Refresh();
}

void MainDrawWindow::SetStatusText(wxString text)
{
	MainFrame* frm = (MainFrame*)GetGrandParent();
	frm->SetStatusText(text);
}

void MainDrawWindow::OnMainToolBar(wxCommandEvent& event)
{
	p_selected_item = NULL;
	p_hover_item = NULL;
	p_floating_item = NULL;
	p_floating_fader = NULL;

	MainFrame* frm = (MainFrame*)GetGrandParent();
	
	switch(event.GetId())
	{
	case IDM_SHOW_DESK:
		p_state = STATE_DESK;
		if(frm != NULL) frm->ShowDeskSetupToolBar(false);
		RefreshDesk();
		SetStatusText(wxString(wxT("")));
		SetCursor(*p_hand_cursor);
		break;
	case IDM_SHOW_DESK_SETUP:
		p_state = STATE_DESK_SETUP;
		if(frm != NULL) frm->ShowDeskSetupToolBar(true);
		p_selected_item = NULL;
		RefreshDesk();
		SetStatusText(wxString(wxT("Select the needed task above.")));
		SetCursor(wxNullCursor);
		break;
	case IDM_SHOW_FUNCTION_SETUP:
		p_state = STATE_FUNCTION_SETUP;
		if(frm != NULL) frm->ShowDeskSetupToolBar(false);
		RefreshDesk();
		SetStatusText(wxString(wxT("Doubleclick to edit. Drag to move, copy (with Ctrl down) or delete (drag on empty space).")));
		SetCursor(wxNullCursor);
		break;
	}
}

void MainDrawWindow::OnDeskSetupToolBar(wxCommandEvent& event)
{
	p_selected_item = NULL;
	p_hover_item = NULL;
	p_floating_item = NULL;
	p_floating_fader = NULL;
	
	switch(event.GetId())
	{
	case IDDS_ADD_GROUP:
		p_desksetup_state = DESKSETUP_ADD_GROUP;
		SetStatusText(wxString(wxT("Click to add. Drag to move (place off the grid with Alt down).")));
		break;
	case IDDS_ADD_PAGE:
		p_desksetup_state = DESKSETUP_ADD_PAGE;
		SetStatusText(wxString(wxT("Click to add. Drag to move (place off the grid with Alt down).")));
		break;
	case IDDS_ADD_FUNCTION:
		p_desksetup_state = DESKSETUP_ADD_FKT;
		SetStatusText(wxString(wxT("Click to add. Drag to move (place off the grid with Alt down).")));
		break;
	case IDDS_ADD_FADER:
		p_desksetup_state = DESKSETUP_ADD_FADER;
		SetStatusText(wxString(wxT("Click to add. Drag to move (place off the grid with Alt down).")));
		break;
	case IDDS_MOVE:
		p_desksetup_state = DESKSETUP_MOVE;
		SetStatusText(wxString(wxT("Drag to move (place off the grid with Alt down).")));
		break;
	case IDDS_NUMBER:
		p_desksetup_state = DESKSETUP_CHANGE_NUM;
		SetStatusText(wxString(wxT("Click to select item, type new number and press Return.")));
		break;
	case IDDS_DELETE:
		p_desksetup_state = DESKSETUP_DELETE;
		SetStatusText(wxString(wxT("Click to delete.")));
		break;
	}
}

void MainDrawWindow::OnKeyDown(wxKeyEvent& event)
{
	switch(p_state)
	{
		case STATE_DESK:
			break;//end case STATE_DESK
		case STATE_DESK_SETUP:
			if(p_desksetup_state == DESKSETUP_CHANGE_NUM)
			{
				int add = -1;
				if((event.GetKeyCode() >= '0') && (event.GetKeyCode() <= '9'))
				{
					add = event.GetKeyCode() - '0';
				}
				else if((event.GetKeyCode() >= WXK_NUMPAD0) && (event.GetKeyCode() <= WXK_NUMPAD9))
				{
					add = event.GetKeyCode() - WXK_NUMPAD0;
				}
				
				if(add != -1)
				{
					p_change_num *= 10;
					p_change_num += add;
				}
				
				if(event.GetKeyCode() == WXK_DELETE)
					p_change_num = 0;
				if(event.GetKeyCode() == WXK_BACK)
					p_change_num /= 10;
				if(event.GetKeyCode() == WXK_RETURN || event.GetKeyCode() == WXK_NUMPAD_ENTER)
					if(p_selected_item != NULL)
					{
						p_selected_item->set_id(p_change_num);
						p_selected_item = NULL;
					}
				
				RefreshDesk();
			}
			else if(p_selected_item != NULL)
			{
				int x = p_selected_item->get_pos_x();
				int y = p_selected_item->get_pos_y();
				double draw_scale = storage::config.get_draw_scale();
				bool control = event.ControlDown();

				switch(event.GetKeyCode())
				{
					case WXK_NUMPAD_UP:
					case WXK_UP:
						if(control)
							y -= 1;
						else
							y -= (int)(20*draw_scale);
						break;
					case WXK_NUMPAD_DOWN:
					case WXK_DOWN:
						if(control)
							y += 1;
						else
							y += (int)(20*draw_scale);
						break;
					case WXK_NUMPAD_LEFT:
					case WXK_LEFT:
						if(control)
							x -= 1;
						else
							x -= (int)(20*draw_scale);
						break;
					case WXK_NUMPAD_RIGHT:
					case WXK_RIGHT:
						if(control)
							x += 1;
						else
							x += (int)(20*draw_scale);
						break;
					case WXK_NUMPAD_ENTER:
					case WXK_RETURN:
						p_selected_item = NULL;
						return; // get outta here
				}
				
				if(x < 0) x = 0;
				else if(x > 1000*draw_scale) x = (int)(1000*draw_scale);

				if(y < 0) y = 0;
				else if(y > 1000*draw_scale) y = (int)(1000*draw_scale);
			
				p_selected_item->set_pos_x(x);
				p_selected_item->set_pos_y(y);
				
				RefreshDesk();

			}
			else
			{
				if(event.GetKeyCode() == WXK_RETURN || event.GetKeyCode() == WXK_NUMPAD_ENTER)
				{
					switch(p_desksetup_state)
					{
						case DESKSETUP_ADD_FKT:
							p_selected_item = new deskitem(deskitem::T_FUNCTION);
							break;
						case DESKSETUP_ADD_FADER:
							p_selected_item = new deskitem(deskitem::T_FADER);
							break;
						case DESKSETUP_ADD_PAGE:
							p_selected_item = new deskitem(deskitem::T_PAGE);
							break;
						case DESKSETUP_ADD_GROUP:
							p_selected_item = new deskitem(deskitem::T_GROUP);
							break;
					}
					RefreshDesk();
				}
			}
			break;//end case STATE_DESK_SETUP
		case STATE_FUNCTION_SETUP:
			if(p_floating_item || p_floating_fader)
			{
				if(p_hover_item)
				{
					if(event.GetKeyCode() == WXK_CONTROL)
						SetCursor(*p_copy_cursor);
				}
			}
			break;//end case STATE_DESK_FUNCTION
	}		
}

void MainDrawWindow::OnKeyUp(wxKeyEvent& event)
{
	switch(p_state)
	{
		case STATE_DESK:
			break;//end case STATE_DESK
		case STATE_DESK_SETUP:
			break;//end case STATE_DESK_SETUP
		case STATE_FUNCTION_SETUP:
			if(p_floating_item || p_floating_fader)
			{
				if(p_hover_item)
				{
					if(event.GetKeyCode() == WXK_CONTROL)
						SetCursor(*p_move_cursor);
				}
			}
			break;//end case STATE_DESK_FUNCTION
	}		
}			

void MainDrawWindow::OnMouseEvent(wxMouseEvent& event)
{
	int wh, ww;
	GetClientSize(&ww,&wh);
	double winh = (double)wh;
	double winw = (double)ww;
	wxClientDC dc(this);
	wxPoint pos = event.GetLogicalPosition(dc);
	double draw_scale = storage::config.get_draw_scale();
	deskitem* item = NULL;
	functionitem* fitem = NULL;
	faderitem* fditem = NULL;
	bool  changed = false;
	
	//for highlighting
	item = storage::deskitem_for_position(pos.x,pos.y,ww,wh);
	if(item != p_hover_item)
	{
		p_hover_item = item;
		changed = true;
	}
	
	switch(p_state)	
	{
		case STATE_DESK:
			item = storage::deskitem_for_position(pos.x,pos.y,ww,wh);
			if(item)
			{
				if(event.LeftDown())
				{
					if(item->get_type() == deskitem::T_PAGE)
					{
						if(storage::page != item->get_page_id())
						{
							storage::page = item->get_page_id();
							changed = true;
						}
					}
					else if(item->get_type() == deskitem::T_FUNCTION)
					{
						functionitem* fitem = storage::functionitem_for_deskitem(item,storage::page);
						if(fitem)
						{
							fitem->activate();
							changed = true;
						}
					}
					else if(item->get_type() == deskitem::T_GROUP)
					{
						groupselectitem* gitem = storage::groupselectitem_for_deskitem(item,storage::page);
						if(gitem)
						{
							gitem->activate(true);
							gitem->activate(false);
							changed = true;
						}
					}
				}
				if(event.RightDown())
				{
					if(item->get_type() == deskitem::T_FADER)
					{
						faderitem* fitem = storage::faderitem_for_deskitem(item,storage::page);
						if(fitem)
						{
							fitem->off_toggle();
							changed = true;
						}
					}
					else if(item->get_type() == deskitem::T_GROUP)
					{
						groupselectitem* gitem = storage::groupselectitem_for_deskitem(item,storage::page);
						if(gitem)
						{
							gitem->toggle();
							changed = true;
						}
					}
				}
				if(event.LeftDown() || event.Dragging())
				{
					if(item->get_type() == deskitem::T_FADER)
					{
						int winh, winw;
						GetClientSize(&winw,&winh);	
						double facy = winh/(1000.0*storage::config.get_draw_scale());
						int	height = (int)(storage::config.get_fader_height()*facy);

						int y = (int)(item->get_pos_y() * facy);
						
						int position = (int)255-(255*(pos.y - y)/height);
						
						//hardware position
						if(position >= 0)
						{
							if(position != item->pos)
							{
								if(item->pos != position)
								{
									item->pos = position;
									changed = true;
								}
						
								//software position
								faderitem* fitem = storage::faderitem_for_deskitem(item,storage::page);
								if(fitem)
								{
									if(fitem->get_active_pos() != position)
									{
										fitem->set_active_pos(position);
										changed = true;
									}
								}
							}
						}
						else //pos < 0 -> fader button
						{
							faderitem* fitem = storage::faderitem_for_deskitem(item,storage::page);
							if(fitem)
							{
								if(event.ButtonDown())
								{
									fitem->tab();
									changed = true;
								}
							}							
						}
					}
				}
				else if(event.LeftUp())
				{
					if(item->get_type() == deskitem::T_FUNCTION)
					{
						functionitem* fitem = storage::functionitem_for_deskitem(item,storage::page);
						if(fitem)
						{
							fitem->deactivate();
							changed = true;
						}
					}
					else if(item->get_type() == deskitem::T_FADER)
					{
						faderitem* fitem = storage::faderitem_for_deskitem(item,storage::page);
						if(fitem)
						{
							fitem->tab_release();
							changed = true;
						}
					}
				}
				
				if(changed)
				{
					storage::update_key_led_states();
					RefreshDesk();
				}
			}
			break;//end case STATE_DESK
		//----------------------------------------------------------------------------
		//----------------------------------------------------------------------------
		case STATE_DESK_SETUP:
			if(event.LeftDown())
			{
				deskitem* ditem;
				switch(p_desksetup_state)
				{
					case DESKSETUP_CHANGE_NUM:
						p_selected_item = storage::deskitem_for_position(pos.x,pos.y,ww,wh);
						p_change_num = 0;
						changed = true;
						break;
					case DESKSETUP_DELETE:
						ditem = storage::deskitem_for_position(pos.x,pos.y,ww,wh);
						if(ditem != NULL)
						{
							ditem->delete_deps();
							delete ditem;
							changed = true;
						}
						break;
					default:
						p_selected_item = storage::deskitem_for_position(pos.x,pos.y,ww,wh);
						if(!p_selected_item)
						{
							switch(p_desksetup_state)
							{
								case DESKSETUP_ADD_FKT:
									p_selected_item = new deskitem(deskitem::T_FUNCTION);
									break;
								case DESKSETUP_ADD_FADER:
									p_selected_item = new deskitem(deskitem::T_FADER);
									break;
								case DESKSETUP_ADD_PAGE:
									p_selected_item = new deskitem(deskitem::T_PAGE);
									break;
								case DESKSETUP_ADD_GROUP:
									p_selected_item = new deskitem(deskitem::T_GROUP);
									break;
							}
							changed = true;
						}
						break;
				}
				
				if(p_selected_item != NULL && p_desksetup_state != DESKSETUP_CHANGE_NUM)
				{
					int x,y;
					x = (int)((pos.x/winw)*1000*draw_scale);
					y = (int)((pos.y/winh)*1000*draw_scale);
	
					if(x < 0) x = 0;
					else if(x > 1000*draw_scale) x = (int)(1000*draw_scale);
					
					if(y < 0) y = 0;
					else if(y > 1000*draw_scale) y = (int)(1000*draw_scale);
					
					p_selected_item->set_pos_x(x);
					p_selected_item->set_pos_y(y);

					changed = true;
				}
			}
			else if(event.LeftUp())
			{
				if(p_desksetup_state != DESKSETUP_CHANGE_NUM)
				{
					if(p_selected_item)
					{
						p_selected_item = NULL;
						changed = true;
					}
				}
			}
			else if(event.Moving() || event.Dragging())
			{
				if(p_selected_item != NULL && p_desksetup_state != DESKSETUP_CHANGE_NUM)
				{
					int x,y;

					if(event.AltDown())
					{
						//move without a grid
						x = (int)((pos.x/winw)*1000*draw_scale);
						y = (int)((pos.y/winh)*1000*draw_scale);
					}
					else
					{
						//move with grid
						x = (int)((pos.x/winw)*50*draw_scale);
						y = (int)((pos.y/winh)*50*draw_scale);
						x *= (int)(20*draw_scale);
						y *= (int)(20*draw_scale);
					}

					if(x < 0) x = 0;
					else if(x > 1000*draw_scale) x = (int)(1000*draw_scale);
	
					if(y < 0) y = 0;
					else if(y > 1000*draw_scale) y = (int)(1000*draw_scale);
					
					if(p_selected_item->get_pos_x() != x || p_selected_item->get_pos_y() != y)
					{
						p_selected_item->set_pos_x(x);
						p_selected_item->set_pos_y(y);
						changed = true;
					}
				}
			}
			
			if(changed)
				RefreshDesk();
			
			break;//end case STATE_DESK_SETUP
		//----------------------------------------------------------------------------
		//----------------------------------------------------------------------------
		case STATE_FUNCTION_SETUP:
			item = storage::deskitem_for_position(pos.x,pos.y,ww,wh);
			if(item)
			{
				if(event.LeftDown())
				{
					if(item->get_type() == deskitem::T_PAGE)
					{
						if(storage::page != item->get_page_id())
						{
							storage::page = item->get_page_id();
							changed= true;
						}
					}
					else if(item->get_type() == deskitem::T_FUNCTION)
					{
						//Begin Move/Copy/Delete of function
						p_floating_item = storage::functionitem_for_deskitem(item,storage::page, true);
						changed = true;
					}
					else if(item->get_type() == deskitem::T_FADER)
					{
						p_floating_fader = storage::faderitem_for_deskitem(item,storage::page, true);
						changed = true;
					}
				}
				
				if(event.Dragging())
				{
					if(p_floating_item || p_floating_fader)
					{
						if(event.ControlDown())
							SetCursor(*p_copy_cursor);
						else
							SetCursor(*p_move_cursor);
							
						if(item->get_type() == deskitem::T_PAGE)
						{
							if(storage::page != item->get_page_id())
							{
								storage::page = item->get_page_id();
								changed= true;
							}
						}
					}
				}
				
				if(event.ButtonDClick(wxMOUSE_BTN_LEFT))
				{
					if(item->get_type() == deskitem::T_FUNCTION)
					{
						FunctionDialog dlg(this,-1,wxT("Function Setup"));
						dlg.SetItem(item,storage::page);
						dlg.ShowModal();
					}
					else if(item->get_type() == deskitem::T_FADER)
					{
						FaderDialog dlg(this,-1,wxT("Fader Setup"));
						dlg.SetItem(item,storage::page);
						dlg.ShowModal();
					}
					else if(item->get_type() == deskitem::T_GROUP)
					{
						GroupSelectDialog dlg(this,-1,wxT("Group Select Dialog"));
						dlg.SetItem(item,storage::page);
						dlg.ShowModal();
					}
				}
			}
			else if(p_floating_item || p_floating_fader)
			{
				SetCursor(*p_delete_cursor);
			}
			
			if(event.LeftUp())
			{
				SetCursor(wxNullCursor);

				//End of movement
				if(p_floating_item)
				{
					if(item)
					{
						fitem = storage::functionitem_for_deskitem(item,storage::page, true);
						
						if(fitem != p_floating_item)
						{
							if(fitem)
							{
								wxMessageDialog mdlg(this, wxT("There is aleady a function. Do you want to overwrite the function?"), wxT("Overwrite?"), wxYES_NO | wxNO_DEFAULT);
								if(mdlg.ShowModal() == wxID_YES)
								{
									delete fitem;
								}
								else
								{
									p_floating_item = NULL;
									changed= true;
									break;
								}
							}
							
							if(event.ControlDown())
							{
								p_floating_item->copy_to(item, storage::page);
							}
							else
							{
								p_floating_item->move_to(item, storage::page);
							}
							
							changed= true;
						}
					}
					else
					{
						//Delete
						wxMessageDialog mdlg(this, wxT("Do you really want to delete the Function?"), wxT("Delete?"), wxYES_NO | wxNO_DEFAULT);
						if(mdlg.ShowModal() == wxID_YES)
						{
							delete p_floating_item;
							changed= true;
						}
					}
					
					p_floating_item = NULL;
				}

				//End of movement fader
				if(p_floating_fader)
				{
					if(item)
					{
						fditem = storage::faderitem_for_deskitem(item,storage::page, true);
						
						if(fditem != p_floating_fader)
						{
							if(fditem)
							{
								wxMessageDialog mdlg(this, wxT("There is aleady a fader-function. Do you want to overwrite the function?"), wxT("Overwrite?"), wxYES_NO | wxNO_DEFAULT);
								if(mdlg.ShowModal() == wxID_YES)
								{
									delete fditem;
								}
								else
								{
									p_floating_fader = NULL;
									changed= true;
									break;
								}
							}
							
							if(event.ControlDown())
							{
								p_floating_fader->copy_to(item, storage::page);
							}
							else
							{
								p_floating_fader->move_to(item, storage::page);
							}
							
							changed= true;
						}
					}
					else
					{
						//Delete
						wxMessageDialog mdlg(this, wxT("Do you really want to delete the fader-function?"), wxT("Delete?"), wxYES_NO | wxNO_DEFAULT);
						if(mdlg.ShowModal() == wxID_YES)
						{
							delete p_floating_fader;
							changed= true;
						}
					}

					p_floating_fader = NULL;
				}
				
				if(changed)
					RefreshDesk();
			}
			break;//end case STATE_DESK_FUNCTION
	}	
}

void MainDrawWindow::DrawDesk(wxDC& dc)
{
	dc.BeginDrawing();

	dc.SetBackground(p_background_brush);
	dc.SetPen(p_border_pen);
	dc.SetTextForeground(p_text_color);
	dc.Clear();

	int winh, winw;
	GetClientSize(&winw,&winh);	
	
	double facx = winw/(1000.0*storage::config.get_draw_scale());
	double facy = winh/(1000.0*storage::config.get_draw_scale());
	int rounds_size = (int)(5*facx);
		
	int x = 0;
	int y = 0;
	int width = 0;
	int height = 0;
	int height_sb = 0;
	
	storageitemlist::iterator it;
	for(it = storage::list_deskitem.begin();it != storage::list_deskitem.end();it++)
	{
		deskitem* item = (deskitem*)(*it); //static_cast because can't be anything else
		
		x = (int)(item->get_pos_x() * facx);
		y = (int)(item->get_pos_y() * facy);
		if(item->get_type() != deskitem::T_FADER)
		{
			width = (int)(storage::config.get_button_width()*facx);
			height = (int)(storage::config.get_button_height()*facy);
		}
		else
		{
			width = (int)(storage::config.get_fader_width()*facx);
			height = (int)(storage::config.get_fader_height()*facy);
			height_sb = (int)(storage::config.get_fader_button_height()*facy);
		}

		bool act = FALSE;
		bool switching = TRUE;
		bool setup = (p_state == STATE_FUNCTION_SETUP);
		wxString name = wxT("----");
		wxString name2 = wxT("");
		functionitem* function_item = NULL;
		faderitem* fader_item = NULL;
		groupselectitem* group_item = NULL;
		int fader_sw_pos = 0;
		int fader_hw_pos = 0;
		double fader_speed = -1;

		int funcdesk = 1;

		if(p_state != STATE_DESK_SETUP)
		{
			switch(item->get_type())
			{
			case deskitem::T_GROUP:
				name = wxT("Group");
				group_item = storage::groupselectitem_for_deskitem(item,storage::page,setup);
				if(group_item != NULL)
				{
					act = group_item->get_active();
					name2 = group_item->get_name();
				}
				break;
			case deskitem::T_PAGE:
				name = wxT("Page");
				name2 = (wxChar) ('A' - 1 + item->get_page_id());
				if(item->get_page_id() == storage::page)
					act = true;
				break;
			case deskitem::T_FUNCTION:
				function_item = storage::functionitem_for_deskitem(item,storage::page,setup);
				if(function_item != NULL)
				{
					act = function_item->get_active();
					switching = function_item->get_switching();
					name = function_item->get_name();
					name2 = function_item->get_name2();
					funcdesk = function_item->get_page();
				}
				break;
			case deskitem::T_FADER:
				fader_item = storage::faderitem_for_deskitem(item,storage::page,setup);
				if(fader_item != NULL)
				{
					name = fader_item->get_name();
					name2 = fader_item->get_name2();
					fader_sw_pos = fader_item->get_active_pos();
					if(fader_item->get_type() & faderitem::T_SPEED)
					{
						//TODO herausfinden ob so richtig
						fader_speed = fader_item->get_active_pos()*1.25;
					}
				}
				fader_hw_pos = item->pos;
				break;
			}
		}

		if(item == p_hover_item)
			dc.SetPen(p_border_highlite_pen);
		
		switch(item->get_type())
		{
		case deskitem::T_GROUP:
			dc.SetBrush(p_group_brush);
			dc.DrawRoundedRectangle(x, y, width, height, rounds_size);
			break;
		case deskitem::T_PAGE:
			dc.SetBrush(p_page_brush);
			dc.DrawRoundedRectangle(x, y, width, height, rounds_size);
			break;
		case deskitem::T_FUNCTION:
			if(switching)
			{
				if(funcdesk != 1) dc.SetBrush(p_function_brush);
				else dc.SetBrush(p_function_otherpage_brush);
				dc.DrawRoundedRectangle(x, y, width, height, rounds_size);
			}
			else
			{
				if(funcdesk != 1) dc.SetBrush(p_function_pb_brush);
				else dc.SetBrush(p_function_pb_otherpage_brush);
				dc.DrawRoundedRectangle(x, y, width, height, rounds_size);
			}
			break;
		case deskitem::T_FADER:
			dc.SetBrush(p_fader_brush);
			dc.DrawRoundedRectangle(x, y, width, height+3, rounds_size);

			dc.SetBrush(p_fader_button_brush);
			dc.DrawRoundedRectangle(x, y+height+6, width, height_sb, rounds_size);
			break;
		}
		
		if(item == p_hover_item)
			dc.SetPen(p_border_pen);

		if(p_state != STATE_DESK_SETUP)
		{
			if(item->get_type() != deskitem::T_FADER)
			{
				if(act)
					dc.SetBrush(p_led_on_brush);
				else
					dc.SetBrush(p_led_off_brush);
	
				dc.DrawCircle(x + width/2,y - 8, 4);
				
				int tw,th;
				
				dc.GetTextExtent(name,&tw,&th);
				dc.DrawText(name, x + width/2 - tw/2, y);
				dc.GetTextExtent(name2,&tw,&th);
				dc.DrawText(name2, x + width/2 - tw/2, y + height/2);
			}
			else
			{
				dc.SetBrush(p_fader_active_brush);
				dc.DrawRectangle(x + 2, (int)(y + height - (height-4)*fader_sw_pos/255.0), width - 4, (int)((height-4)*fader_sw_pos/255.0));

				dc.SetBrush(*wxBLACK_BRUSH);
				dc.DrawRectangle(x + 2, (int)(y + height - (height-4)*fader_hw_pos/255.0), width - 4, 3);
				
				int tw,th;
				
				if(fader_speed != -1)
				{
					dc.SetTextForeground(p_text_infader_color);
					wxString speed = storage::double_to_str(fader_speed);
					dc.GetTextExtent(speed,&tw,&th);
					dc.DrawText(speed, x + width/2 - tw/2, y + 17);
					dc.SetTextForeground(p_text_color);
				}
				
				dc.GetTextExtent(name,&tw,&th);
				dc.DrawText(name, x + width/2 - tw/2, y + height + 5);
				dc.GetTextExtent(name2,&tw,&th);
				dc.DrawText(name2, x + width/2 - tw/2, y + height + 5 + height_sb/2);
			}
		}
	
		if(p_state == STATE_DESK_SETUP || item->get_type() == deskitem::T_FADER)
		{
			wxString id;
			if(p_desksetup_state == DESKSETUP_CHANGE_NUM && item == p_selected_item)
			{
				dc.SetTextForeground(*wxRED);
				id = storage::int_to_str(p_change_num);
			}
			else
			{
				dc.SetTextForeground(p_text_infader_color);
				id = storage::int_to_str(item->get_id());
			}
			
			int tw,th;
			dc.GetTextExtent(id,&tw,&th);
			dc.DrawText(id,x + width/2 - tw/2, y + 2);
			dc.SetTextForeground(p_text_color);
		}
	}
	
	dc.EndDrawing();
}
