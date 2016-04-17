#include <Wire.h> 
#include <Servo.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_L3GD20.h>
#include <Adafruit_ADXL345_U.h>
#include <Adafruit_HMC5883_U.h>
#include <Adafruit_BMP085.h>

//Motor 
#define INIT_SPEED 35
#define STOP_SPEED 90
#define STEP 5

//With the back in fornt of you
Servo r_motor,l_motor,vertical_motor; //; motor 1, 2 and 3 in this order

// Buffer to store incoming commands from serial port
String inData;
int index,i = 0;
String number; 

//IMU 
/* Assign a unique ID to this sensor at the same time */
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(1);
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
Adafruit_L3GD20 gyro;
Adafruit_BMP085 bmp;

double gyrox, gyroy, gyroz;
double accx, accy, accz;  
double magx, magy, magz; 
double pressure, temp;  

//comunication 
String buffer  = "";         // a string to hold incoming data
boolean is_buffer_completed = false;  // whether the string is complete

void setup() 
{
  Serial.begin(115200);
  
  if(!gyro.begin(gyro.L3DS20_RANGE_250DPS, gyro.L3DS20_ADDRESS_L3G4200D) && !accel.begin() && !mag.begin() && !bmp.begin())
  {
    Serial.println("unable to initialize the sensors!");
    while (1);
  }
  //config sensors
  accel.setRange(ADXL345_RANGE_16_G);

  //Pin the motors 
  r_motor.attach(2); 
  l_motor.attach(5); 
  vertical_motor.attach(8); 
  
  //start the motors 
  arm();

  delay(1000);
}

void loop() 
{
  if (is_buffer_completed) {
    process_buffer(buffer);
    buffer = "";
    is_buffer_completed = false;
  }
}




