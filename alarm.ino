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

#define TIME_MSG_LEN  11   // time sync to PC is HEADER followed by Unix time_t as ten ASCII digits
#define TIME_HEADER  'T'   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message 




// Audio stuffs
// --------------------
#include "pitches.h"

// notes in the melody:
//int melody[] = {
//  NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};
//
//// note durations: 4 = quarter note, 8 = eighth note, etc.:
//int noteDurations[] = {
//  4, 8, 8, 4,4,4,4,4 };
int melody[] = {
  NOTE_C4};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4};

int buzz = NOTE_C4;
int buzzDuration = 4;



// Arduino Pins
// --------------------
int speaker = 8;
int photoResistor = A0;








void setup() {
  
  Serial.begin(9600);
  
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 1; thisNote++) {
//  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/noteDurations[thisNote];
    tone(8, melody[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}

void loop() {

  int lightReading = analogRead(photoResistor);
//  Serial.println(lightReading);
  
  int threshold = 300;
  // if there is light, the box is open
  if(lightReading > threshold) {
    Serial.println("light is on");
//    Serial.println("box is open");
    buzzer();
  } else if(lightReading < threshold) {
    Serial.println("light is off");
  }
  
  
  
//  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
//  int sensorValue = analogRead(A0);
//  float voltage = sensorValue * (5.0 / 1023.0);
  
  // Print out the value you read:
//  Serial.print(sensorValue);
//  Serial.println(voltage);
//  if(sensorValue > 0) {
//    Serial.println("touchh");
////    Serial.print(sensorValue);
//  }
  // Wait 100 milliseconds
//  delay(100);
  
  
  
  // ----------
  delay(250);
}

void buzzer() {
  Serial.println("buzzzzzz");
  int noteDuration2 = 1000/buzzDuration;

  tone(speaker, buzz, noteDuration2);
  delay(noteDuration2 * 1.30); // to distinguish the notes, set a minimum time between them.

  noTone(speaker); // stop the tone playing:  
}
