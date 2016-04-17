
void read_sensors(){  
   
  /*Get a new sensor event */ 
  gyro.read();
  sensors_event_t event; 
  mag.getEvent(&event);
  accel.getEvent(&event);
  
  //Put the mag data at global var with the calibration offsets  
  magx = event.magnetic.x + 32.54;
  magy = event.magnetic.y*0.89 +20.55;
  magz = event.magnetic.z*0.91 +8.63;
  
  //Put the acc data at global var with the calibration offsets   
  accx = event.acceleration.x + 0.1602;
  accy = event.acceleration.y - 0.1612;
  accz = event.acceleration.z +1.1881;
  
  //Put the gyro data at the global var with the calibration offsets 
  gyrox = gyro.data.x - 1.4461;
  gyroy = gyro.data.y + 0.1216;
  gyroz = gyro.data.z + 0.3217;
  
  //Pressure and temperature 
  temp = bmp.readTemperature();  
  //convert to decibars 
  pressure = bmp.readPressure()*0.0001; 

  
}

void send_beagle(){
   //To anwser Request with <;;;> protocol 11 reads. 
  Serial.print("<");
  Serial.print(gyrox); Serial.print(";");
  Serial.print(gyroy); Serial.print(";");
  Serial.print(gyroz); Serial.print(";");
  Serial.print(accx);Serial.print(";");
  Serial.print(accy); Serial.print(";");
  Serial.print(accz); Serial.print(";");
  Serial.print(magx); Serial.print(";");
  Serial.print(magy); Serial.print(";");
  Serial.print(magz); Serial.print(";");
  Serial.print(pressure); Serial.print(";");
  Serial.print(temp); Serial.print(";");
  Serial.println(">");
}
