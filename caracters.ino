///////////// CARS ////////////////////
#ifdef CARACTERS_USED
PROGMEM prog_uchar letters[50][5] = { 
  {
    B00000000, // |||
    B01101100,
    B01101100,
    B00000000,
    B00000000
  }
  ,
  {
    B11000000, //A 1
    B00111000,
    B00100110,
    B00111000,
    B11000000
  }
  ,
  {
    B11111110, //B 
    B10010010,
    B10010010,
    B10010010,
    B01101100
  }
  ,
  {
    B01111100, //C
    B10000010,
    B10000010,
    B10000010,
    B01000100
  }
  ,
  {
    B11111110, //D
    B10000010,
    B10000010,
    B10000010,
    B01111100
  }
  ,
  {
    B11111110, //E
    B10010010,
    B10010010,
    B10010010,
    B10000010
  }
  ,
  {
    B11111110, //F
    B00010010,
    B00010010,
    B00010010,
    B00000010
  }
  ,
  {
    B01111100, //G
    B10000010,
    B10000010,
    B10010010,
    B01110100
  }
  ,
  {
    B11111110, //H
    B00010000,
    B00010000,
    B00010000,
    B11111110
  }
  ,
  {
    B00000000, //I
    B10000010,
    B11111110,
    B10000010,
    B00000000
  }
  ,
  {
    B10000000, //J
    B10000010,
    B01111110,
    B00000010,
    B00000000
  }
  ,
  {
    B11111110, //K
    B00010000,
    B00101000,
    B01000100,
    B10000010
  }
  ,
  {
    B11111110, //L
    B10000000,
    B10000000,
    B10000000,
    B10000000
  }
  ,
  {
    B11111110, //M
    B00000100,
    B00001000,
    B00000100,
    B11111110
  }
  ,
  {
    B11111110, //N
    B00001100,
    B00011000,
    B0110000,
    B11111110
  }
  ,
  {
    B01111100, //O
    B10000010,
    B10000010,
    B10000010,
    B01111100
  }
  ,
  {
    B11111110, //P
    B00010010,
    B00010010,
    B00010010,
    B00001100
  }
  ,
  {
    B01111100, //Q
    B10000010,
    B10000010,
    B10100010,
    B11111100
  }
  ,
  {
    B11111110, //R
    B00010010,
    B00110010,
    B01010010,
    B10001100
  }
  ,
  {
    B01001100, //S
    B10010010,
    B10010010,
    B10010010,
    B01100100
  }
  ,
  {
    B00000010, //T
    B00000010,
    B11111110,
    B00000010,
    B00000010 
  }
  ,
  {
    B01111110, //U
    B10000000,
    B10000000,
    B10000000,
    B01111110
  }
  ,
  {
    B00000110, //V
    B00011000,
    B11100000,
    B00011000,
    B00000110
  }
  ,
  {
    B00011110, //W
    B11100000,
    B00111000,
    B11100000,
    B00011110
  }
  ,
  {
    B10000010, //X
    B01000100,
    B00111000,
    B01000100,
    B10000010
  }
  ,
  {
    B00000010, //Y
    B00000100,
    B11111000,
    B00000100,
    B00000010
  }
  ,
  {
    B11000010, //Z 25
    B10100010,
    B10010010,
    B10001010,
    B10000110
  }
  ,
  {
    B00000000, // ' ' 26
    B00000000,
    B00000000,
    B00000000,
    B00000000
  }
  ,
  {
    B01111100, //0 27
    B10100010,
    B10010010,
    B10001010,
    B01111100
  }
  ,
  {
    B00001000, //1
    B10000100,
    B11111110,
    B10000000,
    B00000000
  }
  ,
  {
    B11000100, //2
    B10100010,
    B10010010,
    B10001010,
    B10000100
  }
  ,
  {
    B01000100, //3
    B10010010,
    B10010010,
    B10010010,
    B01101100
  }
  ,
  {
    B00010000, //4
    B00011000,
    B00010100,
    B11111110,
    B00010000
  }
  ,
  {
    B10011110, //5
    B10010010,
    B10010010,
    B10010010,
    B01100000
  }
  ,
  {
    B01111000, //6
    B10010100,
    B10010010,
    B10010010,
    B01100000
  }
  ,
  {
    B00000010, //7
    B11100010,
    B00010010,
    B00001010,
    B00000110
  }
  ,
  {
    B01101100, //8
    B10010010,
    B10010010,
    B10010010,
    B01101100
  }
  ,
  {
    B00001100, //9 37
    B10010010,
    B10010010,
    B01010010,
    B00111100
  }
  ,
  {
    B00011100, // TDM $ 38
    B11110100,
    B10111110,
    B11110100,
    B00011100  
  }
  ,
  {
    B11111100, // INVADER1 ( 39
    B00110010,
    B11111110,
    B00110010,
    B11111100
  }
  ,
  {
    B00111100, // INVADER2 )
    B11110010,
    B00111110,
    B11110010,
    B00111100
  }
  ,
  {
    B00111100, // PAC1 a 41
    B01111110,
    B01111110,
    B01111110,
    B00111100
  }
  ,
  {
    B00111100, // PAC2 b
    B01111110,
    B01111110,
    B01100110,
    B00100100
  }
  ,
  {
    B00111100, // PAC3 c
    B01111110,
    B01100110,
    B01000010,
    B00000000  
  }
  ,
  {
    B00011000, // < d
    B00111100,
    B01111110,
    B11111111,
    B11111111  
  }
  ,
  {
    B00000000, // << e
    B00011000,
    B00111100,
    B01111110,
    B11111111  
  }
  ,
  {
    B00000000, // <<< f
    B00000000,
    B00011000,
    B00111100,
    B01111110  
  }
  ,
  {
    B00000000, // <<<< g
    B00000000,
    B00000000,
    B00011000,
    B00111100  
  } 
  ,
  {
    B00000000, // <<<<< h
    B00000000,
    B00000000,
    B00000000,
    B00011000  
  } 
};

