
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define CHEST_PIN 1
#define CHEST_COUNT 16
#define WIPE_PIN 2
#define WIPE_COUNT 9

int chest_pos = 4;  //Starting chest position
bool chest_going_up = true;

int wipe_pos = 0;
int wipe_extra_delay = 5;

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel chest_strip = Adafruit_NeoPixel(CHEST_COUNT, CHEST_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel wipe_strip = Adafruit_NeoPixel(WIPE_COUNT, WIPE_PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  chest_strip.begin();
  chest_strip.show(); // Initialize all pixels to 'off'

  wipe_strip.begin();
  wipe_strip.show();
  
}

void loop() {
  uint8_t pos;  //Used for position to set
  
  // Red Swoosh
  if (chest_going_up) {
    pos = abs(chest_pos - 5);
    chest_strip.setPixelColor(pos, chest_strip.Color(0, 0, 0));
    pos = abs(chest_pos - 4);
    chest_strip.setPixelColor(pos, chest_strip.Color(15, 0, 0));
    pos = abs(chest_pos - 3);
    chest_strip.setPixelColor(pos, chest_strip.Color(31, 0, 0));
    pos = abs(chest_pos - 2);
    chest_strip.setPixelColor(pos, chest_strip.Color(63, 0, 0));
    pos = abs(chest_pos - 1);
    chest_strip.setPixelColor(pos, chest_strip.Color(127, 0, 0));
    pos = chest_pos;
    chest_strip.setPixelColor(pos, chest_strip.Color(255, 0, 0));
    chest_strip.show();
    chest_pos += 1;
    if (chest_pos > 15) {
      chest_pos = 15;
      chest_going_up = false;
    }
  } else {
    if (chest_pos + 5 > 15) {
      pos = 16 - 4 - (15 - chest_pos);
    } else {
      pos = chest_pos + 5;
    }
    chest_strip.setPixelColor(pos, chest_strip.Color(0, 0, 0));
    if (chest_pos + 4 > 15) {
      pos = 16 - 3 - (15 - chest_pos);
    } else {
      pos = chest_pos + 4;
    }
    chest_strip.setPixelColor(pos, chest_strip.Color(15, 0, 0));
    if (chest_pos + 3 > 15) {
      pos = 16 - 2 - (15 - chest_pos);
    } else {
      pos = chest_pos + 3;
    }
    chest_strip.setPixelColor(pos, chest_strip.Color(31, 0, 0));
    if (chest_pos + 2 > 15) {
      pos = 16 - 1 - (15 - chest_pos);
    } else {
      pos = chest_pos + 2;
    }
    chest_strip.setPixelColor(pos, chest_strip.Color(63, 0, 0));
    if (chest_pos + 1 > 15) {
      pos = 16 - 0 - (15 - chest_pos);
    } else {
      pos = chest_pos + 1;
    }
    chest_strip.setPixelColor(pos, chest_strip.Color(127, 0, 0));
    pos = chest_pos;
    chest_strip.setPixelColor(pos, chest_strip.Color(255, 0, 0));
    chest_strip.show();
    chest_pos -= 1;
    if (chest_pos < 0) {
      chest_pos = 0;
      chest_going_up = true;
    }
  }

  // RedWipe
  if (wipe_pos < WIPE_COUNT) {
    wipe_strip.setPixelColor(wipe_pos, wipe_strip.Color(255, 0, 0));
    wipe_strip.show();
    wipe_pos += 1;
  } else if (wipe_pos < WIPE_COUNT + wipe_extra_delay) {
    wipe_pos +=1;
  } else {
    for (int i = 0; i < WIPE_COUNT; i++) {
      wipe_strip.setPixelColor(i, wipe_strip.Color(0, 0, 0));
    }
    wipe_strip.show();
    wipe_pos = 0;
  }
 
  delay(100);

}


