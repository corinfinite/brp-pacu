# BRP-PACU - An Audio Configuration utility
BRP-PACU is a dual channel FFT audio analysis tool. It is designed to aid in the equalization and time alignment of a sound system. It compares the output of the system to the input of the system to obtain the transfer function of the system.u It is similar to commercial products like (Smaart)[https://en.wikipedia.org/wiki/Smaart].

## Dependencies
To install these dependencies from the command line on Ubuntu 16.04 (Xenial) run  
```
sudo apt install build-essential libfftw3-dev libc6 libglade2-dev libglib2.0-dev libgtk2.0-dev libgtkdatabox-0.9.2-0-dev libjack-jackd2-dev
```
This list of packages was tested on Ubuntu Studio 16.04.

* `build-essential` for build tools
* jack2. Any recent version will work, just take what the distribution provides, the package is probably named "jackd".  
 * Tip: If jack is not already installed on your system, try to install the package "qjackctl" which depends on JACK and provides an easy way to manage JACK connections.
* jack2 development files that matches the installed version of JACK.
  * Finding the right development package: Search for packages with libjack in their names. Notice the name of the installed libjack*, and find the most similar named package which name is ending in "-dev", and install that one.
* GTK+ and Glade packages (including its dependencies such as Glib and Pango), with these packages (and their dependencies):  
```
libglade2-dev libgtk-3-dev libglib2.0-dev
```
* (GTKdatabox)[https://sourceforge.net/projects/gtkdatabox], library and header files, in version 0.9.1-1 (that will work) or preferable newer.
  * ./configure --enable-glade
* FFTW version 3

libgladeui-dev glade

## Building

If you are building from the git repo you must first run `./autogen.sh` to setup the build.

Run the traditional `./configure`, `make`, and `make install` to install BRP-PACU.

When BRP-PACU is installed on your system using `make install`, the executable is named “BRP_PACU”. It can be started from the Run dialog (that comes up when pressing ALt-F2), or from a command line which will give extra debugging information.

If you just ran `make` you can start BRP-PACU with `./BRP-PACU`.

## Usage
See [docs/Usage.md](docs/Usage.md)
