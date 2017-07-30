/*
* analysis.c : Simply perform the fft of channel 1 and channel 2 inputs,
*             Assumes data is windowed.  Modifies and reads input memory pointed
*             to by struct session.
*
*
* Copyright (C) 2007 Brian Phelps(lm317t@gmail.com)
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
#include "analysis.h"
#include <fftw3.h>
#include <glib.h>
#include <jack/jack.h>
#include <math.h>

// Creates a new AnalysisSession
struct AnalysisSession *analysis_create() {
    int k;
    struct AnalysisSession *session =
        (struct AnalysisSession *)malloc(sizeof(struct AnalysisSession));

	session->input_audio = (GMutex *) malloc(sizeof(GMutex));
	g_mutex_init(session->input_audio);
	session->unprocessed_samples = 0;
	session->jack_buffer_mea = (float *)malloc(sizeof(float) * 8192);
	session->jack_buffer_ref = (float *)malloc(sizeof(float) * 8192);

	session->buffer_data_1 = (short *)malloc(sizeof(short) * N_FFT);
    session->buffer_data_2 = (short *)malloc(sizeof(short) * N_FFT);
	session->delay = (short *)malloc(sizeof(short) * DELAY_BUFFER_SIZE);
	session->delay_size = 0;
	session->prewin_buffer_data_1 = (short *)malloc(sizeof(short) * N_FFT);
    session->prewin_buffer_data_2 = (short *)malloc(sizeof(short) * N_FFT);

	session->plan_buf1 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N_FFT);
    session->plan_buf2 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N_FFT);
	session->plan1 = fftw_plan_dft_1d(N_FFT, session->plan_buf1, session->plan_buf1, FFTW_FORWARD, FFTW_ESTIMATE);
    session->plan2 = fftw_plan_dft_1d(N_FFT, session->plan_buf2, session->plan_buf2, FFTW_FORWARD, FFTW_ESTIMATE);
    session->reverse_plan = fftw_plan_dft_1d(N_FFT, session->plan_buf1, session->plan_buf1, FFTW_BACKWARD, FFTW_ESTIMATE);

	session->fft_result_mag_mea = (double *)malloc(sizeof(double) * N_FFT);
    session->fft_result_mag_ref = (double *)malloc(sizeof(double) * N_FFT);
	session->transfer_fn = (double *)malloc(sizeof(double) * N_FFT);
    session->impulse_response = (double *)malloc(sizeof(double) * N_FFT);

    session->find_delay = 0;
    session->find_impulse = 0;

    for (k = 0; k < N_FFT; k++) {
        session->delay[k] = 0;
        session->prewin_buffer_data_1[k] = 0;
        session->prewin_buffer_data_2[k] = 0;
        session->buffer_data_1[k] = 0;
        session->buffer_data_2[k] = 0;
        session->fft_result_mag_mea[k] = 0;
        session->fft_result_mag_ref[k] = 0;
        session->delay[k] = 0;
    }

    return session;
}

void analysis_destroy(volatile struct AnalysisSession *session) {
	free(session->input_audio);
	free(session->jack_buffer_mea);
	free(session->jack_buffer_ref);

	fftw_destroy_plan(session->plan1);
    fftw_destroy_plan(session->plan2);
    fftw_destroy_plan(session->reverse_plan);
    free(session->delay);
    free(session->buffer_data_1);
    free(session->buffer_data_2);
    free(session->prewin_buffer_data_1);
    free(session->prewin_buffer_data_2);
    free(session->fft_result_mag_mea);
    free(session->fft_result_mag_ref);
	free(session->transfer_fn);
	free(session->impulse_response);
    free((struct AnalysisSession *)session);
}

void analysis_process_new_input(volatile struct AnalysisSession *session) {
	int k, j, period_size;

	period_size = session->unprocessed_samples;
	// fprintf(stderr, "The period size is %d\n",period_size);
	//
	// Fill delay with old data
	for (k = 0; k < (DELAY_BUFFER_SIZE - period_size); k++) {
		// Rotate dellay data to the left to make room for new
		// samples
		session->delay[k] = session->delay[k + period_size];
	}

	j = N_FFT - period_size;
	for (k = DELAY_BUFFER_SIZE - period_size; k < DELAY_BUFFER_SIZE; k++) {
		//// Copy old delay data to end of delayed buffer 2
		// Copy old buffer data to end of delay buffer
		session->delay[k] =
			session->prewin_buffer_data_2[j - N_FFT + period_size];
		j++;
	}

	// Rotate data to the left to make room for new samples
	for (k = 0; k < (N_FFT - period_size); k++) {
		session->prewin_buffer_data_1[k] =
			session->prewin_buffer_data_1[k + period_size];
		session->prewin_buffer_data_2[k] =
			session->prewin_buffer_data_2[k + period_size];
	}

	j = 0;
	for (k = N_FFT - period_size; k < N_FFT; k++) {
		// copy channels to the end of the data

		session->prewin_buffer_data_1[k] =
			(short)32767.0 * session->jack_buffer_mea[j]; // Copy Begining of
										// Audio buff to end of
										// delay from last
										// buffer fill
		session->prewin_buffer_data_2[k] = (short)32767.0 * session->jack_buffer_ref[j];
		j++;
	}

	for (k = 0; k < N_FFT; k++) {
		// Copy data to working buffer #2
		session->buffer_data_1[k] = session->prewin_buffer_data_1[k];
		// Copy data to working #1 and apply delay
		if (k - session->delay_size >= 0)
			session->buffer_data_2[k] =
				session
					->prewin_buffer_data_2[k -
										   session->delay_size]; // copy end
		// of normal
		// buffer to
		// working
		// buffer
		else
			session->buffer_data_2[k] =
				session->delay[k + DELAY_BUFFER_SIZE -
							   session->delay_size]; // copy
													 // most
													 // recent samples
													 // of the delay
													 // buffer to
													 // beginning
													 // (oldest)
													 // buffer_data_2
	}

	analysis_apply_window(session);
	session->unprocessed_samples = 0;
}

/*
 * Applies a window to the incoming audio
 */