#else
PROGMEM prog_uchar letters[1][1] = {
};
#endif


/*
void dispblock( int posx, int carnb ) {
 for(int i=0; i <= CARWIDTH; i++) {
 virtualdisplay[i + posx] = (byte)random(256);
 }
 }
 */
/*
void dispcar( int posx, int carnb ) {
 //  for(int i=CARWIDTH-1; i >= 0; --i) {
 for(int i=0; i <= CARWIDTH; i++) {
 byte val = pgm_read_byte ( &letters[carnb][i] );
 pointvirtual(posx + i, val);
 //virtualdisplay[posx + i] = (byte)35;
 }
 }
 
 void setcaroffset(int nb) { // espace entre caracteres
 OFFSET = nb;
 }
 
 void resetcarseq() { // pointeur courant de caractere
 carptr = 0;
 }
 
 void backcar() { // remonte de OFFSET dans le pointeur courant
 carptr -= OFFSET;
 }
 
 void dispcarseq( int posx, int posy, byte carascii) {
 int carnb =  carascii - 'A' + 1;
 if (carascii == ' ')  carnb = 27;
 if (carascii == '$')  carnb = 38;
 if (carascii >= '(' && carascii <= ')')  carnb = carascii - '(' + 39; // invader
 if (carascii >= 'a' && carascii <= 'c')  carnb = carascii - 'a' + 41; // pacman
 if (carascii >= '0' && carascii <= '9')  carnb = carascii - '0' + 28;  
 dispcar(  carptr + posx,  posy,  carnb );
 carptr = carptr + OFFSET;
 }
 
 
 
 // NORMAL CHAR DISPLAY ROTATION
 void dispcar( int posx, int posy, int carnb, float rot ) {
 if( posy > 7 ) posy=7;
 if( posy < -7 ) posy=-7;
 int matinit[5][7];
 int matres[5][7];
 for(int i=0; i < CARWIDTH; i++) {
 byte car = pgm_read_byte (&letters[carnb][i]);
 int xp = xrot( 1, i, rot);
 int yp = yrot( 1, i, rot);
 if( posy > 0 ) pointxorvirtual(posx + CARWIDTH - i, (byte)(letters[carnb][i]  >> posy     ) );
 else           pointxorvirtual(posx + CARWIDTH - i, (byte)(letters[carnb][i]  << abs(posy)) );
 }
 }
 
 float xrot(float x, float y, float rot) {
 return x*cos(rot) - y*sin(rot);
 }
 
 float yrot(float x, float y, float rot) {
 return x*sin(rot) + y*cos(rot);
 }
 
 // NORMAL CHAR DISPLAY
 void dispcar( int posx, int posy, int carnb ) {
 if( posy > 7 ) posy=7;
 if( posy < -7 ) posy=-7;
 for(int i=0; i < CARWIDTH; i++) {
 byte car = pgm_read_byte (&letters[carnb][i]);
 if( posy > 0 ) pointxorvirtual(posx + CARWIDTH - i, (byte)(car  >> posy     ) );
 else           pointxorvirtual(posx + CARWIDTH - i, (byte)(car  << abs(posy)) );
 }
 }
 
 // REVERSE OU NORMAL CHAR DISPLAY
 void dispcarreverse( int posx, int posy, int carnb ) {
 if( posy > 7 ) posy=7;
 if( posy < -7 ) posy=-7;
 for(int i=0; i < CARWIDTH; i++) {
 byte car = pgm_read_byte (&letters[carnb][i]);
 if( posy > 0 ) pointxorvirtual(posx +  i, (byte)(car  >> posy     ) );
 else           pointxorvirtual(posx +  i, (byte)(car  << abs(posy)) );
 }
 }
 
 // INVERT VIDEO
 void dispcarinverse( int posx, int posy, int carnb ) {
 if( posy > 7 ) posy=7;
 if( posy < -7 ) posy=-7;
 for(int i=0; i < CARWIDTH; i++) {
 byte car = pgm_read_byte (&letters[carnb][i]);
 car = car ^ 255 ;
 if( posy > 0 ) pointxorvirtual(posx +  i, (byte)(car >> posy     ) );
 else           pointxorvirtual(posx +  i, (byte)(car << abs(posy)) );
 }
 }
 
 
 */

