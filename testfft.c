/*
* testfft.c : Simply perform the fft of channel 1 and channel 2 inputs,
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
#include <fftw.h>
#include <math.h>
#include "main.h"
#include "testfft.h"


int fft_capture(struct FFT_Frame * session)
{
   int k;
   double datapt;
   ///////////////////////////////////
   double * fft;
   short * buf;
   fftw_plan plan = session->plan;
   fft = (double *)malloc(sizeof(double) * N_FFT);

   fftw_complex * in, *out; //, power_spectrum[N/2+1];
   in = fftw_malloc ( sizeof ( fftw_complex ) * N_FFT );
   out = fftw_malloc ( sizeof ( fftw_complex ) * N_FFT );

   ///////////////////////////////////////////////////////////////////

   buf = session->buffer_data_1;
   for (k = 0;k < N_FFT; k++)
   {
      // Fill empty slots with 0's, Copy interleaved audio data
      fft[k] = 0;
   }

   for (k = 0; k < N_FFT; k++)
   {
      c_re(in[k]) = (double) buf[k];
      c_im(in[k]) = 0.0;
   }

   fftw_one(plan, in, out);

   for (k = 0; k < N_FFT; k++)
   {
      datapt = (double)(sqrt(c_re(out[k]) * c_re(out[k]) + c_im(out[k]) * c_im(out[k]) ));
      fft[k] = datapt;
   }
   for (k = 0; k < N_FFT; k++)
   {
      session->fft_returned_1[k] = fft[k] / 32767.0 + 0.00000001;
   }

   buf = session->buffer_data_2;
   for (k = 0;k < N_FFT; k++)
   {
      // Fill empty slots with 0's, Copy interleaved audio data
      fft[k] = 0;
   }

   for (k = 0; k < N_FFT; k++)
   {
      c_re(in[k]) = (double) buf[k];
      c_im(in[k]) = 0.0;
   }

   fftw_one(plan, in, out);

   for (k = 0; k < N_FFT; k++)
   {
      datapt = (double)(sqrt(c_re(out[k]) * c_re(out[k]) + c_im(out[k]) * c_im(out[k]) ));
      fft[k] = datapt;
      //fft[k] = 20.0 * log10(datapt + 1);
   }
   for (k = 0; k < N_FFT; k++)
   {
      session->fft_returned_2[k] = fft[k] / 32767.0 + 0.00000001;
   }
   free(fft);
   fftw_free(in);
   fftw_free(out);
   return 0;
}

int impulse_capture(struct FFT_Frame * session)
{
   int k;
   int tmr;
   ///////////////////////////////////
   short * buf;
   fftw_plan plan = session->plan;
   fftw_plan reverse_plan = session->reverse_plan;

   fftw_complex * in1, *out1; //, power_spectrum[N/2+1];
   fftw_complex * in2, *out2; //, power_spectrum[N/2+1];
   in1 = fftw_malloc ( sizeof ( fftw_complex ) * N_FFT );
   out1 = fftw_malloc ( sizeof ( fftw_complex ) * N_FFT );
   in2 = fftw_malloc ( sizeof ( fftw_complex ) * N_FFT );
   out2 = fftw_malloc ( sizeof ( fftw_complex ) * N_FFT );

   ///////////////////////////////////////////////////////////////////

   buf = session->buffer_data_1;

   for (k = 0; k < N_FFT; k++)
   {
      c_re(in1[k]) = (double) buf[k];
      c_im(in1[k]) = 0.0;
   }

   fftw_one(plan, in1, out1);


   buf = session->buffer_data_2;

   for (k = 0; k < N_FFT; k++)
   {
      c_re(in2[k]) = (double) buf[k];
      c_im(in2[k]) = 0.0;
   }

   fftw_one(plan, in2, out2);

   for (k = 0; k < N_FFT; k++)
   {
      c_re(in1[k]) = (double)(  c_re(out1[k]) * c_re(out2[k]) + c_im(out2[k]) * c_im(out1[k])  ) / \
                     (  c_re(out2[k]) * c_re(out2[k]) + c_im(out2[k]) * c_im(out2[k]) );

      c_im(in1[k]) = (double)( c_re(out2[k]) * c_im(out1[k]) - c_im(out2[k]) * c_re(out1[k])  ) / \
                     (  c_re(out2[k]) * c_re(out2[k]) + c_im(out2[k]) * c_im(out2[k]) );
      // This code is an explanation for the above lines, do not delete
      // a = c_re(out1)
      // b = c_im(out1)
      // c = c_re(out2)
      // d = c_im(out2)
      // (a+b*i)/(c+d*i) = (a*c+c*b*i-d*i*a+d*b)/(c^2+d^2)
      // The impulse response, h(t) is the Inv Fourier Trxfm of the above line, H(f) = Y(f) / X(f) =  ( Y(f) x X*(f) ) / ( X(f) x X*(f) )
   }

   fftw_one(reverse_plan, in1, out1);

   for (k = 0; k < N_FFT; k++)
   {
      session->rfft_returned_1[k] = c_re(out1[k]) / 32767.0;
   }
   fftw_free(in1);
   fftw_free(out1);
   fftw_free(in2);
   fftw_free(out2);
   return 0;
}
