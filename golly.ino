#ifdef GOLLY
/*
 * Conway's "Life"
 *
 * Adapted from the Life example
 * on the Processing.org site
 */

//#include <FrequencyTimer2.h>
byte col = 0;

#define GOLLY_DELAY 0

#ifndef GOLLY_SIZE
#define GOLLY_SIZE 0
#endif

extern byte leds[GOLLY_SIZE][GOLLY_SIZE];
byte world[GOLLY_SIZE][GOLLY_SIZE][2];
long density = 50;

// take screen for input
void golly_setup_screen() {
  for (int i = 0; i < GOLLY_SIZE; i++) {
    for (int j = 0; j < GOLLY_SIZE; j++) {
      //leds[i][j] = world[i][j][0];
     world[i][j][0] = getpixel(i*XMAX/GOLLY_SIZE,j*YMAX/GOLLY_SIZE)?1:0;
    }
  }
}

void golly_setup_random() {
  randomSeed(analogRead(5));
  for (int i = 0; i < GOLLY_SIZE; i++) {
    for (int j = 0; j < GOLLY_SIZE; j++) {
      if (random(100) < density) {
        world[i][j][0] = 1;
      }
      else {
        world[i][j][0] = 0;
      }
      world[i][j][1] = 0;
    }
  }

}

int savecountbirth=0;

boolean golly_loop() {
   golly_loop(true, MIDX, MIDY);
}
  
boolean golly_loop(boolean iscentered, int posx, int posy) {
  // Display current generation
  //for (int i = 0; i < GOLLY_SIZE; i++) {
  //  for (int j = 0; j < GOLLY_SIZE; j++) {
  //    leds[i][j] = world[i][j][0];
  //  }
  //}

  // Display current generation - PANEAU LEDS

/*
  int golly_cell_factor = 2;
  int offsetx = 18;
  int offsety = 1;
  for (int idx = 0; idx < GOLLY_SIZE; idx++) {
    for (int jdx = 0; jdx < GOLLY_SIZE; jdx++) {
      int i= idx*golly_cell_factor + offsetx;
      int j= jdx*golly_cell_factor + offsety;
      int cell_color = (world[idx][jdx][0] > 0)?15:0;
      if( cell_color > 0 ) {
      pointvirtual16( i,   j  , cell_color );
      pointvirtual16( i+1, j  , cell_color );
      pointvirtual16( i+1, j+1, cell_color );
      pointvirtual16( i,   j+1, cell_color );
      }
    }
  }
  */

  int offsetx = (XMAX - golly_cell_factor*GOLLY_SIZE)>>1;
  int offsety = (YMAX - golly_cell_factor*GOLLY_SIZE)>>1;
  for (int idx = 0; idx < GOLLY_SIZE; idx++) {
    for (int jdx = 0; jdx < GOLLY_SIZE; jdx++) {
      int i,j;
      if( iscentered ) {
         i= idx*golly_cell_factor + offsetx;
         j= jdx*golly_cell_factor + offsety;
      }
      else {
        i=posx;
        j=posy;
      }
      int cell_color = (world[idx][jdx][0] > 0)?MAX_INTENSITY:0;
      if( !cell_color )  rect16(i,j, i+golly_cell_factor, j+golly_cell_factor, cell_color);
      /*
      //if(world[idx][jdx][0] > 0 ) {
        int cell_color = (world[idx][jdx][0] > 0)?15:0;
        for(int l=0; l< golly_cell_factor;l++) {
          for(int m=0; m< golly_cell_factor;m++) {          
            //pointvirtual16( i+l,   j+m  , 15 );
            pointvirtual16( i+l,   j+m  , cell_color );
          }
        }
      //}
      */
    }
  }

  delay(GOLLY_DELAY);
  int countbirth = 0;

  // Birth and death cycle
  for (int x = 0; x < GOLLY_SIZE; x++) {
    for (int y = 0; y < GOLLY_SIZE; y++) {
      // Default is for cell to stay the same
      world[x][y][1] = world[x][y][0];
      int count = neighbours(x, y);
      if (count == 3 && world[x][y][0] == 0) {
        // A new cell is born
        world[x][y][1] = 1;
        countbirth++;
      }
      if ((count < 2 || count > 3) && world[x][y][0] == 1) {
        // Cell dies
        world[x][y][1] = 0;
      }
    }
  }

  // Copy next generation into place
  for (int x = 0; x < GOLLY_SIZE; x++) {
    for (int y = 0; y < GOLLY_SIZE; y++) {
      world[x][y][0] = world[x][y][1];
    }
  }
  
  //  boolean iscycling = (countbirth > 0 && ( savecountbirth != countbirth ||countbirth == 0) );
  boolean iscycling = (countbirth > 0 && savecountbirth != countbirth);
  savecountbirth = countbirth;
  return iscycling;
  
}

int neighbours(int x, int y) {
  return world[(x + 1) % GOLLY_SIZE][y][0] +
    world[x][(y + 1) % GOLLY_SIZE][0] +
    world[(x + GOLLY_SIZE - 1) % GOLLY_SIZE][y][0] +
    world[x][(y + GOLLY_SIZE - 1) % GOLLY_SIZE][0] +
    world[(x + 1) % GOLLY_SIZE][(y + 1) % GOLLY_SIZE][0] +
    world[(x + GOLLY_SIZE - 1) % GOLLY_SIZE][(y + 1) % GOLLY_SIZE][0] +
    world[(x + GOLLY_SIZE - 1) % GOLLY_SIZE][(y + GOLLY_SIZE - 1) % GOLLY_SIZE][0] +
    world[(x + 1) % GOLLY_SIZE][(y + GOLLY_SIZE - 1) % GOLLY_SIZE][0];
}

/*
void setupLeds() {
  // sets the pins as output
  for (int i = 1; i <= 16; i++) {
    pinMode(pins[i], OUTPUT);
  }

  // set up cols and rows
  for (int i = 1; i <= 8; i++) {
    digitalWrite(cols[i - 1], LOW);
  }

  for (int i = 1; i <= 8; i++) {
    digitalWrite(rows[i - 1], LOW);
  }

  clearLeds();

  // Turn off toggling of pin 11
  FrequencyTimer2::disable();
  // Set refresh rate (interrupt timeout period)
  FrequencyTimer2::setPeriod(2000);
  // Set interrupt routine to be called
  FrequencyTimer2::setOnOverflow(display);

}

void clearLeds() {
  // Clear display array
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      leds[i][j] = 0;
    }
  }
}

// Interrupt routine
void display() {
  digitalWrite(cols[col], LOW);  // Turn whole previous column off
  col++;
  if (col == 8) {
    col = 0;
  }
  for (int row = 0; row < 8; row++) {
    if (leds[col][7 - row] == 1) {
      digitalWrite(rows[row], LOW);  // Turn on this led
    }
    else {
      digitalWrite(rows[row], HIGH); // Turn off this led
    }
  }
  digitalWrite(cols[col], HIGH); // Turn whole column on at once (for equal lighting times)
  delayMicroseconds(900);  // Delay so that on times are longer than off time = brighter leds
}
*/

#endif

