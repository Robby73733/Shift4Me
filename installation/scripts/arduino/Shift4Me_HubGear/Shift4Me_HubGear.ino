// Shift4Me script v.1.0 (for schematic feb 19 2020)
// written to control an Arduino Nano board (or 100% compatible) 
// feb 19, 2020
// original author: Jan Oelbrandt / Shift4me.com
// contact: info@shift4me.com - +3254503538

// THIS SOFTWARE IS DISTRIBUTED UNDER A GPL LICENSE - see bottom of script for all terms and conditions
///////////////////////////////////////////////////
// there are a bunch of USER CONFIGURABLE PARAMETERS on the three TABS
// please the notes on the seperate TABS to see what each parameter does, before you change anything

// DO NOT CHANGE THE FOLLOWING CODE (unless you know what you're doing)

int Frequency;
int ToleranceHigherGear;
int ToleranceLowerGear;
int ChangeDelayHeavy;
int ChangeDelayLight;
int HiLoAmount;
int MaxTurns;
String UseBuzzer;
String UseLed;

#include <Servo.h>
Servo myservo;

int RPM;
int FrequencyCount;
int ButtonDebounce = 250;
int ButtonDebounceShort = 50;
//int ReleaseTime;
unsigned long previousMillis = 0;
int pos;  
int GearAmount;
int CorrectAmount;
int prev_pos;
int ActiveGear;
int buttonRed = 9;  // to force to a smaller sprocket
int buttonGreen = 8; // to force to a larger sprocket
int Sensor = 7;     // reads the hall sensor on/off value
int buttonBypass = 2; // reads the Bypass button
int buzzer = 12; //buzzer to arduino pin 12
String action = "none";
unsigned long currentMillis;
unsigned long refTime;
boolean SensorOverride = false;
int correctFrequency = 0;
int ledPin = 4; // led-connection (on/off and battery status)
int  sensorValue; // analog voltage sensing at pin Vin
float  Voltage; // convert sensorvalue voltage to 5V max
int Cycles = 0;
unsigned long pressTime;
String mode;
String Act = "no";

void setup() {
myservo.attach(10);  // attaches the servo 
pinMode(buttonRed, INPUT_PULLUP); // connects the manual override button (shift to smaller sprocket)
pinMode(buttonGreen, INPUT_PULLUP); // connects the manual override button (shift to larger sprocket)
pinMode(buttonBypass, INPUT_PULLUP); // connects the bypass button
pinMode(Sensor, INPUT_PULLUP);    // connection of the hall sensor
pinMode(ledPin, OUTPUT); // led-connection (on/off and battery status)
pinMode(buzzer, OUTPUT); // Set buzzer output
Serial.begin(9600);
// load derailleur data
  CorrectAmount = LoadSprocketWidth("CorrectAmount",0);
  GearAmount = LoadSprocketWidth("GearAmount",0);
  pos = LoadSprocketWidth("GetGear",99);
  ActiveGear = LoadSprocketWidth("StartingGear",0);
prev_pos = pos;
// load preferences
  Frequency = LoadRidePrefs("Frequency");
  ToleranceHigherGear = LoadRidePrefs("ToleranceHigherGear");
  ToleranceLowerGear = LoadRidePrefs("ToleranceLowerGear");
  ChangeDelayHeavy = LoadRidePrefs("ChangeDelayHeavy");
  ChangeDelayLight = LoadRidePrefs("ChangeDelayLight");
  HiLoAmount = LoadRidePrefs("HiLoAmount");
  MaxTurns = LoadRidePrefs("MaxTurns");
  UseBuzzer = LoadSignalPrefs("UseBuzzer");
  UseLed = LoadSignalPrefs("UseLed");
//myservo.writeMicroseconds(pos);
PerformReset();
Serial.print("Starting in position: ");
Serial.print(pos);
Serial.print(", gear number ");
Serial.println(ActiveGear);

unsigned long currentMillis = millis();
Serial.println(currentMillis);
previousMillis = currentMillis;
refTime = currentMillis;
digitalWrite(ledPin, HIGH); 

}

