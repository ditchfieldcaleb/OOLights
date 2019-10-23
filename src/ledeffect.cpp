#include <FastLed.h>
#include "variables.h"

// The LedEffect super class. All instances of leds effects should subclass from this
class LedEffect {

  private:
    // Each LedEffect subclass will have its own private variables
    int index;
    int direction;
    int hue;


  public:
    // Each LedEffect instance has its own array to write led data to
    CRGBArray<NUM_LEDS> leddata;

    // Default constructor - random starting index, random hue
    LedEffect(uint8_t startIndex=0, uint8_t startHue=0) {
      index=startIndex;
      if (startIndex == 0) {
        index = random16() % NUM_LEDS;
      } else index = startIndex;
      direction=0; // (0 - moving right; 1 - moving left)
      if (startHue == 0) {
        hue = random8();
      } else hue = startHue;
    }

    // Each LedEffect subclass must implement render(), which renders the next frame to the ledData array
    void render() {
      // This example effect just moves a dot up and down the strip
      // Dot has a trail of less-saturated leds
      if (direction == 0) { index++; } else { index--; }
      if (index == 0 && direction == 1) { direction = 0; }
      if (index == NUM_LEDS-1 && direction == 0) { direction = 1; }

      leddata.fill_solid(CRGB::Black);
      leddata[index] = CHSV(hue++, 255, 255);
    }
};
