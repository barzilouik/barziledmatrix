/********************************************************************************************************************
 * DISPLAY VERT
 * 
 * Desciption : 
 * Panneau de marque SAYAG ELECTRONIC, modèle BG 18 de 1989
 * Dimension physiques approx : 2m * 20cm
 * 
 * longeur  : 18 * 8 = 144 pixels
 * largeur  : 7 pixels
 * 
 * Principe :
 * Le circuit principal d'injection est un registre a decalage (CD4094)
 * Ils sont daisy-chainés. Pas de Enable trouvé ...(pas besoin en fait)
 * 
 * Des ULN viennent récupérer les donnée et les injecter en X
 * En Y, on se rebranche en entrée des transistors BDW44 motorola
 * 
 * On utilise un principe de balayage X/Y :
 * Pour chaque ligne on itère ...
 * 1)on affiche les données en X en les serialisant sur le mode 
 * STROBE ENABLE
 * BITBANG SUR DATA
 * CLOCK PULSE
 * 2)on affiche allume la ligne courante ou les points s'allument
 * 
 * CD4094 attaqué sur le panneau : (dans l'ordre sur le panneau, les pad d'étain haut->bas)
 * STROBE -> 4
 * CLOCK  -> 3
 * DATA   -> 2
 * 
 * LIGNE AFFICHEUR (en haut d'abord) repiquées en entrée des transistor sur la carte
 * L0 -> 12
 * ...
 * L7 -> 6
 * 
 * Cablage arduino :
 * 2  DATA
 * 3  CLOCK
 * 4  STROBE
 * 5
 * 6  L6
 * 7  L5
 * 8  L4
 * 9  L3              (-) GND
 * 10 L2
 * 11 L1
 * 12 L0
 ********************************************************************************************************************/

#ifdef HORIZONTAL_DISPLAY


// DRIVER pins 
#define pin_enable  4
#define pin_clock   3
#define pin_data    2
int pins[7] = {  
  12,10,11,9,8,6,7};

void testdisplay() {
  setvirtualdisplay( 0 );
  for(int i=0; i< 8; i++){
    blockvirtual(i + 8, 10, 0);
    blockvirtual(i + 32, 10, 1);
    blockvirtual(i + 64, 10, 2);
  }
  render();
}

void initlogicdisplay() {
  // set the digital pin as output: 
  pinMode(pin_enable, OUTPUT); 
  pinMode(pin_clock,  OUTPUT);
  pinMode(pin_data,  OUTPUT);

  for(int i=0; i<8; i++) {
    pinMode(pins[i], OUTPUT);  
  }
  
  
}

void setPORTON(byte pinnb) {
  switch( pinnb ) {
    // PORT B
  case 12:
    PORTB |= B00010000;
    break;
  case 11:
    PORTB |= B00001000;
    break;
  case 10:
    PORTB |= B00000100;
    break;
  case 9:
    PORTB |= B00000010;
    break;
  case 8:
    PORTB |= B00000001;
    break;
    // PORT D
  case 7:
    PORTD |= B10000000;
    break;
  case 6:
    PORTD |= B01000000;
    break;
  }
}

void setPORTOFF(byte pinnb) {
  switch( pinnb ) {
    // PORT B
  case 12:
    PORTB &= B11101111;
    break;
  case 11:
    PORTB &= B11110111;
    break;
  case 10:
    PORTB &= B11111011;
    break;
  case 9:
    PORTB &= B11111101;
    break;
  case 8:
    PORTB &= B11111110;
    break;
    // PORT D
  case 7:
    PORTD &= B01111111;
    break;
  case 6:
    PORTD &= B10111111;
    break;
  }
}

void PulseClockPORT() {
  PORTD |= B00001000;
  PORTD &= B11110111;
}

void PulseEnablePORT() {
  PORTD &= B11101111;
  PORTD |= B00010000;
}

void PulseClock() {
  digitalWrite(pin_clock, HIGH);
  digitalWrite(pin_clock, LOW);
}

void renderline(int linenb, int bitplane) {
  PORTD |= B00010000; //digitalWrite( pin_enable, HIGH); // DISPLAY OFF
  for(int i=0; i < XMAX; i++) {  // a line is made of 18 bytes
    if( virtualdisplay[bitplane][ XMAX - i - 1 ] & (1 << linenb)  ) { //    if( bitRead( virtualdisplay[ 143 - i ], linenb ) ) {
      PORTD |= B00000100; // digitalWrite( pin_data, HIGH)
    }
    else {
      PORTD &= B11111011; // digitalWrite( pin_data, LOW)
    }
    PulseClockPORT();
  }
  PORTD &= B11101111; //digitalWrite( pin_enable, LOW); // DIPLAY ON

}

void renderalllines(int delayms, int bitplane) {
  for(int i=0; i < YMAX ; i++) {  // a line is made of 18 bytes
    setPORTOFF( pins[i]);//digitalWrite(pins[i], LOW);
    renderline( YMAX - i  , bitplane );
    setPORTON( pins[i]); //digitalWrite(pins[i], HIGH);
    delayMicroseconds( delayms );

  }
}

void render() {
  render( displayPause );
}

void render(int PAUSE) {
  if( PAUSE ==0 ) return;
  /*
  for(int i=0; i<= 4; i++){
   
   if(i>3)   render7linesPORTgrey( PAUSE, 0 );
   if(i>2)   render7linesPORTgrey( PAUSE, 1 );
   if(i>1)   render7linesPORTgrey( PAUSE, 2 );
   if(i>0)   render7linesPORTgrey( PAUSE, 3 );    
   if(i>0)   render7linesPORTgrey( PAUSE, 3 ); 
   }
   */
  /*
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
   */

  renderalllines( PAUSE, 0 );
  renderalllines( 2*PAUSE, 1 );
  renderalllines( 5*PAUSE, 2 );
  renderalllines( 10*PAUSE, 3 );

  /*
  renderalllines( PAUSE, 0 );
   renderalllines( PAUSE, 1 );
   renderalllines( PAUSE, 2 );
   renderalllines( PAUSE, 3 );
   */
}

void rendermono() {
  int PAUSE = 1500;
  renderalllines( PAUSE, 0 );
}

#endif






