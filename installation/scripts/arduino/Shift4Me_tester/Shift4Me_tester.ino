// Shift4Me test script v.1.0 (for schematic may 14 2019)
// written to control an Arduino Nano board (or 100% compatible) 
// june 19 2019
// author: Jan Oelbrandt / Shift4me.com
// contact: info@shift4me.com - +3254503538

// THIS SOFTWARE IS DISTRIBUTED UNDER A GPL LICENSE - see bottom of script for all terms and conditions
///////////////////////////////////////////////////
// USER-CONFIGURABLE PARAMETERS
  // change only the figures. Make sure there you end each line with ";" 
  // READ the NOTES below to see what each parameter does, before you change anything
  
#include <Servo.h>
Servo myservo;


int ButtonDebounce = 250;
int buttonRed = 9;  // to force to a smaller sprocket
int buttonGreen = 8; // to force to a larger sprocket
int Sensor = 7;     // reads the hall sensor on/off value
int buttonBypass = 2; // reads the Bypass button
//int switchHigher = 6; // preset-switch (faster pedal rotation desired)
//int switchLower = 5;  // preset-switch (slower pedal rotation desired)
int buzzer = 12; //buzzer to arduino pin 12
boolean SensorOverride = false;
int ledPin = 4; // led-connection (on/off and battery status)
//int ledPinShift = 3; // led-connection (shift warning)
int  sensorValue; // analog voltage sensing at pin Vin
float  Voltage; // convert sensorvalue voltage to 5V max 
int Loops = 0;

void setup() {
myservo.attach(10);  // attaches the servo 
pinMode(buttonRed, INPUT_PULLUP); // connects the manual override button (shift to smaller sprocket)
pinMode(buttonGreen, INPUT_PULLUP); // connects the manual override button (shift to larger sprocket)
pinMode(buttonBypass, INPUT_PULLUP); // connects the bypass button
pinMode(Sensor, INPUT_PULLUP);    // connection of the hall sensor
pinMode(ledPin, OUTPUT); // led-connection (on/off and battery status)
pinMode(buzzer, OUTPUT); // Set buzzer output
Serial.begin(9600);
}

void loop() 
{
   Serial.println();
  if(Loops >1) { 
    Loops= 0;
  }

   if(digitalRead(buttonRed)==LOW)
    {
    Serial.println("manual switch position: pull cable");
    }
   if(digitalRead(buttonGreen)==LOW)
    {
    Serial.println("manual switch position: release cable");
    }
//   if(digitalRead(buttonGreen)==HIGH && digitalRead(buttonRed)==HIGH) {
//    Serial.println("manual switch position: OFF");
//   }

sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 9V):
Voltage = sensorValue * (8.4 / 1023.0);

// Serial.println();
  Serial.print("battery voltage: ");
      Serial.println(Voltage);
      
    
// test buzeer and LEDS
 
if(Loops == 1) {
  Serial.println("power LED should be flashing");
digitalWrite(ledPin, HIGH); delay(100);      digitalWrite(ledPin, LOW); delay(100); 
  digitalWrite(ledPin, HIGH); delay(100);      digitalWrite(ledPin, LOW); delay(100); 
  digitalWrite(ledPin, HIGH); delay(100);      digitalWrite(ledPin, LOW); delay(100); 
  digitalWrite(ledPin, HIGH); delay(100);      digitalWrite(ledPin, LOW); delay(100); 
  digitalWrite(ledPin, HIGH); delay(100);      digitalWrite(ledPin, LOW); delay(100); 
  digitalWrite(ledPin, HIGH); delay(100);      digitalWrite(ledPin, LOW); delay(100); 
  Loops = Loops + 1;
}  
if(Loops == 0) {
  Serial.println("buzzer test");
  tone(buzzer, 3000); // Send buzz...
  delay(75);       
  noTone(buzzer);     // Stop sound...
  delay(50);  
  tone(buzzer, 2000); // Send buzz...
  delay(75);    
  noTone(buzzer);     // Stop sound...
  delay(50);  
   tone(buzzer, 4000); // Send buzz...
  delay(150);    
  noTone(buzzer);     // Stop sound...
  Loops = Loops + 1;
}
if(digitalRead(buttonBypass)==LOW || digitalRead(Sensor)==LOW) {
  

    if(digitalRead(buttonBypass)==LOW){
      Serial.println("BYPASS button is active");
    }
    if(digitalRead(Sensor)==LOW) {
    Serial.println("HALL SENSOR has sent a trigger");
    }
  }
  else {
    delay(500); 
  }

} // end of loop
//        This program is free software: you can redistribute it and/or modify
//        it under the terms of the GNU General Public License v.3 as published by
//        the Free Software Foundation.

//        This program is distributed in the hope that it will be useful,
//        but WITHOUT ANY WARRANTY; without even the implied warranty of
//        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//        GNU General Public License for more details.

//        For a full copy of the GNU General Public License
//        see <http://www.gnu.org/licenses/>
