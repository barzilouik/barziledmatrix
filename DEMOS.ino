static float rotlocal=0;
static int roll=0;  

//static boolean golly_init = false;


void renderdemo( int demonb ){
  setvirtualdisplay( 0 );
  demo( demonb );
  render();
}

void demo( int demonb ){

  switch( demonb ) {  
    ////// avec BLOC soirée /////////
  case BIG_CHARS_GLITCH: // FULLSCREEN - Gros caracteres GLITCH defilant
    {
      expandfactorX = 4;
      expandfactorY = 4;
      // recalcul
      factor = expandfactorX*(CARWIDTH+2); 
      BIGMAX = factor << 3; //*8;

      int offsety = MIDY - ( expandfactorY*CARHEIGHT ) >> 1;

      dispcarbig16( BIGMAX - bigroll - 1*factor, offsety, 'G' );
      dispcarbig16( BIGMAX - bigroll - 2*factor, offsety, 'L' );
      dispcarbig16( BIGMAX - bigroll - 3*factor, offsety, 'I' );
      dispcarbig16( BIGMAX - bigroll - 4*factor, offsety, 'T' );
      dispcarbig16( BIGMAX - bigroll - 5*factor, offsety, 'C' );
      dispcarbig16( BIGMAX - bigroll - 6*factor, offsety, 'H' );

      break;
    }
  case BIG_CHARS: // FULLSCREEN - Gros caracteres
    {
      expandfactorX = (abs)(15.0*sin( TWO_PI*mov2/XMAX) + PI) + 2;
      expandfactorY = (abs)(10.0*sin( TWO_PI*mov2/XMAX)     ) + 2; //(int)mov2%20;
      // recalcul
      factor = expandfactorX*(CARWIDTH+2); 
      BIGMAX = factor << 3; //*8;

      int offsety = MIDY - ( expandfactorY*CARHEIGHT )/2;

      dispcarbig16( BIGMAX - bigroll - 1*factor, offsety, 'B' );
      dispcarbig16( BIGMAX - bigroll - 2*factor, offsety, 'L' );
      dispcarbig16( BIGMAX - bigroll - 3*factor, offsety, 'A' );
      dispcarbig16( BIGMAX - bigroll - 4*factor, offsety, 'C' );
      dispcarbig16( BIGMAX - bigroll - 5*factor, offsety, 'K' );
      dispcarbig16( BIGMAX - bigroll - 6*factor, offsety, 'B' );
      dispcarbig16( BIGMAX - bigroll - 7*factor, offsety, 'O' );
      dispcarbig16( BIGMAX - bigroll - 8*factor, offsety, 'X' );
      dispcarbig16( BIGMAX - bigroll - 8*factor, offsety, 'E' );

      break;
    }
    ////// avec Print /////////
  case GLITCH_EFFECT: // FULLSCREEN - Game of life
    {
      /*
   if( ! golly_init) {
       golly_setup();
       golly_init = true;
       }
       */
      //
      PulseClock();

      //
      break;
    }
  case GOLLY_EFFECT: // FULLSCREEN - Game of life
    {
#ifdef GOLLY
      if( ! golly_init) {
        golly_init = true;
        golly_cell_factor = 4;
        golly_setup_screen();
      }

      golly_init = golly_loop(true, 0,0);
#endif
      break;
    }
    ///// avec DAG ///////////
  case DEMO_GAVMIX: // FULLSCREEN - GARDE A VUE 10 - MIXER
    {
      //setvirtualdisplay( 255 );

      //if( mov2< 20) PSYCHE_MODE = true;

      if(mov2 < 80) {
        //       dispsprite( &gav10,  20*sin(mov2/5 + 2) , 20*sin(mov2/3)  );
      }
      if(mov2 > 30 && mov2 < 60 ) {
#ifdef GAV2 
        dispsprite( &gav2, mov2 , mov + 20*sin(-mov2/3)  );
        dispsprite( &gav2, mov2 - 63, mov + 20*sin(-mov2/3)  );
#endif
      }
      if(mov2 > 60) {
#ifdef GAV1
        dispsprite( &gav1, mov2, mov2 + 15*sin(mov2/6)  );
        dispsprite( &gav1, mov2 - 96, mov2 + 15*sin(mov2/6)  );
#endif   
      }


      break;
    } 
  case DEMO_GAVANIM: // FULLSCREEN - GARDE A VUE - ANIME
    {
      //setvirtualdisplay( 255 );

      //PSYCHE_FACTOR = mov2;
      //PSYCHE_MODE = true;
#ifdef GAV10
      dispsprite( &gav10,  0,0);  //20*sin(mov2/5 + 2) , 20*sin(mov2/3)  );
#endif
      //dispsprite( &gav3, mov2 - 112, 0  );

      break;
    } 



  case DEMO_GAV10: // FULLSCREEN - GARDE A VUE 10 - BONHOMME
    {
      //setvirtualdisplay( 255 );

      //PSYCHE_FACTOR = mov2;
      //PSYCHE_MODE = true;
#ifdef GAV10
      dispsprite( &gav10,  0,0);  //20*sin(mov2/5 + 2) , 20*sin(mov2/3)  );
#endif
      //dispsprite( &gav3, mov2 - 112, 0  );

      break;
    } 
  case DEMO_GAV3: // FULLSCREEN - GARDE A VUE 3 - TUKIF
    {

#ifdef GAV3 
      dispsprite( &gav3, mov2 , 0  );
      dispsprite( &gav3, mov2 - 112, 0  );
#endif
      inc2 = 1;

      break;
    } 
  case DEMO_GAV2: // FULLSCREEN - GARDE A VUE 2 - RAZZLE
    {

#ifdef GAV2 
      dispsprite( &gav2, mov2 , mov + 10*sin(mov2/3)  );
      dispsprite( &gav2, mov2 - 63, mov + 10*sin(mov2/3)  );
#endif

      break;
    } 
  case DEMO_GAV1: // FULLSCREEN - GARDE A VUE 1 - DAZZLE
    {

#ifdef GAV1
      dispsprite( &gav1, 0, mov2/3 + 15*sin(mov2/2)  );
#endif
      //dispsprite( &gav1, - 96, mov2 + 15*sin(mov2/2)  );     

      break;
    } 


    ///////////////// from 0_5 /////////////////////////////
  case CAR_EXP: // FULLSCREEN - TEST CAR EXPANDED16
    {

      //dispcarexpanded16( int posx, int posy, byte carascii, int bitplane, float expandfactor )
      int scale = YMAX / 7;
      dispcarexpanded16( 10 +mov2, MIDY + scale*sin(ang + 1*PI/2), 'Y' , 0 , PIG/4 +1);
      dispcarexpanded16( 20 +mov2, MIDY + scale*sin(ang + 2*PI/2), 'D' , 0 , PIG/4 +1);
      dispcarexpanded16( 30 +mov2, MIDY + scale*sin(ang + 3*PI/2), 'A' , 0 , PIG/4 +1);
      dispcarexpanded16( 40 +mov2, MIDY + scale*sin(ang + 4*PI/2), 'D' , 0 , PIG/4 +1);

      break;
    }
  case FS_MULTI_SPRITE: // FULLSCREEN (96*63) -  FS_MULTI_SPRITE
    {      
      //if(ang > 0 && ang < 30) 

      int seglength = 60;

      incang = .9;

#ifdef UMBRELLA
      dispsprite( &umbrella, XMAX-mov2, 20*sin(mov2/5 + 8*PI/10)  );      // sin10[ (int)rotlocal ] / 10 );
#endif

      //dispsprite( &umbrella, mov2, 20*sin(mov2/5 + 2*PI/10)  );      // sin10[ (int)rotlocal ] / 10 );
      //dispsprite( &umbrella, MIDX - (mov2)/2,  20*sin(mov2/2 - 2*PI/10)  );
      //      dispsprite( &umbrella, XMAX-mov2, 20*sin(mov2/5 + 8*PI/10)  );      // sin10[ (int)rotlocal ] / 10 );

      rotlocal += .2;
      if(rotlocal > 255) rotlocal=0;
#ifdef PICODON    
      dispanimation( &picodon, mov2, 10*sin(mov2/5 + 8*PI/10)  ); //sin10[(int)rotlocal]/5 );
#endif
#ifdef CHEVAL    
      dispanimation( &cheval, mov2, 10*sin(mov2/5 + 8*PI/10)  ); //sin10[(int)rotlocal]/5 );
#endif


      break;
    }
  case ONE_SPRITE: // FULL SCREEN (96*63) - ONE_SPRITE
    {      

#ifdef UMBRELLA   
      dispsprite( &umbrella, XMAX-mov2, 10*sin(mov2/5 + 8*PI/10) );      // sin10[ (int)rotlocal ] / 10 );
#endif

      break;
    }
 
  case MULTI_PHRASE_SIN :
    { // FULLSCREEN - MULTI_PHRASE_SIN 

        resetcarseq();
      setticks( 1, 3, 5000 );

      //setticksonce( 2, 255, 10 );//settickupdown( 2, 255, 10 );

      setticks( 2, 314, 1 );
      float alpha = gettick(2)/10.;
      int fact = 10;


      int intensity = MAX_INTENSITY>>2;
      switch( gettick(1) ) {
      case 0: 
        //intensity = gettick(2);
        dispstringsin16( mov2, MIDY, str1, sizeof(str1) , intensity, alpha, fact); 
        //fadein( 5000 );
        break;
      case 1: 
        //intensity = gettick(2);
        dispstringsin16( mov2, MIDY, str2, sizeof(str2) , intensity, alpha, fact); 
        //fadeout( 5000 );
        break;
      case 2: 
        //intensity = gettick(2);
        dispstringsin16( mov2, MIDY, str3, sizeof(str3) , intensity, alpha, fact); 
        break;
      }

      break;
    }
  case MULTI_PHRASE :
    { // SIMPLE - MULTI_PHRASE 

        resetcarseq();
      setticks( 1, 3, 5000 );
      setticksonce( 2, 255, 10 );//settickupdown( 2, 255, 10 );

      int intensity = MAX_INTENSITY;
      switch( gettick(1) ) {
      case 0: 
        //intensity = gettick(2);
        dispstring16( 0, 0, str1, sizeof( str1 ) , intensity ); 
        //fadein( 5000 );
        break;
      case 1: 
        //intensity = gettick(2);
        dispstring16( 0, 0, str2, sizeof( str2 ) , intensity ); 
        //fadeout( 5000 );
        break;
      case 2: 
        //intensity = gettick(2);
        dispstring16( 0, 0, str3, sizeof( str2 ) , intensity ); 
        break;
      }

      break;
    }
  case 130: // DUAL SCREEN - BLOCK_EXPANSION
    {


      roll = roll + 5;
      if( roll > 255) roll = 0;

      int x1 = 0;
      int x2 = tabsin10(roll )/3;
      int y1 = 0;
      int y2 = tabsin10(roll )/5;

      rect16( x1, y1, x2, y2, MAX_INTENSITY  );
      rect16( XMAX - x1 - 1, YMAX - y1 -1, XMAX - x2 -1, YMAX - y2 -1, MAX_INTENSITY  );


      break;
    }
  case 120: // DUAL SCREEN - D_BLOCK_BRIGHTNESS_2
    {


      static int cell = 5;
      static int celly = 5;

      roll = roll + 1;
      if( roll > 255) roll = 0;
      rotlocal += .1;
      if(rotlocal >= 2*cell) rotlocal = 0;
      for(int i=(int)rotlocal; i < XMAX; i=i+ 2*cell) {
        for(int j=0; j < YMAX; j=j+2*celly) {
          rect16( i, j, i+cell - 1, j+celly-1, tabsin10(byte(roll + i)&255)  );
        }
      }  
      for(int i=(int)rotlocal+cell; i < XMAX; i=i+ 2*cell) {
        for(int j=celly; j < YMAX; j=j+2*celly) {
          rect16( i, j, i+cell - 1, j+celly-1, tabsin10(byte(128-roll + i)&MAX_INTENSITY)  );
        }
      }

      break;
    }
  case 110: // DUAL SCREEN - SIN_HACKART
    {  

      resetcarseq() ; 

      int stringoffset = 80;
      int a = (int)(ang*5);
      int intensity = MAX_INTENSITY;
      int offsety = - MIDY;
      int k = EXPANDED;
      dispcarseq16( XMAX - stringoffset, (tabsin10(a + 5)>>6 + offsety ), 'T'  + k,intensity); 
      dispcarseq16( XMAX - stringoffset, (tabsin10(a + 10)>>6 + offsety ), 'R' + k,intensity);  
      dispcarseq16( XMAX - stringoffset, (tabsin10(a + 15)>>6 + offsety ), 'A' + k,intensity);  
      dispcarseq16( XMAX - stringoffset, (tabsin10(a + 20)>>6 + offsety ), ' ' + k,intensity);  
      dispcarseq16( XMAX - stringoffset, (tabsin10(a + 25)>>6 + offsety ), 'K' + k,intensity); 
      dispcarseq16( XMAX - stringoffset, (tabsin10(a + 30)>>6 + offsety ), 'C' + k,intensity);
      dispcarseq16( XMAX - stringoffset, (tabsin10(a + 35)>>6 + offsety ), 'A' + k,intensity);
      dispcarseq16( XMAX - stringoffset, (tabsin10(a + 40)>>6 + offsety ), 'H' + k,intensity);

      break;
    }
  case 111: // SIMPLE SCREEN - SIN_BB
    {      

      resetcarseq();
      /*
      if(inc2 > 0) {
       dispcarseq( mov2, 5*sin(mov2/10 + 2*PI/10), 'N',0);
       dispcarseq( mov2, 5*sin(mov2/10 + 3*PI/10), 'O',0);
       }
       else {
       dispcarseq( mov2, 5*sin(mov2/10 + 2*PI/10), 'F',0);
       dispcarseq( mov2, 5*sin(mov2/10 + 2*PI/10), 'F',0);
       dispcarseq( mov2, 5*sin(mov2/10 + 3*PI/10), 'O',0);
       }
       dispcarseq( mov2, 5*sin(mov2/10 + 4*PI/10), ' ',0);  
       dispcarseq( mov2, 5*sin(mov2/10 + 5*PI/10), 'K',0); 
       dispcarseq( mov2, 5*sin(mov2/10 + 6*PI/10), 'C',0);
       dispcarseq( mov2, 5*sin(mov2/10 + 7*PI/10), 'U',0);
       dispcarseq( mov2, 5*sin(mov2/10 + 8*PI/10), 'F',0); 
       */
      /*
      int trim = MIDY;
       int fact = 5;
       float alpha = ang;//mov2 / 100;
       setticks(1, XMAX, 50);
       int x = gettick(1) - 20;
       //int a = (int)(ang*100);
       
       if(inc2 > 0) {
       dispcarseq16( mov2, fact*sin(mov2/d + 2*PI/10) + trim, 'N',255);
       dispcarseq16( mov2, fact*sin(mov2/d + 3*PI/10) + trim, '',255);
       }
       else {
       dispcarseq16( mov2, fact*sin(mov2/d + 2*PI/10) + trim, 'F',255);
       dispcarseq16( mov2, fact*sin(mov2/d + 2*PI/10) + trim, 'F',255);
       dispcarseq16( mov2, fact*sin(mov2/d + 3*PI/10) + trim, 'O',255);
       }
       */
      /*
      dispcarseq16( x, fact*sin(alpha + 5*PI/10) + trim, 'E' + EXPANDED,255);
       dispcarseq16( x, fact*sin(alpha + 5*PI/10) + trim, 'X' + EXPANDED,255);
       dispcarseq16( x, fact*sin(alpha + 5*PI/10) + trim, 'O' + EXPANDED,255);
       dispcarseq16( x, fact*sin(alpha + 5*PI/10) + trim, 'B' + EXPANDED,255);  
       dispcarseq16( x, fact*sin(alpha + 5*PI/10) + trim, 'K' + EXPANDED,255); 
       dispcarseq16( x, fact*sin(alpha + 5*PI/10) + trim, 'C' + EXPANDED,255); 
       dispcarseq16( x, fact*sin(alpha + 5*PI/10) + trim, 'A' + EXPANDED,255);
       dispcarseq16( x, fact*sin(alpha + 5*PI/10) + trim, 'L' + EXPANDED,255);
       dispcarseq16( x, fact*sin(alpha + 5*PI/10) + trim, 'B' + EXPANDED,255);
       */
      int x = mov2 - 30;//gettick(1) - 20;
      int a = (int)(ang*30);
      int offsety = 0;
      int t = 5;
      dispcarseq16( x, (tabsin10(a + 5 )>>t + offsety ), 'E' + EXPANDED,MAX_INTENSITY);
      dispcarseq16( x, (tabsin10(a + 10)>>t + offsety ), 'X' + EXPANDED,MAX_INTENSITY);
      dispcarseq16( x, (tabsin10(a + 15)>>t + offsety ), 'O' + EXPANDED,MAX_INTENSITY);
      dispcarseq16( x, (tabsin10(a + 20)>>t + offsety ), 'B' + EXPANDED,MAX_INTENSITY);  
      dispcarseq16( x, (tabsin10(a + 25)>>t + offsety ), 'K' + EXPANDED,MAX_INTENSITY); 
      dispcarseq16( x, (tabsin10(a + 30)>>t + offsety ), 'C' + EXPANDED,MAX_INTENSITY); 
      dispcarseq16( x, (tabsin10(a + 35)>>t + offsety ), 'A' + EXPANDED,MAX_INTENSITY);
      dispcarseq16( x, (tabsin10(a + 40)>>t + offsety ), 'L' + EXPANDED,MAX_INTENSITY);
      dispcarseq16( x, (tabsin10(a + 45)>>t + offsety ), 'B' + EXPANDED,MAX_INTENSITY);
      /*
       dispcarseqhomotetic( mov2, 0, 'a' + floor(mov2), -inc2 ); 
       dispcarseqhomotetic( mov2, 0, 'a' + int(floor(mov2) + 1)%3, -inc2 ); 
       dispcarseqhomotetic( mov2, 0, 'a' + int(floor(mov2) + 2)%3, -inc2 );   
       */

      dispcarseq16( x, 1, ' ',MAX_INTENSITY);
      dispcarseq16( x, (tabsin10(a + 100)>>t + offsety ), 'a' + ((int)mov2%3)    , MAX_INTENSITY );
      dispcarseq16( x, (tabsin10(a + 110)>>t + offsety ), 'a' + ((int)mov2 + 1)%3, MAX_INTENSITY ); 
      dispcarseq16( x, (tabsin10(a + 120)>>t + offsety ), 'a' + ((int)mov2 + 2)%3, MAX_INTENSITY );



      break;
    }
  case 100: // DUAL SCREEN - QUAD_LINE_ROTATE
    {

      setticks(1, 314, 100);
      setticks(2, 400, 200);
      if( gettick( 2 ) == 0 ) setvirtualdisplay( 0 );      
      int seglength = 60;
      float ang = gettick(1) / 10.;

      int x2 = sin(  ang )*seglength;
      int y2 = cos(  ang )*seglength;

      line(  MIDX,  MIDY,  x2 + MIDX,  y2 + MIDY, MAX_INTENSITY );  

      x2 = sin(  ang + PI/2 )*seglength;
      y2 = cos(  ang + PI/2 )*seglength;

      line(  MIDX,  MIDY,  x2 + MIDX,  y2 + MIDY, 128 ); 

      x2 = sin(  ang + PI )*seglength;
      y2 = cos(  ang + PI )*seglength;

      line(  MIDX,  MIDY,  x2 + MIDX,  y2 + MIDY, MAX_INTENSITY );  

      x2 = sin(  ang + 3*PI/2 )*seglength;
      y2 = cos(  ang + 3*PI/2 )*seglength;

      line(  MIDX,  MIDY,  x2 + MIDX,  y2 + MIDY, 128 );  


      break;
    }
  case 1: // ANY - LINES
    {

      int seglength = 20;
      setticks(1, 314, 100);
      //float angrad = 6*ang / MAX_INTENSITY;
      float angrad = gettick(1) / 100;

      int x2 = sin(  ang )*seglength;
      int y2 = cos(  ang )*seglength;

      for(int i=0; i<10; i++) {
        line(  i*10,  4,  x2 + i*10,  y2 + 4, MAX_INTENSITY );  
      }

      for(int i=0; i<10; i++) {
        x2 = sin( 2*PI- ang + i )*seglength;
        y2 = cos( 2*PI- ang +i )*seglength;

        line(  i*10,  4,  x2 + i*10,  y2 + 4, MAX_INTENSITY );  
      }

      break;
    }
  case 2: 
    { // ANY - ROT_TRIANGLES
      setticks( 1, 314, 20 );


      //float rot = gettick(1)/100;
      rotlocal = rotlocal + .02;
      int seg = 2 *(int(rotlocal + 1)%3);
      int halfseg = seg / 2;

      int x0 = rotx( 0, seg, rotlocal);
      int y0 = roty( 0, seg, rotlocal);

      int x1 = rotx( halfseg, -halfseg, rotlocal);
      int y1 = roty( halfseg, -halfseg, rotlocal);

      int x2 = rotx( -halfseg, -halfseg, rotlocal);
      int y2 = roty( -halfseg, -halfseg, rotlocal);

      line(  x0 + MIDX,  y0 + MIDY,  x1 + MIDX,  y1 + MIDY, cos(rotlocal)*MAX_INTENSITY );  
      line(  x1 + MIDX,  y1 + MIDY,  x2 + MIDX,  y2 + MIDY, cos(rotlocal+PI/2)*MAX_INTENSITY ); 
      line(  x2 + MIDX,  y2 + MIDY,  x0 + MIDX,  y0 + MIDY, cos(rotlocal+PI)*MAX_INTENSITY ); 

      x0 = rotx( -halfseg, halfseg, -rotlocal);
      y0 = roty( -halfseg, halfseg, -rotlocal);

      x1 = rotx( halfseg, halfseg, -rotlocal);
      y1 = roty( halfseg, halfseg, -rotlocal);

      x2 = rotx( halfseg, -halfseg, -rotlocal);
      y2 = roty( halfseg, -halfseg, -rotlocal);

      int x3 = rotx( -halfseg, -halfseg, -rotlocal);
      int y3 = roty( -halfseg, -halfseg, -rotlocal);

      line(  x0 + 30,  y0 + MIDY,  x1 + 30,  y1 + MIDY, sin(3*rotlocal)*MAX_INTENSITY );  
      line(  x1 + 30,  y1 + MIDY,  x2 + 30,  y2 + MIDY, cos(2*rotlocal+PI/4)*MAX_INTENSITY  ); 
      line(  x2 + 30,  y2 + MIDY,  x3 + 30,  y3 + MIDY, sin(5*rotlocal+PI/3)*MAX_INTENSITY  ); 
      line(  x3 + 30,  y3 + MIDY,  x0 + 30,  y0 + MIDY, cos(10*rotlocal+PI/2)*MAX_INTENSITY  ); 

      if(DEBUG) Serial.println( gettick(1) );

      // display rotlocal
      //dispcarascii( XMAX - OFFSET, 1, ( '0' + int(rotlocal/10) %9) ,3 );
      //dispcarascii( XMAX - 2*OFFSET, 1, ('0' + (int)rotlocal % 9)  ,3 );

      break;
    }
  case WIREFRAME_SHOW: 
    { // 3D ELITE SHIPS
#if defined(WIREFRAME) 
      wireframeloop();
#endif
      break;
    }
  case WIREFRAME_SINGLE: 
    { // ANY - WIREFRAME_SINGLE
#if defined(WIREFRAME) 
      setticks( 1, 314, 15 );
      int a = sin(rotlocal);
      drawship(8, 150 + a*a*120, gettick(1)/10. );   
      rotlocal = rotlocal + .08; 
#endif
      break;
    }
  case 5: 
    { // ANY - CIRCLES 
      //circle(int x0, int y0, int radius, int intensity)

      // circle( MIDX, 3, 20, MAX_INTENSITY);
      rotlocal = rotlocal + .1;
      if(rotlocal > 2) rotlocal=0;

      for( int i=1; i < 2*MIDX; i++ ) 
        circle( MIDX + (rotlocal)*20 -10, MIDY, i/5 - rotlocal*10, MAX_INTENSITY );//(int)(i*2 + 100)%255 );

      break;
    }
  case 6:
    { // SIMPLE - ROCKET (fusee)
      rotlocal = rotlocal + .1;

      dispcarascii( 75 + mov2, 0, 'e' + (int)rotlocal%5 ,0);
      dispcarexpanded( 70 + mov2, 0, 'E' ,3 , 2 );
      delay(20);

      break;
    }
  case 7:
    { // SIMPLE - WARNING_REBOOT ("REBOOT <<<")

      resetcarseq() ; 
      setticks( 2, 5, 100 );

      rotlocal += .8;
      if(rotlocal > 255) rotlocal=0;

      int stringoffset = 80;// + sin10[(int)rotlocal]/25;            
      int posy =  0;//8 - sin10[(int)rotlocal + 1]/5;      
      int intensity = tabsin10((int)rotlocal);

      dispcarseq16( XMAX - stringoffset , posy, ('d' +gettick(2)       )  , MAX_INTENSITY);
      dispcarseq16( XMAX - stringoffset , posy, ('d' +(gettick(2)+1)%5 )  , MAX_INTENSITY);
      dispcarseq16( XMAX - stringoffset , posy, ('d' +(gettick(2)+2)%5 )  , MAX_INTENSITY);

      dispcarseq16( XMAX - stringoffset, posy, ':' + EXPANDED,128 );  
      dispcarseq16( XMAX - stringoffset, posy, ' ' + EXPANDED,intensity );  
      dispcarseq16( XMAX - stringoffset, posy, 'T' + EXPANDED,intensity );  
      dispcarseq16( XMAX - stringoffset, posy, 'C' + EXPANDED,intensity ); 
      dispcarseq16( XMAX - stringoffset, posy, 'E' + EXPANDED,intensity );
      dispcarseq16( XMAX - stringoffset, posy, 'J' + EXPANDED,intensity );
      dispcarseq16( XMAX - stringoffset, posy, 'E' + EXPANDED,intensity );

      setcarseq(4) ; 

      dispcarseq16( XMAX - stringoffset, posy, 'G' + EXPANDED,MAX_INTENSITY - intensity ); 
      dispcarseq16( XMAX - stringoffset, posy, 'N' + EXPANDED,MAX_INTENSITY - intensity );  
      dispcarseq16( XMAX - stringoffset, posy, 'I' + EXPANDED,MAX_INTENSITY - intensity );  
      dispcarseq16( XMAX - stringoffset, posy, 'N' + EXPANDED,MAX_INTENSITY - intensity ); 
      dispcarseq16( XMAX - stringoffset, posy, 'R' + EXPANDED,MAX_INTENSITY - intensity );
      dispcarseq16( XMAX - stringoffset, posy, 'A' + EXPANDED,MAX_INTENSITY - intensity );
      dispcarseq16( XMAX - stringoffset, posy, 'W' + EXPANDED,MAX_INTENSITY - intensity );


      break;
    }
  case 8:
    {  // ANY - SIN_BARBINDUR

      resetcarseq() ; 

      int stringoffset = 80;
      int a = (int)ang;
      int intensity = a;
      dispcarseq16( XMAX - stringoffset, tabsin10(a     )>>4 - 10, 'R' + EXPANDED,intensity);  
      dispcarseq16( XMAX - stringoffset, tabsin10(a + 16)>>4 - 10, 'U' + EXPANDED,intensity); 
      dispcarseq16( XMAX - stringoffset, tabsin10(a + 32)>>4 - 10, 'D' + EXPANDED,intensity);  
      dispcarseq16( XMAX - stringoffset, tabsin10(a + 64)>>4 - 10, 'N' + EXPANDED,intensity);  
      dispcarseq16( XMAX - stringoffset, tabsin10(a + 128)>>4 - 10, 'I' + EXPANDED,intensity);  
      dispcarseq16( XMAX - stringoffset, tabsin10(a + 64)>>4 - 10, 'B' + EXPANDED,intensity); 
      dispcarseq16( XMAX - stringoffset, tabsin10(a + 32)>>4 - 10, 'R' + EXPANDED,intensity);
      dispcarseq16( XMAX - stringoffset, tabsin10(a + 16)>>4 - 10, 'A' + EXPANDED,intensity);
      dispcarseq16( XMAX - stringoffset, tabsin10(a     )>>4 - 10, 'B' + EXPANDED,intensity);

      break;
    }
  case 9:
    { // ANY - COUNTER

      //dispcountern( unsigned long c, int x, int y, int ndigits, int bitplane, boolean isdouble  )
      resetcarseq() ; // !ATTENTION
      setticks( 1, 100000, 10 );
      dispcountern( gettick(1), 6,  MIDX , 0, 3, false );

      break;
    }
  case 10:
    { // ANY - CLOCK

      resetcarseq() ; 
      clock( 2*3600 + 57*60 + millis() / 1000, 6, MIDX, false, 0);

      break;
    }
  case 12:
    { // ANY - BLOCK_BRIGHTNESS

      int cell = 5 ;
      int celly = 5 ;

      roll = roll + .1;
      if( roll > 255) roll = 0;

      rotlocal += .1;
      if(rotlocal >= 2*cell) rotlocal = 0;

      for(int i=(int)rotlocal; i < XMAX; i=i+ 2*cell) {
        for(int j=0; j < YMAX; j=j+2*celly) {
          rect16( i, j+PIG, i+cell - 1, j+celly-1, tabsin10( roll + i)  );
        }
      }  
      for(int i=(int)rotlocal+cell; i < XMAX; i=i+ 2*cell) {
        for(int j=celly; j < YMAX; j=j+2*celly) {
          rect16( i, j, i+cell - 1, j+celly-1, tabsin10( 128-roll + i)  );
        }
      }

      break;
    }
  case 14:
    { // ANY - ANIMATION  

      rotlocal += .2;
      if(rotlocal > 255) rotlocal=0;
#ifdef PICODON 
      dispanimation( &picodon, MIDX, tabsin10( (int)rotlocal)/10);
#endif
#ifdef CHEVAL 
      dispanimation( &cheval, MIDX, tabsin10( (int)rotlocal)/10);
#endif

      break;
    } 
  case 15:
    { // ANY - SIN_UMBRELLA

      setticks(1, 255, 20);
      rotlocal = gettick(1);

      //rotlocal += .2;
      //if(rotlocal > 255) rotlocal=0;
#ifdef UMBRELLA 
      dispsprite( &umbrella , MIDX, tabsin10( rotlocal)/12);
      dispsprite( &umbrella, XMAX-(mov2), MIDY + 10*sin(mov2/10 + 2*PI/5) );
#endif 
      delay(10);

      break;
    } 
  case 16:
    { // ANY - REBOOT_PHRASE  "reboot" + phrases


      resetcarseq();

      setticks( 1, 4, 5000 );
      setticksonce( 2, 255, 10 );
      //settickupdown( 2, 255, 10 );

      int intensity = 0;

      switch( gettick(1) ) {
      case 0: 
        resettick(2, 0);
        intensity = gettick(2);
        dispstring16( 0, 0, str1, sizeof( str1 ) , intensity ); 
        break;
      case 1: 
        resettick(2, 1);
        intensity = gettick(2);
        dispstring16( 0, 0, str2, sizeof( str2 ) , intensity ); 
        break;
      case 2: 
        resettick(2, 2);
        intensity = gettick(2);
        dispstring16( 0, 0, str3, sizeof( str3 ) , intensity ); 
        break;  
      case 3:
        setticks( 2, 5, 100 );
        int stringoffset = 80;// + sin10[(int)rotlocal]/25;            
        int posy =  0;//8 - sin10[(int)rotlocal + 1]/5;      
        intensity = tabsin10((int)rotlocal);
        rotlocal += .8;
        if(rotlocal > 255) rotlocal=0;

        dispcarseq16( XMAX - stringoffset , posy, ('d' +gettick(3)       )  ,128);
        dispcarseq16( XMAX - stringoffset , posy, ('d' +(gettick(3)+1)%5 )  ,128);
        dispcarseq16( XMAX - stringoffset , posy, ('d' +(gettick(3)+2)%5 )  ,128);

        dispcarseq16( XMAX - stringoffset, posy, ':' + EXPANDED,128 );  
        dispcarseq16( XMAX - stringoffset, posy, 'T' + EXPANDED,intensity );  
        dispcarseq16( XMAX - stringoffset, posy, 'O' + EXPANDED,intensity );  
        dispcarseq16( XMAX - stringoffset, posy, 'O' + EXPANDED,intensity ); 
        dispcarseq16( XMAX - stringoffset, posy, 'B' + EXPANDED,intensity );
        dispcarseq16( XMAX - stringoffset, posy, 'E' + EXPANDED,intensity );
        dispcarseq16( XMAX - stringoffset, posy, 'R' + EXPANDED,intensity );
        break;
      }


      break;
    }
  case 17:
    { // SIMPLE - COUNTER_REBOOT

      //void dispcountern( unsigned long c, int ndigits, int x, int y, int bitplane, boolean isdouble  )
      resetcarseq() ; // !ATTENTION
      setticks( 1, -1, 1000 );
      //dispcountern( 45*3600*24 - gettick(1), 10,  MIDX , 0, 3, false );
      dispcountern( gettick(1) , 7, 50 , 0, 3, false );

      setticks( 1, 5, 100 );
      int stringoffset = 80;// + sin10[(int)rotlocal]/25;            
      int posy =  0;//8 - sin10[(int)rotlocal + 1]/5;      
      int intensity = tabsin10((int)rotlocal);
      rotlocal += .8;
      if(rotlocal > 255) rotlocal=0;

      resetcarseq() ; // !ATTENTION
      dispcarseq16( XMAX - stringoffset , posy, ('d' +gettick(3)       )  ,128);
      dispcarseq16( XMAX - stringoffset , posy, ('d' +(gettick(3)+1)%5 )  ,128);
      dispcarseq16( XMAX - stringoffset , posy, ('d' +(gettick(3)+2)%5 )  ,128);

      dispcarseq16( XMAX - stringoffset, posy, ':' + EXPANDED,128 );  
      dispcarseq16( XMAX - stringoffset, posy, 'T' + EXPANDED,intensity );  
      dispcarseq16( XMAX - stringoffset, posy, 'O' + EXPANDED,intensity );  
      dispcarseq16( XMAX - stringoffset, posy, 'O' + EXPANDED,intensity ); 
      dispcarseq16( XMAX - stringoffset, posy, 'B' + EXPANDED,intensity );
      dispcarseq16( XMAX - stringoffset, posy, 'E' + EXPANDED,intensity );
      dispcarseq16( XMAX - stringoffset, posy, 'R' + EXPANDED,intensity );


      break;
    }
  case 18:
    { // ANY - BALLS_SPRITE 
#ifdef BALLS
      setticks( 1, 10000, 1000 );
      setticks( 2, 2, 50 );
      if( gettick( 1 ) == 0 ) {
        initballs();
      }
      else {
        if( pulsetick( 2 )  ) {
          updateballs();
        }
        displayBalls();
      }
      break;
#endif
    }

    /*
Bombastic Edison
     An abstract gait
     Surrounded by coils of binary and luminescence.
     Suave, purple suits clasping to morphed skin.
     Electrical vibes, transistors atomically sized.
     Brain dives, the concept of thought diluted.
     
     She can only wish it was palpable. 
     
     In a mirror mirage,
     Static fumbles,
     Repos the limelight. 
     
     Cyberpunk gen, neo-noir,
     A relevant memento. 
     Deciphering the metaphysical is
     Unattainable. 
     Screw it all,
     Maneuver the landscape.
     Might as well enjoy the sights
     In the nick of a quivering snap.
     */

  }

}













































