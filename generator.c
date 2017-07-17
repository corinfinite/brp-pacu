/*
 * generator.c
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

#include "generator.h"
#include <jack/jack.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h> //memcpy

int muted = 1;
enum generator_output_type output_type = PINK_NOISE;
static float working_buffer[8192];
float b0, b1, b2, b3, b4, b5, b6, white;
float scale_it = 1.0f; // was 0.98, which is wrong (shifts the
                       // poles to create a highpass. Let's hope
                       // this wasn't a quick hack to work around
                       // a numerical instability...
float volume = 5.05;

void generator_setup() {
	b0 = 0;
    b1 = 0;
    b2 = 0;
    b3 = 0;
    b4 = 0;
    b5 = 0;
    b6 = 0;
    white = 0;
}

void generator_fill_buffer_pink_noise(jack_nframes_t nframes) {
	for (int k = 0; k < nframes; k++) {
		white = ((float)(rand() % 10000) - 10000.0 / 2.0) / 999900.0;
		// http://www.firstpr.com.au/dsp/pink-noise/#Filtering
		// Based on a filter by  Robert Bristow-Johnson
		// See Jnoise or JAPA for similar implementations:
		// http://kokkinizita.linuxaudio.org/linuxaudio/
		b0 = (0.99886 * b0 + white * 0.0555179) * scale_it;
		b1 = (0.99332 * b1 + white * 0.0750759) * scale_it;
		b2 = (0.96900 * b2 + white * 0.1538520) * scale_it;
		b3 = (0.86650 * b3 + white * 0.3104856) * scale_it;
		b4 = (0.55000 * b4 + white * 0.5329522) * scale_it;
		b5 = (-0.7616 * b5 - white * 0.0168980) * scale_it;
		working_buffer[k] = (b0 + b1 + b2 + b3 + b4 + b5 + b6 +
							 (white * 0.5362) * scale_it) *
							(pow(2.0, volume + 29) /
							 (pow(2.0, 32.0)));
		b6 = (white * 0.115926) * scale_it;
	}
}

void generator_fill_buffer_white_noise(jack_nframes_t nframes) {
	for (int k = 0; k < nframes; k++) {
		white = ((float)(rand() % 10000) - 10000.0 / 2.0) / 999900.0;
		working_buffer[k] = ((white) * scale_it) *
							(pow(2.0, volume + 29) / (pow(2.0, 32.0)));
	}
}

/*
 * Fills the JACK buffer with the appropriate noise.
 */
void generator_fill_buffer(jack_nframes_t nframes, 
                                    jack_default_audio_sample_t *jack_buffer){
	if (muted) {
		for (int k = 0; k < nframes; k++) {
			working_buffer[k] = 0.0;
		}
		memcpy(jack_buffer, working_buffer,
                   sizeof(jack_default_audio_sample_t) * nframes);
		return;
	}

	switch (output_type) {
		case PINK_NOISE :
			generator_fill_buffer_pink_noise(nframes);
			break;
		
		case WHITE_NOISE :
			generator_fill_buffer_white_noise(nframes);
			break;
	}

	memcpy(jack_buffer, working_buffer,
                   sizeof(jack_default_audio_sample_t) * nframes);
}

// Mute functions
int generator_is_muted() {
	return muted;
}

void generator_set_muted(int state) {
	muted = state;
}

void generator_toggle_muted() {
	muted ^= 1;
}

//Volume functions
float generator_get_volume() {
	return volume;
}

void generator_set_volume(float new_volume) {
	volume = new_volume;
}
