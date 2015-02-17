// key.ino - use the ttmorse_PWMt library tone generator to implement manual key

// started: Feb 14, 2015  G. D. (Joe) Young <jyoung@islandnet.com>
//
// revised: Feb 15/15 - use booleans in tests


#include <Bounce2.h>
#include <ttMorse.h>
#include <ttMorse_PWMt.h>


const int ledpin = 13;	       // show code on built-in led
const char tonepin = 11;       // pwm tone output pin number
const byte dotpaddle = 2;      // key dot input pin
const byte dashpaddle = 3;     // key dash input pin
const unsigned long dotdurn = 100;
const byte risetime = 5;
const int debtime = 5;


//instantiate objects to use
Bounce dot;
Bounce dash;
ttMorse_PWMt ttm( ledpin, tonepin, 850, 10, "", risetime );

//globals
boolean senddot, senddash, ton;
boolean dot_s, dah_s;            //paddle state
boolean idle;

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
}

void loop( ) {
  dot.update( );		// refresh debounced inputs
  dash.update( );
  dot_s = ( dot.read( ) == LOW );		// read current states
  dah_s = ( dash.read( ) == LOW );

  // test for level
  if( dah_s && !dot_s && !ton ) {
    ttm.toneOn( );
    ton = true;
    digitalWrite( ledpin, HIGH );
  }
  if( !dah_s && !dot_s && ton ) {
    ttm.toneOff( );
    ton = false;
    digitalWrite( ledpin, LOW );
  } // if dash paddle closed
  if( dot_s && !dah_s && !ton ) {
    ttm.toneOn( );
    ton = true;
    digitalWrite( ledpin, HIGH );
  }
  if( !dot_s && !dah_s && ton ) {
    ttm.toneOff( );
    ton = false;
    digitalWrite( ledpin, LOW );
  } // if dot paddle closed

}