///////////////////////// TOOLS ///////////////////////////////////////////
int ascii2nb(byte carascii) {
  int carnb=-1;
  if (carascii >= 'A' && carascii <= 'Z')    carnb =  carascii - 'A' + 1;
  else if (carascii == ':')  carnb = 0;
  else if (carascii == ' ')  carnb = 27;
  else if (carascii == '$')  carnb = 38;
  else if (carascii >= '(' && carascii <= ')')  carnb = carascii - '(' + 39; // invader
  else if (carascii >= 'a' && carascii <= 'h')  carnb = carascii - 'a' + 41; // pacman a b c, fleche d e f g h
  else if (carascii >= '0' && carascii <= '9')  carnb = carascii - '0' + 28; 
  return carnb; 
}

void setcaroffset(int nb) { // espace entre caracteres
  OFFSET = nb;
}

void resetcarseq() { // pointeur courant de caractere
  carptr = 0;
}

void setcarseq(int nb) { // pointeur courant de caractere
  carptr = nb*OFFSET;
}

void backcar() { // remonte de OFFSET dans le pointeur courant
  carptr -= OFFSET;
}

///////////////////////// SEQUENCE ///////////////////////////////////////////
void dispcarseq( int posx, int posy, int carascii , int bitplane) {
  if( carptr > XMAX ) return;
  if( carascii < 0 )  {
    dispcarreverse(  carptr + posx,  posy, -carascii , bitplane );
    carptr = carptr + OFFSET;
  }
  else if( carascii >= EXPANDED ) {
    dispcardouble(  carptr + posx,  posy,  ascii2nb( carascii - EXPANDED ), bitplane );
    carptr = carptr + OFFSET + 1;
  }
  else {
    dispcar(  carptr + posx,  posy,  ascii2nb( carascii ), bitplane );
    carptr = carptr + OFFSET;
  }
}

