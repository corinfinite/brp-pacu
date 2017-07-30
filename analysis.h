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
#include <jack/jack.h>
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

#define c_re(c) ((c)[0]) // Get real element of FFTW complex type
#define c_im(c) ((c)[1]) // Get imaginary element of FFTW complex type

// An AnalysisSession contains the components of a dual channel analysis
struct AnalysisSession {
	// 1 = measured, 2 = reference

	GMutex *input_audio;
	/* Begin data protected by input_audio mutex */
	/* This is where samples are passed from JACK to BRP-PACU for analysis */
	int unprocessed_samples; // Number of samples not processed
	float *jack_buffer_mea;  // Unprocessed samples from measured input
	float *jack_buffer_ref;  // Unprocessed samples from reference input
	/* End data protected by input_audio mutex */

	short *delay;
    int delay_size;
    short *prewin_buffer_data_1; // Data from channel
    short *prewin_buffer_data_2;
    short *buffer_data_1; // data from channel after window function
    short *buffer_data_2; // data from channel after window function

	fftw_complex *plan_buf1;
    fftw_complex *plan_buf2;
	fftw_plan plan1;              // FFT Plan
    fftw_plan plan2;              // FFT Plan
    fftw_plan reverse_plan;       // FFT Plan
    double *fft_result_mag_mea;
    double *fft_result_mag_ref;

	double *transfer_fn;
    double *impulse_response;

    char find_delay;
    char find_impulse;
};

struct AnalysisSession *analysis_create();

void analysis_destroy(volatile struct AnalysisSession *session);

gboolean analysis_process(volatile struct AnalysisSession *session);

int impulse_capture(struct AnalysisSession *session);
#endif
