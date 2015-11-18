AS2181 (c) 1996 Martin Mares <mj@ucw.cz>


This is a simple, but powerful assembler for the AD2181 signal processors
by Analog Devices.

It can be freely distributed and used according to the GNU General
Public License.

Unfortunately, I've never had time to write any documentation on it, so
the only source of information is the "test.dsp" example in this directory
and the source. Also, I've tried to make the syntax as close as possible
to the DOS assembler distributed by AD.

If you have any questions, feel free to ask me, but I don't guarantee fast
response since I haven't worked with the 2181 since summer 1996.

18. 11. 2015:   I did small cleanup so the source compiles on modern
                linux distribution and works on 64bit machine.

                New switch -x was added which forces DM to be treated
                as 24bit. This is usefull for DSP core used by Actions
                Semiconductors which is some ADSP-218x clone but with
                24bit data path.

                Preprocessor (-p switch) was fixed.
                Marcin Bukat <marcin.bukat@gmail.com>

15. 12. 2000:	I've received some feedback from Edward March, so I've
		released a "new" version 0.9.1 containing a couple of bug
		fixes (mostly for portability problems) and accepting "@"'s
		in labels in order to allow CPP local label tricks.

				Have fun
						Martin
