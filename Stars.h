#include "Arduboy.h"

#ifndef STARS_H
#define STARS_H

class Stars {
  public:
    Stars();
    void activate(Arduboy *d);


  private:
  
  struct Point
  {
  public:
      int16_t x;
      int16_t y;
  };

  Point bgStars[16] = {{0,5} , {8,45} , {16,22} , {32,60} , {40,18} , {48,57} , {56,33} , {64,17} , {72,47} , {80,8} , {88,27} , {96,47} , {104,7} , {112,52} , {120,3} , {128,14}};

};
#endif