// HOMOTHETIC DISPLAY ... 
void dispcarseqhomotetic( int posx, int posy, byte carascii, float sens) {
  if( posy > YMAX ) posy=YMAX;
  if( posy < CARHEIGHT ) posy=-CARHEIGHT;
  int carnb =  ascii2nb(carascii); 
  if( sens >= 0 ) {
    dispcar(  carptr + posx,  posy,  carnb, MAX_INTENSITY );
  }
  else if( sens < 0 ) {
    dispcarreverse(  carptr + posx,  posy,  carnb, MAX_INTENSITY );
  }
  carptr = carptr + OFFSET;
}

void dispcarseq16( int posx, int posy, int carascii , int intensity) {
  if( carptr > XMAX ) return;
  if( carascii < 0 )  {
    //dispcarreverse(  carptr + posx,  posy, -carascii , bitplane );
    carptr = carptr + OFFSET;
  }
  else if( carascii >= EXPANDED ) {
    //dispcardouble16(  carptr + posx,  posy, carascii - EXPANDED , intenstity );
    dispcar16(  carptr + posx,  posy,  ascii2nb( carascii - EXPANDED ), intensity );
    dispcar16(  carptr + posx + 1,  posy,  ascii2nb( carascii -EXPANDED), intensity );
    carptr = carptr + OFFSET + 1;
  }
  else {
    dispcar16(  carptr + posx,  posy,  ascii2nb( carascii ), intensity );
    carptr = carptr + OFFSET;
  }
}


///////////////////////// SPECIALS ///////////////////////////////////////////
void dispcarreverse( int posx, int posy, byte carascii, int bitplane ) {
  if( posy > YMAX ) posy=YMAX;
  if( posy < CARHEIGHT ) posy=-CARHEIGHT;
  for(int i=0; i < CARWIDTH; i++) {
    byte car = pgm_read_byte (&letters[ ascii2nb(carascii) ][i]);
    if( posy >= 0 ) pointxorvirtual(posx +  i, (byte)(car  >> posy     ), bitplane );
    else            pointxorvirtual(posx +  i, (byte)(car  << abs(posy)), bitplane );
  }
}

void dispcardouble( int posx, int posy, byte carascii, int bitplane ) {
  if( posy > YMAX ) posy=YMAX;
  if( posy < CARHEIGHT ) posy=-CARHEIGHT;
  for(int i=0; i < CARWIDTH; i++) {
    byte car = pgm_read_byte (&letters[ ascii2nb(carascii) ][i]);
    if( posy >= 0 ) {
      pointorvirtual(posx + CARWIDTH - i  ,   (byte)(car  >> posy     ), bitplane );
      pointorvirtual(posx + CARWIDTH - i + 1, (byte)(car  >> posy     ), bitplane );
    }
    else {
      pointorvirtual(posx + CARWIDTH - i  ,   (byte)(car  << abs(posy)), bitplane );
      pointorvirtual(posx + CARWIDTH - i + 1, (byte)(car  << abs(posy)), bitplane );
    }
  }
}

