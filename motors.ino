
//Put the motors on a initial state  
void arm(){
  setSpeed(INIT_SPEED,1);
  setSpeed(INIT_SPEED,2);
  setSpeed(INIT_SPEED,3);
  delay(1000);
}

//Put the motors on a initial state  
void stop_motors(){
  setSpeed(STOP_SPEED,1);
  setSpeed(STOP_SPEED,2);
  setSpeed(STOP_SPEED,3);
  delay(1000);
}

//Change the speed and the rotation of the motors, 45 to 90 one direction and 100 to 145 another one (speed)
void setSpeed(int speed,int motor){
  switch (motor){
  case 1:  
    r_motor.write(speed); 
    break;
  case 2: 
    l_motor.write(speed);
    break;
  case 3:
    vertical_motor.write(speed);
    break; 
  }
}

float map_double(double x, double in_min, double in_max, double out_min, double out_max){
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void right_motor_command(double value){
  setSpeed( (int)  map(value, -1.0,1.0, 45.0, 145.0),1);
}

void left_motor_command(double value){
  setSpeed( (int)  map(value, -1.0,1.0, 45.0, 145.0),2);
}

void vertical_motor_command(double value){
  setSpeed( (int) map(value, -1.0,1.0, 45.0, 145.0),3); 
}

