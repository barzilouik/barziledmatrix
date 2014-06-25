/********************************************************************************************************************
 * Display Driver de Panneau Affichage a LEDs défilant !
 * Version générique car il pilote des circuit avec "feed" horizontal et vertical
 ********************************************************************************************************************
 *
 *
 * Revisions :
 * --------------
 * crea : 21 décembre 2012, barzilouik@gmail.com
 * added gfx                          : 6 janv 2013
 * added streaming : 1st implementation 7 janv 2013
 * added counter                      : 8 janvier 2013
 * version générique avec #defines    : 15 janv 2013
 * added sprite                       : 10 fev 2013
 * added animation                    : 12 fev 2013
 * added abitrary grayscale           : 13 fev 2013
 * line                               : 17 fev 2013
 * 3d + elite ship (thx gameduino)    : 21 fev 2013
 * demos + tests + multiticks         : 22 fev 2013
 * rotation 2D                        : 23 fev 2013
 * rect16                             : 28 fev 2013
 * dispcar16                          : 1 mar 2013
 * 0_2 stream GENERIC (handle video with variable bitplanes/compression : 28 mai 2013
 * 0_3 stream with interrupt + serialhandle + pulsetick + balls
 * 0_4 DUAL DISPLAY   : 24 jun 2013 + DUALified ( pixel16, rect16, dispcar16, line2, DISP_V_LOGIC, demo-0-100-110-120 )
 * dispcarbig16 + demo (display fullscreen chars) : 25 oct 2013
 * speed up : rect16 , DISP_SF
 * demos : renderdemo(), strip out clear()/render() from demos
 * 0_5 SERIAL DISPLAY : 13 sept 2013 : manage another type of display "9 multisegment" : serial bit bang ! + RASTER_MODE + FULLSCREEN_DISPLAY + MONOCHROM
 * correction bug dispgfx + optional datas; fullscreen CAR16; RASTER MODE (GML); DEMO_MODE
 * 0_6 ATTENTION : Seeduino MEGA : !!! not compatible with UNO (removed PROGMEM... all goes to RAM)
 * + game of life (golly) + effects
 * 0_7 OUTPUT_SPI : fullscreen "9 multisegment" SPI mode ... a lot of speed up for the display!!! yeah : 24 dec 2013
 * ...going 4 BTPLANES for this display
 * displayFPS()
 * z-shaded wireframe
 * display with interuptions
 * double buffer and page flipping
 * MAX_INTENSITY is 0...255 : is now a "virtual intensity" on 8 bits for all public drawing functions, 0 means CLEAR
 *
 *
 * TODO FEATURES :
 * ---------------
 * - gérer un affichage avec le ZERO a gauche ( pour éviter de faire des calcul de merde pour inverser les choses)
 * - OK - tick manager fonctionnel -> caracteres clignotants par ex ( plage > 2000 ?)
 * - OK - ajouter fade in / fade out
 * - coder caractère minuscules, autres
 * - un protocole de description des items a afficher (Texte clignotant a telle vitesse : "ATTENTION ! #10 #C" par ex)
 * - gestion du temps sous interuption (et indicateur de "dirty" /..)
 * - implementer un mode BAM (bit angle modulation) pour le rendu en niveau de gris et un GAMMA !
 * - des transitions !!!!
 * - afficher les FPS
 * - systeme de TILES avec des MOTIFS
 * - gfx ZOOM
 * - automates cellulaires - wireworld - golly linux (avec scroll dans la map des nombres premiers ?)
 * - ASCII art , cf bank de labomedia
 * - OK - tester le bitbang par SPI !!!
 * - niveaux de gris sur le grand panneau vert (63X96)
 * - tests affichage sous interruptions
 *
 * ID GRAFX
 * - anim disquette Amiga
 * - boucle animation bocuhe qui se mange elle meme
 * - "PIXEL PORN"
 * -
 *
 * BUGS (9 janv 2013) :
 * --------------------
 * - OK - corriger affichage des numéro des dizaines dans caracters/dispcountern
 * - OK - affichage des gfx avec la ligne du bas qui ne marche pas
 * - MI-OK - faire un streaming correct
 *
 *
 * INSTALLATION
 * - lib used :
 * #include <digitalWriteFast.h>
 * #include <TimerOne.h>
 *
 ********************************************************************************************************************/
