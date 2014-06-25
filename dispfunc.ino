

/*
int getvirtualdisplay( int x, int y) {
 return bitRead( virtualdisplay[ x ], y );
 }
 
 void pointvirtual(float x, float y) {
 if(x > XMAX-1 || y > YMAX) return;
 if(x < 0 || y < 0) return;
 bitSet(virtualdisplay[(int)x], (int)y);
 }
 
 void pointvirtual(float x, byte value) {
 if(x > XMAX-1 || x < 0) return;
 virtualdisplay[(int)x] = value;
 }
 
 void pointxorvirtual(float x, byte value) {
 if(x > XMAX-1 || x < 0) return;
 virtualdisplay[(int)x] = virtualdisplay[(int)x] ^ value;
 }
 
 void setvirtualdisplay( byte val ) {
 //memset( void *s, int c, size_t n );
 memset( virtualdisplay, val, DMAXSIZE );
 }
 
 void setvirtualdisplayrnd() {
 for(int i=0; i < XMAX; i++) {
 virtualdisplay[i] = (byte)random(256);
 }
 }
 
 void blockvirtual( int x, int mySize ) {
 if(x < 0 ) {  // règle bug affichage qq block quitte écran
 x = min( mySize, abs(x) );
 mySize = mySize - x;
 x = 0;
 }
 //memset( void *s, int c, size_t n );
 memset( virtualdisplay + x, 255, mySize );
 }
 
 
 void disprndblock( int posx, int posy, int carnb ) {
 if( posy > 7 ) posy=7;
 if( posy < -7 ) posy=-7;
 for(int i=0; i <= CARWIDTH; i++) {
 //pointvirtual(posx + i, letters[carnb][i]);
 //virtualdisplay[i] = (byte)letters[carnb][i];
 if( posy >= 0 ) virtualdisplay[i + posx] = (byte)random(256) >> posy;
 else           virtualdisplay[i + posx] = (byte)random(256) << abs(posy);
 
 }
 }
 
 
 */

/////////////////////////////// VECTOR SECTION /////////////////////////////////

// 2D rotation, returns X
float rotx(float x, float y, float alpha) {
  return x*cos( alpha ) + y*sin( alpha );
}
// 2D rotation, returns y
float roty(float x, float y, float alpha) {
  return -x*sin( alpha ) + y*cos( alpha );
}

void swap(int* a , int* b) {
  int t = *a;
  *a = *b;
  *b = t;
}

#define LLIM 300
void  line(int x0, int y0, int x1, int y1, int intensity) { // Bresenham Line Algorithm
  if( x0 > LLIM) x0=LLIM;
  if( y0 > LLIM) y0=LLIM;
  if( x1 > LLIM) x1=LLIM;
  if( y1 > LLIM) y1=LLIM;
  if( x0 < -LLIM) x0=-LLIM;
  if( y0 < -LLIM) y0=-LLIM;
  if( x1 < -LLIM) x1=-LLIM;
  if( y1 < -LLIM) y1=-LLIM;

  int Dx = x1 - x0; 
  int Dy = y1 - y0;
  int steep = (abs(Dy) >= abs(Dx));
  if (steep) {

    int a = x0;
    int b = y0;
    x0=b;
    y0=a;

    a = x1;
    b = y1;
    x1=b;
    y1=a;

    // recompute Dx, Dy after swap
    Dx = x1 - x0;
    Dy = y1 - y0;
  }
  int xstep = 1;
  if (Dx < 0) {
    xstep = -1;
    Dx = -Dx;
  }
  int ystep = 1;
  if (Dy < 0) {
    ystep = -1;		
    Dy = -Dy; 
  }

  int TwoDy = 2*Dy; 
  int TwoDyTwoDx = TwoDy - 2*Dx; // 2*Dy - 2*Dx
  int E = TwoDy - Dx; //2*Dy - Dx
  int y = y0;
  int xDraw, yDraw;	
  for (int x = x0; x != x1; x += xstep) {		
    if (steep) {			
      xDraw = y;
      yDraw = x;
    } 
    else {			
      xDraw = x;
      yDraw = y;
    }
    // plot
    //setpixel(xDraw, yDraw);
    setpixel16( int(xDraw), int(yDraw), intensity );
    // next
    if (E > 0) {
      E += TwoDyTwoDx; //E += 2*Dy - 2*Dx;
      y = y + ystep;
    } 
    else {
      E += TwoDy; //E += 2*Dy;
    }
  }
}