void analysis_apply_window(volatile struct AnalysisSession *session) {
	for (int k = 0; k < N_FFT; k++)
	{
		// Apply Window function
		// Blackman window
		// https://en.wikipedia.org/wiki/Window_function#Blackman_windows
		// Previously reported to cause errors in the response but appears fine
		// as of writing
		session->buffer_data_1[k] = (short)(
		                                    (((float)session->buffer_data_1[k])*(0.42 - 0.5 *
		                                                                          cos(2.0 * M_PI * ((float)k) / (  ((float)N_FFT) - 1.0))
		                                                                          + 0.08 * cos(4.0 * M_PI * ((float)k) / (((float)N_FFT) -
		                                                                                                                1.0)))  ));
		session->buffer_data_2[k] = (short)(
		                                    ((float)session->buffer_data_2[k])*(0.42 - 0.5 * cos(2.0 *
		                                                                                         M_PI * ((float)k) / (  ((float)N_FFT) - 1.0))
		                                                                        + 0.08 * cos(4.0 * M_PI * ((float)k) / (((float)N_FFT) -
		                                                                                                              1.0))));
	}
}

int fft_capture(struct AnalysisSession *session) {
    int k;
    double datapt;
    ///////////////////////////////////
    double *fft;
    short *buf;
    fftw_complex *in, *out;

    fftw_plan plan = session->plan1;
    fft = (double *)malloc(sizeof(double) * N_FFT);

    //fftw_complex *in, *out; //, power_spectrum[N/2+1];
    //in = fftw_malloc(sizeof(fftw_complex) * N_FFT);
    //out = fftw_malloc(sizeof(fftw_complex) * N_FFT);

    ///////////////////////////////////////////////////////////////////

    buf = session->buffer_data_1;
    in  = session->plan_buf1;
    out = session->plan_buf1;
    for (k = 0; k < N_FFT; k++) {
        // Fill empty slots with 0's, Copy interleaved audio data
        fft[k] = 0;
    }

	// Copy real values from buffer into complex fftw array
    for (k = 0; k < N_FFT; k++) {
        c_re(in[k]) = (double)buf[k];
        c_im(in[k]) = 0.0;
    }

    //fftw_one(plan, in, out);
    fftw_execute(plan);

	// Calculate power:
    for (k = 0; k < N_FFT; k++) {
        datapt = (double)(sqrt(c_re(out[k]) * c_re(out[k]) +
                               c_im(out[k]) * c_im(out[k])));
        fft[k] = datapt;
    }
	// Put result in
    for (k = 0; k < N_FFT; k++) {
        session->fft_result_mag_mea[k] = fft[k] / 32767.0 + 0.00000001;
    }

	////////////////////////////////////////////////////////////////////////

    buf = session->buffer_data_2;
    for (k = 0; k < N_FFT; k++) {
        // Fill empty slots with 0's, Copy interleaved audio data
        fft[k] = 0;
    }

    for (k = 0; k < N_FFT; k++) {
        c_re(in[k]) = (double)buf[k];
        c_im(in[k]) = 0.0;
    }

    //fftw_one(plan, in, out);
    fftw_execute(plan);

    for (k = 0; k < N_FFT; k++) {
        datapt = (double)(sqrt(c_re(out[k]) * c_re(out[k]) +
                               c_im(out[k]) * c_im(out[k])));
        fft[k] = datapt;
        // fft[k] = 20.0 * log10(datapt + 1);
    }
    for (k = 0; k < N_FFT; k++) {
        session->fft_result_mag_ref[k] = fft[k] / 32767.0 + 0.00000001;
    }
    free(fft);
    return 0;
}

