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
  rainbow(5);    
  delay(10);
}

// https://codebender.cc/sketch:85796


void rainbow(uint8_t wait) {
  uint16_t ledNum, color, wheelPos, j;

  for(j=0; j<256; j++) {
    for(ledNum=0; ledNum<8; ledNum++) {
      // color = Wheel((ledNum+j) & 255);
      wheelPos = (ledNum+j) & 255; // wtf is 255 doing here?
      strip.setPixelColor( ledNum, Wheel( wheelPos) );
      strip.show();
    }
    delay(wait);
  }
}



// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
// Return color based on Wheel Position
// j=color wheel??

uint32_t Wheel(uint16_t WheelPos) {
  uint16_t offset, twiddleFactor;
  offset = WheelPos * 3;

  twiddleFactor = 0;
  
  if(WheelPos < 85) {
    return strip.Color(offset, 255 - offset, twiddleFactor);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - offset, twiddleFactor, offset);
  } 
  else {
    WheelPos -= 170;
    return strip.Color(twiddleFactor, offset, 255 - offset);
  }
}


