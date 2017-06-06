# BRP-PACU - An Audio Configuration utility
Wikipedia: en.wikipedia.org/wiki/BRP-PACU

## Dependencies
To compile BRP-PACU on Linux, this must be installed:
* JACK. Any recent version will work, just take what the distribution provides, the package is probably named "jackd".
– Tip: If jack is not already installed on your system, try to install the package "qjackctl" which depends on JACK.

* The development files that matches the installed version of JACK.
– Finding the right development package: Search for packages with libjack in their names. Notice the name of the installed libjack*, and find the most similar named package which name is ending in "-dev", and install that one.

* GTK databox, library and header files, in version 0.9.1-1 (that will work) or preferable newer.
        – In Ubuntu 10.10 you can install the package libgtkdatabox-0.9.1-1-dev , but:
        – It is recommended to use a newer version, because there are a few UI tweaks in the latest gtkdatabox. Get it from the source code released on https://sourceforge.net/projects/gtkdatabox

* FFTW version 3

* the GTK+ and Glade stuff (including its dependencies such as Glib and Pango), with these packages (and their dependencies)
	libglade2-dev
	libgtk2.0-dev
	libglib2.0-dev
	GTK+ stable release from http://gtk.org
* The building tools in these packages:
	build-essential
	autotools-dev
	autoconf
	automake
	pkg-config
	make
	gcc

## Building

If you are building from the git repo you must first run `./autogen.sh` to setup the build.

Run the traditional `./configure`, `make`, and `make install` to install BRP-PACU.

When BRP-PACU is installed on your system using `make install`, the executable is named “BRP_PACU”. It can be started from the Run dialog (that comes up when pressing ALt-F2), or from a command line which will give extra debugging information.

If you just ran `make` you can start BRP-PACU `./BRP-PACU`.

## A tip for JACK and PulseAudio co-existense (not unique to BRP-PACU)

A way to automate the switching between which software that can get direct (and thus exclusive) access to the audio hardware ins and outs.

In Ubuntu (at least) the file /etc/pulse/client.conf needs to have the line:
autospawn = no

and put “pulseaudio -k” in the jackd start script and “pulseaudio --start” in the jackd stop script (can be done from qjackctl under setup->options-> execute script at startup).

Otherwise pulseaudio will grab ownership instantly on any sound card you try and you will never get jackd to start.

## Never before asked questions
What is BRP-PACU?
- It is an analysis tool to configure any sound system with an equalizer.  It compares the
   output of the system to the input of the system and allows you to use this data to
   perform final equalization by matching the results with actual DSP/EQ.

How do you do this?
- There are many tutorials on doing this, but it takes practice, experience, and a good
   ear.  You could try: http://www.sounddevices.com/notes/usbpre/usbpre-with-sia-smaart-software/
   its a brief introduction to the concept, although the USBPre is not supported by linux as of writing this,
   so you couldn't use it with this software.  Try the M-Audio usb preamp, its what I use.  You
   also need a decent omnidirectional calibrated mic (reasonably flat 20Hz-20kHz).

Isn't this software basically like what XYZ company sells for $1100?
- Yes

Why are you giving it away for free?
- There currently is no Linux port for any of these programs and I needed one.  Also I believe anyone who knows how to perform the transfer function properly on an audio system should be able to without selling your soul with some ridiculous EULA and forking over $1100.  The barrier to entry in any market should be knowledge and skill, not overpriced tools.  There are many
   markets already headed in this direction.

What if I try it and it doesn't work?
- Email me and I can probably figure it out.  My email is lm317t@gmail.com.  Also try the mailing list, it should be working.

Why is there no documentation?
- "Measured Signal" is the output of the system we are observing, "Reference Signal" is the input to the system we are observing. You also need a decent calibrated omnidrectional microphone (reasonably flat 20Hz-20kHz) and either a USB-Preamp like the 2-channel M-Audio, or a mixer with a 30dB pad or so going into the laptop mic input.  No Pad is necessary if you are lucky enough to have a laptop or PC with a line input.  The headphone out will have the pink noise.

How do you handle a delay between measured and referenced signals?
- There is an automatic delay finding button.  You can also insert a custom delay if you want.

Is there a way to find the impulse response?
- It is in the menu under action