void dispcarexpanded( int posx, int posy, byte carascii, int bitplane, int expandfactor ) {
  if( posy > YMAX ) posy=YMAX;
  if( posy < CARHEIGHT ) posy=-CARHEIGHT;
  for(int i=0; i < CARWIDTH; i++) {
    byte car = pgm_read_byte (&letters[ ascii2nb(carascii) ][i]);
    if( posy >= 0 ) {
      for(int j=0; j < expandfactor; j++) {
        pointorvirtual(posx + expandfactor*CARWIDTH - i + j , (byte)(car  >> posy     ), bitplane );
      }
    }
    else {
      for(int j=0; j < expandfactor; j++) {
        pointorvirtual(posx + expandfactor*CARWIDTH - i + j , (byte)(car  << abs(posy)), bitplane );
      }
    }
  }
}

// FULLSCREEN ONLY ... TODO for the rest!

// display BIG fullscreen character
void dispcarbig16( int posx, int posy, byte carascii ) {
  dispcarbig16(  posx,  posy,  carascii, MAX_INTENSITY );
}

void dispcarbig16( int posx, int posy, byte carascii, int intensity ) {
  //#ifdef FULLSCREEN_DISPLAY

  /*
  if( posy > YMAX ) posy=YMAX;
   if( posy < CARHEIGHT ) posy=-CARHEIGHT;
   for(int i=0; i < CARWIDTH; i++) {
   byte car = pgm_read_byte (&letters[ ascii2nb(carascii) ][i]);
   if( posy >= 0 ) {
   for(int j=0; j < expandfactor; j++) {
   pointorvirtual(posx + expandfactor*CARWIDTH - i + j , (byte)(car  >> posy     ), bitplane );
   }
   }
   else {
   for(int j=0; j < expandfactor; j++) {
   pointorvirtual(posx + expandfactor*CARWIDTH - i + j , (byte)(car  << abs(posy)), bitplane );
   }
   }
   }
   */

  if( posy > YMAX  ) posy = YMAX;
  if( posy < -CARHEIGHT ) posy = -CARHEIGHT;
  int carnb = ascii2nb(carascii);

  for(int i=0; i < CARWIDTH; i++) {
    //int cell = expandfactorX / 8; // TODO
    byte car = pgm_read_byte (&letters[carnb][i]);
    for(int k=0; k<8 ;k++ ) {
      //if( bitRead( car, k ) ) setpixel16( posx - i, posy + k, MAX_INTENSITY);
      if( bitRead( car, k ) ) {
        int x = posx - i*expandfactorX;
        int y = posy + k*expandfactorY;
        //setpixel16( x, y, MAX_INTENSITY);
        rect16( x, y, x+expandfactorX, y+expandfactorY, intensity);
        /*
        for(int j=0; j < expandfactorX; j++) { // EXPANSION X
         for(int l=0; l < expandfactorY; l++) { // EXPANSION
         int x = posx - i*expandfactorX + j;
         int y =  posy + l*expandfactorY + j;
         setpixel16( x, y, MAX_INTENSITY);
         //rect16( x, y, x+expandfactor+1, y+expandfactor+1, MAX_INTENSITY);
         }
         }
         */
      } 
    }
  }

  //#endif
}

