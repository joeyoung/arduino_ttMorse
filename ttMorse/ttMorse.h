// ttMorse.h header for text to morse code generator - library version


// started: Feb 25/13 - G. D. Young

// revised: Mar  1/13 - sendingsp boolean for complete spacing handling.
//          

#ifndef TTMORSE_H
#define TTMORSE_H

#include "Arduino.h"

#define NONE 0xff		// to specify no tone in constructors

class ttMorse {

public:

	// constructor
	ttMorse( byte ledpin, byte tonepin, unsigned int tfreq, byte cspwpm, char *str );

	// access functions
	bool msend( );				// start sending constructed string
	bool msend( char *str );	// start sending new string
	bool mbusy( );  			// true if sending underway
	void msetStr( char *str );  // specify string to send
	void mspeed( byte speed );	// change sending speed


private:
	byte mlpin, mtpin, cspwpm;
	unsigned int mtfreq;
	char *mstr;

	unsigned long elementStart, elementEnd;  // for timers
	unsigned long dotDur;
	bool sending = false;
	bool eltOn = false;
	bool endCode = true;
	bool lastelt;
	bool toneon;
	bool sendingsp;

	char cidx, mtidx, lcount;
	char tabsiz;

	byte codeChar;
	byte bitCnt;
	byte nextBit;         // mask for element position

	bool getBit( );
	void setGetBit( );
	void msendSet( );
	bool mmsend( );

}; // class ttMorse

#endif

