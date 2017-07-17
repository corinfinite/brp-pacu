/*
 * generator.h
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

#ifndef __BRP_PACU_GENERATOR_H__
#define __BRP_PACU_GENERATOR_H__

#include <jack/jack.h>

enum generator_output_type {PINK_NOISE, WHITE_NOISE};

void generator_setup();
void generator_fill_buffer(jack_nframes_t nframes, 
                                    jack_default_audio_sample_t *buffer);

// Mute functions
int generator_is_muted();
void generator_set_muted(int state);
void generator_toggle_muted();

// Volume functions
float generator_get_volume();
void generator_set_volume(float new_volume);

#endif	/* __BRP_PACU_GENERATOR_H__ */
