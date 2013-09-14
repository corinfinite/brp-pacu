BRP-PACU for Mac OS X (Intel architecture only)
Version 2.1.2 and higher require a 64-bit computer. For 32-bit computers, download and use Version 2.1.1.

Web site
_______________________________________
http://sourceforge.net/projects/brp-pacu

Dependencies
_______________________________________
You should first download and install:

Jack-OS X from
http://www.jackosx.com/

Instructions
_______________________________________
To install BRP-PACU, drag the BRP-PACU icon into the Application folder.
The double-click on BRP-PACU to start.

If Jack-OS X is not present or not running, a warning will appear, and Jack Pilot will open. CLick on "Start" on the JackPilot window, then on "Continue"" on the warning box.

If Jack Pilot does not open, this means that Jack-OS X is not installed correctly.

Never before asked questions
-------------------------------------------
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
- There currently is no Linux port for any of these programs and I needed one.  Also I believe 
   anyone who knows how to perform the transfer function properly on an audio system should be 
   able to without selling your soul with some ridiculous EULA and forking over $1100.  The 
   barrier to entry in any market should be knowledge and skill, not overpriced tools.  There are many
   markets already headed in this direction.

What if I try it and it doesn't work?
- Email me and I can probably figure it out.  My email is lm317t@gmail.com.  Also try the mailing list, 
   it should be working.

Why is there no documentation?
- Channel 1 is the output of the system we are observing (measured), channel 2 is the input (reference).  
   You also need a decent calibrated omnidrectional microphone (reasonably flat 20Hz-20kHz) and either a
   USB-Preamp like the 2-channel M-Audio, or a mixer with a 30dB pad or so going into the laptop mic input.  No Pad is
   neccessary if you are lucky enough to have a laptop or PC with a line input.  The headphone out will have the pink noise.

How do you handle a delay between measured and referenced signals?
- There is an automatic delay finding button.  You can also insert a custom delay if you want.

Is there a way to find the impulse response?
- It is in the menu under action