void circle(int x0, int y0, int radius, int intensity)
{
  int f = 1 - radius;
  int ddF_x = 1;
  int ddF_y = -2 * radius;
  int x = 0;
  int y = radius;

  setpixel16(x0, y0 + radius, intensity );
  setpixel16(x0, y0 - radius, intensity );
  setpixel16(x0 + radius, y0, intensity );
  setpixel16(x0 - radius, y0, intensity );

  while(x < y)
  {
    if(f >= 0) 
    {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;    
    setpixel16(x0 + x, y0 + y, intensity );
    setpixel16(x0 - x, y0 + y, intensity );
    setpixel16(x0 + x, y0 - y, intensity );
    setpixel16(x0 - x, y0 - y, intensity );
    setpixel16(x0 + y, y0 + x, intensity );
    setpixel16(x0 - y, y0 + x, intensity );
    setpixel16(x0 + y, y0 - x, intensity );
    setpixel16(x0 - y, y0 - x, intensity );
  }
}

float distance(float x, float y, int mx, int my) {
  return sqrt( (mx - x)*(mx - x) - (my - y)*(my - y) );
}

/////////////////////////////// HW EFFECTS SECTION /////////////////////////////////
// Fadin / Fadout
boolean fadein(int timeToFadems) {
  if( ( displayPause < displayPauseSTD ) && ( lastimeFade < (millis() - timeToFadems / FADE_FRACTIONS) ) ) {
    lastimeFade = millis();
    displayPause = displayPause + displayPauseSTD / FADE_FRACTIONS;
    setBrightness( displayPause );
    return false;
  }
  else if( displayPause == displayPauseSTD ) return true;
}  
boolean fadeout(int timeToFadems) {
  if( ( displayPause >=0  ) && ( lastimeFade < (millis() - timeToFadems / FADE_FRACTIONS) ) ) {
    lastimeFade = millis();
    displayPause = displayPause - displayPauseSTD / FADE_FRACTIONS;
    setBrightness( displayPause );
    return false;
  }
  else if( displayPause == 0 ) return true;
}
void setBrightness(int val) {
  if(val >= 0 ) displayPause = val;
  else displayPause = 1;
} 
void resetBrightness() {
  displayPause = displayPauseSTD;
} 

void setvirtualdisplay( byte val, int bitplane ) {
  //memset( void *s, int c, size_t n );
  for(int i=0; i < SEGMENTS; i++)  memset( &virtualdisplay[currfb][i][bitplane][0] , val, XMAX );
}

void setvirtualdisplay( byte val ) {
  //memset( void *s, int c, size_t n );
  for(int j=0; j < SEGMENTS; j++) {
    for(int i=0; i<BITPLANES; i++) {
      //memset( &virtualdisplay[currfb][j][i][0] , val, XMAX );
      //if(currfb_disp == 1)
      memset( &virtualdisplay[currfb][j][i][0] , val, XMAX );
      //else
      //  memset( &virtualdisplay[currfb_disp][j][i][0] , val, XMAX );
    }
  }
#if (defined DOUBLE_DISPLAY)
  for(int i=0; i<BITPLANES; i++) {
    memset( &virtualdisplay2[i][0] , val, XMAX );
  }
#endif
}

// very experimental
void setvirtualdisplay( byte val, byte alpha ) {
  //memset( void *s, int c, size_t n );
  if(alpha > BITPLANES) alpha = BITPLANES;
  for(int j=0; j < SEGMENTS; j++) {
    for(int i=0; i<alpha; i++) {    // BITPLANES
      //memset( &virtualdisplay[currfb][j][i][0] , val, XMAX );
      if(currfb_disp == 1)
        memcpy( &virtualdisplay[currfb_disp][j][i][0] , &virtualdisplay[currfb][j][i][0],      XMAX );
      else 
        memcpy( &virtualdisplay[currfb][j][i][0]      , &virtualdisplay[currfb_disp][j][i][0], XMAX );      
    }
  }
  for(int j=0; j < SEGMENTS; j++) {
    for(int i=alpha; i<BITPLANES; i++) {
      if(currfb_disp == 1)
        memset( &virtualdisplay[currfb][j][i][0] , val, XMAX );
      else
        memset( &virtualdisplay[currfb_disp][j][i][0] , val, XMAX );
    }
  }
#if (defined DOUBLE_DISPLAY)
  for(int i=0; i<BITPLANES; i++) {
    memset( &virtualdisplay2[i][0] , val, XMAX );
  }
#endif
}


/////////////////////////////// SHAPE SECTION /////////////////////////////////
void blockvirtual( int x, byte mySize, int bitplane ) {
  if(x < 0 ) {  // règle bug affichage qq block quitte écran
    x = min( mySize, abs(x) );
    mySize = mySize - abs(x);
    if(mySize < 0) mySize=0; 
    x = 0;
  }
  if(x+mySize >= XMAX_MINUS) {
    x = XMAX_MINUS - mySize;
  }
  //memset( void *s, int c, size_t n );
  //for(int i=0; i<=bitplane; i++) {
  memset( &virtualdisplay[currfb][0][bitplane][0] + x, 255, mySize );
  //}
}

// rectangle shaded
#ifdef DOUBLE_DISPLAY
void rect16( int x1, int y1, int x2, int y2, byte intensity ) {
  int color16 = intensity>>4;

  // SWAP
  int a=0;
  if( x1 > x2 ) { 
    a=x1; 
    x1=x2; 
    x2=a; 
  }
  if( y1 > y2 ) { 
    a=y1; 
    y1=y2; 
    y2=a; 
  }

  if(x1 < 0 ) x1=0;
  if(x2 < 0 ) x2=0;
  if(y1 < 0 ) y1=0;
  if(y2 < 0 ) y2=0;
  if(x1 > XMAX_MINUS) x1 = XMAX_MINUS;
  if(x2 > XMAX_MINUS) x2 = XMAX_MINUS;

  //if(y1 > YMAXMID-1 ) y1 = YMAXMID-1;
  int y2temp=0;
  if(y1 < YMAXMID ) {
    if(y2 >= YMAXMID-1 ) y2temp = YMAXMID-1;
    byte b = 0;
    for(int i=y1; i <= y2temp; i++) bitSet( b, i );

    for(int i=x1; i <= x2; i++) {
      if(color16 & B0001) virtualdisplay[currfb][0][0][i] ^= b;
      if(color16 & B0010) virtualdisplay[currfb][0][1][i] ^= b;
      if(color16 & B0100) virtualdisplay[currfb][0][2][i] ^= b;
      if(color16 & B1000) virtualdisplay[currfb][0][3][i] ^= b;
    }
  }

  if(y2 >= YMAXMID ) { 
    {
      if(y2 > YMAX_MINUS ) y2 = YMAX_MINUS;
      y2 = y2 - YMAXMID;
      if(y1 < YMAXMID - 1 ) y1 = 0;
      else y1 = y1 - YMAXMID;

      byte b = 0;
      for(int i=y1; i <= y2; i++) bitSet( b, i );
      for(int i=x1; i <= x2; i++) {
        if(color16 & B0001) virtualdisplay2[0][i] ^= b;
        if(color16 & B0010) virtualdisplay2[1][i] ^= b;
        if(color16 & B0100) virtualdisplay2[2][i] ^= b;
        if(color16 & B1000) virtualdisplay2[3][i] ^= b;
      }  
    }
  }
  //for(int i=x1; i <= x2; i++) virtualdisplay[bitplane][i] ^= b;
}

#elif defined FULLSCREEN_DISPLAY
void rect16( int x1, int y1, int x2, int y2, byte intensity ) {

  int color16 = intensity>>4;
  if(x1 < 0 ) x1=0;
  if(x2 < 0 ) x2=0;
  if(y1 < 0 ) y1=0;
  if(y2 < 0 ) y2=0;

  if(x1 > XMAX_MINUS) x1 = XMAX_MINUS;
  if(x2 > XMAX_MINUS) x2 = XMAX_MINUS;

  if(y1 > YMAX_MINUS ) y1 = YMAX_MINUS;
  if(y2 > YMAX_MINUS ) y2 = YMAX_MINUS;

  //avoid stuck pixel on the sides
  if(x1 ==0 && x2==0) return;
   if(y1 ==0 && y2==0) return;
   if(x1 ==XMAX_MINUS && x2==XMAX_MINUS) return;
   if(y1 ==YMAX_MINUS && y2==YMAX_MINUS) return;

  if(x1 > x2) { // swap
    int temp=x2; 
    x2=x1; 
    x1=temp; 
  };

  if(y1 > y2) { // swap
    int temp=y2; 
    y2=y1; 
    y1=temp; 
  };


  // FILL BRUT VERSION
  for(int j=y1; j <= y2; j++) {
    for(int i=x1; i <= x2; i++) {
      //setpixel16( i, j, intensity );
      //pointvirtual16( i, j, intensity );
      //int bitplane = .142857*j;
      int k = floor(j / SEGMENTS);
      /*
      if(color16 >= 1) bitSet(   virtualdisplay[k][bitplane][i], j-7*bitplane );   // pointvirtual16 INLINE
       else             bitClear( virtualdisplay[k][bitplane][i], j-7*bitplane );
       */
      byte bitToSet = j - 7*k;

      if( color16 >=1 ) {
        if(color16 & B0001) bitSet( virtualdisplay[currfb][k][0][i], bitToSet ); 
        if(color16 & B0010) bitSet( virtualdisplay[currfb][k][1][i], bitToSet ); 
        if(color16 & B0100) bitSet( virtualdisplay[currfb][k][2][i], bitToSet ); 
        if(color16 & B1000) bitSet( virtualdisplay[currfb][k][3][i], bitToSet );  
      }
      /*
      else {
        if(color16 & B0001) bitClear( virtualdisplay[currfb][k][0][i], bitToSet ); 
        if(color16 & B0010) bitClear( virtualdisplay[currfb][k][1][i], bitToSet ); 
        if(color16 & B0100) bitClear( virtualdisplay[currfb][k][2][i], bitToSet ); 
        if(color16 & B1000) bitClear( virtualdisplay[currfb][k][3][i], bitToSet );          
      }
      */

      /*
      byte b = 1 << bitToSet;
       if(color16 & B0001) virtualdisplay[currfb][k][0][i] ^= b ; 
       if(color16 & B0010) virtualdisplay[currfb][k][1][i] ^= b ; 
       if(color16 & B0100) virtualdisplay[currfb][k][2][i] ^= b ; 
       if(color16 & B1000) virtualdisplay[currfb][k][3][i] ^= b ;  
       */
    }
  }

  /*
  // FILL FAST VERSION 2 (Y)
   int filllength = x2 - x1+ 1;
   int bp1 = y1 % 7;
   int bp2 = y2 % 7;
   
   // AU DESSUS
   byte * bp_ptr = &virtualdisplay[bp1][x1]; 
   byte pattern = B11111111 >> ( bp1 * 7 - bp1);
   memset( bp_ptr, pattern, (byte)filllength  );
   
   // LE PLEIN
   for(int b=bp1; b < bp2; b++) {
   bp_ptr = &virtualdisplay[b][x1];                         //virtualdisplay[BITPLANES][XMAX];
   memset( bp_ptr, 255, (byte)filllength       );          // fill bytes as much as possiblr   
   } 
   
   // EN DESSOUS
   bp_ptr = &virtualdisplay[bp2][x1]; 
   pattern = B11111111 << ( bp2 * 7 - bp2);
   memset( bp_ptr, pattern, (byte)filllength  );
   */
  /*
  int mySize = filllength / 7; // >> 3;
   int reste_mySize = filllength - mySize;
   for(int j=y1; j <= y2; j = j+7) {
   int bp = j % 8;                                          //int reste_bp = j - bp*7;
   byte * bp_ptr = &virtualdisplay[bp][x1];                 //virtualdisplay[BITPLANES][XMAX];
   memset( bp_ptr, 255, (byte)mySize       );               // fill bytes as much as possiblr
   if(reste_mySize !=0 ) {
   byte * lastptr = bp_ptr + mySize;
   *lastptr = B11111111 << (byte)(8 - reste_mySize);      // fill bit left then
   }
   }
   */

  /*
  // FILL FAST VERSION ...
   int filllength = x2 - x1;
   int mySize = filllength / 8; // >> 3;
   int reste_mySize = filllength - mySize;
   for(int j=y1; j <= y2; j++) {
   int bp = j % 8;                                          //int reste_bp = j - bp*7;
   byte * bp_ptr = &virtualdisplay[bp][x1];                 //virtualdisplay[BITPLANES][XMAX];
   memset( bp_ptr, 255, (byte)mySize       );               // fill bytes as much as possiblr
   if(reste_mySize !=0 ) {
   byte * lastptr = bp_ptr + mySize;
   *lastptr = B11111111 << (byte)(8 - reste_mySize);      // fill bit left then
   }
   }
   */
  /*
  byte b = 0;
   for(int i=y1; i <= y2; i++) 
   bitSet( b, i );
   for(int i=x1; i <= x2; i++) {
   if(color16 & B0001) virtualdisplay[0][i] ^= b;
   }
   //for(int i=x1; i <= x2; i++) virtualdisplay[bitplane][i] ^= b;
   }
   */
}

#else
void rect16( int x1, int y1, int x2, int y2, byte intensity ) {
  int color16 = intensity>>4;
  if(x1 < 0 ) x1=0;
  if(x2 < 0 ) x2=0;
  if(y1 < 0 ) y1=0;
  if(y2 < 0 ) y2=0;

  if(x1 > XMAX_MINUS) x1 = XMAX_MINUS;
  if(x2 > XMAX_MINUS) x2 = XMAX_MINUS;

  if(y1 > YMAX_MINUS ) y1 = YMAX_MINUS;
  if(y2 > YMAX_MINUS ) y2 = YMAX_MINUS;

  //exp
  if(x1 ==0 && x2==0) return;
  if(y1 ==0 && y2==0) return;
  if(x1 ==XMAX_MINUS && x2==XMAX_MINUS) return;
  if(y1 ==YMAX_MINUS && y2==YMAX_MINUS) return;

  byte b = 0;
  for(int i=y1; i <= y2; i++) bitSet( b, i );

  for(int i=x1; i <= x2; i++) {
    if(color16 & B0001) virtualdisplay[currfb][0][0][i] ^= b;
    if(color16 & B0010) virtualdisplay[currfb][0][1][i] ^= b;
    if(color16 & B0100) virtualdisplay[currfb][0][2][i] ^= b;
    if(color16 & B1000) virtualdisplay[currfb][0][3][i] ^= b;
  }
  //for(int i=x1; i <= x2; i++) virtualdisplay[bitplane][i] ^= b;
}
#endif

/////////////////////////////// PIXEL SECTION /////////////////////////////////
void pointxorvirtual(int x, byte value, int bitplane) {
  if(x > XMAX_MINUS || x < 0) return;
  if(bitplane < 0 || bitplane > BITPLANES-1) return;
  //virtualdisplay[bitplane][(int)x] = virtualdisplay[bitplane][(int)x] ^ value;
  virtualdisplay[currfb][0][bitplane][x] ^= value;
}

void pointorvirtual(int x, byte value, int bitplane) {
  if(x > XMAX_MINUS || x < 0) return;
  if(bitplane < 0 || bitplane > BITPLANES-1) return;
  virtualdisplay[currfb][0][bitplane][x] |= value;
}

void pointvirtual(int x, int y, int bitplane) {
  if( (x > XMAX || y > YMAX)  || (x < 0 || y < 0) || (bitplane < 0 || bitplane > BITPLANES-1) )return;
  bitSet( virtualdisplay[currfb][0][bitplane][x], y );
  //virtualdisplay[bitplane][x] = virtualdisplay[bitplane][x] | 1<<(y%7);
}

void setpixel(int x, int y, int intensity) {
  intensity = map( intensity, 0, MAX_INTENSITY, 0, BITPLANES-1);
  pointvirtual( x,  y, intensity );  // répartir dans les BITPLANES
}

///// return BOOLEAN pixel value!
boolean getpixel(int x, int y) {
#if defined FULLSCREEN_DISPLAY
  //int bitplane = floor((y-1)/7);
  int bitplane = .142857*y;
  return bitRead(   virtualdisplay[currfb][0][bitplane][x], y-7*bitplane );
#else
  return false;
#endif

}



void setpixel16(int x, int y, int intensity) {
  //intensity = map( intensity, 0, 255, 0, COLORS);
  //pointvirtual16( x,  y, intensity );
  pointvirtual16( x,  y, intensity>>4 );
}

void pointvirtual16(int x, int y, int color16) {
  if( x >= XMAX || y >= YMAX || x < 0 || y < 0 ) return;
  if( color16 > COLOR_MINUS ) color16 = COLOR_MINUS;
  else if( color16 < 0 ) color16 = 0;
  //for(int i=0; i<4 ; i++) {
#ifdef DOUBLE_DISPLAY
  if( y < YMAXMID ) {
    if(color16 & B0001) bitSet( virtualdisplay[currfb][0][0][x], y );
    if(color16 & B0010) bitSet( virtualdisplay[currfb][0][1][x], y );
    if(color16 & B0100) bitSet( virtualdisplay[currfb][0][2][x], y );
    if(color16 & B1000) bitSet( virtualdisplay[currfb][0][3][x], y );
  }
  else {
    y = y - YMAXMID;
    if(color16 & B0001) bitSet( virtualdisplay2[0][x], y );
    if(color16 & B0010) bitSet( virtualdisplay2[1][x], y );
    if(color16 & B0100) bitSet( virtualdisplay2[2][x], y );
    if(color16 & B1000) bitSet( virtualdisplay2[3][x], y );      
  }
#elif defined FULLSCREEN_DISPLAY
  int seg = floor((y) / SEGMENT_HEIGHT);  // slow...
  //int bitplane = .142857*y;    // /7 pour 7 pixel par segments
  //if(color16 >= 1) bitSet(   virtualdisplay[seg][bitplane][x], y-7*bitplane );
  //else            bitClear( virtualdisplay[seg][bitplane][x], y-7*bitplane );
  int byteValue = (y - SEGMENT_HEIGHT*seg);
  if(color16 >= 1) {
    if( color16 & B0001) bitSet( virtualdisplay[currfb][seg][0][x], byteValue );
    if(BITPLANES >=2 && color16 & B0010) bitSet( virtualdisplay[currfb][seg][1][x], byteValue );
    if(BITPLANES >=3 && color16 & B0100) bitSet( virtualdisplay[currfb][seg][2][x], byteValue );
    if(BITPLANES >=4 && color16 & B1000) bitSet( virtualdisplay[currfb][seg][3][x], byteValue );
  }
  else {
    if(color16 & B0001) bitClear( virtualdisplay[currfb][seg][0][x], byteValue );
    if(BITPLANES >=2 && color16 & B0010) bitClear( virtualdisplay[currfb][seg][1][x], byteValue );
    if(BITPLANES >=3 && color16 & B0100) bitClear( virtualdisplay[currfb][seg][2][x], byteValue );
    if(BITPLANES >=4 && color16 & B1000) bitClear( virtualdisplay[currfb][seg][3][x], byteValue );
  }
#else 
  if(color16 & B0001) bitSet( virtualdisplay[currfb][0][0][x], y );
  if(color16 & B0010) bitSet( virtualdisplay[currfb][0][1][x], y );
  if(color16 & B0100) bitSet( virtualdisplay[currfb][0][2][x], y );
  if(color16 & B1000) bitSet( virtualdisplay[currfb][0][3][x], y );
#endif

  // virtualdisplay[bitplane][x] &= ( 1<<( y%bitplane ) )
  // virtualdisplay[bitplane][x] = virtualdisplay[bitplane][x] | 1<<(y%7);

}

// experimental
void blockvirtual16( int x, byte mySize, byte color16 ) {
  if(x < 0 ) {  // règle bug affichage qq block quitte écran
    x = min( mySize, abs(x) );
    mySize = mySize - abs(x);
    if(mySize < 0) mySize=0; 
    x = 0;
  }
  if(x+mySize >= XMAX_MINUS) {
    x = XMAX_MINUS - mySize;
  }
  //if(color16 & B0001) memset( &virtualdisplay[0][0] + x, 255, mySize );
  //if(color16 & B0010) memset( &virtualdisplay[1][0] + x, 255, mySize );
  //if(color16 & B0100) memset( &virtualdisplay[2][0] + x, 255, mySize );
  //if(color16 & B1000) memset( &virtualdisplay[3][0] + x, 255, mySize );
  for(int i=0; i<BITPLANES; i++) {
    if( (color16 & 1<<i) != 0 ) memset( &virtualdisplay[currfb][0][i][0] + x, 255, mySize );
  }

}

/////////////////////////////// GFX SECTION /////////////////////////////////
void dispgfx(int width, int height, int offsetx, int offsety, prog_uchar* bitmaptodiplay ) {
  int dispy=0;

  //int ylimit = YMAX - offsety;
  //for(int j=0; j < ylimit; j++) {
  for(int j=0; j < height; j++) {
    dispy = offsety + j;
    //if( dispy > height-1 ) break;
    //if( dispy < 0)       continue;//dispy=height-1;

    for(int i=0; i < width; i++) {
      //byte color16 = (byte)pgm_read_byte ( bitmaptodiplay + i + dispy*width );
      byte color16 = (byte)pgm_read_byte ( bitmaptodiplay + i + j*width );
#ifdef MONOCHROM
      //if( intensity > 1                        ) pointvirtual16( XMAX - i + offsetx,  j, 15 );
      //pointvirtual16( XMAX - i + offsetx,  j, intensity);
      // INLINE FOR SPEED

      int x = XMAX - i + offsetx;
      if( x < XMAX && j < YMAX && x >= 0 && j >= 0 ) {
        int bitplane = .142857*j;  // 7*j
        if(color16 > 1) bitSet(   virtualdisplay[currfb][0][bitplane][x], j - 7*bitplane );
        //else              bitClear( virtualdisplay[bitplane][x], j - 7*bitplane );
      }
#elif defined FULLSCREEN_DISPLAY
      int x = XMAX - i + offsetx;
      if( x < XMAX && dispy < YMAX && x >= 0 && dispy >= 0 ) {
        //int bitplane = .142857*j;  // 7*j
        if(color16 >= 1) { 
          //bitSet(   virtualdisplay[0][bitplane][x], j - 7*bitplane );
          int seg = floor(dispy / SEGMENT_HEIGHT);  // slow...
          byte byteValue = (byte)(dispy - SEGMENT_HEIGHT*seg);
          if(color16 & B0001) bitSet( virtualdisplay[currfb][seg][0][x], byteValue );
          if(color16 & B0010) bitSet( virtualdisplay[currfb][seg][1][x], byteValue );
          if(color16 & B0100) bitSet( virtualdisplay[currfb][seg][2][x], byteValue );
          if(color16 & B1000) bitSet( virtualdisplay[currfb][seg][3][x], byteValue );
        }
        //else              bitClear( virtualdisplay[bitplane][x], j - 7*bitplane );
      }
#else
      if( color16 > 0 && color16 <= COLORS ) pointvirtual16( XMAX - i + offsetx,  j, intensity-1 );
#endif
    }

  }
}


/*
// ZOOMED SPRITE : NEED REWORK !!!!!
 // sprite display + zoom X
 void dispgfx(int width, int height, int offsetx, int offsety, float zoomfactor, prog_uchar* bitmaptodiplay ) {
 int dispy=0;
 
 for(int j=0; j < YMAX; j = j+ 1) {
 dispy = offsety + j;
 if( dispy > height -1 ) break;//dispy=height-1;
 
 for(int i=0; i < width; i = i + 1) {
 byte intensity = (byte)pgm_read_byte ( bitmaptodiplay + i + dispy*width );
 if( intensity > 0 && intensity < BITPLANES ) {
 for(int t=floor(i*zoomfactor); t < floor( (i+1)*zoomfactor ) ; t++) pointvirtual( t + offsetx,  j, intensity );
 }
 }
 
 }
 }
 
 // sprite display + zoom XY
 void dispgfx(int width, int height, int offsetx, int offsety, float zoomfactorx,  float zoomfactory, prog_uchar* bitmaptodiplay ) {
 int dispy=0;
 
 for(int j=0; j < YMAX; j = j+ 1) {
 dispy = offsety + j;
 if( dispy > height -1 ) break;//dispy=height-1;
 
 for(int s=floor(dispy*zoomfactory); s < floor( (dispy+1)*zoomfactory ) ; s++) {
 //if(offsety+8 > height) offsety = height;
 
 for(int i=0; i < width; i = i + 1) {
 byte intensity = (byte)pgm_read_byte ( bitmaptodiplay + i + dispy*width );
 if( intensity > 0 && intensity < BITPLANES ) {
 for(int t=floor(i*zoomfactorx); t < floor( (i+1)*zoomfactorx ) ; t++) pointvirtual( t + offsetx,  dispy, intensity );
 }
 }
 
 }// zoom y 
 
 }
 }
 */

// sprite simple display
void dispsprite( sprite* s, int x, int y) {
  dispgfx(s->width, s->height, x, y, s->sprite_ptr );
}

// animation simple display
void dispanimation( animation* a, int x, int y) {
  if( (millis() - a->lastplayedmillis) > a->frequencemillis) {
    //a.currentframe = (a.currentframe + 1) % a.nbframes;
    a->currentframe = (a->currentframe + 1) % a->nbframes;
    a->lastplayedmillis = millis();
    //blinkled();
  }
  dispsprite( &(a->sp[a->currentframe]), x, y);
  //dispsprite( picodon_anim[0], x, y);
  // dispsprite( picodon0, x, y);
}

///////////////////////////// FRAME BUFFERS //////////////////////////////////
void flipFrameBuffers() {
#ifdef DOUBLE_BUFFERING
  noInterrupts();
  if( currfb == 0 ) { 
    currfb = 1;
    currfb_disp = 0;
  }
  else {
    currfb = 0;
    currfb_disp = 1;
  }
  interrupts();
#endif
}

///////////////////////////// TOOLS //////////////////////////////////
boolean ledstate = false;
void blinkled() {
  ledstate = !ledstate;
  if( ledstate ) digitalWrite( 13, HIGH);
  else  digitalWrite( 13, LOW);
}

// sin table helper
int tabsin10(int a) {
#ifdef TABSIN
  a = a%255;
  return (int)sin10[a];
#else
  float a_ = a%255;
  float val = sin(a_*TWO_PI/255.)*127. + 127.;
  return int(val);
#endif
}

void intTabSin() {
#ifdef TABSIN
  // init sin10[x]   sinus pour x = 0...255 -> valeurs entre 0 et 255
  float a=0;
  for(int i=0; i< 256 ; i++) {
    a += 2*PI/255. ;
    sin10[i] = (byte)(int)(sin( a ) * 127. + 127.);
  }
#endif
}

unsigned long lastTimeFrame=0;

void displayFPS() {
  FrameInterTime = millis() - lastTimeFrame;
  currFPS = 1000/FrameInterTime;

  /* ne marchent pas 
   //dispcountern( unsigned long c, int ndigits, int x, int y, int bitplane, boolean isdouble  )
   //dispcountern( currFPS, 3, 10, BITPLANES_MINUS, 0, false  );
   dispcountern16(   currFPS, 3, MIDX, 0, 255, true  );
   
   // clock( unsigned long seconds_from_midnigth, int x, int y, boolean isdouble, int bitplane  )
   clock16( millis()/100, MIDX, 14, false, 3  );
   
   //dispcar16( int posx, int posy, int carnb, int intensity )
   //dispcar16( 10, 0, ascii2nb('A'), 255 ),
   */

  // FPS graphical VUMETER
  //rect16( int x1, int y1, int x2, int y2, byte intensity )
  //rect16( 0, 8, currFPS, 14, MAX_INTENSITY );

  //rect16( MIDX - 10, MIDY - 10, MIDX + 10, MIDY + 10, MAX_INTENSITY );

  int x = 40;
  int y = YMAX - CARHEIGHT +1;
  //rect16( x, y, x - 3*OFFSET, y + CARHEIGHT, CLEAR_COLOR );

  int mil = int(currFPS/1000);
  int cent = int((currFPS - mil*1000)/100);
  dispcarascii16(  x -   OFFSET, y, '0' + cent , MAX_INTENSITY );
  int diz = int((currFPS - cent*100)/10);
  dispcarascii16(  x - 2*OFFSET, y, '0' + diz  , MAX_INTENSITY );
  int unit = int(currFPS - cent*100 - diz*10);
  dispcarascii16(  x - 3*OFFSET, y, '0' + unit , MAX_INTENSITY );

  /*
  dispcarbig16( XMAX -   10, 7, '0' + cent ,254 );
   dispcarbig16( XMAX - 2*20, 7, '0' + diz  ,128 );
   dispcarbig16( XMAX - 3*20, 7, '0' + unit ,64 );
   */

  lastTimeFrame = millis();
}

void dispDemoInfos( int curr_demo ) {
  int x = XMAX;
  int y = YMAX - CARHEIGHT +1;
  //rect16( x - 3*OFFSET, y, x , y + CARHEIGHT, CLEAR_COLOR );

  int mil = int(curr_demo/1000);
  int cent = int((curr_demo - mil*1000)/100);
  dispcarascii16( x -   OFFSET, y , '0' + cent , MAX_INTENSITY );
  int diz = int((curr_demo - cent*100)/10);
  dispcarascii16( x - 2*OFFSET, y, '0' + diz  , MAX_INTENSITY );
  int unit = int(curr_demo - cent*100 - diz*10);
  dispcarascii16( x - 3*OFFSET, y, '0' + unit , MAX_INTENSITY );


}










































