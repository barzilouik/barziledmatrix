#ifdef BALLS

//
// Bouncng balls
//

// nb of balls
#define  nbballs  10
// screen size X - 1

int blobsize = 10;
int xlimit = XMAX - blobsize;
int ylimit = YMAX - blobsize;

int xlimitmin = blobsize;
int ylimitmin = blobsize;


float x[nbballs];
float y[nbballs];

float vx[nbballs];
float vy[nbballs];

void initballs() {
  for(int i=0;i < nbballs; i++) {
    x[i] = random(XMAX - blobsize);//random(96);
    y[i] = random(YMAX - blobsize);//random(96);
    vx[i] = (15.1 - random(6))/2;// + random(30)/10.0;
    vy[i] = (15.1 - random(6))/20;// + random(30)/10.0;

    //Serial.println(i);   
    /* 
     Serial.print("vx = ");
     Serial.print(vx[i]);
     Serial.print(", vy = ");
     Serial.println(vy[i]);
     */
  }
}

void updateballs() {
  //Serial.println("*");

  for(int i=0; i < nbballs ; i++) {

    vx[i] *= .99;
    if ( abs(vx[i]) < .1 ) { 
      vx[i] = random(4);
      vy[i] = random(20)/19.;
    }

    // X
    x[i] += vx[i];
    if( x[i] > xlimit ) {
      vx[i] = -vx[i]; 
      x[i] = xlimit; 
    }
    if( x[i] < xlimitmin ) {
      vx[i] = -vx[i]; 
      x[i] = xlimitmin; 
    }

    // Y
    y[i] += vy[i];
    if( y[i] > ylimit ) {
      vy[i] = -vy[i]; 
      y[i] = ylimit; 
    }
    if( y[i] < ylimitmin ) {
      vy[i] = -vy[i]; 
      y[i] = ylimitmin; 
    }
  }
}

void displayBalls() {
  for(int i=0; i < nbballs ; i++) {
  //#ifdef UMBRELLA
  //     dispsprite( &umbrella, x[i], y[i] - 30  ); 
  //#else
  //rect16( x[i], y[i], x[i] +blobsize, y[i] +blobsize, i*20 );

  //setpixel16( x[i], y[i] , 200 );
  //#endif


  // space invaders
  setticks( 3, 5, 100 );
  dispcar16( x[i], y[i] , '(' +(gettick(3))%2, 255 );
  }
}

#endif






