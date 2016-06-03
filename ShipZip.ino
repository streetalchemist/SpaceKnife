#include "Arduboy.h"
#include "bitmaps.h"
#include "Stars.h"
#include "Bullets.h"

Arduboy arduboy;
Stars stars;
Bullets bullets;


float x=0; //Ship x
float y=0; //Ship y
float shipSpeed=3;
uint8_t bulletCounter = 0;

#define X_MAX (WIDTH - 20)

#define Y_MAX (HEIGHT - 10)

void setup() {
  // put your setup code here, to run once:
  arduboy.begin();
  arduboy.setFrameRate(60);
  arduboy.display();
  intro();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!(arduboy.nextFrame())) {
    return;
  }

  //active background starz
  stars.activate(&arduboy);
  bullets.activate(&arduboy);

  // if the right button is pressed move 1 pixel to the right every frame
  if(arduboy.pressed(RIGHT_BUTTON) && (x < X_MAX)) {
    x+= shipSpeed;
  }

  // if the left button is pressed move 1 pixel to the left every frame
  if(arduboy.pressed(LEFT_BUTTON) && (x > 0)) {
    x-= shipSpeed;
  }

  // if the up button or B button is pressed move 1 pixel up every frame
  if(arduboy.pressed(UP_BUTTON) && (y > 0)) {
    y-= shipSpeed;
  }

  // if the down button or A button is pressed move 1 pixel down every frame
  if(arduboy.pressed(DOWN_BUTTON) && (y < Y_MAX)) {
    y+= shipSpeed;
  }

  if(arduboy.pressed(A_BUTTON)) {
    bullets.bullets[bulletCounter].x = x+10;
    bullets.bullets[bulletCounter].y = y+4;
    bulletCounter++;
    if(bulletCounter > 16) {
      bulletCounter = 0;
    }
  }

  arduboy.drawBitmap(x, y, bitmap_ship, 20, 10, WHITE);

  arduboy.display();
  arduboy.clear();
}

void intro()
{
  for(int i = -8; i < 28; i = i + 2)
  {
    arduboy.clear();
    arduboy.setCursor(46, i);
    arduboy.print("ShipZip");
    arduboy.display();
  }

  //arduboy.tunes.tone(987, 160);
  delay(160);
  //arduboy.tunes.tone(1318, 400);
  delay(2000);
}