#define FIRMWARE_VERSION 7

#include <TimerOne.h>
//#include <EEPROM.h>
#include <avr/pgmspace.h>
#include <ctype.h>


//#include <boost/preprocessor/arithmetic/div.hpp>
//BOOST_PP_DIV(11, 5) // expands to 2
//#define KB 1024
//#define HKB BOOST_PP_DIV(A,2)
//#define REM(A,B) BOOST_PP_SUB(A, BOOST_PP_MUL(B, BOOST_PP_DIV(A,B)))
//#define RKB REM(KB,2)

/////////////// DEMO DEFINES ////////////////


/*
#define CAR_EXP 302
#define FS_MULTI_SPRITE 301
#define ONE_SPRITE 20
#define MULTI_PHRASE_SIN 19
#define MULTI_PHRASE 140
#define BLOCK_EXPANSION 21
#define BLOCK_BRIGHTNESS_2 22
#define SIN_HACKART 110
#define SIN_BB 111
#define SIN_FUCK 112
#define QUAD_LINE_ROTATE 100
#define LINES 1
#define ROT_TRIANGLES 2
#define WIREFRAME_SHOW 3
#define WIREFRAME_SINGLE 4
#define CIRCLES 5
#define ROCKET 6
#define WARNING_REBOOT 7
#define SIN_BARBINDUR 8
#define COUNTER 9
#define CLOCK 10
#define BALLS_SPRITE 18
#define COUNTER_REBOOT 17
#define REBOOT_PHRASE 16
#define SIN_UMBRELLA 15
#define ANIMATION 14
#define BLOCK_BRIGHTNESS 12
#define DEMO_GAV1 500
#define DEMO_GAV2 501
#define DEMO_GAV3 502
#define DEMO_GAV4 503
#define DEMO_GAV10 510
#define DEMO_GAVMIX 550
#define DEMO_GAVANIM 560

#define BIG_CHARS 600
#define BIG_CHARS_GLITCH 601


#define GOLLY_EFFECT 23
#define GLITCH_EFFECT 24

*/


//////////////////// INCLUDEs ///////////////////
#define CARACTERS_USED
// WIREFRAME USED ? (Elite Ships Dataaaas)
#define WIREFRAME
#define BALLS
#define GOLLY

// graphics : which included ?
#define PICODON
#define UMBRELLA
#define CHEVAL
//#define GAVANIM
////#define GAV10
//#define GAV4
#define GAV3
#define GAV2
#define GAV1

// graphics...there
#include "gfx.h"
/////////////////// Library Settings //////////////////////
#define BITPLANES 2
#define COLORS 8
#define MAX_INTENSITY 255
#define CLEAR_COLOR 0
#define SEGMENTS 1
#define SEGMENTS_MINUS 0
#define SEGMENT_HEIGHT 7
#define MAXCHARDISPLAY 16

#define DOUBLE_BUFFERING
#define TABSIN

#define NB_TICKS 2
#define NOCYCLE -1

#define GOLLY_SIZE 2

/////////////////// Define TYPE of diplay  (must set one) //////////////////////
//display VERT (ligne par ligne, le VERT) f
//#define HORIZONTAL_DISPLAY

// display ROUGE (colonne par colonne, le ROUGE)
//#define VERTICAL_DISPLAY

// display ROUGE DUAL DISPLAY (2 ROUGES l'un sur l'autre)
//#define VERTICAL_DISPLAY_DUAL

// display ROUGE DUAL DISPLAY (2 ROUGES l'un sur l'autre, géré en FULLSCREEN MONOCHROM... pour les besoin de tester dessus le FULLSCREEN)
//#define VERTICAL_DISPLAY_DUAL_FULLSCREEN

