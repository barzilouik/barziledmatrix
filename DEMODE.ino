
/////////////////////////// LOOP DEMO MODEs ////////////////////////////////////
//#if defined  (DEMO_MODE)





#if defined  (DEMO_MULTI_SEGMENT_DISPLAY_FULLSCREEN_DEMO_BUNKER)

//int curr_demo = 0;

void loop()
{
  manageticks();
  manageVariables();

  flipFrameBuffers();
  setvirtualdisplay( 0 );


  //curr_demo = SIN_BB;
  //curr_demo BIG_CHARS_GLITCH;
  //curr_demo CAR_EXP;
  //curr_demo = WIREFRAME_SINGLE ; 
  //curr_demo = FS_MULTI_SPRITE;
  //curr_demo = ONE_SPRITE;
  //curr_demo = WARNING_REBOOT;
  //curr_demo = CIRCLES;

  //demo( curr_demo ); // draw in current FB


  //demo( WIREFRAME_SINGLE ); 
  //demo( FS_MULTI_SPRITE ); 

  //demo( BALLS_SPRITE );
  //demo( MULTI_PHRASE_SIN );

  //displayFPS();
  //dispDemoInfos( curr_demo );

  /*
  setticks( 2, 314, 1 );
   float alpha = gettick(2)/10.;
   int fact = 10;
   int MAXCHARDISPLAY = 16;
   
   //setticks( 3 + ring_cpt , abs( BUFFMAXCHAR - MAXCHARDISPLAY) * 6, 20 + random(20) );
   setticks( 3  , abs( BUFFMAXCHAR - MAXCHARDISPLAY) * 6, 120 + random(20) );
   
   //dispstringsin16( 0, ring_cpt * 7, txtMsg[ring_cpt], sizeof( txtMsg[ring_cpt] ) , 255, 0, 0);
   //void dispstring16( int posx, int posy, String s, int taille, int intensity ) {
   //dispstring16( 0, ring_cpt * 7, txtMsg[ring_cpt], sizeof( txtMsg[ring_cpt] ) , 255 );
   //if( stringComplete ) dispstring16( 0, MIDY, inputString, sizeof( inputString ) , MAX_INTENSITY );
   //dispstring16( XMAX - sizeof( inputString )*5, 7 , inputString, sizeof( inputString ) , MAX_INTENSITY );
   */

  if( curr_demo >= 0 ) {
    demo( curr_demo );
  }
  for(int i=0; i < SEGMENTS; i++) {
    resetcarseq();
    //dispstring16(mov2 , i*7 , txtMsg[i], txtMsg[i].length() , MAX_INTENSITY );
    // dispstring16(   gettick( 3  ) - abs( BUFFMAXCHAR - MAXCHARDISPLAY) * 6 - XMAX/2 , 2*i*7 , txtMsg[i], 20 , MAX_INTENSITY );  // 1 ligne sur 2
    dispstring16( gettick( 3  ) + ( 3 - abs( BUFFMAXCHAR - MAXCHARDISPLAY) )*6  , i*7 , txtMsg[i], BUFFMAXCHAR - 3 , MAX_INTENSITY );  // 1 ligne sur 2
  }


  // compensate for constant FrameRate
  int FrameIntertimeMax = 10;
  if( FrameInterTime < FrameIntertimeMax )  delay( FrameIntertimeMax - FrameInterTime);

}
#endif


#if defined  (DEMO_MODE_MULTI_SEGMENT_DISPLAY_FULLSCREEN_1)
void loop()
{
  manageticks();
  manageVariables();

  flipFrameBuffers();
  setvirtualdisplay( 0 );

  int curr_demo;
  //curr_demo = SIN_BB;
  //curr_demo BIG_CHARS_GLITCH;
  //curr_demo CAR_EXP;
  //curr_demo = WIREFRAME_SINGLE ; 
  //curr_demo = FS_MULTI_SPRITE;
  //curr_demo = ONE_SPRITE;
  curr_demo = WARNING_REBOOT;
  //curr_demo = CIRCLES;

  demo( curr_demo ); // draw in current FB
  demo( WIREFRAME_SINGLE ); 
  //demo( FS_MULTI_SPRITE ); 

  //demo( BALLS_SPRITE );

  displayFPS();
  dispDemoInfos( curr_demo );

  // compensate for constant FrameRate
  int FrameIntertimeMax = 10;
  if( FrameInterTime < FrameIntertimeMax )  delay( FrameIntertimeMax - FrameInterTime);

  //delay( 5 ); 
  //}
  /*
 if( VBLANK ) {
   currfb=1;
   currfb_disp=0; 
   }
   */
  //displayDirty = false;

  /*
    frames++;
   if (frames>3){
   frames=0;
   setvirtualdisplay( 0 ); 
   }
   */


  //displayFPS();
  //demo( WIREFRAME_SHOW );  
  // demo ( BALLS_SPRITE  );
  //demo( WARNING_REBOOT );
  //demo( SIN_UMBRELLA );
  //demo( ANIMATION );
  //  demo( ROT_TRIANGLES );

  /*
  if( !golly_init ) {
   golly_setup_random();
   golly_init = true;
   }
   demo( GOLLY_EFFECT );
   */

  //render();
  //delay( random( 10 ) );
}
#endif

// MEGADEMO BIG CARRE VERT !!! -->> pour trait d'union
#if defined  (DEMO_MODE_MULTI_SEGMENT_DISPLAY_FULLSCREEN)

