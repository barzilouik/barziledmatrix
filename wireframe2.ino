// from GameDuino Project
// http://excamera.com/sphinx/gameduino/samples/wireframe/index.html
////////////////////////////////////////////////////////////////////////////////
//                                  3D Projection
////////////////////////////////////////////////////////////////////////////////

#if defined(WIREFRAME)

struct ship
{
  const char *name;
  byte nvertices;
  prog_char *vertices;
  byte nedges;
  prog_uchar *edges;
};

#include "eliteships.h"
#define NSHIPS (sizeof(eliteships) / sizeof(eliteships[0]))

static float mat[9];

// Taken from glRotate()
static void rotation(float phi)
{
  float x = 0.57735026918962573;
  float y = 0.57735026918962573;
  float z = 0.57735026918962573;

  float s = sin(phi);
  float c = cos(phi);

  mat[0] = x*x*(1-c)+c;
  mat[1] = x*y*(1-c)-z*s;
  mat[2] = x*z*(1-c)+y*s;

  mat[3] = y*x*(1-c)+z*s;
  mat[4] = y*y*(1-c)+c;
  mat[5] = y*z*(1-c)-x*s;

  mat[6] = x*z*(1-c)-y*s;
  mat[7] = y*z*(1-c)+x*s;
  mat[8] = z*z*(1-c)+c;
}

//static byte projected[40 * 2];
static byte projected[40 * 3];   // add z in the projected truc ... vinz 24/02/2013

static byte sn;      // Ship number, 0-NSHIPS
static float phi;    // Current rotation angle

void project(struct ship *s, float distance)
{
  byte vx;
  prog_char *pm = s->vertices; 
  prog_char *pm_e = pm + (s->nvertices * 3);
  byte *dst = projected;
  char x, y, z;

  while (pm < pm_e) {
    x = pgm_read_byte_near(pm++);
    y = pgm_read_byte_near(pm++);
    z = pgm_read_byte_near(pm++);
    float xx = x * mat[0] + y * mat[3] + z * mat[6];
    float yy = x * mat[1] + y * mat[4] + z * mat[7];
    float zz = x * mat[2] + y * mat[5] + z * mat[8] + distance;
    //float q = 140 / (140 + zz);
    //*dst++ = byte(128 + xx * q);
    //*dst++ = byte(128 + yy * q);
    float q = 100 / (100 + zz);
    *dst++ = byte((MIDX + xx * q )*1.01);  // correction perspective sur le grand ecran
    *dst++ = byte(MIDY + yy * q);
    *dst++ = byte(  128 + zz );    // add z in the projected truc ... vinz 24/02/2013
  }
}

// added for outside call without include ... vince 24/02/2013
void drawship(int shipnb, float distance, float rot) {
  //rotation(rot);
  rotation(phi);
  phi += 0.02;
  //if( phi > 3.14 ) phi = 0;
  draw(&eliteships[shipnb], distance);
}

void draw(struct ship *s, float distance)
{
  project(s, distance);

  prog_uchar *pe = s->edges; 
  prog_uchar *pe_e = pe + (s->nedges * 2);
  while (pe < pe_e) {
    //byte *v0 = &projected[pgm_read_byte_near(pe++) *3 ];
    //byte *v1 = &projected[pgm_read_byte_near(pe++) *3 ];
    byte *v0 = &projected[ pgm_read_byte_near(pe++) *3 ]; // add z in the projected truc ... vinz 24/02/2013
    byte *v1 = &projected[ pgm_read_byte_near(pe++) *3 ]; // add z in the projected truc ... vinz 24/02/2013

    int ax = v0[0];
    int ay = v0[1];

    int bx = v1[0];
    int by = v1[1];

    int az = v0[2];    
    int bz = v1[2];   


line( ax, ay, bx, by, abs( ((az+bz)/2+10) / (distance/100) )+ 5 );
    //line( ax, ay, bx, by, map( (az+bz), 0, 200, 1, 255) );
    //line( ax, ay, bx, by, 255);

#ifdef DEBUG
      Serial.print("->");
      Serial.print("\t");
      Serial.print(ax);
      Serial.print("\t");
      Serial.print(ay);
      Serial.print("\t");
      Serial.print(bx);
      Serial.print("\t");
      Serial.print(by);
      Serial.print("\t\t");
      Serial.print(bz);
      Serial.print("\t");
      Serial.print(bz);
      Serial.println();
#endif 

  }
}

// Draw one frame of ship
void cycle(float distance)
{
  rotation(phi);
  phi += 0.15;

  //setvirtualdisplay( 0 );
  draw(&eliteships[sn], distance);
  //render(); 
}

void rendercycle(float distance)
{
  rotation(phi);
  //phi += 0.15;
  phi += 0.05;

  setvirtualdisplay( 0 );
  draw(&eliteships[sn], distance);

//#ifdef WIREFRAME_NUMBER
  int diz = int( sn/10);
  dispcarascii( MIDX - OFFSET, 1, '0' + diz  ,3 );
  int unit = int(sn - diz*10);
  dispcarascii( MIDX - 2*OFFSET, 1, '0' + unit ,3 );
//#endif
  render(); 
}