// display 9 SEGMENTS VERT, DOUBLEDISPLAY(le gros panneau VERT de la ville)
//#define MULTI_SEGMENT_DISPLAY

// display 9 SEGMENTS VERT, FULLSCREEN (le gros panneau VERT de la ville)
//#define MULTI_SEGMENT_DISPLAY
#define MULTI_SEGMENT_DISPLAY_FULLSCREEN
//#define MULTI_SEGMENT_DISPLAY_FULLSCREEN_MEMORY
//#define MULTI_SEGMENT_DISPLAY_FULLSCREEN_REDUCED

// DISPLAY SUBTECHNOLOGY (il faudra migrer les autres sous tech au dessus)
//#define OUTPUT_STANDARD
#define OUTPUT_SPI

////////////////// MODE SELECTOR (must set one) ////////////////////////////

// SIMPLE LOOP
//#define NORMAL_LOOP

// TEST MODE ?        (test color fullscreen! + serialhandle)
//#define TEST_MODE

// SERIAL USED ?
#define SERIALON
#define SERIAL1ON
#define SERIALON_STRINGS
#define SERIAL_BAUDRATE 9600
#define SERIAL1_BAUDRATE 9600
#define SERIAL_LINEMAX 15

// WIREFRAME LOOP MODE ?
//#define WIREFRAME_LOOP

// STREAMming ?        (streamer de la video de Processing)
//#define STREAM_SIMPLE
//#define STREAM_COMPRESSED
//#define STREAM_GENERIC
//#define STREAMDEBUG

// GML PAINTING MODE ?  (from processing)
//#define RASTER_MODE

/////////////////////////////////////////////////////////////
// DEMO modes ?         (mega demo per pannel technologies)
/////////////////////////////////////////////////////////////
//#define DEMO_MODE

// ancient modes ... (DEMO_MODE should replace)         BUG ???
//#define DEMO_MODE_MULTI_SEGMENT_DISPLAY_FULLSCREEN
//#define DEMO_MODE_MULTI_SEGMENT_DISPLAY_FULLSCREEN_1
//#define DEMO_MODE_MULTI_SEGMENT_DISPLAY_FULLSCREEN_TRAIT_UNION
//#define DEMO_MODE_HORIZONTAL_DISPLAY
//#define DEMO_MODE_VERTICAL_DISPLAY_DUAL
//#define DEMO_MULTI_SEGMENT_DISPLAY_FULLSCREEN_DEMO_BUNKER

////////////////// Enforce Display settings (optional) ////////////////////////////

//#define MONOCHROM
//#define DOUBLE_DISPLAY
//#define FULLSCREEN_DISPLAY
//#define PSYCHE_MODE_MANAGE

//////////////////       Bug?               ////////////////////////////
boolean DEBUG = false;

int curr_demo = 0;
#define SPLASH_SCREEN


////////////////// Display Hardware Definitions  ////////////////////////////////////
#ifdef HORIZONTAL_DISPLAY
#define XMAX 144
#define YMAX 7
#define DMAXSIZE  144
#define DISPLAYPAUSESTD_SPECIFIC 20
#endif

#ifdef VERTICAL_DISPLAY
#define XMAX 96
#define YMAX 7
#define YMAXMID 3
#define DISPLAYPAUSESTD_SPECIFIC 30
#endif

#ifdef VERTICAL_DISPLAY_DUAL
#define XMAX 96
#define YMAX 14
#define YMAXMID 7
#define DISPLAYPAUSESTD_SPECIFIC 30
#define DOUBLE_DISPLAY
#endif

#ifdef VERTICAL_DISPLAY_DUAL_FULLSCREEN
#define XMAX 96
#define YMAX 14
#define YMAXMID 7
#define DISPLAYPAUSESTD_SPECIFIC 30
//#define DOUBLE_DISPLAY
#define FULLSCREEN_DISPLAY
#undef BITPLANES
#define BITPLANES 2
#define MONOCHROM
#endif

#ifdef MULTI_SEGMENT_DISPLAY
#define XMAX 96
#define YMAX 14
#define YMAXMID 7
#define DISPLAYPAUSESTD_SPECIFIC 0
// (en double display pour le moment)
#define DOUBLE_DISPLAY
//#define MONOCHROM
#endif

