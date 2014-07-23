// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

#define LEFT_LED 4
#define RIGHT_LED 5
#define ACCEL FIXMEFIXME

int led_pin = A6;
int x_accel;
int y_accel;
int z_accel;

void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)
  
  pinMode(led_pin, OUTPUT);
  led_on = false;
}

void loop()
{
  getAccelVals();
  
  // TODO: determine orientation based on accel
  int color = 4;
  set_remote_leds(color);

  digitalWrite(led_pin, HIGH);
  delay(50);
  digitalWrite(led_pin, LOW);
  delay(50);
}

void toggle_remote_led(int color){  
    // TODO: determine what to write to LEDs based on color
  
    Wire.beginTransmission(RIGHT_LED);
    Wire.write(0x00);
    Wire.write(0x01);
    Wire.endTransmission();    

    Wire.beginTransmission(LEFT_LED);
    Wire.write(0x00);
    Wire.write(0x01);
    Wire.endTransmission();  
}

void get_accel_vals() {
  
  
}
