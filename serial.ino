#if defined  (SERIALON_STRINGS)


String command = "";

void handle_command() {
  char action = command.charAt(0);
  if ( (action >= '0') && (action <= '8') ) {
    int index = action - '0';
    txtMsg[index] = command.substring(1);
  }
  else if ( action == '>' ) {
    for (int i = SEGMENTS; i > 0; i--) {
      txtMsg[i] = txtMsg[i - 1];
    }
    txtMsg[0] = command.substring(1);
  }
  else if ( action == '<' ) {
    for (int i = 1; i < SEGMENTS ; i++) {
      txtMsg[i - 1] = txtMsg[i];
    }
    txtMsg[SEGMENTS - 1] = command.substring(1);
  }
  else if ( action == '-' ) {
    for (int i = 0; i < SEGMENTS ; i++) {
      txtMsg[i] = "";
    }
  }
  else if ( action == '*' ) {
    int tmp = command.charAt(1);
    if ( tmp >= 'A' && tmp <= 'Z') {
      curr_demo = tmp - 'A';
    }
  }
  else txtMsg[0] = "SYNTAX ERROR";
}


void serialEvent() {
  while ( Serial.available() ) {
    handleSerial( (char)Serial.read() );
  }
}

#if defined (SERIAL1ON)
void serialEvent1() {
  while ( Serial1.available() ) {
    handleSerial( (char)Serial1.read() );
  }
}
#endif

void handleSerial( char inChar ) {

  if ( inChar == '\n' || inChar == '\r') {
    command.toUpperCase();
    handle_command();
    command = "";
  }
  else {
    if (  command.length() > SERIAL_LINEMAX ) {
      command.toUpperCase();
      handle_command();
      command = ">";
      command += inChar;
    }
    else {
      command += inChar;
    }
  }
}


#endif






















