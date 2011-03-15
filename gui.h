/*
* gui.h : defines window sizes, and functions used
*
*
*
* Copyright (C) 2007-2008 Brian Phelps(lm317t@gmail.com)
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU Library General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include <gtk/gtk.h>
#include "main.h"


#ifndef GUI_H
#define GUI_H

#define WINDOW_H 600
#define WINDOW_W 950

#define IMPULSE_WINDOW_H 500
#define IMPULSE_WINDOW_W 900

#define N_BUFF 5


gboolean gui_idle_func (struct FFT_Frame * data);

gboolean create_gui (struct FFT_Frame * data, char* datadir);

#endif
