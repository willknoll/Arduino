#include <Curve.h>
#include <LEDFader.h>

  const byte BLINKPIN = 8; //Set Pin 8 as the blink LED
  const byte CONSTPIN = 9; //Set Pin 9 as the constant LED
  
  long previousMillis = 0;
  long interval;
  long longOn;
  
  byte delayedoff; //Create a Integer variable named delayedoff
  byte delayedon; //Create a Integer variable named delayedon
  //If you want to go higher than 255 you must change from "byte" to "int"

  // Create new LED Fader on pin CONSTPIN
  LEDFader led = LEDFader(CONSTPIN);

void setup() {
  // put your setup code here, to run once:


  //Set outputs
  pinMode(BLINKPIN, OUTPUT);
  pinMode(CONSTPIN, OUTPUT);

  // Fader
  // Fade from 0 - 255 in 3 seconds
  led.set_value(0);
  led.fade(255, 3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis();


  //randomize the interval
  interval = random(1000, 5000);

  if (currentMillis - previousMillis > interval)
  {
    //every few seconds, stay on for longer
    longOn = random (1, 3);
    digitalWrite(BLINKPIN, HIGH);
    delay(longOn * 1000);

    previousMillis = millis();
  }

  led.update();
  
  // Turn on the constant LED
  //digitalWrite(CONSTPIN, HIGH); //Turn on the constant LED

  //digitalWrite(BLINKPIN, HIGH); //Turn on the Blink LED
  
  delayedoff = random(1, 250); //Generates a random delay and assigns it to the variable named delayed
  delayedon = random(1, 500); //Generates a random delay and assigns it to the variable named 

  
  digitalWrite(BLINKPIN, HIGH); //We turn on the BLINK LED
  delay(delayedon); //random delay on time
  digitalWrite(BLINKPIN, LOW); //We turn off the BLINK LED
  delay(delayedoff); //Random delay off time
}
