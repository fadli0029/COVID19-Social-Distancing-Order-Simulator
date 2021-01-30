#include <LiquidCrystal_PCF8574.h> 
#include <Wire.h>

LiquidCrystal_PCF8574 lcd(0x27); // set the LCD address to 0x27 for a 16 chars and 2 line display

const int Trig_Pin   = 2; // the arduino pin that is connected to the Ultrasonic Sensor's TRIG pin
const int Echo_Pin   = 3; // the arduino pin that is connected to the Ultrasonic Sensor's ECHO pin
const int Buzzer_Pin = 4; // the arduino pin that is connected to the Piezo Buzzer's pin
const int Distance = 10; // this is the minimum/threshold distance, in centimeters, that will trigger the buzzer

float duration_us, distance_cm; 
//duration of the pulse measured by the ultrasonic sensor
//distance of object from the ultrasonic sensor

void setup() 
{
  Serial.begin (9600);
  Wire.begin();

  pinMode(Trig_Pin, OUTPUT);   
  pinMode(Echo_Pin, INPUT);  
  pinMode(Buzzer_Pin, OUTPUT);
  lcd.clear();         
  lcd.setBacklight(255); 
  lcd.setCursor(0,0);
}

void loop() 
{
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(Trig_Pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig_Pin, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(Echo_Pin, HIGH);
  // calculate the distance
  distance_cm = 0.017 * duration_us;

  if(distance_cm < Distance)
  {
    digitalWrite(Buzzer_Pin, HIGH); // here, what should be the condition of the Piezo Buzzer, on or off?
    lcd.print("You’re too close! Maintain social distancing."); // What do you want to print on the LCD screen
  }
  else if (distance_cm < 15)
  {
    digitalWrite(Buzzer_Pin, LOW); // here, what should be the condition of the Piezo Buzzer, on or off?
    lcd.print("You're 6ft away, good!"); // What do you want to print on the LCD screen 
  }
  
  // print the distance values to Serial Monitor
  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  delay(500);
}
