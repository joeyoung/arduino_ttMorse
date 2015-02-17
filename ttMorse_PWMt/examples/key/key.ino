// key.ino - use the ttmorse_PWMt library tone generator to implement manual key

// started: Feb 14, 2015  G. D. (Joe) Young <jyoung@islandnet.com>
//
// revised: Feb 15/15 - use booleans in tests, basic key function


#include <Bounce2.h>
#include <ttMorse.h>
#include <ttMorse_PWMt.h>


const byte ledpin = 13;	       // show code on built-in led
const char tonepin = 11;       // pwm tone output pin number
const byte dotpaddle = 2;      // key dot input pin
const byte dashpaddle = 3;     // key dash input pin
const byte cspwpm = 15;        // code speed in words/min (approx)
const unsigned long dotdurn = 1200UL/cspwpm;
const word tfreq = 850;
const byte risetime = 5;       // times in msec (approx for ttm timers)
const int debtime = 5;


//instantiate objects to use
Bounce dot;
Bounce dash;
ttMorse_PWMt ttm( ledpin, tonepin, tfreq, cspwpm, "", risetime );

//globals
boolean dot_s, dah_s;                 //paddle state
boolean ton, idle, elem, dot_e, lsp;  //sequence states

//function definitions
void startElement( );

void setup( ) {
  // paddle interface setup
  pinMode( dotpaddle, INPUT_PULLUP );
  pinMode( dashpaddle, INPUT_PULLUP );
  dot.attach( dotpaddle );
  dash.attach( dashpaddle );
  dot.interval( debtime );
  dash.interval( debtime );

  // tone generator setup
  ttm.setTimInt( );
  // test
  ttm.toneOn( );
  delay( 2000 );
  ttm.toneOff( );
  delay( 1000 );

  // logic output setup
  pinMode( ledpin, OUTPUT );
  ton = false;
  idle = true;
} // setup( )

void loop( ) {
  dot.update( );                   // refresh debounced inputs
  dash.update( );
  dot_s = ( dot.read( ) == LOW );  // read current states
  dah_s = ( dash.read( ) == LOW );

  if( idle && ( dot_s || dah_s ) ) {
    //set up on and off timers
    startElement( );
    idle = false;
  } // if idle and paddle
  
  if( !idle && ton ) {
    if( ttm.onTimer( ) ) {
      ttm.toneOff( );
      digitalWrite( ledpin, LOW );
      ton = false;
    } // if on time is up
  } // if tone on
  
  if( !idle && !ton && elem ) {
    if( ttm.offTimer( ) ) {
      elem = false;
      if( !dot_s && !dah_s ) {
        lsp = true;              //setup for letter space
        ttm.elementEnd += 2*dotdurn;
      } // if no paddle
      if( dot_s || dah_s ) {
        // if both closed, setup for alternate element
        if( dot_s && dah_s ) {
          if( dot_e ) {
            dot_s = false;
          } else {
            dah_s = false;
          } // if element just ended was dot
        } // if both closed
        startElement( );
      } // one or both paddles closed
    } // if element space ended
  } // if element spacing

  if( !idle && lsp ) {
    if( ttm.offTimer( ) ) {
      idle = true;            // but need to re-check paddles??
    } // if leterspace ended
  }// if letter spacing

} // loop( )

void startElement( ) {
    //set up on and off timers
    ttm.elementStart = ttm.initTimers( ) + dotdurn;
    if( dah_s ) {
      ttm.elementStart += 2*dotdurn;
      dot_e = false;
    } else {
      dot_e = true;
    } // if dash paddle
    ttm.elementEnd = ttm.elementStart + dotdurn;
    ttm.toneOn( );
    digitalWrite( ledpin, HIGH );
    ton = true;
    elem = true;
} // startElement( )
