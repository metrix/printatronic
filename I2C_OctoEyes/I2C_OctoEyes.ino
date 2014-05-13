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

int led_pin = A6;
boolean led_on;

void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)
  
  pinMode(led_pin, OUTPUT);
  led_on = false;
}

void loop()
{
  toggle_remote_led();

  digitalWrite(led_pin, HIGH);
  delay(500);
  digitalWrite(led_pin, LOW);
  delay(500);
}

void toggle_remote_led(){
  led_on = !led_on;
  
  if (led_on) {
    Wire.beginTransmission(RIGHT_LED);
    Wire.write(0x00);
    Wire.write(0x01);
    Wire.endTransmission();    

    Wire.beginTransmission(LEFT_LED);
    Wire.write(0x00);
    Wire.write(0x01);
    Wire.endTransmission();  

  } else {
    Wire.beginTransmission(RIGHT_LED);
    Wire.write(0x00);
    Wire.write(0x00);
    Wire.endTransmission();
    
    Wire.beginTransmission(LEFT_LED);
    Wire.write(0x00);
    Wire.write(0x00);
    Wire.endTransmission();
  }
}
