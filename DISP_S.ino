/********************************************************************************************************************
 * DISPLAY VERT MULTISEGMENTS (9)
 * 
 * longeur  : 2 * 48 = 96 pixels
 * largeur  : 9 * 7 pixels
 * 
 * pins :
 * clock  -> 4
 * d      -> 5
 * data   -> 6
 * 
 * #TODO ##### ## Mapping de ports arduino :
 * #--------------------------
 * #PORTD maps to Arduino digital pins 0 to 7
 * #PORTD - The Port D Data Register - read/write
 * #
 * #PORTB maps to Arduino digital pins 8 to 13 The two high bits (6 & 7) map to the crystal pins and are not usable
 * #PORTB - The Port B Data Register - read/write
 * 
 * #PORTD = B10101000; // sets digital pins 7,5,3 HIGH
 ********************************************************************************************************************/

//#ifdef VERTICAL_DISPLAY
#if (defined MULTI_SEGMENT_DISPLAY)


// DRIVER  1 pins 
#define pin_load    6
#define pin_clock   5
#define pin_data    4

void initlogicdisplay() {
  // set the digital pin as output: 
  pinMode(pin_load, OUTPUT); 
  pinMode(pin_clock,  OUTPUT);
  pinMode(pin_data,   OUTPUT); 

}

void PulseClockPORT() {
  PORTD &= B11011111;
  PORTD |= B00100000;
}


void PulseClock() {
  digitalWrite(pin_clock, HIGH);
  //digitalWrite(pin_load, HIGH);
  delayMicroseconds( 1 );
  digitalWrite(pin_clock, LOW);
  // digitalWrite(pin_load, LOW);
  delayMicroseconds( 1 );
}


void renderalllines(int delayms, int bitplane) {
/*
    byte seg = virtualdisplay[bitplane][i];
     for(int j=7; j>=0 ; j--) {
     digitalWrite( pin_data, bitRead( seg, j) );
     PulseClock();
     }
*/
  digitalWrite(pin_load, LOW);
  
  for( int i=XMAX-1 ; i >= 0 ; i-- ) {
    shiftOut(pin_data, pin_clock, MSBFIRST, virtualdisplay[bitplane][i] ); //shiftOut(dataPin, clockPin, bitOrder, value)
  }

#ifdef DOUBLE_DISPLAY
  for( int i=XMAX-1 ; i >= 0 ; i-- ) {
    shiftOut(pin_data, pin_clock, MSBFIRST, virtualdisplay2[bitplane][i] ); //shiftOut(dataPin, clockPin, bitOrder, value)
  }
#endif


  // DIPLAY ON
  digitalWrite(pin_load, HIGH);
  // WAIT FOR THE EYE TO SEE !
  // delayMicroseconds( delayms );
  // digitalWrite(pin_load, LOW); 
}


void renderold() {
  int PAUSE = 5000;
  for(int j=0; j < BITPLANES ; j++) {
    renderalllines( PAUSE,  j );
  }
}

void render() {
  render( displayPause );
}


void render(int PAUSE) {
  render( PAUSE, 4);
}
void render(int PAUSE, int option) {
  switch( option ) {
  case 1 : 
    {
      /*
      for(int i=0; i<= 4; i++){
       if(i>3)   render7linesPORTgrey( PAUSE, 0 );
       if(i>2)   render7linesPORTgrey( PAUSE, 1 );
       if(i>1)   render7linesPORTgrey( PAUSE, 2 );
       if(i>0)   render7linesPORTgrey( PAUSE, 3 );    
       if(i>0)   render7linesPORTgrey( PAUSE, 3 ); 
       }
       */
      break;
    }
  case 2 : 
    {
      renderalllines( PAUSE, 0 );
      renderalllines( PAUSE, 1 );
      renderalllines( PAUSE, 1 );
      renderalllines( PAUSE, 2 );
      renderalllines( PAUSE, 2 );
      renderalllines( PAUSE, 2 );
      renderalllines( PAUSE, 3 );    
      renderalllines( PAUSE, 3 ); 
      renderalllines( PAUSE, 3 ); 
      renderalllines( PAUSE, 3 );
      break;
    }
  case 3 : 
    {
      renderalllines(   PAUSE, 0 );
      renderalllines( 3*PAUSE, 1 );
      renderalllines( 8*PAUSE, 2 );
      renderalllines( 17*PAUSE, 3 );
      break;
    }
  case 4 : 
    {
      renderalllines(   PAUSE, 0 );
      renderalllines( 2*PAUSE, 1 );
      renderalllines( 4*PAUSE, 2 );
      renderalllines( 8*PAUSE, 3 ); 
      break;
    }

  case 5 : 
    {
      renderalllines( PAUSE, 3 ); 
      renderalllines( PAUSE, 0 );
      renderalllines( PAUSE, 3 ); 
      renderalllines( PAUSE, 2 );
      renderalllines( PAUSE, 3 ); 
      renderalllines( PAUSE, 1 );
      renderalllines( PAUSE, 3 ); 
      renderalllines( PAUSE, 2 );
      renderalllines( PAUSE, 3 ); 
      renderalllines( PAUSE, 1 );
      renderalllines( PAUSE, 3 ); 
      renderalllines( PAUSE, 2 );
      renderalllines( PAUSE, 3 ); 
      renderalllines( PAUSE, 2 );
      renderalllines( PAUSE, 3 ); 
      break;
    }
  }
}

void rendermono() {
  renderalllines( 3000, 0 );
}

#endif

