// FULLSCREEN ONLY ... TODO for the rest!
void dispcarexpanded16( int posx, int posy, byte carascii, int bitplane, float expandfactor ) {
  //#ifdef FULLSCREEN_DISPLAY

  /*
  if( posy > YMAX ) posy=YMAX;
   if( posy < CARHEIGHT ) posy=-CARHEIGHT;
   for(int i=0; i < CARWIDTH; i++) {
   byte car = pgm_read_byte (&letters[ ascii2nb(carascii) ][i]);
   if( posy >= 0 ) {
   for(int j=0; j < expandfactor; j++) {
   pointorvirtual(posx + expandfactor*CARWIDTH - i + j , (byte)(car  >> posy     ), bitplane );
   }
   }
   else {
   for(int j=0; j < expandfactor; j++) {
   pointorvirtual(posx + expandfactor*CARWIDTH - i + j , (byte)(car  << abs(posy)), bitplane );
   }
   }
   }
   */

  if( posy > YMAX  ) posy = YMAX;
  if( posy < -CARHEIGHT ) posy = -CARHEIGHT;
  int carnb = ascii2nb(carascii);

  for(int i=0; i < CARWIDTH; i++) {
    int cell = expandfactor / 8; // TODO
    byte car = pgm_read_byte (&letters[carnb][i]);
    for(int k=0; k<8 ;k++ ) {
      //if( bitRead( car, k ) ) setpixel16( posx - i, posy + k, MAX_INTENSITY);
      if( bitRead( car, k ) ) {
        for(int j=0; j < expandfactor; j++) { // EXPANSION
          int x = posx - i*expandfactor + j;
          int y =  posy + k*expandfactor + j;
          setpixel16( x, y, MAX_INTENSITY);
          //rect16( x, y, x+expandfactor+1, y+expandfactor+1, MAX_INTENSITY);
        }
      } 
    }
  }

  //#endif
}
///////////////////////// SIMPLE ///////////////////////////////////////////
void dispcarascii( int posx, int posy, byte carascii, int bitplane ) {
  dispcar(  posx,  posy,  ascii2nb(carascii), bitplane );
}

void dispcarascii16( int posx, int posy, byte carascii, int intensity ) {
  dispcar16(  posx,  posy,  ascii2nb(carascii), intensity >> 2 );
}

// BITPLANE CHAR DISPLAY
void dispcar( int posx, int posy, int carnb, int bitplane ) {
  //if(posx + OFFSET > XMAX) return;
  if(carnb < 0) {
    dispcarreverse(  posx,  posy,  -carnb,  bitplane );
    return;
  }
  if(carnb > CARMAX ) return;
  if( posy > 7  ) posy = 7;
  if( posy < -7 ) posy = -7;
  if( bitplane > BITPLANES -1 || bitplane < 0) return;

  for(int i=0; i < CARWIDTH; i++) {
    byte car = pgm_read_byte (&letters[carnb][i]);
    if( posy >= 0 ) pointxorvirtual( posx + CARWIDTH - i -1, car  >> posy     , bitplane);
    else            pointxorvirtual( posx + CARWIDTH - i -1, car  << abs(posy), bitplane);
  }
}

