#include "Arduboy.h"

#ifndef ENEMIES_H
#define ENEMIES_H

class Enemies {
  public:
    Enemies();
    void activate(Arduboy *d);
    void setup();
    void reset(int index);
  
  struct Enemy
  {
  public:
      int16_t x;
      int16_t y;
      int16_t speed;
  };

  Enemy enemiesArr[8] = {{300,300, 1} , {300,300, 1} , {300,300, 1} , {300,300, 1} , {300,300, 1}, {300,300, 1}, {300,300, 1}, {300,300, 1}};
  int enemyWidth = 21;
  int enemyHeight = 15;
  int frameCount = 0;
};
#endif
