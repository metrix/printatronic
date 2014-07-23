// TetraDice Control FW
//   by Morgan Redfield (morgan@metrix.net)
//
// read an accelerometer and change LED colors based on
// acceleration readings
//
// relies on Adafruit_ADXL345 and Adafruit_Sensor libraries


#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

#define LEFT_LED 4
#define RIGHT_LED 5

/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

int led_pin = A6;
boolean led_on;
boolean accel_ready;
void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)
  
  pinMode(led_pin, OUTPUT);
  accel_ready = true;
  if(!accel.begin())
  {
    accel_ready = false;
  }
    
  accel.setRange(ADXL345_RANGE_2_G);
  
  pinMode(led_pin, OUTPUT);
  led_on = false;
}

void loop()
{
  /* Get a new sensor event */ 
  sensors_event_t event;
  
  if (accel_ready) {
    // get the accel data
    accel.getEvent(&event);
  } else {
   // no sensor, so just light something up
   event.acceleration.x = -9;
   event.acceleration.y = -9;
   event.acceleration.z = -9; 
  }
  
  // TODO: determine orientation based on accel
  if (event.acceleration.x < -8) { // accelerometer is vertial
      set_remote_leds(1);
  } else if (event.acceleration.z < -6) {
      set_remote_leds(2);
  } else if (event.acceleration.y > 6) {
      set_remote_leds(3);
  } else {
      set_remote_leds(4);
  }

  digitalWrite(led_pin, HIGH);
  delay(50);
  digitalWrite(led_pin, LOW);
  delay(50);
}

void set_remote_leds(int color){    
    Wire.beginTransmission(RIGHT_LED);
    Wire.write(0x00);
    switch (color) {
      case 1:
        Wire.write(0x01); // red
        Wire.write(0x00); // grn
        Wire.write(0x00); // blu
      break;
      case 2:
        Wire.write(0x00); // red
        Wire.write(0x01); // grn
        Wire.write(0x00); // blu      
      break;
      case 3:
        Wire.write(0x00); // red
        Wire.write(0x00); // grn
        Wire.write(0x01); // blu
      break;
      default:
        Wire.write(0x01); // red
        Wire.write(0x01); // grn
        Wire.write(0x00); // blu     
      break;    
    }
    Wire.endTransmission();    

    Wire.beginTransmission(LEFT_LED);
    Wire.write(0x00);
    switch (color) {
      case 1:
        Wire.write(0x01); // red
        Wire.write(0x00); // grn
        Wire.write(0x00); // blu
      break;
      case 2:
        Wire.write(0x00); // red
        Wire.write(0x01); // grn
        Wire.write(0x00); // blu      
      break;
      case 3:
        Wire.write(0x00); // red
        Wire.write(0x00); // grn
        Wire.write(0x01); // blu
      break;
      default:
        Wire.write(0x01); // red
        Wire.write(0x01); // grn
        Wire.write(0x00); // blu     
      break;    
    }
    Wire.endTransmission();  
}
