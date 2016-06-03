#include "Arduboy.h"

#ifndef BULLETS_H
#define BULLETS_H

class Bullets {
  public:
    Bullets();
    void activate(Arduboy *d);

  
  struct Point
  {
  public:
      int16_t x;
      int16_t y;
  };

  Point bullets[16] = {{-5,-5} , {-5,-5} , {-5,-5} , {-5,-5} , {-5,-5} , {-5,-5} , {-5,-5} , {-5,-5} , {-5,-5} , {-5,-5} , {-5,-5} , {-5,-5} , {-5,-5} , {-5,-5} , {-5,-5} , {-5,-5}};

};
#endif
