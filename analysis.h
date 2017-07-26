/*
* analysis.h : defines Audio_Sesssion struct, various FFT Parameters
*             such as window size.
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
#include "main.h"
#include <fftw3.h>
#include <math.h>
#define DELAY_BUFFER_SIZE 44100
#define N_FFT 8192
#define RATIO 2
#define MAX_AVG_NUM 32
#define BUFF_NUM 32
#define FSAMP 44100
#define SCALEF 32765
#define NYQUIST FSAMP / 2
#define PLOT_PTS (N_FFT) / RATIO
#define FBIN (float)((float)NYQUIST) / (((float)PLOT_PTS) / 1.0)
#define BUFSIZE 256
#define B_N N_FFT / BUFSIZE

#ifndef ANALYSIS_H
#define ANALYSIS_H

struct AUDIO_SESSION {
    fftw_plan plan;
    short *buffer_data;
    double *fft_returned;
};

int fft_capture(struct FFT_Frame *session);

int impulse_capture(struct FFT_Frame *session);
#endif
