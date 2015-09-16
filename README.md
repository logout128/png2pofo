png2pofo
--------
Converts PNG images to formats viewable on Atari Portfolio handheld,
either uncompressed PGF (size of result image is allways 1920B) 
or to PGC, which is compressed. Source PNG image has to be exactly
240x64 with 1bpp, this can be done in GIMP or any other image editor
of your choice.

This is in fact my first ever completed utility written in C for 
unix-like operating systems. I wanted to convert some pictures
for my Portfolio and discovederd, that all existing (year 2010) 
utilities required a MS-DOS computer and some aditional software.
As I didn't have any of that, I had to write a new utlity myself.

Installation
------------
FreeImage library is required. On Ubuntu derived Linux distributions
you have to install libfreeimage-dev package, RedHat based distros
have similar package called freeimage-devel.

Building is as simple as typing 'make' in the png2pofo source folder.

Successful build reports:
*	CentOS 7 64bit (logout)
*	Xubuntu 10.04LTS 64bit (logout)
*	Fedora 8 (krupkaj)
*	Slackware64-13.1 (pol)

If you have succesfully built png2pofo on another system, let me know
(my contact info can be displayed from the utility itself), I'll add
you to the list.

License
-------
This software is licenced under the terms of GNU General Public 
License, version 3 or later. See attached file GPL.txt for full text
of this license.

This software uses the FreeImage open source image library.
See http://freeimage.sourceforge.net for details.
FreeImage is used under the terms of GNU GPL license, version 3.
