
// TICKS
unsigned int tickinterval[NB_TICKS];    // ms
int maxtickval[NB_TICKS];      // nb tick max, -1 for no cycle
int tickselapsed[NB_TICKS];    // current ticks from start
unsigned long previousMillis[NB_TICKS];
boolean pulseDone[NB_TICKS];    // impulsion released

boolean islooping[NB_TICKS];
boolean running[NB_TICKS];
byte ticksession[NB_TICKS];              // session for ressetting a tick : must be different to reset !

void  initticks() {
  for(int i=0; i < NB_TICKS; i++) {
    previousMillis[i] = millis();
    tickselapsed[i] = 0;
    maxtickval[i] = NOCYCLE;
    islooping[i] = false;
    running[i] = false;
    ticksession[i] = 255;
    pulseDone[i] = true;
  }
}

void setticks(int ticknb, int _maxtickval, int _tickinterval){
  if( ticknb < NB_TICKS ) {
    tickinterval[ticknb] = _tickinterval;
    maxtickval[ticknb] = _maxtickval;
    running[ticknb] = true;
    islooping[ticknb] = true;
  }
}

// with looping function
void setticksonce(int ticknb, int _maxtickval, int _tickinterval){
  if( ticknb < NB_TICKS ) {
    tickinterval[ticknb] = _tickinterval;
    maxtickval[ticknb] = _maxtickval;
    running[ticknb] = true;
    islooping[ticknb] = false;
  }
}

// set a tick to tickselapsed = 0, one per session !
void resettick( int ticknb, int session ) {
  if( ticknb < NB_TICKS && session != ticksession[ticknb] ) {
    tickselapsed[ticknb] = 0;
    ticksession[ticknb] = session;
  }
}

// not using a tick anymore
void disposetick( int ticknb ) {
  running[ticknb] = false;
}

/*
void setmaxtickval( long val ) {
 maxtickval = val;
 }
 
 void settickinterval( long val ) {
 tickinterval = val;
 }
 */

void manageticks() {
  unsigned long currentMillis = millis();
  for(int i=0; i < NB_TICKS; i++) {
    if( !running[i] ) continue;
    if( abs(currentMillis - previousMillis[i]) > (unsigned long)tickinterval[i]) {
      previousMillis[i] = currentMillis;  

      if( !islooping[i] && (tickselapsed[i] == maxtickval[i] - 1) )      continue;    // no loop and max tick -> exit

      /* TODO UPDOWN !!
      if( updown[i] ) {
        if( (tickselapsed[i] == maxtickval[i] - 1) || tickselapsed[i] <= 0) {
          inc[i] = -inc[i];
        }
      }
      */
      
      tickselapsed[i]++;
      if( maxtickval[i] != NOCYCLE )   tickselapsed[i] = tickselapsed[i] % maxtickval[i];
    }
  }
}

long gettick( int ticknb ) {
  if( ticknb < NB_TICKS ) {
    return tickselapsed[ticknb];
  }
  return -1;
}

// pulse a tick once in the interval 
boolean pulsetick( int ticknb ) {
  int lapse = gettick( ticknb );
  if( lapse >= 0 ) {
    if( lapse == 0 &&  pulseDone[ticknb] == false ) {
      pulseDone[ticknb] = true;
      return true;
    }
    else if( lapse != 0 ) {
      pulseDone[ticknb] = false;
      return false;
    }
    
  }
  return false;  
}

/*
// TICKS
 long tickinterval = 1000;  // ms
 long maxtickval = -1;  // nb tick max, -1 for no cycle
 long tickselapsed = 0; // current ticks from start
 unsigned long previousMillis = 0;
 
 
 void  initticks() {
 previousMillis = millis();
 tickselapsed = 0;
 }
 
 void setticks(int _maxtickval, int _tickinterval){
 tickinterval = _tickinterval;
 maxtickval = _maxtickval;
 tickselapsed = 0;
 }
 
 
 void setmaxtickval( long val ) {
 maxtickval = val;
 }
 
 void settickinterval( long val ) {
 tickinterval = val;
 }
 
 
 void manageticks() {
 unsigned long currentMillis = millis();
 if( abs(currentMillis - previousMillis) > (unsigned long)tickinterval) {
 previousMillis = currentMillis;  
 tickselapsed++;
 if( maxtickval > 0 ) tickselapsed = tickselapsed % maxtickval;
 }
 }
 
 long gettick() {
 return tickselapsed;
 }
 */







