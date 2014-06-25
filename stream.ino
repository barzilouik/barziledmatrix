/////////////////////// STREAM SIMPLE ////////////////////////////////
#if defined (STREAM_SIMPLE)
int serindex =0;
int trame = 0;

// Decode Simple Pixel Stream, STREAM_BITPLANES bitplane (defailt = 1)
boolean checkSerial() {
  int STREAM_BITPLANES = 1;   // nb de bitplanes
  int ret = false;
  if (Serial.available()) {
    virtualdisplay[trame][serindex++] = (byte)Serial.read();

    if(serindex == 96) {
      serindex = 0;
      trame++;
      if(trame == STREAM_BITPLANES) { 
        ret = true;
        trame = 0;
      }
    }

  } // end Serial

  return ret;
}
#endif

/////////////////////// STREAM GENERIC ////////////////////////////////
// Decode Composite Pixel Stream with a number of "imageBitplanes" bitplanes (default = 1)

#if defined (STREAM_GENERIC)

byte virtualdisplay_buffer[3][XMAX];

int serindex =0;
int trame = 0;
int SOF[4] = {
  10, 20, 30, 40};
int sofindex = 0;
boolean letsgo = false;
int structstart = 0;
int structindex = 0;
int imageSize = 0;
boolean isCompressed = false;
int imageBitplanes = 1;   // nb de bitplanes
int Compressedsize = 0;
byte crc = 0;

int getUsedBitplanes() {
  return imageBitplanes;
}

//void serialEvent() {
boolean checkSerial() {
  boolean dodisplay = false;

  while( Serial.available() ) {
    int rec = Serial.read();

    /////  HEADER //
    if( !letsgo) {
      if( rec == SOF[structstart] )  { 
        structstart++;   
#ifdef STREAMDEBUG 
        Serial.println(".");
#endif
      } // START OF FRAME 
      else                           { 
        structstart = 0; 
#ifdef STREAMDEBUG 
        Serial.print("_");
        Serial.print(rec);
#endif
      }

      if( structstart == 4 ) {
        letsgo = true; 
        structstart = 0; 
        structindex = 0;
        serindex = 0;
        trame = 0;
        setvirtualdisplay(0);
        crc = 0;
#ifdef STREAMDEBUG 
        Serial.println("H OK");
#endif
      }

    }
    /////  SETTINGS //
    else {
      // PARAM 0
      if( structindex == 0 ) {             // SIZE of image ...
        imageSize = rec;
        if( imageSize > XMAX ) imageSize = XMAX; // error!
        structindex++;
        crc += rec;
#ifdef STREAMDEBUG 
        Serial.print("S: ");
        Serial.println(imageSize);
#endif
      }
      // PARAM 1
      else if( structindex == 1 ){        // COMPRESSION used ?
        if(rec != 0 ) isCompressed = true;
        else isCompressed = false;
        structindex++;
        crc += isCompressed?1:0;
#ifdef STREAMDEBUG 
        Serial.println(isCompressed?"comp":"plain");
#endif
      }
      // PARAM 2
      else if( structindex == 2 ){        // HOW MANY BITPLANES ?
        imageBitplanes = rec;
        if( imageBitplanes > BITPLANES ) imageBitplanes = BITPLANES; // error !
        if( imageBitplanes < 1         ) imageBitplanes = 1;         // error !
        structindex++;
        crc += rec;
#ifdef STREAMDEBUG 
        Serial.print("B: ");
        Serial.println(imageBitplanes);
#endif
      }
      // PARAM 3
      else if( structindex == 3 ){        // FRAME SIZE
        Compressedsize = rec;
        structindex++;
        crc += rec;
#ifdef STREAMDEBUG 
        Serial.print("L: ");
        Serial.println( Compressedsize );
#endif
      }
      // PARAM 4
      else if( structindex == 4 ){         // CRC for the HEADER
        //if( rec != crc ) letsgo = false;   // reset if not the good crc 
        structindex++;
#ifdef STREAMDEBUG 
        Serial.print("C: ");
        Serial.println(rec);
        if( rec != crc )  Serial.println("CRC NOK");        
#endif
      }
      /////  TRAME NOT COMPRESSED /////
      // PARAMs : TRAME
      else if( structindex == 5 ){
        if( ! isCompressed ){
          //virtualdisplay_buffer[trame][serindex++] = rec;  // double buffering transfer for each bitplane
          virtualdisplay[trame][serindex++] = rec;
          if( serindex >= imageSize ) {          // 1 Trame received 
#ifdef STREAMDEBUG 
            Serial.println("trm");
#endif
            serindex = 0;
            if( trame >= imageBitplanes - 1 ) {  // all Trames received
              //dirty = true;
              //memcpy( &virtualdisplay[trame][0], &virtualdisplay_buffer[trame][0], imageSize ); // double buffering transfer for each bitplane
              //dirty = false;
              ////// exp : memcpy( virtualdisplay, virtualdisplay_buffer, imageSize );                     // 
              trame       = 0;
              structstart = 0; 
              structindex = 0;
              serindex = 0;
              letsgo      = false;  
              dodisplay   = true;
#ifdef STREAMDEBUG 
              Serial.println("/");
#endif
            }
            else trame++;
          }
        }
        ///// TRAME COMPRESSED ...WIP ! /////
        else {

          virtualdisplay_buffer[0][serindex++] = rec;

          if( serindex >= Compressedsize ) {          // Trame received 
#ifdef STREAMDEBUG 
            Serial.println("trm");
#endif
            // decoding 1 TRAME
            int indexpix=0;
            int pixval, count;
            for (int idx = 0; idx < Compressedsize; idx = idx + 2 ) {

              pixval = virtualdisplay_buffer[0][ idx  ];
              count  = virtualdisplay_buffer[0][ idx+1];

              for( int k = 0; k < count; k++ ) {
                int x = indexpix % imageSize;
                int y = indexpix / (imageSize);

                if( pixval != 255 )  pointvirtual16( x, y, pixval );

                indexpix++;
              }
            }
            // end decoding

            serindex = 0;
            //memcpy( &virtualdisplay[trame][0], &virtualdisplay_buffer[trame][0], imageSize ); // double buffering transfer for each bitplane
            //memcpy( virtualdisplay, virtualdisplay_buffer, imageSize );                       // 
            trame       = 0;
            structstart = 0; 
            structindex = 0;
            letsgo      = false;  
            dodisplay   = true;

#ifdef STREAMDEBUG 
            Serial.println("/");
#endif

          } // end trame received

        } // trame

      } // end trame

    } 

    return dodisplay;
  } // end Serial
}
#endif