void wireframeloop()
{
  const char *name = eliteships[sn].name;

  int d;
  for (d = 0; d < 100; d=d+2)
    rendercycle(1000 - 8.5 * d);
  for (d = 0; d < 100; d++) 
    rendercycle( 1000 - 8.5*100 );
  for (d = 100; d > 0; d--) 
    rendercycle(1000 - 8.5 * d);
  //for (d = 0; d < 100; d++)
    //cycle(10 * d);
  sn = (sn + 1) % NSHIPS;
}


#endif



/*

 // from GameDuino Project
 // http://excamera.com/sphinx/gameduino/samples/wireframe/index.html
 ////////////////////////////////////////////////////////////////////////////////
 //                                  3D Projection
 ////////////////////////////////////////////////////////////////////////////////
 // ORIGINAL VERSION
 
 struct ship
 {
 const char *name;
 byte nvertices;
 prog_char *vertices;
 byte nedges;
 prog_uchar *edges;
 };
 
 #include "eliteships.h"
 #define NSHIPS (sizeof(eliteships) / sizeof(eliteships[0]))
 
 static float mat[9];
 
 // Taken from glRotate()
 static void rotation(float phi)
 {
 float x = 0.57735026918962573;
 float y = 0.57735026918962573;
 float z = 0.57735026918962573;
 
 float s = sin(phi);
 float c = cos(phi);
 
 mat[0] = x*x*(1-c)+c;
 mat[1] = x*y*(1-c)-z*s;
 mat[2] = x*z*(1-c)+y*s;
 
 mat[3] = y*x*(1-c)+z*s;
 mat[4] = y*y*(1-c)+c;
 mat[5] = y*z*(1-c)-x*s;
 
 mat[6] = x*z*(1-c)-y*s;
 mat[7] = y*z*(1-c)+x*s;
 mat[8] = z*z*(1-c)+c;
 }
 
 static byte projected[40 * 2];
 
 void project(struct ship *s, float distance)
 {
 byte vx;
 prog_char *pm = s->vertices; 
 prog_char *pm_e = pm + (s->nvertices * 3);
 byte *dst = projected;
 char x, y, z;
 
 while (pm < pm_e) {
 x = pgm_read_byte_near(pm++);
 y = pgm_read_byte_near(pm++);
 z = pgm_read_byte_near(pm++);
 float xx = x * mat[0] + y * mat[3] + z * mat[6];
 float yy = x * mat[1] + y * mat[4] + z * mat[7];
 float zz = x * mat[2] + y * mat[5] + z * mat[8] + distance;
 //float q = 140 / (140 + zz);
 //*dst++ = byte(128 + xx * q);
 //*dst++ = byte(128 + yy * q);
 float q = 100 / (100 + zz);
 *dst++ = byte(MIDX + xx * q);
 *dst++ = byte(MIDY + yy * q);
 }
 }
 
 // added for outside call without include ... vince 24/02/2013
 void drawship(int shipnb, float distance, float phi) {
 rotation(phi);
 draw(&eliteships[shipnb], distance);
 }
 
 void draw(struct ship *s, float distance)
 {
 project(s, distance);
 
 prog_uchar *pe = s->edges; 
 prog_uchar *pe_e = pe + (s->nedges * 2);
 while (pe < pe_e) {
 //byte *v0 = &projected[pgm_read_byte_near(pe++) << 1];
 //byte *v1 = &projected[pgm_read_byte_near(pe++) << 1];
 byte *v0 = &projected[pgm_read_byte_near(pe++) ];
 byte *v1 = &projected[pgm_read_byte_near(pe++) ];
 
 int ax = v0[0];
 int ay = v0[1];
 
 int bx = v1[0];
 int by = v1[1];
 
 line2(ax,bx,ay,by, MAX_INTENSITY );
 
 if(DEBUG) {
 Serial.print("->");
 Serial.print("\t");
 Serial.print(ax);
 Serial.print("\t");
 Serial.print(ay);
 Serial.print("\t");
 Serial.print(bx);
 Serial.print("\t");
 Serial.print(by);
 Serial.println();
 }  
 
 }
 }
 
 
 static byte sn;      // Ship number, 0-NSHIPS
 static float phi;    // Current rotation angle
 
 // Draw one frame of ship
 void cycle(float distance)
 {
 rotation(phi);
 phi += 0.02;
 
 setvirtualdisplay( 0 );
 
 draw(&eliteships[sn], distance);
 
 render(20); 
 
 }
 
 void wireframeloop()
 {
 const char *name = eliteships[sn].name;
 
 int d;
 for (d = 0; d < 100; d++)
 cycle(1000 - 10 * d);
 for (d = 0; d < 72*6; d++) 
 cycle(0.0);
 for (d = 0; d < 100; d++)
 cycle(10 * d);
 sn = (sn + 1) % NSHIPS;
 }
 
 */





