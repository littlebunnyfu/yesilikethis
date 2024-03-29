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
  rainbow(5, numLeds);    
  delay(10);
}

// https://codebender.cc/sketch:85796


void rainbow(uint8_t wait, int numPixels) {
  uint16_t wheelPos, j;
  uint32_t color;

  for(j=0; j<256; j++) {
    color = colorTwiddler( j ); 
    setPixelColors(color, numPixels);
    delay(wait);
  }
}

// next thing to do is change lightleds to take an array of tuples like [(1,red), (3,green)] -- which would reset two of the lights and leave the others unchanged
// research project, how do we do this in c?
// this would be a candidate for being a library function
void setPixelColors(uint32_t color, int numPixels) {
    uint16_t pixel;
    for(pixel=0; pixel < numPixels; pixel++) {     
      strip.setPixelColor( pixel, color );
      strip.show();
    }  
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
// Return color based on Wheel Position
// j=color wheel??
uint32_t colorTwiddler(uint16_t theWheelPos) {
  uint16_t WheelPos, offset, twiddleFactor;
  WheelPos = theWheelPos & 255; // wtf is 255 doing here?
  offset = WheelPos * 3;

  twiddleFactor = 0;
  
  if(WheelPos < 85) {
    return Adafruit_NeoPixel::Color(offset, 255 - offset, twiddleFactor);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return Adafruit_NeoPixel::Color(255 - offset, twiddleFactor, offset);
  } 
  else {
    WheelPos -= 170;
    return Adafruit_NeoPixel::Color(twiddleFactor, offset, 255 - offset);
  }
}