// BITPLANE CHAR DISPLAY 16 level of GREY
void dispcar16( int posx, int posy, int carnb, int intensity ) {
  //if(posx + OFFSET > XMAX) return;
  int color16 = intensity>>BITPLANES;
  if(carnb < 0) {
    //dispcarreverse16(  posx,  posy,  -carnb,  intensity );   // TODO
    return;
  }
  if(carnb > CARMAX ) return;

#if defined DOUBLE_DISPLAY
  if( posy > YMAX  ) posy = YMAX;
  if( posy < -YMAXMID ) posy = -YMAXMID;

  // DISP 1
  if( posy < YMAXMID && posy > -CARHEIGHT ) {
    for(int i=0; i < CARWIDTH; i++) {
      byte car = pgm_read_byte (&letters[carnb][i]);
      if( posy >= 0 ) car =  car  >> posy;
      else            car =  car  << abs(posy) ;

      int dec = posx + CARWIDTH - i -1;
      if(dec < XMAX && dec >=0 ) {
        if(color16 & B0001) virtualdisplay2[0][dec] |= car;
        if(color16 & B0010) virtualdisplay2[1][dec] |= car;
        if(color16 & B0100) virtualdisplay2[2][dec] |= car;
        if(color16 & B1000) virtualdisplay2[3][dec] |= car;
      }
    }
  }
  // DISP 2  
  if( posy > (YMAXMID - CARHEIGHT) && posy < YMAX ) {
    posy -= YMAXMID;
    for(int i=0; i < CARWIDTH; i++) {
      byte car = pgm_read_byte (&letters[carnb][i]);
      if( posy >= 0 ) car =  car  >> posy;
      else            car =  car  << abs(posy) ;

      int dec = posx + CARWIDTH - i -1;
      if(dec < XMAX  && dec >=0 ) {
        if(color16 & B0001) virtualdisplay[currfb][0][0][dec] |= car;
        if(color16 & B0010) virtualdisplay[currfb][0][1][dec] |= car;
        if(color16 & B0100) virtualdisplay[currfb][0][2][dec] |= car;
        if(color16 & B1000) virtualdisplay[currfb][0][3][dec] |= car;
      }
    }
  }

#elif defined FULLSCREEN_DISPLAY
  if( posy > YMAX + CARHEIGHT   ) posy = YMAX + CARHEIGHT;
  if( posy < -CARHEIGHT ) posy = -CARHEIGHT;
  if( color16 == 0 ) return;

  for(int i=0; i < CARWIDTH; ++i) {
    byte car = pgm_read_byte (&letters[carnb][i]);
    for(int k=0; k<8 ; ++k ) {
      // OLD VERSION    --- WORKING!
      //if( bitRead( car, k ) ) setpixel16( posx - i, posy + k, MAX_INTENSITY);

      // FAST VERSION   --- TESTING!
      if( car & (1 << k)  ) {
        int x = posx - i + CARWIDTH - 1;
        int y = posy + k;
        if( x >= XMAX || x < 0 || y>YMAX || y<0) continue;

        int seg = 0.142857 * y;                            // WHICH SEGMENT ?            y / 7    
        //bitSet(   virtualdisplay[bitplane][x], y-7*bitplane );  
        //virtualdisplay[currfb][seg][bitplane][x] |= ( 1<<( y - 7*seg )); // PUT BIT IN THE SEGMENT ?  
        if(color16 > 0) {
          byte car = 1<<( y - 7*seg);
          if(color16 & B0001) virtualdisplay[currfb][seg][0][x] |= car;
          if(BITPLANES >=2 && color16 & B0010) virtualdisplay[currfb][seg][1][x] |= car;
          if(BITPLANES >=3 && color16 & B0100) virtualdisplay[currfb][seg][2][x] |= car;
          if(BITPLANES >=4 && color16 & B1000) virtualdisplay[currfb][seg][3][x] |= car;
        }
      }
      // FAST VERSION END
    }
  }
#else 

  if( posy > YMAX  ) posy = YMAX;
  if( posy < -CARHEIGHT ) posy = -CARHEIGHT;

  for(int i=0; i < CARWIDTH; i++) {
    byte car = pgm_read_byte (&letters[carnb][i]);
    if( posy >= 0 ) car =  car  >> posy;
    else            car =  car  << abs(posy) ;

    int dec = posx + CARWIDTH - i -1;

    if(color16 & B0001) virtualdisplay[currfb][0][0][dec] |= car;
    if(color16 & B0010) virtualdisplay[currfb][0][1][dec] |= car;
    if(color16 & B0100) virtualdisplay[currfb][0][2][dec] |= car;
    if(color16 & B1000) virtualdisplay[currfb][0][3][dec] |= car;
  }

#endif
}

// BITPLANE STRING, WITH DISPLAY 16 level of GREY
void dispstring16( int posx, int posy, char* s, int taille, int intensity ) {
  int n = 0;

  //if( s[0] == NULL ) taille = taille - 1;

  while( n < taille ) {
    char c = s[taille - n - 1];
    //dispcarseq(  (sizeof(str) - n)*OFFSET + posx,  posy,  c,  3 );
    dispcarseq16(  posx,  posy,  c,  intensity );
    n++;
  }
}

// BITPLANE STRING, WITH DISPLAY 16 level of GREY
void dispstring16( int posx, int posy, String s, int taille, int intensity ) {
  int n = 0;

  //if( s[0] == NULL ) taille = taille - 1;

  while( n < taille ) {
    char c = s[taille - n - 1];
    //dispcarseq(  (sizeof(str) - n)*OFFSET + posx,  posy,  c,  3 );
    dispcarseq16(  posx,  posy,  c,  intensity );
    n++;
  }
}

