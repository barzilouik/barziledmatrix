barziledmatrix
==============

matrix led driver - obsolescence oriented - drive them all!

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
