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

#ifndef __CONFIGITEM_HH
#  define __CONFIGITEM_HH

#include "storage_item.h"

class configitem : public storage_item
{
public:
	configitem();
	virtual ~configitem();

	wxString get_s_param(int id);
	
	bool set_param(int id,wxString value);

	double get_draw_scale() { return p_draw_scale; };
	int get_button_width() { return p_button_width; };
	int get_button_height() { return p_button_height; };
	int get_fader_width() { return p_fader_width; };
	int get_fader_height() { return p_fader_height; };
	int get_fader_button_height() { return p_fader_button_height; };
	bool get_translucent_buttons() { return p_translucent_buttons; };
	bool get_translucent_fader() { return p_translucent_fader; };
	enum
	{
		RED,
		GREEN,
		BLUE
	};
	enum
	{
		PAGE,
		FUNCTION,
		FUNCTION_OTHERPAGE,
		FUNCTION_PB,
		FUNCTION_PB_OTHERPAGE,
		GROUP,
		FADER,
		FADER_BUTTON,
		FADER_ACTIVE,
		LED_ON,
		LED_OFF,
		BORDER,
		BORDER_HIGHLITE,
		BACKGROUND,
		TEXT,
		TEXT_FADER
	};
	unsigned char* get_color(int index) { return p_color[index]; }; 

private:
	double p_draw_scale;
	int p_button_width;
	int p_button_height;
	int p_fader_width;
	int p_fader_height;
	int p_fader_button_height;
	bool p_translucent_buttons;
	bool p_translucent_fader;
	unsigned char p_color[16][3];
};

#endif //__CONFIGITEM_HH
