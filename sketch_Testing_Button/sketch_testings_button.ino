#include <LEDFader.h>

/*
 * Controls several LEDs for different mask lighting effects
 */
  // Define Pins
  #define LED_PIN 9     // Set pin 9 as the LED
  #define BUTTON_PIN 2  // Set Pin 2 as the button input
  
  // Define fader pin options
  #define FADE_TIME 4000  // Fade for 4 seconds, each direction
  #define DIRECTION_UP 1
  #define DIRECTION_DOWN -1

  const int FADE_BRIGHTNESS_MIN = 2; // Minimum value to fade down to ... setting to low makes it look somewhat "blinky"
  const int FADE_BRIGHTNESS_MAX = 180; // Maximum value to fade up to ... setting to high makes it spend too much time at a bright level
  int direction = DIRECTION_UP; // Start off fading up
  
  LEDFader ledFader; // Define an LED fader
  
  // Define blink pin timers
  long lastBlinkMillis = 0; // Store last time blink LEDs were updated

  // Set initial led pin state
  int ledPinState = LOW;
  
  // Blink pin intervals (milliseconds)
  const int SLOW_INTERVAL = 1000;
  const int MED_INTERVAL = 500;
  const int FAST_INTERVAL = 250;

  // Random blink time options (milliseconds)
  // Note, anything less than 30ms is typically not perceptable
  const int RANDOM_OFF_MIN = 30;
  const int RANDOM_OFF_MAX = 250;
  const int RANDOM_ON_MIN = 30;
  const int RANDOM_ON_MAX = 500;

  //Initialize random on and off
  int randomDelayOff = random(1, 250);
  int randomDelayOn = random(1, 500);

  //Initialize Button
  int buttonPushCounter = 0;   // counter for the number of button presses
  int buttonState = 0;         // current state of the button
  int lastButtonState = 0;     // previous state of the button

void setup()
{
  // Initialize random number generator with unique seed
  randomSeed(analogRead(0));
  
  // Setup Fader Pin
  ledFader = LEDFader(LED_PIN); // Create new LED Fader on LED pin

  // Set pin modes
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);

  ledPinState = LOW;

  // Start serial communication
  Serial.begin(9600);
}

void loop()
{
  // read the pushbutton input pin:
  buttonState = digitalRead(BUTTON_PIN);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button
      // went from off to on:
      buttonPushCounter++;
      Serial.println("on");
      Serial.print("number of button pushes:  ");
      Serial.println(buttonPushCounter);
    } else {
      // if the current state is LOW then the button
      // went from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state,
  // for next time through the loop
  lastButtonState = buttonState;

  int ledMode = (buttonPushCounter % 6);

  switch(ledMode)
  {
    case 0:
      // Constant mode
      digitalWrite(LED_PIN, HIGH);
      break;
    case 1:
      //
      RunFadePin();
      break;
    case 2:
      //
      Blink(SLOW_INTERVAL);
      break;
    case 3:
      //
      Blink(MED_INTERVAL);
      break;
    case 4:
      //
      Blink(FAST_INTERVAL);
      break;
    case 5:
      //
      BlinkRandom();
      break;
  }
}

void RunFadePin()
{
  ledFader.update();

  // LED no longer fading, switch direction
  if (!ledFader.is_fading())
  {
    // Fade down
    if (direction == DIRECTION_UP)
    {
      ledFader.fade(FADE_BRIGHTNESS_MIN, FADE_TIME);
      direction = DIRECTION_DOWN;
    }
    // Fade up
    else
    {
      ledFader.fade(FADE_BRIGHTNESS_MAX, FADE_TIME);
      direction = DIRECTION_UP;
    }
  }
}

void Blink(int interval)
{
  unsigned long currentMillis = millis();

  if (currentMillis - lastBlinkMillis >= interval)
  {
    // save the last time we blinked the LED
    lastBlinkMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledPinState == LOW)
    {
      ledPinState = HIGH;
      //Serial.println("on");
    }
    else
    {
      ledPinState = LOW;
      //Serial.println("off");
    }

    // set the LED with the ledState of the variable:
    digitalWrite(LED_PIN, ledPinState);
  }
}

void BlinkRandom()
{
  unsigned long currentMillis = millis();

  if (ledPinState == LOW)
  {
    if (currentMillis - lastBlinkMillis >= randomDelayOff)
    {
      // OFF time is up, time to turn the LED back on
      // Set our ON duration
      randomDelayOn = random(RANDOM_ON_MIN, RANDOM_ON_MAX);
      
      // Turn the LED back on
      digitalWrite(LED_PIN, HIGH);

      // Reset the pin state
      ledPinState = HIGH;

      // Update previous ms counter
      lastBlinkMillis = currentMillis;
    }

    // Time isn't up yet
    return;
  }

  if (ledPinState == HIGH)
  {
    if (currentMillis - lastBlinkMillis >= randomDelayOn)
    {
      // ON time is up, time to turn the LED back off
      // Set our OFF duration
      randomDelayOff = random(RANDOM_OFF_MIN, RANDOM_OFF_MAX);

      // Turn the LED back off
      digitalWrite(LED_PIN, LOW);
      
      // Reset the pin state
      ledPinState = LOW;

      // Update previous ms counter
      lastBlinkMillis = currentMillis;
    }
  }
 }

