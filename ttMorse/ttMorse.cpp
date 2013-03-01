// ttMorse.cpp text to morse code generator - library version

// started: Feb 25/13 - G. D. Young

// revised: Feb 28/13 - remap lower case for smaller code table, fixes
//          Mar  1/13 - complete handling of (extra) spaces - start, end,
//                      middle, spaces-only line
//          
// the calculation of mtidx from each input ascii moves the table down 0x20,
// eliminating the (non-printing) first two rows; in addition, the moved result
// is tested for the lower-case alphabet and those two rows are moved down two
// more. The codetable can then be 0x00 to 0x3f instead of 0x00 to 0x5f. The
// larger-codetable lookup (and the larger table in codeTable.h) is left in
// commented lines, in case it's later desired for some reason unfathomable now.

#include <string.h>
#include "ttMorse.h"
#include "codeTable.h"


ttMorse::ttMorse( byte ledpin, byte tonepin, unsigned int tfreq, byte cspwpm, char *str ) {
	mlpin = ledpin;
	if( tonepin == NONE ) {
		toneon = false;
	} else {
		mtpin = tonepin;
		toneon = true;
	} // if no tone
	mtfreq = tfreq;
	dotDur = 1200UL/cspwpm;  // translate wpm to dot time in msec
	mstr = str;
} // constructor


// access functions

bool ttMorse::msend( ) {
	bool mmsending;
	mmsending = mmsend( );
	return mmsending;
}

bool ttMorse::msend( char *str ) {
	bool mmsending;
	mstr = str;
	mmsending = mmsend( );
	return mmsending;
}

bool ttMorse::mbusy( ) {
	return sending;
} // mbusy( )

void ttMorse::msetStr( char *str ) {
	mstr = str;
} // msetStr( )

void ttMorse::mspeed( byte cspwpm ) {
	dotDur = 900UL/cspwpm;
} // mspeed( )


// (re)set pointers, counters, first charcter
void ttMorse::msendSet( ) {
	pinMode( mlpin, OUTPUT );
	pinMode( mtpin, OUTPUT );
	eltOn = false;
	sending = true;
	elementStart = millis( ) + 2;
	cidx = 0;
	tabsiz = strlen( mstr );
//	codeChar = morseTable[(mstr[cidx]&0x7f)-0x20];
	mtidx = ((mstr[cidx]-0x20)>0x3f) ? mstr[cidx]-0x40 : mstr[cidx]-0x20;
	codeChar = morseTable[mtidx];
	while( codeChar == 0 && cidx < tabsiz ) {		// handle several leading spaces
		elementStart += 7*dotDur;
		cidx++;
//		codeChar = morseTable[(mstr[cidx]&0x7f)-0x20];
		mtidx = ((mstr[cidx]-0x20)>0x3f) ? mstr[cidx]-0x40 : mstr[cidx]-0x20;
		codeChar = morseTable[mtidx];
	}
	if( cidx >= tabsiz ) { 		// only spaces found
		lastelt = true;
		eltOn = true;
		elementEnd = elementStart - dotDur;		// pretend elt on, end after space(s)
	} else {					// char found, setup decoder
		setGetBit( );
		endCode = false;
	}
} // msendSet( )


// enter here at loop scan rate, but action controlled by element timers, many flags
bool ttMorse::mmsend( ) {

	if( !sending ) ttMorse::msendSet( );	// first time in, do setup

	if( !eltOn && sending && (elementStart < millis( )) ) {
		elementStart += 2*dotDur;   	// at least one dot duration and space
		if( getBit( ) ) {
			elementStart += 2*dotDur; 	// if element is dash, add two more
		} // if dash
		elementEnd = elementStart - dotDur;
		digitalWrite( mlpin, HIGH ); 			// send the element as level
		if( toneon ) tone( mtpin, mtfreq );		// and as tone, if on
		eltOn = true;
		if( endCode ) {
			elementStart += 2*dotDur;   // letter space
			cidx++;
			if( cidx >= tabsiz ) {
				lastelt = true;		//str exhausted, prepare to stop when elt over
			} else {
//				codeChar = morseTable[(mstr[cidx]&0x7f)-0x20];
				mtidx = ((mstr[cidx]-0x20)>0x3f) ? mstr[cidx]-0x40 : mstr[cidx]-0x20;
				codeChar = morseTable[mtidx];
				if( codeChar == 0 ) {          // word space(s)
					elementStart += 4*dotDur;	// finish space started with last letter
					sendingsp = true;
					cidx++;
					if( cidx >= tabsiz ) {
						lastelt = true;
					} else {
//						codeChar = morseTable[(mstr[cidx]&0x7f)-0x20];
						mtidx = ((mstr[cidx]-0x20)>0x3f) ? mstr[cidx]-0x40 : mstr[cidx]-0x20;
						codeChar = morseTable[mtidx];
						while( codeChar == 0 ) {
							elementStart += 7*dotDur;
//							sendingsp = true;
							cidx++;
							if( cidx >= tabsiz ) {
								lastelt = true;
								break;		//watch for trailing spaces
							} 
//							codeChar = morseTable[(mstr[cidx]&0x7f)-0x20];
							mtidx = ((mstr[cidx]-0x20)>0x3f) ? mstr[cidx]-0x40 : mstr[cidx]-0x20;
							codeChar = morseTable[mtidx];
						} // while more word spaces
					} // if end table and spacing
				} // if word space
				setGetBit( );
				endCode = false;
			} // if end of string
		} // if end of code character
	} // if elementStart

	if( (elementEnd < millis( )) ) {
		digitalWrite( mlpin, LOW );
		noTone( mtpin );
		if( sendingsp ) {
			elementEnd = elementStart - dotDur;		// 'element' continues for space(s)
			sendingsp = false;
		} else {
			eltOn = false;
			if( lastelt ) {
				sending = false;
				lastelt = false;
			} // if last elt finished
		}
	} // if end of element

	return sending;

} // msend( )


// setup getBit - locate fence bit in codeChar
void ttMorse::setGetBit( ) {

  bitCnt = 7;
  nextBit = 0b10000000;
  
  while( (bitCnt > 0) && ((nextBit & codeChar) == 0) ) {
    nextBit = nextBit >> 1;  // find fence
    bitCnt--;
  } // while leading 0s before fence

} // setGetBit( )


// examine codeCharacter for next element to send
bool ttMorse::getBit( ) {
    nextBit = nextBit>>1;
    bitCnt--;
  if( bitCnt == 0 ) {
    endCode = true; 
  } // if last bit in codeChar
  return( (nextBit & codeChar) == nextBit );
} // getBit( )


