/*

alarm system

keep your stuff guarded.
make it available at specific time of day
else sound an alarm
uses a photosensor to check for light.
if there is light, that means the box is open
*/





// Time lib
// --------------------
#include <Time.h>
#include <TimeAlarms.h>

int waitTime = 10; // wait 30 seconds before being able to open
int openTime = 10; // open for 30 seconds
int closeCountdown = 5; // as the time limit comes to close, give the user a heads up
int counter = 0;
boolean canOpen = false;


// Audio stuffs
// --------------------
#include "pitches.h"

int buzz = NOTE_C4;
int buzzDuration = 4;


// Light threshold
// -------------------
int threshold = 50;


// Arduino Pins
// --------------------
const int speaker = 8;
const int photoResistor = A0;
const int pressureSensor = A1;

const int red = 12;
const int yellow = 11;
const int green = 10;





void setup() {
  
  Serial.begin(9600);
 
//  pinMode(red, OUTPUT);
//  pinMode(yellow, OUTPUT);
//  pinMode(green, OUTPUT); 
  
  buzzer();
}

void loop() {

  // get the time
  counter = now();

  if(counter > waitTime) {
    canOpen = true;
    
//    if(counter > waitTime + (openTime - closeCountdown)) {
//      Serial.println(closeCountdown);
//      closeCountdown--;
//    }
  }
  
  if(counter > waitTime + openTime) {
    canOpen = false;
  }
  
  
  
  // get light value
  int lightReading = analogRead(photoResistor);
  
  // if there is light, the box is open
  if(lightReading > threshold) {
    if(!canOpen) alarm();
  }
  
  
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  int sensorValue = analogRead(pressureSensor);
  Serial.println(sensorValue);
//  
//  float voltage = sensorValue * (5.0 / 1023.0);
  
  
  // ----------
  delay(250);
}

void buzzer() {
  int noteDuration2 = 1000/buzzDuration;

  tone(speaker, buzz, noteDuration2);
  delay(noteDuration2 * 1.30); // to distinguish the notes, set a minimum time between them.

  noTone(speaker); // stop the tone playing:  
}


void alarm() {
  turnOn(13);
  delay(100);
  buzzer();
  delay(100);
  turnOff(13);
}


// convenience functions
// ===================================
void turnOn(int led) {digitalWrite(led, HIGH);}
void turnOff(int led) {digitalWrite(led, LOW);}

