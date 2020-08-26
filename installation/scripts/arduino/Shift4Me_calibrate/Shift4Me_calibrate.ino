

  
#include <Servo.h>      // include the servo working (send pulses)

Servo myservo;  // create servo object to control a servo

int buttonMin = 9;      // connects the LOWER-button to pin 9
int buttonMax = 8;      // connects the HIGHER-button to pin 8
String action = "none"; // action of servo on startup
int MS = 550;          // position of the servo on startup
int AmountMs = 50;      // travel of the servo per button press
int ServoMax = 2400;    // max position of the servo
int ServoMin = 500;     // min position of the servo
int ledPin = 4; // led-connection (on/off and battery status)
int  sensorValue; // analog voltage sensing at pin Vin
float  Voltage; // convert sensorvalue voltage to 5V max


void setup() 
{

MS = ServoMin;
  
myservo.attach(10);  // attaches the servo on pin 10 to the servo object
pinMode(buttonMin, INPUT_PULLUP); 
pinMode(buttonMax, INPUT_PULLUP);
Serial.begin(9600);   // active readout
myservo.writeMicroseconds(MS); // send pulses to the servo
pinMode(ledPin, OUTPUT); // led-connection (on/off and battery status)
digitalWrite(ledPin, HIGH); 
}

void loop() // master loop of the script
{
   action = "none";

   if(digitalRead(buttonMin)==LOW)  // what to do when the LOWER-button is pressed
    {
    delay(200);          // delay for button debounce
    MS = MS - AmountMs;  // lower the pulses by the pre-set amount           
    action = "Min";       // the name of this action
    }
  
   
       if(digitalRead(buttonMax)==LOW) // what to do when the HIGHER-button is pressed
    {
    delay(200);          
    MS = MS + AmountMs;
    action = "Plus";
    }
    
// display action if one of the buttons is pressed 
    if(action == "Min" || action == "Plus")
    {
        // check battery voltage
  // read the input on analog pin 0 for the batteries (2.4V and 6V in series):
sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 9V):
Voltage = sensorValue * (8.4 / 1023.0);
// flash LED if Voltage is too low
// at aprox 7V total, the 6V battery will be about 5.5V, it is too dropped to pull the servo
  if(Voltage<7){
  digitalWrite(ledPin, HIGH); 
  delay(100);      
  digitalWrite(ledPin, LOW); 
  delay(100); 
  digitalWrite(ledPin, HIGH); 
  delay(100);      
  digitalWrite(ledPin, LOW); 
  delay(100); 
  digitalWrite(ledPin, HIGH); 
  delay(100);      
  digitalWrite(ledPin, LOW); 
  delay(100); 
  digitalWrite(ledPin, HIGH); 
  // correct time because of delaying of flashing LED
 // currentMillis = currentMillis + 240;
  }
  else {
    digitalWrite(ledPin, HIGH); 
  }
      // after battery check, see if the max or min are not met
      if(MS > ServoMax){
        Serial.println("you reached the maximum of the servo");
        MS = MS - AmountMs;
      }
      else if (MS < ServoMin){
        Serial.println("you reached the minimum of the servo");
        MS = MS + AmountMs;
      }
      // if all is ok, continue
      else {
         Serial.println();

      Serial.println();
      Serial.print("servo pulsewidth: "); // display the pulse text
      Serial.print(MS);                 // display the amount
        Serial.print(" // battery voltage: ");
      Serial.println(Voltage);
        myservo.writeMicroseconds(MS);    // send the pulse to the servo
      }
      
    }
  
}
