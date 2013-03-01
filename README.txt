ttMorse initial version. March 1, 2013 G. D. (Joe) Young

ttMorse is an arduino library to generate Morse code output from
a text string.

The Morse code engine runs with non-blocking timing, so other loop( )
activities can run simultaneously. An example sketch illustrating this
characteristic captures a line of text from the serial input while a
second (previously input) line is sent in Morse.

This timing method also permits two or more ttMorse objects to run
simultaneously.


