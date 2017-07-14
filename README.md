# BRP-PACU - An Audio Configuration utility
BRP-PACU is a dual channel FFT audio analysis tool. It is designed to aid in the equalization and time alignment of a sound system. It compares the output of the system to the input of the system to obtain the transfer function of the system.u It is similar to commercial products like [Smaart](https://en.wikipedia.org/wiki/Smaart).

## Dependencies
Development versions of the following packages:
* `build-essential` for build tools
* [jack2](http://jackaudio.org/)
  * Tip: If jack is not already installed on your system, try to install the package `qjackctl` which depends on JACK and provides an easy way to manage JACK connections.
* [GtK+](https://www.gtk.org/) and [Glade](https://glade.gnome.org/)
* [GTKdatabox for GTK3](https://github.com/erikd/gtkdatabox)
  * `git clone https://github.com/erikd/gtkdatabox.git`
  * Run `./autogen.sh` and then the traditional `./configure`, `make`, and `make install` since this is not a release, but coming straight from the repo.
  * The original library on SourceForge claims GTK3 support on the [git master branch](https://sourceforge.net/p/gtkdatabox/git/ci/master/tree/) but this has not been tested with BRP-PACU.
* [FFTW version 3](http://www.fftw.org/)

### On Ubuntu 16.04:  
```
sudo apt install build-essential libfftw3-dev libc6 libglade2-dev libglib2.0-dev libgtk2.0-dev libjack-jackd2-dev
```
You can likely tweak this if you are on a different distribution. GTKDatabox must still be installed from the source following the instructions above.

## Building

If you are building from the git repo you must first run `./autogen.sh` to setup the build.

Run the traditional `./configure`, `make`, and `make install` to install BRP-PACU.

You can start BRP-PACU with `./BRP-PACU` if you want to run it before installing.

When BRP-PACU is installed on your system using `make install`, the executable is named “BRP_PACU”. It can be started from the Run dialog (that comes up when pressing ALt-F2), or from a command line which will give extra debugging information.

## Usage
See [docs/Usage.md](docs/Usage.md)
