/********************************************************************************************************************
 * DISPLAY VERT MULTISEGMENTS (9) FULLSCREEN SPI (experimental)
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
 
 
 * SPI Wiring of the arduino MEGA :
  ---------------------------------
 
 * ICSP : 
 3 -> clock (blue)
 5 -> data  (white)
 
    (1) O O
clk --  O O -- data
        O O
 
 * Digital pin 6 :
 -> load   (grey)
 
 
 ********************************************************************************************************************/
#include <SPI.h>
#include <digitalWriteFast.h>

//#ifdef VERTICAL_DISPLAY
#if (defined MULTI_SEGMENT_DISPLAY_FULLSCREEN && defined OUTPUT_SPI)


// DRIVER pins 
// rouge (provient du blanc) // Slave Select
#define pin_load    6

// blanc (provient du bleu) // SCK
#define pin_clock   5

// noir (provient du jaune) // MOSI
#define pin_data    4

// GND -> rouge souple 

void initlogicdisplay() {
  // set the digital pin as output: 
  pinModeFast(pin_load, OUTPUT); 
  //pinMode(pin_clock,  OUTPUT);
  //pinMode(pin_data,   OUTPUT); 
  /*  
   Mode	Clock Polarity (CPOL)	Clock Phase (CPHA)
   SPI_MODE0	0	        0
   SPI_MODE1	0	        1
   SPI_MODE2	1	        0
   SPI_MODE3	1	        1
   */
  SPI.setDataMode(SPI_MODE1);
  /*
Sets the SPI clock divider relative to the system clock. On AVR based boards, the dividers available are 2, 4, 8, 16, 32, 64 or 128. 
   The default setting is SPI_CLOCK_DIV4, which sets the SPI clock to one-quarter the frequency of the system clock (4 Mhz for the boards at 16 MHz).
   SPI_CLOCK_DIV2
   SPI_CLOCK_DIV4
   SPI_CLOCK_DIV8
   SPI_CLOCK_DIV16
   SPI_CLOCK_DIV32
   SPI_CLOCK_DIV64
   SPI_CLOCK_DIV128
   */
  //SPI.setClockDivider(SPI_CLOCK_DIV2); // optionel, pour les perturbations
  SPI.begin();

  //  Timer1.initialize(20000); // set a timer of length 10000 microseconds (or 0.02 sec - or 50Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
  //  Timer1.initialize(1200); // set a timer of length 10000 microseconds (or 0.02 sec - or 50Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
  Timer1.initialize(1200); // set a timer of length 10000 microseconds (or 0.02 sec - or 50Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)

  Timer1.attachInterrupt( displayTimerIsr ); // attach the service routine here

  //currfb = 0;
  //currfb_disp = 1;
}


short dispState = 0;
void displayTimerIsr() {
  //noInterrupts();

  //if( displayDirty) return;
  /*
  if( !VBLANK ) {
   VBLANK = true;
   return;
   }
   */
  //VBLANK = false;

  /*
  if( currfb == 0 ) currfb_disp = 1;
   else currfb_disp = 0;
   */

  int PAUSE = 1;
  switch( dispState ) {
    case( 0 ):
    renderalllines( PAUSE, 0 );
    case( 1 ):
    break;
#if (BITPLANES >= 2)
    case( 2 ):
    renderalllines( PAUSE, 1 );
    break;
    case( 3 ):
    case( 4 ):
    break;
#endif
#if (BITPLANES >= 3)
    case( 5 ):
    renderalllines( PAUSE, 2 );
    break;
    case( 6 ):
    case( 7 ):
    case( 8 ):
    case( 9 ):
    case( 10 ):
    case( 11 ):
    break;
#endif
#if (BITPLANES >= 4)
    case( 12 ):
    renderalllines( PAUSE, 3 );
    break;
    case( 13 ):
    case( 14 ):
    case( 15 ):
    case( 16 ):
    case( 17 ):
    case( 18 ):
    case( 19 ):
    break;
#endif
  }
  delayMicroseconds( PAUSE );

  if( dispState >= 19) {
    dispState = 0;
    //VBLANK = true;
  }
  else  {   
    dispState++;
    //VBLANK = false;
  }

  //interrupts();
}

// render one bitplane -> 1 led segment
void renderalllines(int delayms, int bitplane) {  // non testé
  {
    digitalWriteFast(pin_load, LOW); 
    for( int j=SEGMENTS_MINUS ; j >= 0 ; j-- ) {
      digitalWrite(pin_load, LOW);
      for( int i=XMAX_MINUS ; i >= 0 ; i-- ) {
        // shiftOut(pin_data, pin_clock, MSBFIRST, virtualdisplay[bitplane][i] ); 
        SPI.transfer( virtualdisplay[currfb_disp][j][bitplane][i] );
      }
    }
    digitalWriteFast(pin_load, HIGH);
  }
  // WAIT FOR THE EYE TO SEE !
  //delayMicroseconds( delayms );
}

void PulseClock() {
  digitalWrite(pin_clock, HIGH);
  //digitalWrite(pin_load, HIGH);
  //delayMicroseconds( 1 );
  digitalWrite(pin_clock, LOW);
  // digitalWrite(pin_load, LOW);
  //delayMicroseconds( 1 );
}

void render() {
  //render( displayPause );
  //renderall();
#ifdef MONOCHROM
  render_fullscreen_mono();
#else
  render( displayPause, 1 );
#endif
}

void render(int PAUSE) {
  //render( PAUSE, 4);
  //render( PAUSE, 4);
  //renderalllines(0, 9);
  //renderalllines(0, BITPLANES);   // GOOD OR BUG ?
  //renderalllines(0, BITPLANES-1); 

  //renderall();
}

void render(int PAUSE, int option) {
  switch( option ) {
  case 1 : 
    {
      renderalllines(   PAUSE, 0 );
      renderalllines( 4*PAUSE, 1 );
      renderalllines( 7*PAUSE, 2 );
      renderalllines( 8*PAUSE, 3 ); 
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


#endif










































