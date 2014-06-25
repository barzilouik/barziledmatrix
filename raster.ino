/////////////////////// STREAM RASTER ////////////////////////////////
#if defined (RASTER_MODE)



// Decode Simple Pixel Stream, STREAM_BITPLANES bitplane (defailt = 1)
boolean checkSerial() {
  int ret = false;
  while (Serial.available()) {

    int a = Serial.read();

    if( a == 255 )    {
      setvirtualdisplay( 0 );
      raster_state == 0;
      return true;
    }
    if( a == 254 )    {
      PSYCHE_MODE = !PSYCHE_MODE;
      raster_state == 0;
      return true;
    }
    byte filter  = B01111111;    
    boolean selector = ( (a & B10000000) == 128 );

    if( selector ) {  // X

      //if( raster_state == 0 ) {
      raster_state = 1;
      raster_x = a - 128;// a & filter ;
      ret = false;
      //} 
    }
    else {            // Y
      //if( raster_state == 1 ) {
      //raster_state = 0;
      raster_y = a;
      //setpixel16( XMAX - raster_x, raster_y, 255 ); 
      int brush_size_x = 2;
      int brush_size_y = 2;
      rect16( XMAX - raster_x, raster_y, XMAX - raster_x + brush_size_x, raster_y + brush_size_y, 255 ); 
      ret=true;    
      //}
    }

  } // end Serial
  //Serial.flush();

  return ret;
}
#endif





