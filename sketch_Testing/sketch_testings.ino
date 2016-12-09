#include <LEDFader.h>

/*
 * Controls several LEDs for different mask lighting effects
 */
  // Define Pins
  #define LED_FADE_PIN 9       // Set pin 9 as the fade LED
  #define LED_CONSTANT_PIN 8   // Set Pin 8 as the constant LED
  #define LED_BLINK_PIN_SLOW 7 // Set Pin 7 as the slow blink LED
  #define LED_BLINK_PIN_MED 6  // Set Pin 6 as the medium blink LED
  #define LED_BLINK_PIN_FAST 5 // Set Pin 5 as the fast blink LED
  #define LED_RANDOM_PIN 4     // Set Pin 4 as the random blink LED
  
  // Define fader pin options
  #define FADE_TIME 4000  // Fade for 4 seconds, each direction
  #define DIRECTION_UP 1
  #define DIRECTION_DOWN -1

  const int FADE_BRIGHTNESS_MIN = 2; // Minimum value to fade down to ... setting to low makes it look somewhat "blinky"
  const int FADE_BRIGHTNESS_MAX = 180; // Maximum value to fade up to ... setting to high makes it spend too much time at a bright level
  int direction = DIRECTION_UP; // Start off fading up
  
  LEDFader ledFader; // Define an LED fader
  
  // Define blink pin timers
  long previousSlowMillis = 0; // Store last time slow LEDs were updated
  long previousMedMillis = 0;  // Store last time Medium LEDs were updated
  long previousFastMillis = 0; // Store last time Fast LEDs were updated
  long previousRandMillis = 0; // Store last time Random LEDs were updated

  // Set initial blink pin states
  int slow_pin_state = LOW;
  int med_pin_state = LOW;
  int fast_pin_state = LOW;
  int rand_pin_state = LOW;

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

void setup()
{
  // Initialize random number generator with unique seed
  randomSeed(analogRead(0));
  
  // Setup Fader Pin
  ledFader = LEDFader(LED_FADE_PIN); // Create new LED Fader on pin LED_FADE_PIN
  ledFader.fade(FADE_BRIGHTNESS_MAX, FADE_TIME); // Start fading right away

  // Set pin modes
  pinMode(LED_CONSTANT_PIN, OUTPUT);
  pinMode(LED_BLINK_PIN_SLOW, OUTPUT);
  pinMode(LED_BLINK_PIN_MED, OUTPUT);
  pinMode(LED_BLINK_PIN_FAST, OUTPUT);
  pinMode(LED_RANDOM_PIN, OUTPUT);

  rand_pin_state = LOW;

  // Debugging
  //Serial.begin(9600);
}

void loop()
{
  // Make sure the Constant LED is on
  digitalWrite(LED_CONSTANT_PIN, HIGH);

  // See what fader is up to
  RunFadePin();

  // Manage blinkers
  BlinkSlow();
  BlinkMedium();
  BlinkFast();
  BlinkRandom();
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

void BlinkSlow()
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousSlowMillis >= SLOW_INTERVAL)
  {
    // save the last time you blinked the LED
    previousSlowMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (slow_pin_state == LOW)
    {
      slow_pin_state = HIGH;
      //Serial.println("on");
    }
    else
    {
      slow_pin_state = LOW;
      //Serial.println("off");
    }

    // set the LED with the ledState of the variable:
    digitalWrite(LED_BLINK_PIN_SLOW, slow_pin_state);
  }
}

void BlinkMedium()
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMedMillis >= MED_INTERVAL)
  {
    // save the last time you blinked the LED
    previousMedMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (med_pin_state == LOW)
    {
      med_pin_state = HIGH;
    }
    else
    {
      med_pin_state = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(LED_BLINK_PIN_MED, med_pin_state);
  }
}

void BlinkFast()
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousFastMillis >= FAST_INTERVAL)
  {
    // save the last time you blinked the LED
    previousFastMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (fast_pin_state == LOW)
    {
      fast_pin_state = HIGH;
    }
    else
    {
      fast_pin_state = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(LED_BLINK_PIN_FAST, fast_pin_state);
  }
}

void BlinkRandom()
{
  unsigned long currentMillis = millis();
  //long longOn;
   
  //randomize the interval
  //long interval = random(1000, 5000);
  //if (currentMillis - previousRandMillis > interval)
  //{
    //every few seconds, stay on for longer
    //longOn = random (1, 3);
    //digitalWrite(LED_RANDOM_PIN, HIGH);
    //delay(longOn * 1000);

  //  previousRandMillis = millis();
  //}

  if (rand_pin_state == LOW)
  {
    if (currentMillis - previousRandMillis >= randomDelayOff)
    {
      // OFF time is up, time to turn the LED back on
      // Set our ON duration
      randomDelayOn = random(RANDOM_ON_MIN, RANDOM_ON_MAX);
      
      // Turn the LED back on
      digitalWrite(LED_RANDOM_PIN, HIGH);

      // Reset the pin state
      rand_pin_state = HIGH;

      // Update previous ms counter
      previousRandMillis = currentMillis;
    }

    // Time isn't up yet
    return;
  }

  if (rand_pin_state == HIGH)
  {
    if (currentMillis - previousRandMillis >= randomDelayOn)
    {
      // ON time is up, time to turn the LED back off
      // Set our OFF duration
      randomDelayOff = random(RANDOM_OFF_MIN, RANDOM_OFF_MAX);

      // Turn the LED back off
      digitalWrite(LED_RANDOM_PIN, LOW);
      
      // Reset the pin state
      rand_pin_state = LOW;

      // Update previous ms counter
      previousRandMillis = currentMillis;
    }
  }
 }

