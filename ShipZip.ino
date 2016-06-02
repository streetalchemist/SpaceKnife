#include "Arduboy.h"
#include "bitmaps.h"

Arduboy arduboy;

float shipX=0; //Ship x
float shipY=0; //Ship y

#define X_MAX (WIDTH - 20)

#define Y_MAX (HEIGHT - 10)

void setup() {
  // put your setup code here, to run once:
  arduboy.begin();
  arduboy.setFrameRate(24);
  arduboy.display();
  intro();
}

void loop() {
  // put your main code here, to run repeatedly:

  // if the right button is pressed move 1 pixel to the right every frame
  if(arduboy.pressed(RIGHT_BUTTON) && (x < X_MAX)) {
    x+= .2;
  }

  // if the left button is pressed move 1 pixel to the left every frame
  if(arduboy.pressed(LEFT_BUTTON) && (x > 0)) {
    x-= .2;
  }

  // if the up button or B button is pressed move 1 pixel up every frame
  if((arduboy.pressed(UP_BUTTON) || arduboy.pressed(B_BUTTON)) && (y > 0)) {
    y-= .2;
  }

  // if the down button or A button is pressed move 1 pixel down every frame
  if((arduboy.pressed(DOWN_BUTTON) || arduboy.pressed(A_BUTTON)) && (y < Y_MAX)) {
    y+= .2;
  }
  arduboy.clear();

  arduboy.drawBitmap(shipX, shipY, ship, 20, 10, WHITE);

  arduboy.display();
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

  arduboy.tunes.tone(987, 160);
  delay(160);
  arduboy.tunes.tone(1318, 400);
  delay(2000);
}
