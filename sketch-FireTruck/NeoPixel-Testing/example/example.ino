#include <Adafruit_NeoPixel.h>
 #ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
 #include <avr/power.h>
#endif

#define PIN 0
 
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(7, PIN, NEO_RGB + NEO_KHZ800);
 
void setup() {
  #ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
  if(F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  strip.begin();
  //strip.setBrightness(30); //adjust brightness here
  strip.show(); // Initialize all pixels to 'off'
}
 
void loop() {
  // Some example procedures showing how to display to the pixels:
  //colorSpin(16, 4, strip.Color(255, 0, 0), 50);
  //colorWipe(strip.Color(255, 0, 0), 50); // Red
  //colorWipe(strip.Color(0, 255, 0), 50); // Green
  //colorWipe(strip.Color(0, 0, 255), 50); // Blue
  rainbow(1000);
  //rainbowCycle(16);
}
int offset = 0; // Position of spinny eyes

void colorSpin(int numberOfPixels, int spokes, uint32_t color, int wait) {
  int spokeOffset = numberOfPixels / spokes;
  //0 4 8 12
  //1 5 9 13
  //2 6 9 14
  int spoke1 = 0;
  int spoke2 = 4;
  int spoke3 = 8;
  int spoke4 = 12;
  // loop 10 times
  //uint32_t color2  = 0xFF0000;
  //for (int i = 0; i < 20; i++)
  //{
   // for(int j=0; j<16; j++) {
    //  uint32_t c = 0;
    //  if(((offset + j) & 7) < 1) c = color; // 4 pixels on...
    //  strip.setPixelColor(   i, c); // First eye
 //   strip.show();
  //  offset--;
  //  delay(50);
    
  //  }
int j = 0;
int i = 0;
for (i = 0; i < 10; i++){
for (j = 0; j < 4; j++){
   strip.setPixelColor(spoke1 + j, color);
      strip.setPixelColor(spoke2 + j, color);
      strip.setPixelColor(spoke3 + j, color);
     strip.setPixelColor(spoke4 + j, color);
    strip.show();
    delay(50);
    strip.setPixelColor(spoke1 + j, strip.Color(0,0,0));
      strip.setPixelColor(spoke2 + j, strip.Color(0,0,0));
      strip.setPixelColor(spoke3 + j, strip.Color(0,0,0));
     strip.setPixelColor(spoke4 + j, strip.Color(0,0,0));
     strip.show();
}
}

for (i = 0; i < 10; i++){
for (j = 0; j < 4; j++){
    int firstSpoke = 0;
    if (spoke1-j == 0) firstSpoke = 0;
    if (spoke1-j == -1) firstSpoke = 15;
    if (spoke1-j == -2) firstSpoke = 14;
    if (spoke1-j == -3) firstSpoke = 13;

   strip.setPixelColor(firstSpoke, color);
      strip.setPixelColor(spoke2 - j, color);
      strip.setPixelColor(spoke3 - j, color);
     strip.setPixelColor(spoke4 - j, color);
    strip.show();
    delay(50);
    strip.setPixelColor(firstSpoke, strip.Color(0,0,0));
      strip.setPixelColor(spoke2 - j, strip.Color(0,0,0));
      strip.setPixelColor(spoke3 - j, strip.Color(0,0,0));
     strip.setPixelColor(spoke4 - j, strip.Color(0,0,0));
     strip.show();
}
}
    //for (int j = 0; j < numberOfPixels; j++)
    //{
   //   strip.setPixelColor(spoke1 + j, color);
     // strip.setPixelColor(spoke2 + j, color);
     // strip.setPixelColor(spoke3 + j, color);
     // strip.setPixelColor(spoke4 + j, color);
     // strip.show();
     // delay(wait);
     // strip.setPixelColor(spoke1 + j, strip.Color(0,0,0));
     // strip.setPixelColor(spoke2 + j, strip.Color(0,0,0));
     // strip.setPixelColor(spoke3 + j, strip.Color(0,0,0));
     // strip.setPixelColor(spoke4 + j, strip.Color(0,0,0));
     // strip.show();
    //}
//  }
}

 
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}
 
void rainbow(uint8_t wait) {
  uint16_t i, j;
 
  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
 
// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
 
  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
 
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