int impulse_capture(struct AnalysisSession *session) {
    int k;
    ///////////////////////////////////
    short *buf;

    fftw_complex *in1, *in2, *out1, *out2;

    fftw_plan plan1 = session->plan1;
    fftw_plan plan2 = session->plan2;
    fftw_plan reverse_plan = session->reverse_plan;

    ///////////////////////////////////////////////////////////////////

    buf  = session->buffer_data_1;
    in1  = session->plan_buf1;
    out1 = session->plan_buf1;
    in2  = session->plan_buf2;
    out2 = session->plan_buf2;

    for (k = 0; k < N_FFT; k++) {
        c_re(in1[k]) = (double)buf[k];
        c_im(in1[k]) = 0.0;
    }

    //fftw_one(plan, in1, out1);
    fftw_execute(plan1);

    buf = session->buffer_data_2;

    for (k = 0; k < N_FFT; k++) {
        c_re(in2[k]) = (double)buf[k];
        c_im(in2[k]) = 0.0;
    }

    //fftw_one(plan, in2, out2);
    fftw_execute(plan2);

    for (k = 0; k < N_FFT; k++) {
        c_re(in1[k]) =
            (double)(c_re(out1[k]) * c_re(out2[k]) +
                     c_im(out2[k]) * c_im(out1[k])) /
            (c_re(out2[k]) * c_re(out2[k]) + c_im(out2[k]) * c_im(out2[k]));

        c_im(in1[k]) =
            (double)(c_re(out2[k]) * c_im(out1[k]) -
                     c_im(out2[k]) * c_re(out1[k])) /
            (c_re(out2[k]) * c_re(out2[k]) + c_im(out2[k]) * c_im(out2[k]));
        // This code is an explanation for the above lines, do not delete
        // a = c_re(out1)
        // b = c_im(out1)
        // c = c_re(out2)
        // d = c_im(out2)
        // (a+b*i)/(c+d*i) = (a*c+c*b*i-d*i*a+d*b)/(c^2+d^2)
        // The impulse response, h(t) is the Inv Fourier Trxfm of the above
        // line, H(f) = Y(f) / X(f) =  ( Y(f) x X*(f) ) / ( X(f) x X*(f) )
		// X(f): FFT of reference signal
		// Y(f): FFT of measured signal
		//
		// Further reading: "Dual Channel FFT Analysis (Part I)" (BV0013) - Brüel & Kjær
		// https://www.bksv.com/media/doc/bv0013.pdf
    }

    //fftw_one(reverse_plan, in1, out1);
    fftw_execute(reverse_plan);

    for (k = 0; k < N_FFT; k++) {
        session->impulse_response[k] = c_re(out1[k]) / 32767.0;
    }
    return 0;
}
