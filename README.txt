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

ttMorse_PWM arduino library extends ttMorse to provide dds sine wave
generator with pwm analog output using timer2 fast pwm mode.

ttMorse now handles prosign generation, output logic polarity control,
and now has several virtual functions to permit ttMorsePWM extension
of tone generation and timing.


April 16, 2013

Added ttMorse_PWMt which provides a table-lookup control of the envelope
shape of the generated Morse elements, along with some example tables.

Each of the (three) arduino library folders includes a 'docs' file with
more extensive descriptions of the programs.


Feb 17, 2015

Added key, key_msend, and key_testinputs to ttMorse_pwmt examples which
illustrate using just the tone generator and timers from the library
functions and consequent smaller memory footprint even though compiled 
against whole library.


