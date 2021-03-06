// ttMorse_PWMt.cpp - dds, pwm tone generator for ttMorse library
// created from: toneGen2 - DDS tone with pwm output
// created: Mar 6/13 G. D. Young
//          Mar 7/13 - start/stop, risetime control

// revised: Mar 8/13 - ttMorse_PWM library version
//          Mar 11/13 - using signed table format - simplify ramp * sample
//			Mar 13/13 - using pwm interrupt for timing
//          Apr 11/13 - stop timer interrupts around toneOn, toneOff flag set
//          Apr 11/13 - ttMorse_PWMt - lookup table for rise/fall control
//          Apr 16/13 - cleanups.

#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include "sinTab.h"
#include "luTab.h"

#include "ttMorse_PWMt.h"



ISR( TIMER2_OVF_vect ) {
	cli( );
	ttMorse_PWMt::timer_int( );
	sei( );
} // interrupt access to class handler


// timer2 overflow interrupt - dds, pwm generator, ramp on and off
void ttMorse_PWMt::timer_int( ) {
  pwmkhz--;
  if( pwmkhz == 0 ) {
	pwmtick++;						// for pwm timer timing
	pwmkhz = 62;
  }

  if( tonestart ) {

    accumulator += increment;
    highbyte = accumulator >> 24;

    if( !armtoff && (amplacc < 0xff00) ) {
      amplacc += amplinc;
      luidx = (byte)((amplacc >> 8)&0xff);
      sample = ((int)luTab[luidx]) * ((int)sinTab[highbyte]);
      if( pwmoutput == 3 ) OCR2B = (unsigned char)((sample >> 8) + 128);
      if( pwmoutput == 11 ) OCR2A = (unsigned char)((sample >> 8) + 128);
    } else {
      if( pwmoutput == 3 ) OCR2B = sinTab[highbyte] + 128;
      if( pwmoutput == 11 ) OCR2A = sinTab[highbyte] + 128;
	} // if rising

    if( armtoff && (amplacc < 0xff00) ) {
      amplacc += amplinc;
      luidx = (byte)((amplacc >> 8)&0xff);
      sample = ((int)(255-luTab[luidx])) * ((int)sinTab[highbyte]);
      if( pwmoutput == 3 ) OCR2B = (unsigned char)((sample >> 8) + 128);
      if( pwmoutput == 11 ) OCR2A = (unsigned char)((sample >> 8) + 128);
	} else if( armtoff && amplacc >= 0xff00 ) {
      if( pwmoutput == 3 ) OCR2B = 128;
      if( pwmoutput == 11 ) OCR2A = 128;
	  tonestart = false;
	} // if turn off time

  } // if tonestart tone on

} // timer2 count overflow interrupt service

// using pwm generator for timing
bool ttMorse_PWMt::onTimer( ) {
    TIMSK2 = 0; 		// no interruptions
	bool lt = ( elementStart < pwmtick );
	TIMSK2 = 1;
	return lt; 
} // onTimer( )

bool ttMorse_PWMt::offTimer( ) {
    TIMSK2 = 0; 		// no interruptions
	bool lt = ( elementEnd < pwmtick );
	TIMSK2 = 1;
	return lt; 
} // offTimer( )

unsigned long ttMorse_PWMt::initTimers( ) {
	TIMSK2 = 0;
	unsigned long tk = pwmtick;
	TIMSK2 = 1;
	return tk;
} // initTimers( )

// setup the timer2 for fast pwm and overflow interrupt
void ttMorse_PWMt::setTimInt( ) {
	TCCR2B = 1;
	if( pwmpin == 11 ) {
		TCCR2A = (1<<COM2A0) | (1<<COM2A1) | (1<<WGM20) | (1<<WGM21);
		pwmoutput = 11;
		pinMode( 11, OUTPUT );
	}
	if( pwmpin == 3 ) {
		TCCR2A= (1<<COM2B0) | (1<<COM2B1) |(1<<WGM20) | (1<<WGM21);
		pwmoutput = 3;
		pinMode( 3, OUTPUT );
	}
  TIMSK2 = (1<<TOIE2);
  pwmkhz = 62;
  pwmtick = 0;
} // setTimInt

void ttMorse_PWMt::setFreq( unsigned int ptfreq ) {
  increment = 68719L * ptfreq;
  accumulator = 0L;
  if( pwmoutput == 3 ) OCR2B = 128;
  if( pwmoutput == 11 ) OCR2A = 128;
} // setFreq

void ttMorse_PWMt::setRise( byte rtmsec ) {
  if( rtmsec == 0 ) rtmsec = 1;
  if( rtmsec > 50 ) rtmsec = 50;
  amplinc = 1048/rtmsec;
} // setRise

void ttMorse_PWMt::toneOn( ) {
  TIMSK2 = 0;		//no interruptions when setting flags
  amplacc = 0;
  armtoff = false;
  tonestart = true;
  TIMSK2 = (1<<TOIE2);
} // toneOn

void ttMorse_PWMt::toneOff( ) {
  TIMSK2 = 0;		//no interruptions when setting flags
  armtoff = true;
  amplacc = 0;
  TIMSK2 = (1<<TOIE2);
} // toneOff