#ifdef MULTI_SEGMENT_DISPLAY_FULLSCREEN
#define XMAX 96
#define YMAX 63
#ifdef OUTPUT_SPI
#define DISPLAYPAUSESTD_SPECIFIC 1000
#undef MONOCHROM
#else
#define DISPLAYPAUSESTD_SPECIFIC 0
//#define MONOCHROM
#endif
#define FULLSCREEN_DISPLAY
#undef BITPLANES
#define BITPLANES 2
#define BITPLANES_MINUS 1
#define COLORS 4
#define COLOR_MINUS 3
#undef SEGMENTS
#define SEGMENTS 9
#define SEGMENTS_MINUS 8
#define XMAX_MINUS 95
#define YMAX_MINUS 62
#define MIDX  48
#define MIDY  31
#undef MAXCHARDISPLAY
#define MAXCHARDISPLAY 16


#endif

// SUBSET MULTI_SEGMENT_DISPLAY_FULLSCREEN ...Experimental
// reduced display area
#ifdef MULTI_SEGMENT_DISPLAY_FULLSCREEN_REDUCED
#define MULTI_SEGMENT_DISPLAY_FULLSCREEN
#define XMAX 96
//#define YMAX 63
#define YMAX 28
#define DISPLAYPAUSESTD_SPECIFIC 3
#define FULLSCREEN_DISPLAY
#undef BITPLANES
#define BITPLANES 9
//#define BITPLANES 4
#define MONOCHROM
#endif

// SUBSET MULTI_SEGMENT_DISPLAY_FULLSCREEN ...Experimental
// experimental pour visualiser la mémoire + wireframe ...Experimental
#ifdef MULTI_SEGMENT_DISPLAY_FULLSCREEN_MEMORY
#define MULTI_SEGMENT_DISPLAY_FULLSCREEN
#define XMAX 96
#define YMAX 63
//#define YMAX 28
#define DISPLAYPAUSESTD_SPECIFIC 3
#define FULLSCREEN_DISPLAY
#undef BITPLANES
//#define BITPLANES 4
#define BITPLANES 2
#define MONOCHROM
#define WIREFRAME_LOOP
#endif

///////////////////////////// Chars settings ////////////////////////////////////////////////
#define CARWIDTH 5
#define CARHEIGHT 8
#define CARMAX 48
#define EXPANDED 1000
static int OFFSET = CARWIDTH + 1;
static int carptr = 0;

// in FULL_SCREEN_MULTI.... for big chars :
int expandfactorX = 5;
int expandfactorY = 5;

enum Blah {
 CAR_EXP,
 FS_MULTI_SPRITE,
 ONE_SPRITE,
 MULTI_PHRASE_SIN ,
 MULTI_PHRASE ,
 BLOCK_EXPANSION ,
 BLOCK_BRIGHTNESS_2 ,
 SIN_HACKART ,
 SIN_BB ,
 SIN_FUCK ,
 QUAD_LINE_ROTATE ,
 LINES ,
 ROT_TRIANGLES ,
 WIREFRAME_SHOW ,
 WIREFRAME_SINGLE ,
 CIRCLES ,
 ROCKET ,
 WARNING_REBOOT ,
 SIN_BARBINDUR ,
 COUNTER ,
 CLOCK ,
 BALLS_SPRITE ,
 COUNTER_REBOOT ,
 REBOOT_PHRASE,
 SIN_UMBRELLA ,
 ANIMATION ,
 BLOCK_BRIGHTNESS ,
 DEMO_GAV1 ,
 DEMO_GAV2 ,
 DEMO_GAV3 ,
 DEMO_GAV4 ,
 DEMO_GAV10 ,
 DEMO_GAVMIX ,
 DEMO_GAVANIM ,

 BIG_CHARS ,
 BIG_CHARS_GLITCH ,


 GOLLY_EFFECT ,
 GLITCH_EFFECT 
};


