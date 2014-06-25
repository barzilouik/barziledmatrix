/********************************************************************************************************************
 * DISPLAY ROUGE
 * 
 * longeur  : 12 * 8 = 96 pixels
 * largeur  : 7 pixels
 * 
 * pins : leds   -> 12-4 (cable rouge sur le 4)
 * clock  ->  5
 * enable -> 4
 * DOUBLE_DISPLAY
 * Mapping de ports arduino :
 * --------------------------
 * PORTD maps to Arduino digital pins 0 to 7
 * PORTD - The Port D Data Register - read/write
 * 
 * PORTB maps to Arduino digital pins 8 to 13 The two high bits (6 & 7) map to the crystal pins and are not usable
 * PORTB - The Port B Data Register - read/write
 * 
 * PORTD = B10101000; // sets digital pins 7,5,3 HIGH
 ********************************************************************************************************************/

//#ifdef VERTICAL_DISPLAY
#if (defined VERTICAL_DISPLAY) || defined (VERTICAL_DISPLAY_DUAL) || defined (VERTICAL_DISPLAY_DUAL_FULLSCREEN)


// DRIVER  1 pins 
#define pin_enable  4
#define pin_clock   5

// DRIVER  2 pins (if _DOUBLE_DISPLAY_)
#define pin_enable2  2
#define pin_clock2   3

// Data pins (Common if _DOUBLE_DISPLAY_)
int pins[7] = {
  12,11,10,9,8,7,6};

void initlogicdisplay() {
  // set the digital pin as output: 
  pinMode(pin_enable, OUTPUT); 
  pinMode(pin_clock,  OUTPUT);

  pinMode(pin_enable2, OUTPUT); 
  pinMode(pin_clock2,  OUTPUT);

  for(int i=0; i<8; i++) {
    pinMode(pins[i], OUTPUT);  
  }
}

void PulseClockPORT() {
  PORTD &= B11011111;
  PORTD |= B00100000;
}

//DUAL_SCREEN
void PulseClockPORT2() {
  PORTD &= B11110111;
  PORTD |= B00001000;
}

void PulseClock() {
  digitalWrite(pin_clock, HIGH);
  digitalWrite(pin_clock, LOW);
}

void PulseClock2() {
  digitalWrite(pin_clock2, HIGH);
  digitalWrite(pin_clock2, LOW);
}

//////////////////////// FULLSCREEN DOUBLE DISPLAY MODE ////////////////////////////////
#if (defined FULLSCREEN_DISPLAY)
void renderalllines(int delayms, int bitplane) {
  digitalWrite( pin_enable2, LOW); // DIPLAY OFF
  digitalWrite( pin_enable, LOW);  // DISPLAY OFF

  // DISP 2
  bitplane = 1;
  for( int i=XMAX-1 ; i >= 0 ; --i ) {
    PORTB = virtualdisplay[bitplane][i] >> 3;
    PORTD = virtualdisplay[bitplane][i] << 5;// & B01011;
    PulseClockPORT2();
  }

  // DISP 1
  bitplane = 0;
  for( int i=XMAX-1 ; i >= 0 ; --i ) {
    PORTB = virtualdisplay[bitplane][i] >> 3;
    PORTD = virtualdisplay[bitplane][i] << 5;// & B01011;;
    PulseClockPORT();
  }

  digitalWrite( pin_enable2, HIGH); // DIPLAY ON
  digitalWrite( pin_enable, HIGH);  // DIPLAY ON
  delayMicroseconds( delayms );
}
//////////////////////// DOUBLE DISPLAY MODE ////////////////////////////////
#elif (defined DOUBLE_DISPLAY)
void renderalllines(int delayms, int bitplane) {

  // DISPLAY2
  //PORTD &= B11111011;  //digitalWrite( pin_enable2, LOW); // DIPLAY OFF
  //PORTD &= B11101111; //digitalWrite( pin_enable, LOW); // DISPLAY OFF
  //PORTD &= B11101011; //digitalWrite( pin_enable, LOW); // DISPLAY OFF of the 2 displatys
  digitalWrite( pin_enable2, LOW); // DIPLAY OFF
  digitalWrite( pin_enable, LOW); // DISPLAY OFF

  for( int i=XMAX-1 ; i >= 0 ; --i ) {
    PORTB = virtualdisplay2[bitplane][i] >> 3;
    PORTD = virtualdisplay2[bitplane][i] << 5;// & B01011;
    PulseClockPORT2();
  }


  for( int i=XMAX-1 ; i >= 0 ; --i ) {
    PORTB = virtualdisplay[bitplane][i] >> 3;
    PORTD = virtualdisplay[bitplane][i] << 5;// & B01011;;
    PulseClockPORT();
  }

  //delayMicroseconds( delayms );

  // DISPLAY 1
  //for( int i=XMAX-1 ; i >= 0 ; --i ) {

  //}

  //PORTD |= B00000100; //digitalWrite( pin_enable2, HIGH); // DIPLAY ON
  //PORTD |= B00010000; //digitalWrite( pin_enable, HIGH); // DIPLAY ON
  //PORTD |= B00010100; //digitalWrite( pin_enable, HIGH); // DIPLAY ON of the 2 displatys

  digitalWrite( pin_enable2, HIGH); // DIPLAY ON
  digitalWrite( pin_enable, HIGH); // DIPLAY ON

  delayMicroseconds( delayms );

  /*  
   // DISPLAY1
   PORTD &= B11101111; //digitalWrite( pin_enable, LOW); // DISPLAY OFF
   //digitalWrite( pin_enable, LOW); // DISPLAY OFF
   for( int i=XMAX-1 ; i >= 0 ; --i ) {
   PORTB = virtualdisplay[bitplane][i] >> 3;
   PORTD = virtualdisplay[bitplane][i] << 5;
   PulseClockPORT();
   }
   PORTD |= B00010000; //digitalWrite( pin_enable, HIGH); // DIPLAY ON
   //digitalWrite( pin_enable, HIGH); // DIPLAY ON
   delayMicroseconds( delayms );
   
   // DISPLAY2
   PORTD &= B11111011;  //digitalWrite( pin_enable2, LOW); // DIPLAY OFF
   //digitalWrite( pin_enable2, LOW); // DIPLAY OFF
   for( int i=XMAX-1 ; i >= 0 ; --i ) {
   PORTB = virtualdisplay2[bitplane][i] >> 3;
   PORTD = virtualdisplay2[bitplane][i] << 5;
   PulseClockPORT2();
   }
   PORTD |= B00000100; //digitalWrite( pin_enable2, HIGH); // DIPLAY ON
   //digitalWrite( pin_enable2, HIGH); // DIPLAY ON
   delayMicroseconds( delayms );
   */
}

#else 
//////////////////////// SIMPLE DISPLAY MODE ////////////////////////////////
void renderalllines(int delayms, int bitplane) {
  PORTD &= B11101111; //digitalWrite( pin_enable, LOW); // DISPLAY OFF

  for( int i=XMAX-1 ; i >= 0 ; --i ) {
    PORTB = virtualdisplay[bitplane][i] >> 3;
    PORTD = virtualdisplay[bitplane][i] << 5;
    PulseClockPORT();
  }

  PORTD |= B00010000; //digitalWrite( pin_enable, HIGH); // DIPLAY ON

  delayMicroseconds( delayms );
}

#endif

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
#if (defined FULLSCREEN_DISPLAY)
  renderalllines( PAUSE, -1 );
#else
  render( PAUSE, 4);
#endif
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













