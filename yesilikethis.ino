#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

// constants won't change. They're used here to 
// set pin numbers:
const int ledPin = 1;     // the number of the neopixel strip
const int numLeds = 8;

//Adafruit_NeoPixel pixels = Adafruit_NeoPixel(8, ledPin);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(numLeds, ledPin, NEO_GRB + NEO_KHZ800);


void setup() {
  strip.begin();
  strip.setBrightness(255); // 1/3 brightness

}

void loop() {

    
    rainbow(3);
    
  delay(10);


}

// https://codebender.cc/sketch:85796


void rainbow(uint8_t wait) {
  uint16_t pixelNum, j;

  for(j=0; j<256; j++) {
    for(pixelNum=0; pixelNum<strip.numPixels(); pixelNum++) {
      strip.setPixelColor(pixelNum, Wheel((pixelNum+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}



// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
// Return color based on Wheel Position
// j=color wheel??

uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}