///////////////////////////// Display HACKEFFECTS ///////////////////////////////////////////
boolean PSYCHE_MODE = false;  // for fullscreen display
int PSYCHE_FACTOR   = 24;

int golly_cell_factor = 8;
static boolean golly_init = false;

int currFPS = 0;
int FrameInterTime = 0;
///////////////////////////// Various Definitions ///////////////////////////////////////////
// precalculus - should be handwritten in the driver for speed!
#if !defined (XMAX_MINUS)
#define XMAX_MINUS (XMAX-1)
#endif
#if !defined (YMAX_MINUS)
#define YMAX_MINUS (YMAX-1)
#endif
#if !defined (BITPLANES_MINUS)
#define BITPLANES_MINUS (BITPLANES-1)
#endif
#if !defined (MIDX)
#define MIDX  (XMAX >> 1)
#endif
#if !defined (MIDY)
#define MIDY  (YMAX >> 1)
#endif
#if !defined (COLOR_MINUS)
#define COLOR_MINUS (COLORS - 1)
#endif

//#define XMAX_MINUS 95
//#define YMAX_MINUS 62
//#define BITPLANES_MINUS 8
//#define MIDX  48
//#define MIDY  31

// precalc functs
//byte sin10[256];
#ifdef TABSIN
byte sin10[256];
#else
byte sin10[2];
#endif

/////////////////////////////////////////  VIRTUAL DISPLAY ///////////////////////////////
#ifdef DOUBLE_BUFFERING
byte virtualdisplay[2][SEGMENTS][BITPLANES][XMAX];
unsigned short currfb = 0;
unsigned short currfb_disp = 1;
#else
byte virtualdisplay[1][SEGMENTS][BITPLANES][XMAX];
unsigned short currfb = 0;
unsigned short currfb_disp = 0;
#endif

#if (defined DOUBLE_DISPLAY) || (defined VERTICAL_DISPLAY_DUAL_FULLSCREEN)
byte virtualdisplay2[BITPLANES][XMAX];
#endif

/////////////////////////////////////////  REMANENCE TIMES ///////////////////////////////

// Display times
const static int displayPauseSTD = DISPLAYPAUSESTD_SPECIFIC;
int displayPause = DISPLAYPAUSESTD_SPECIFIC;
unsigned long lastimeFade = 0;
#define FADE_FRACTIONS 80

// misc vars
float mov = 0;
float mov2 = 0;
int inc = 1;
int inc2 = 1;

float PIG = 0;
int inc3 = 1;

float ang = 1;
float incang = .1;

float frames ;

//String txtMsg = "";                         // a string for incoming text
//int lastStringLength = txtMsg.length();     // previous length of the String

// Demo strings
/*
static char str1[] = "IN A MIRROR OF MIRAGE";
static char str2[] = "STATIC FUMBLES";
static char str3[] = "REPOS THE LIMELIGHT";
*/

char str1[] = "LA COPIE EST SACREE\0";
char str2[] = "INTERNET EST SAINT\0";
char str3[] = "\0LE CODE EST LOI\0";

//static char str1[] = "IN A MIRROR OF MIRAGE";
//static char str2[] = "STATIC FUMBLES";
//static char str3[] = "REPOS THE LIMELIGHT";
//static char str1[] = "";//SO MANY HOLES";
//static char str2[] = "";//SO LITTLE TIME";
//static char str3[] = "";//POINT POINT POINT.ORG";

//BIG cHARS demo
int BIGMAX = expandfactorX * (CARWIDTH + 2) * 8;
int factor = expandfactorX * (CARWIDTH + 2);
int bigroll = BIGMAX;
#define BIGINCVALUE 2
int biginc = BIGINCVALUE;

// Demo String Serial On

int BUFFMAXCHAR = 20;   // max char per line

#if defined  (SERIALON_STRINGS)
String txtMsg[SEGMENTS];
int ring_cpt = 0;
String inputString = "";
boolean stringComplete = false;
#endif


