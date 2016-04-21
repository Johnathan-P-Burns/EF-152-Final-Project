/* 
	FPS_Enroll.ino - Library example for controlling the GT-511C3 Finger Print Scanner (FPS)
	Created by Josh Hawley, July 23rd 2013
	Licensed for non-commercial use, must include this license message
	basically, Feel free to hack away at it, but just give me credit for my work =)
	TLDR; Wil Wheaton's Law

	This sketch will attempt to identify a previously enrolled fingerprint.
*/

#include "FPS_GT511C3.h"
#include "SoftwareSerial.h"

#define BUTTON 2
#define ALLCOOLLED 3
#define PANICLED 8
#define BUZZER 9
#define MOTIONSENSOR 10

// Hardware setup - FPS connected to:
//	  digital pin 4(arduino rx, fps tx)
//	  digital pin 5(arduino tx - 560ohm resistor fps tx - 1000ohm resistor - ground)
//		this brings the 5v tx line down to about 3.2v so we dont fry our fps

FPS_GT511C3 fps(4, 5);
bool alarm = false;
int count = 0;

void setup()
{
	Serial.begin(9600);
	delay(100);
	fps.Open();
	fps.SetLED(true);

        pinMode(BUTTON, INPUT);
        pinMode(ALLCOOLLED, OUTPUT);
        pinMode(PANICLED, OUTPUT);
        pinMode(BUZZER, OUTPUT);
        pinMode(MOTIONSENSOR, INPUT);
}

void loop()
{

	// Identify fingerprint test
	if (fps.IsPressFinger())
	{
		fps.CaptureFinger(false);
		int id = fps.Identify1_N();
		if (id <200)
		{
			Serial.print("Verified ID:");
			Serial.println(id);
                        alarm = false;
       		}
		else
		{
			Serial.println("Finger not found");
                        alarm = true;
		}
	}
	else
	{
		Serial.println("Button: " + String(digitalRead(BUTTON)));
                Serial.println("Motion: " + String(digitalRead(MOTIONSENSOR)));
	}

        if(digitalRead(BUTTON) == HIGH || digitalRead(MOTIONSENSOR) == HIGH) {
          alarm = true;
        }

        //see if we should panic
        if(alarm) {
          //PANIC TIME BOYS
          panic();
          
        } else {
          //Life is good, no bugs
          if(count == 10) {
            count = 0;
            digitalWrite(ALLCOOLLED, HIGH);
            delay(100);
            digitalWrite(ALLCOOLLED, LOW);
          } else {
            count++;
            delay(100);
          }
        }
}


void panic() {
  tone(BUZZER, 600);
  for(int i = 0; i != 3; i++) {
    digitalWrite(PANICLED, HIGH);
    delay(100);
    digitalWrite(PANICLED, LOW);
    delay(100);
  }
  noTone(BUZZER);
  delay(500);
}