void loop() 
{

// correct if button actions (MANUAL OVERRIDE)
   if(digitalRead(buttonRed)==LOW)
    {
    action = "less";
    SensorOverride = true;
    delay(ButtonDebounce);
    }
   if(digitalRead(buttonGreen)==LOW)
    {
    action = "more";  
    SensorOverride = true;
    delay(ButtonDebounce);
    }
    if(digitalRead(buttonBypass)==LOW) {
      pressTime = millis();
     // delay(ButtonDebounce);
      BypassButton(pressTime);
Serial.print("mode: ");
Serial.println(mode);
    if(mode == "bypass") {
    action = "none";  
    SensorOverride = true;
    }
    else if(mode == "reset") {
      SensorOverride = true;
      action = "reset";  
    }
    
    }
    else {
      mode = "normal";
    }
// if max Cycles is exceeded
   if(Cycles > MaxTurns) {
  //  action = "less";
    SensorOverride = true;
    Serial.println("MAX TURNS EXCEEDED");
    //  Serial.println(RPM);
   }

// count rotation
currentMillis = millis();

if(digitalRead(Sensor)==LOW || SensorOverride == true)
{
    if(digitalRead(Sensor)==LOW) {
Serial.println("hall triggered");
      Cycles = Cycles + 1;
     //currentMillis = millis();
     FrequencyCount = currentMillis - previousMillis;
      delay(ButtonDebounce);
      previousMillis = currentMillis;    
      // 1000 milliseconds, 60 seconds
      RPM = 60000/FrequencyCount;
    //    Serial.print("actual RPM: ");
    //  Serial.println(RPM);

// if RPM exceeds limits

  // turning too fast, so move to smaller sprocket
if((RPM - ToleranceHigherGear)>(Frequency)) {
  action = "less";
  // Serial.println("HALL TRIGGERED less");
  }
  // turning too slow, so move to larger sprocket
  else if((RPM + ToleranceLowerGear)<(Frequency)) {
      action = "more";
    //  Serial.println("HALL TRIGGERED more");   
 }
 else {
  action = "none";
 }


// if RPM is too low (stalling): take no action
      if(RPM < 15) {
         action = "none";
         Serial.println("STALLING");
         // RESET
          RPM = 0;
          refTime = currentMillis;
          Cycles = 0;
      }   
// if RPM is too high (pedal stalls at hall sensor): take no action
       if(RPM > 200) {
         action = "none";
      }   
     
    }
   
// process action if ChangeDelay time has passed since last change
// if buttonBypass is not pushed
if(  ( (refTime + ChangeDelayHeavy)<currentMillis || SensorOverride == true) && digitalRead(buttonBypass)==HIGH ) {


if(action == "less") {
  Act = "yes";
  // move to heavier gear
  ActiveGear = ActiveGear-1;
  pos = LoadSprocketWidth("GetGear",ActiveGear);
  

  // correct if below zero gear
  if (ActiveGear < 0) { ActiveGear = 0; action = "none"; pos = LoadSprocketWidth("GetGear",ActiveGear); }
  else{

pos = pos + CorrectAmount;
   if(UseLed == "yes") {
    digitalWrite(ledPin, HIGH);
   }
   if(UseBuzzer == "yes"){
BuzzerLightGear ();
        }
     }
  
}
}
if(  ( (refTime + ChangeDelayLight)<currentMillis || SensorOverride == true) && digitalRead(buttonBypass)==HIGH ) {
  
if(action == "more") {
  Act = "yes";
  // move to lighter gear
   ActiveGear = ActiveGear+1;
   pos = LoadSprocketWidth("GetGear",ActiveGear);
     // correct if above derailleur maximum
  if (ActiveGear > (GearAmount-1)) { ActiveGear = GearAmount-1; action = "none";   pos = LoadSprocketWidth("GetGear",ActiveGear);
 // pos = pos + CorrectAmount;
  }
  else {
    if(UseLed == "yes") {
    digitalWrite(ledPin, HIGH);
   }
     if(UseBuzzer == "yes"){
    // send audio signal for light gear
BuzzerHeavyGear ();
     }
  }
  
}
if(mode == "reset") {
PerformReset();
Act = "yes";
}
// new feb 24
if(mode == "bypass") {
delay(5000);
   Act = "no";
}
} // end of Changedelay cycles
  if(Act == "yes"){ 
    Act = "no";
     myservo.writeMicroseconds(pos);  

   // Correction to release tension on cable
      if(action == "more")  {
         }
      if(action == "less")  {
      pos = pos - CorrectAmount;
         delay(300);
         }
      myservo.writeMicroseconds(pos);

         // display action every ChangeDelay and reset all
  // check battery voltage
  // read the input on analog pin 0 for the batteries (2.4V and 6V in series):
sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 9V):
Voltage = sensorValue * (8.4 / 1023.0);
// flash LED if Voltage is too low
// at aprox 7V total, the 6V battery will be about 5.5V, it is too dropped to pull the servo
  if(Voltage<7){
  LowBatteryWarning();
  }
  else {
    digitalWrite(ledPin, HIGH); 
  }
 Serial.println();
  Serial.print("battery voltage: ");
      Serial.println(Voltage);
      Serial.println();
      Serial.print("measured RPM: ");
      Serial.println(RPM);
      Serial.print("target RPM: ");
      Serial.println(Frequency+correctFrequency);
      Serial.print("action: ");
      Serial.println(action);
      if(mode != "normal"){
        Serial.print("button mode: ");
      Serial.println(mode);
      }
      Serial.print("now in gear number: ");
      Serial.print(ActiveGear);
      Serial.print(", pos is ");
      Serial.println(pos);

    prev_pos = pos;
    action = "none";
    RPM = 0;
    refTime = currentMillis;
    Cycles = 0;
    if(SensorOverride == true){
      refTime = refTime + 5000;
      Cycles = Cycles-5;
    SensorOverride = false;
    Serial.print(" - battery voltage: ");
      Serial.println(Voltage);
    }
    
 } // end of processing
} // end of Sensor Loop 
} // end of loop
void BuzzerLightGear (){
  tone(buzzer, 2000); 
  delay(100);     
  noTone(buzzer);    
  delay(80);      
   tone(buzzer, 1500);
  delay(100);       
  noTone(buzzer);   
  delay(80);      
   tone(buzzer, 1000); 
  delay(100);       
 noTone(buzzer);    
  delay(300);        // delay to allow pedal force disengage
}
void BuzzerHeavyGear (){
  tone(buzzer, 2000); 
  delay(150);     
  noTone(buzzer);   
  delay(50);      
   tone(buzzer, 2220); 
   delay(50);       
  noTone(buzzer);   
  delay(20);     
   tone(buzzer, 2300); 
  delay(50);   
  noTone(buzzer);     
  delay(50);       
   tone(buzzer, 2220); 
   delay(50);     
   noTone(buzzer); 
  delay(400);        // delay to allow pedal force disengage
}
void LowBatteryWarning(){
   digitalWrite(ledPin, HIGH); 
  delay(100);      
  digitalWrite(ledPin, LOW); 
 // tone(buzzer, 2000); 
  delay(100); 
  digitalWrite(ledPin, HIGH); 
 // noTone(buzzer); 
  delay(100);      
  digitalWrite(ledPin, LOW); 
 // tone(buzzer, 2000); 
  delay(100); 
  digitalWrite(ledPin, HIGH); 
 // noTone(buzzer); 
  delay(100); 
  digitalWrite(ledPin, LOW); 
 // tone(buzzer, 2000); 
  delay(100); 
  digitalWrite(ledPin, HIGH); 
}
void PerformReset(){
  ActiveGear = LoadSprocketWidth("StartingGear",0);
   pos = LoadSprocketWidth("GetGear",99);
   pos = pos + CorrectAmount;
   myservo.writeMicroseconds(pos);
         delay(200);
   pos = pos - CorrectAmount;
   myservo.writeMicroseconds(pos);  
}