//////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////  SETUP  /////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////////////////
void setup() {

#if defined (SERIALON)
  Serial.begin( SERIAL_BAUDRATE );
  for (int i = 0; i < SEGMENTS; i++) {
    txtMsg[i].reserve( BUFFMAXCHAR );
  }
#endif

#if defined (SERIAL1ON)
  Serial1.begin( SERIAL1_BAUDRATE );
#endif

#if defined (STREAM_COMPRESSED) || defined (STREAM_SIMPLE) || defined (STREAM_GENERIC) || defined (RASTER_MODE)
  Serial.begin( SERIAL_BAUDRATE );
#endif

  // call to all inits
  initlogicdisplay();
  resetBrightness();
  setvirtualdisplay( 0 );
  initticks();
  intTabSin();

#if defined (SPLASH_SCREEN)
  while ( millis() < 2500 ) {
    flipFrameBuffers();
    setvirtualdisplay( 0 );
    demo( WIREFRAME_SINGLE );
    resetcarseq();
    String strplash1 = "BIG LED DISPLAY";
    dispstring16( ( MAXCHARDISPLAY - strplash1.length() ) * 6, 0, strplash1, strplash1.length() , MAX_INTENSITY );

    resetcarseq();
    String strplash2 = "VERSION " ;//+ ('0' + FIRMWARE_VERSION);
    strplash2 += FIRMWARE_VERSION;
    dispstring16( ( MAXCHARDISPLAY - strplash2.length() ) * 6, 1 * 7, strplash2, strplash2.length() , MAX_INTENSITY );
  }
#endif

}


//////////////////////////////////////////////////////////////////////////////////////////
//
//                                       LOOPs
//
//////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////// LOOP DEMO MODEs /////////////////////////////////////
// cf DEMOMODE >>

/////////////////////////// LOOP SERIAL MODE /////////////////////////////////////
#if defined  (SERIALON_STRINGS)

void loop()
{
  manageticks();                     // handle vars...
  manageVariables();

  flipFrameBuffers();                // handle display...
  setvirtualdisplay( 0 );

  //displayFPS();                      // display infos...
  //dispDemoInfos( curr_demo );

  if ( curr_demo >= 0 ) {            // handle demos...
    demo( curr_demo );
  }

  for (int i = 0; i < SEGMENTS; i++) { // handle texts
    resetcarseq();
    dispstring16(  ( 3 - abs( BUFFMAXCHAR - MAXCHARDISPLAY) ) * 6  , i * 7 , txtMsg[i], BUFFMAXCHAR - 3 , MAX_INTENSITY ); // 1 ligne sur 2
  }

  // compensate for constant FrameRate
  int FrameIntertimeMax = 10;
  //if ( FrameInterTime < FrameIntertimeMax )  delay( FrameIntertimeMax - FrameInterTime);
}

#endif

/////////////////////////// LOOP RASTER MODE ////////////////////////////////////
#if defined (RASTER_MODE)

int raster_state = 0;
int raster_x = 0;
int raster_y = 0;

void loop()
{
  if (  checkSerial() ) {
    //setpixel16( XMAX - raster_x, raster_y, 255 );
  }

  render();
}
#endif

/////////////////////////// LOOP STREAM MODEs ////////////////////////////////////
#if defined (STREAM_SIMPLE)
void loop()
{
  if ( checkSerial() ) render();
}
#endif


#if defined (STREAM_COMPRESSED) ||  defined (STREAM_GENERIC)
int seqdisplay = 0;

void loop()
{
  int PAUSE = 30;

  if ( checkSerial() )
  {

    int nbbitplanes = getUsedBitplanes();

    if ( nbbitplanes == 1 ) {
      renderalllines( PAUSE, 0 );
    }
    else if ( nbbitplanes == 2 ) {
      renderalllines( PAUSE, 0 );
      renderalllines( 2 * PAUSE, 1 );
    }
    else if ( nbbitplanes == 3) {
      renderalllines( PAUSE, 0 );
      renderalllines( 2 * PAUSE, 1 );
      renderalllines( 5 * PAUSE, 2 );
    }
    seqdisplay = 0;
  }
  else    {
    seqdisplay++;
    seqdisplay = seqdisplay % 20;
    //if(seqdisplay==0) renderalllines( 50, 0 );
  }
  delay(1);

  //else setvirtualdisplay(0);
  //rendermono();
}


