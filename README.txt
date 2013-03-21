ttMorse initial version. March 1, 2013 G. D. (Joe) Young

ttMorse is an arduino library to generate Morse code output from
a text string.

The Morse code engine runs with non-blocking timing, so other loop( )
activities can run simultaneously. An example sketch illustrating this
characteristic captures a line of text from the serial input while a
second (previously input) line is sent in Morse.

This timing method also permits two or more ttMorse objects to run
simultaneously.

March 20, 2013

ttMorsePWM arduino library extends ttMorse to provide dds sine wave
generator with pwm analog output using timer2 fast pwm mode.

ttMorse now handles prosign generation, output logic polarity control,
and now has several virtual functions to permit ttMorsePWM extension
of tone generation and timing.