#define MAX_DEMO  6
//int demoloop[ MAX_DEMO ] = {
int demoloop[ ] = {
  //  GAV1, BALLS_SPRITE, ONE_SPRITE, FS_MULTI_SPRITE, WIREFRAME, CIRCLES, BLOCK_BRIGHTNESS, QUAD_LINE_ROTATE, SIN_HACKART, SIN_BB };
  //MULTI_PHRASE_SIN};
  //DEMO_GAV1, DEMO_GAV2, DEMO_GAV3};
  //DEMO_GAV1, DEMO_GAV2, DEMO_GAV10};
  COUNTER_REBOOT, DEMO_GAV1, DEMO_GAV2, QUAD_LINE_ROTATE, BLOCK_BRIGHTNESS, SIN_HACKART};
//DEMO_GAV1, DEMO_GAV2,BLOCK_BRIGHTNESS,SIN_HACKART};
//DEMO_GAV1};
//WIREFRAME_SHOW};
//SIN_FUCK };
//FS_MULTI_SPRITE};


//sizeof( demoloop );


void loop()
{

  //  int curr_demo = 1;
  setticks( 0 , MAX_DEMO   , 5000 );
  manageticks();
  manageVariables();
  int curr_demo = demoloop[ gettick(0) ];
  //if( curr_demo == BLOCK_BRIGHTNESS || curr_demo == QUAD_LINE_ROTATE || curr_demo == GAV2) PSYCHE_MODE = true; 
  //else PSYCHE_MODE = false;

  //if(gettick(3)==0)PSYCHE_MODE = true;
  //else PSYCHE_MODE = false;

  flipFrameBuffers();
  setvirtualdisplay( 0 );
  demo( curr_demo );
  //render();

  displayFPS();

}

#endif

/*
int demoloop[] = {
 SIN_UMBRELLA,WARNING_REBOOT,BLOCK_BRIGHTNESS,LINES,QUAD_LINE_ROTATE, SIN_HACKART, BLOCK_BRIGHTNESS_2, BLOCK_EXPANSION, SIN_BB };
 //SIN_HACKART, SIN_BB };
 
 int MAX_DEMO  = sizeof( demoloop );
 int last_demo = demoloop[ 0 ];
 
 void loop()
 {
 
 setticks( 0 , MAX_DEMO , 5000 );
 manageticks();
 manageVariables();
 if( last_demo != gettick(0) )  { resettick(1,0); }
 demo( demoloop[ gettick(0) ] );
 last_demo = gettick(0);
 }
 */

#if defined  (DEMO_MODE_MULTI_SEGMENT_DISPLAY_FULLSCREEN_TRAIT_UNION)

// RANDOM TEST
//#define MAX_DEMO  8
int demoloop[  ] = {
  //  SIN_UMBRELLA,BLOCK_BRIGHTNESS,LINES,QUAD_LINE_ROTATE, SIN_HACKART, BLOCK_BRIGHTNESS_2, BLOCK_EXPANSION, SIN_BB };
  SIN_HACKART, BLOCK_BRIGHTNESS_2, SIN_BB, COUNTER_REBOOT,
  GOLLY_EFFECT, 
  //GLITCH_EFFECT,
  BIG_CHARS,
  WIREFRAME_SINGLE,
  DEMO_GAV1, DEMO_GAV2, DEMO_GAV3, DEMO_GAV10
};

static int MAX_DEMO  = 0;
//int curr_demo = 0;
int curr_time = 10000;
boolean choice_done = false;

void loop()
{
  MAX_DEMO  = sizeof( demoloop );
  setticks( 0 , 5 , curr_time );
  manageticks();
  manageVariables();
  flipFrameBuffers();

  if( 0 == gettick(0) && !choice_done )  { // next presets first time -> DEMOs SETUP
    choice_done = true;
    // choice
    curr_demo = demoloop[ random( MAX_DEMO + 1) ];  
    curr_time = random( 3000 ) + 500;

    // setup demo...if any
    PSYCHE_MODE = (random( 15 ) > 10 );
    PSYCHE_FACTOR = (random( 24 ) +1 );
    //golly_init = false;

    golly_cell_factor = random(10) + 4;
    golly_setup_random();  // golly_set_up_screen();
  }
  else {
    choice_done = false;
  }

  ///// EFFECTS
  // - PSYCHE
  if( random(30) > 27) {
    PSYCHE_MODE = (random( 15 ) > 11 );
    PSYCHE_FACTOR = (random( 12 ) +1 );
  }
  // - GOLLY
  if( random(30) ==  10) {
    golly_loop();
  }    
  // - GLITCH
  if( random(200) == 50) {
    int ran=random(3);
    for(int i=0; i<ran; i++) {
      PulseClock();
    }
    //render();
    delay(5);
  }  
  // - CLEAR SCREEN  
  if( random(100) > 50 ) setvirtualdisplay( 0 );

  // setups
  if( !golly_init ) {
     
      golly_setup_random();
    golly_init = true;
  }
  //demo( GOLLY_EFFECT );

  demo( curr_demo );
  displayFPS();
  dispDemoInfos( curr_demo );
  //render();

}
#endif




// MEGADEMO ROUGE !!!
//#if defined  (VERTICAL_DISPLAY_DUAL)
#if defined  (DEMO_MODE_VERTICAL_DISPLAY_DUAL)
int demoloop[] = {
  // 15,7,BLOCK_BRIGHTNESS,LINES,QUAD_LINE_ROTATE, SIN_HACKART, 120, 130, SIN_BB };
  SIN_HACKART, SIN_BB };

static int MAX_DEMO  = 0; //sizeof( demoloop );
int last_demo = demoloop[ 0 ];
void loop()
{
  MAX_DEMO  = sizeof( demoloop );
  setticks( 0 , MAX_DEMO , 5000 );
  manageticks();
  manageVariables();
  if( last_demo != gettick(0) )  { 
    resettick(1,0); 
  }
  renderdemo( demoloop[gettick(0) ] );
  last_demo = gettick(0);
}
#endif


// end DEMO_MODE
//#endif
