#endif


//////////////////////////////////// LOOP NORMAL MODE ////////////////////////////////////
#ifdef NORMAL_LOOP
void loop()
{
  // manage functions
  //#if defined (SERIALON)
  //  serialHandle();
  //  demo( current_demo );
  //#endif

  //manageticks();


  //setvirtualdisplay( 0 );
  //render();

  //demo( 112 );
  setvirtualdisplay( 0 );
  demo(DEMO_GAVMIX);
  render();


  //demo( 301 );
  //demo( 301 );
  //demo( 140 );
  //demo( 17 ); // BLOCK

  /*
  while (Serial.available() > 0) {
   char inChar = Serial.read();
   txtMsg += inChar;
   if( inChar == 13 ) txtMsg="";
   }

   setvirtualdisplay( 0 );
   resetcarseq();

   int yop = txtMsg.length() - ang/2 +70;
   if( yop>0) {
   for(int i=yop; i >= 0; i--) {
   dispcarseq( 0, 0, txtMsg.charAt(i) ,0);
   }
   rendermono();
   }
   else {
   setvirtualdisplay( 0 );
   int dispwidth = 144;
   dispgfx(27, 27, 60, abs(sin10[(int)ang]/10) );
   render();
   }
   */
  manageVariables();

}
#endif

/////////////////////////// LOOP TESTMODE ////////////////////////////////////
#ifdef  TEST_MODE
void loop()
{
  setticks( 0, 4, 2000 );
  //setmaxtickval(4);
  //settickinterval(2000);
  manageticks();
  int test = 3; //gettick(0)
  setvirtualdisplay( 0 );

  switch ( test ) {
    case 1:       // COLOR TEST WITH  BLOCK
      {
        int bsize = XMAX / COLORS;
        int curcolor = 0;
        for (int i = 0; i < XMAX; i = i + bsize) {
          blockvirtual16( i, bsize, curcolor );
          curcolor++;
        }
        //if(millis() > 5000 )   fadeout(5000);
        break;
      }
    case 2:      // COLOR TEST WITH POINTS
      {
        int bsize = XMAX / COLORS;
        int curcolor = 0;
        for (int i = 0; i < XMAX; i = i + bsize) {
          int x = 0;
          for (; x < bsize; x ++) {
            for (int j = 0; j < 2; j ++) {
              pointvirtual16( i + x, j, curcolor );
            }
          }
          //if( (i % bsize) == 0)
          curcolor++;
        }
        break;
      }
    case 3:       // LINE TEST
      {
        line2(5, 7, XMAX - 1, 0, ang);
        ang ++;
        if (ang > 255) ang = 0;
        break;
      }
  }

  //  render( 50, 5 ); // render experimental ...
  render();

}
#endif

/////////////////////////// WIREFRAME MODE ////////////////////////////////////
#ifdef  WIREFRAME_LOOP
void loop()
{
  wireframeloop();
}
#endif
///////////// FIN       ///////////

void manageVariables() {
  if ( ang >= 255 || ang < 1) {
    incang *= -1;
  }
  ang += .5 * incang;

  if ( mov2 >= XMAX || mov2 < -40) {
    inc2 *= -1;
  }
  mov2 += 1 * inc2;

  if ( PIG > 5 ||  PIG < 0 ) {
    inc3 *= -1;
  }
  PIG = PIG + 1 * inc3;

  if ( mov >= 3 ||  mov <= 0 ) {
    //mov = 0;
    inc *= -1;
  }
  mov = mov + .1 * inc;

  //frameCount += 1;

  // BIG CHARS
  bigroll += biginc;
  if (bigroll < 0) {
    bigroll = 0;
    biginc = BIGINCVALUE;
  };
  if (bigroll > BIGMAX ) {
    bigroll = BIGMAX;
    biginc = -BIGINCVALUE;
  };

}









































