/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    char val = (char)Serial.read(); 
    buffer += val;
    if (val == '\n') {
      is_buffer_completed = true;
    }
  }
}

void process_buffer(String buffer) {
  int header_index = buffer.indexOf('<');
  int footer_index = buffer.indexOf('>');
  
  if (header_index == -1 || footer_index == -1){
    Serial.flush();
    return;
  }

  String content = buffer.substring(header_index+1, footer_index);
  content.trim();
  if (content.length() >= 1) {
    char request = content.charAt(0);
    if (request == 'L') {
      read_sensors();
      send_beagle();
    }
    else if (request == 'C') {
      char buf[buffer.length()];
      content.toCharArray(buf, buffer.length());
      float motors_commands[3];
      if (extract_motor_commands(motors_commands, buf)) {
        setSpeed((int)motors_commands[0], 1);
        setSpeed((int)motors_commands[1], 2);
        setSpeed((int)motors_commands[2], 3);
        //int i = 0;
        //while (i < 3) Serial.println(motors_commands[i++]);
      }
    }

    Serial.flush();
  }
}

boolean extract_motor_commands(float motors_commands[3], char *buf) {
  char *ch;
  strtok(buf, ";");
  ch = strtok(NULL, ";");
  int i = 0;
  memset(motors_commands, 0, sizeof(motors_commands));
  while (ch) {
    float val = atof(ch);
    motors_commands[i++] = val;
    ch = strtok(NULL, ";");
    if (i >= 3) break;
  }
  return (i >= 3); 
}


