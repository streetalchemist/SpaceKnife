#include "Enemies.h"
#include "bitmaps.h"

Enemies::Enemies() {

}

void Enemies::activate(Arduboy *d) {

  for (uint8_t i = 0; i < 8; i++) {

    if(d->everyXFrames(2)) {
      enemiesArr[i].x-= enemiesArr[i].speed;
      if(enemiesArr[i].x+enemyWidth < -80) {
        enemiesArr[i].x = random(150, 230);
        enemiesArr[i].y = random(5,50);
        enemiesArr[i].speed = random(1,3); 
      }
    }
  
    if(frameCount%4 == 0) {
      d->drawBitmap(enemiesArr[i].x, enemiesArr[i].y, bitmap_enemy_1, enemyWidth, enemyHeight, WHITE);
    } else if(frameCount%4 == 1) {
      d->drawBitmap(enemiesArr[i].x, enemiesArr[i].y, bitmap_enemy_2, enemyWidth, enemyHeight, WHITE);
    } else if(frameCount%4 == 2) {
      d->drawBitmap(enemiesArr[i].x, enemiesArr[i].y, bitmap_enemy_3, enemyWidth, enemyHeight, WHITE); 
    } else {
      d->drawBitmap(enemiesArr[i].x, enemiesArr[i].y, bitmap_enemy_2, enemyWidth, enemyHeight, WHITE);
    }
  }

  if (d->everyXFrames(6)) {
    frameCount++;
    if(frameCount > 11) {
      frameCount = 0;
    }
  }
}

void Enemies::setup() {
 for (uint8_t i = 0; i < 8; i++) {
  enemiesArr[i].x = random(130, 350);
  enemiesArr[i].y = random(5, 50);
  enemiesArr[i].speed = random(1,3); 
 }
}

void Enemies::reset(int index) {
  enemiesArr[index].x = random(130, 350);
  enemiesArr[index].y = random(5, 50);
  enemiesArr[index].speed = random(1,3); 
}