// BITPLANE SIN STRING, WITH DISPLAY 16 level of GREY
void dispstringsin16( int posx, int posy, String s, int taille, int intensity, float alpha, float fact ) {

  int n = taille - 1;
  float shift = 3.14/(float)taille;
  //if( s[0] == NULL ) taille = taille - 1;

  while( n < taille ) {
    char c = s[taille - n - 1];
    //dispcarseq(  (sizeof(str) - n)*OFFSET + posx,  posy,  c,  3 );
    dispcarseq16(  posx,  posy + fact*sin(alpha + shift*n),  c,  intensity );
    n++;
  }

}


/////////////////////////// CLOCK, COUNTER, ... ////////////////////////////////////////////////////
void dispcountern( unsigned long c, int ndigits, int x, int y, int bitplane, boolean isdouble  ){
  resetcarseq();
  int offset = OFFSET;
  if( isdouble ) offset = 2*OFFSET;

  unsigned long  dispc = c;
  for(int i=ndigits; i > 0; i--) {
    //switch( ndigits ) {
    int naine = dispc / pow( 10, i - 1 );
    dispc = dispc - naine*pow( 10, i - 1);
    if( isdouble ) dispcardouble( x + 2*i*OFFSET - 2*ndigits*OFFSET, y, '0' + naine, bitplane );
    dispcarascii( x + i*OFFSET - ndigits*OFFSET, y, '0' + naine, bitplane );
  }  
}

void dispcountern16( unsigned long c, int ndigits, int x, int y, int bitplane, boolean isdouble  ){
  resetcarseq();
  int offset = OFFSET;
  if( isdouble ) offset = 2*OFFSET;

  unsigned long  dispc = c;
  for(int i=ndigits; i > 0; i--) {
    //switch( ndigits ) {
    int naine = dispc / pow( 10, i - 1 );
    dispc = dispc - naine*pow( 10, i - 1);
    if( isdouble ) dispcardouble( x + 2*i*OFFSET - 2*ndigits*OFFSET, y, '0' + naine, bitplane );
    dispcar16( x + i*OFFSET - ndigits*OFFSET, y, '0' + naine, MAX_INTENSITY );
  }  
}

void clock( unsigned long seconds_from_midnigth, int x, int y, boolean isdouble, int bitplane  ){
  int hours = (seconds_from_midnigth / 3600) % 12;
  int minutes = ( (seconds_from_midnigth - hours*3600) / 60 ) % 60;
  int secondes = ( seconds_from_midnigth - (hours * 3600 + minutes * 60) ) % 60;

  dispcountern( secondes, 2, x, y, bitplane, isdouble);
  dispcarseq( x, y, ':' + EXPANDED, bitplane);
  dispcountern( minutes, 2, x, y, bitplane, isdouble);
  dispcarseq( x, y, ':' + EXPANDED, bitplane);
  dispcountern( hours, 2, x, y, bitplane, isdouble);
}

void clock16( unsigned long seconds_from_midnigth, int x, int y, boolean isdouble, int bitplane  ){
  int hours = (seconds_from_midnigth / 3600) % 12;
  int minutes = ( (seconds_from_midnigth - hours*3600) / 60 ) % 60;
  int secondes = ( seconds_from_midnigth - (hours * 3600 + minutes * 60) ) % 60;

  dispcountern16( secondes, 2, x, y, bitplane, isdouble);
  dispcarseq16( x, y, ':' + EXPANDED, MAX_INTENSITY);
  dispcountern16( minutes, 2, x, y, bitplane, isdouble);
  dispcarseq16( x, y, ':' + EXPANDED, MAX_INTENSITY);
  dispcountern16( hours, 2, x, y, bitplane, isdouble);
}









