String BypassButton(unsigned long var){
//int pressTime2 = pressTime;
int StopSound = 0;
unsigned long ReleaseTime;
delay(ButtonDebounceShort);
 while (digitalRead(buttonBypass) == LOW)
 {
// buzz shortly for bypass
if(StopSound == 0) 
  { 
     
    if (millis()>(var+500) ) {
      noTone(buzzer); 
   //   StopSound = 1;
    }
    else {
      tone(buzzer, 500);
    }
  } 
// if button is released buzz for reset
if (millis()>(var+2500) && StopSound == 0){
  noTone(buzzer); 
  delay(100); 
  tone(buzzer, 2000); 
  delay(50); 
  noTone(buzzer); 
  delay(50); 
  tone(buzzer, 1000); 
  delay(100); 
  noTone(buzzer); 
  StopSound = 1;
  }
 }
  ReleaseTime = millis();
  noTone(buzzer); 

delay(ButtonDebounceShort);

if (( ReleaseTime-2000 )<var){
  mode = "bypass";
  return mode;
}
else
{
  mode = "reset";
  return mode;
}
}
//        This program is free software: you can redistribute it and/or modify
//        it under the terms of the GNU General Public License v.3 as published by
//        the Free Software Foundation.

//        This program is distributed in the hope that it will be useful,
//        but WITHOUT ANY WARRANTY; without even the implied warranty of
//        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//        GNU General Public License for more details.

//        For a full copy of the GNU General Public License
//        see <http://www.gnu.org/licenses/>
