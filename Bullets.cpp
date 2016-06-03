#include "Bullets.h"

Bullets::Bullets() {

}
void Bullets::activate(Arduboy *d) {

  for (uint8_t i = 0; i < 16; i++) {
    d->drawPixel(bullets[i].x, bullets[i].y, WHITE);
    d->drawPixel(bullets[i].x+1, bullets[i].y, WHITE);
    d->drawPixel(bullets[i].x+2, bullets[i].y, WHITE);
    if (bullets[i].x < 0) {

    } else if(bullets[i].x > 128) {
      bullets[i].x = -5;
    } else {
        bullets[i].x += 3;
    }
  }
}

