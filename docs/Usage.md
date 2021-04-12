# Basic Usage
- "Measured Signal" is the output of the system we are observing, "Reference Signal" is the input to the system we are observing. You also need a decent calibrated omnidrectional microphone (reasonably flat 20Hz-20kHz) and either a USB-Preamp like the 2-channel M-Audio, or a mixer with a 30dB pad or so going into the laptop mic input.  No Pad is necessary if you are lucky enough to have a laptop or PC with a line input.  The headphone out will have the pink noise.

How do I learn more about dual channel FFT analysis?
- There are many online resources on dual FFT analysis, but it takes practice, experience, and a good
   ear.  You could try: http://www.sounddevices.com/notes/usbpre/usbpre-with-sia-smaart-software/
   its a brief introduction to the concept, although the USBPre is not supported by linux as of writing this,
   so you couldn't use it with this software.  Try the M-Audio usb preamp, its what I use.  You
   also need a decent omnidirectional calibrated mic (reasonably flat 20Hz-20kHz).

How do you handle a delay between measured and referenced signals?
- There is an automatic delay finding button.  There you can also insert a custom delay if you want.

Is there a way to find the impulse response?
- It is in the menu under "View"

## JACK and PulseAudio co-existense (not unique to BRP-PACU)
A way to automate the switching between which software that can get direct (and thus exclusive) access to the audio hardware ins and outs.

In Ubuntu (at least) the file /etc/pulse/client.conf needs to have the line:
autospawn = no
and put “pulseaudio -k” (or “pactrl exit”) in the jackd start script and “pulseaudio --start” in the jackd stop script (can be done from qjackctl under Setup->Options-> execute script at startup).

Or you may install the pulseaudio-module-jack package and enable Jack D-Bus (from qjackctl under Setup->Misc-> Enable Jack D-Bus Interface.

Otherwise pulseaudio will grab ownership instantly on any sound card you try and you will never get jackd to start.
