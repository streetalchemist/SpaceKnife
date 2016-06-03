#include "Stars.h"

Stars::Stars() {

}
void Stars::activate(Arduboy *d) {

  for (uint8_t i = 0; i < 16; i++) {
      d->drawPixel(bgStars[i].x, bgStars[i].y, WHITE);
      if (bgStars[i].x < 0) {
          bgStars[i].x = 128 + random(1,8);
      }
      if(i%4 == 0) {
        if (d->everyXFrames(5)) {
          bgStars[i].x--;
        }
      } else if(i%6 == 0) {
        if (d->everyXFrames(2)) {
          bgStars[i].x--;
        }
      } else {
        if (d->everyXFrames(3)) {
          bgStars[i].x--;
        }
      }
    }
}

