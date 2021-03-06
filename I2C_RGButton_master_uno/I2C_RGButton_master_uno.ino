// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

#define RGB_ADDR   0x05              // 7 bit I2C address for DS1621 temperature sensor
#define BUTT_ADDR 0x06

int led_pin = 1;
boolean red_on;
boolean grn_on;
boolean blu_on;


void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)

  pinMode(led_pin, OUTPUT);
  red_on = false;
  blu_on = false;
  grn_on = false;
}

void loop()
{
    Wire.beginTransmission(BUTT_ADDR);
    Wire.write(0x00);
    Wire.endTransmission();
    Wire.requestFrom(BUTT_ADDR, 1);
    if (Wire.available() && Wire.read()) {
      toggle_remote_led('r');
    }
}

void toggle_remote_led(char color){  
  if (color == 'r') {
    red_on = !red_on;
    if (red_on) {
      Wire.beginTransmission(RGB_ADDR);
      Wire.write(0x00);
      Wire.write(0x01);
      Wire.endTransmission(); 
    } else {
      Wire.beginTransmission(RGB_ADDR);
      Wire.write(0x00);
      Wire.write(0x00);
      Wire.endTransmission();
    }
  } else if (color == 'b') {
    blu_on = !blu_on;
    if (blu_on) {
      Wire.beginTransmission(RGB_ADDR);
      Wire.write(0x01);
      Wire.write(0x01);
      Wire.endTransmission(); 
    } else {
      Wire.beginTransmission(RGB_ADDR);
      Wire.write(0x01);
      Wire.write(0x00);
      Wire.endTransmission();
    }
  } else if (color == 'g') {
    grn_on = !grn_on;
    if (grn_on) {
      Wire.beginTransmission(RGB_ADDR);
      Wire.write(0x02);
      Wire.write(0x01);
      Wire.endTransmission(); 
    } else {
      Wire.beginTransmission(RGB_ADDR);
      Wire.write(0x02);
      Wire.write(0x00);
      Wire.endTransmission();
    }
  }
}
