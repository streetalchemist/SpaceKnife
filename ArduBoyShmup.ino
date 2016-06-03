#include "Arduboy.h"
#include "bitmaps.h"
#include "Stars.h"
#include "Bullets.h"

Arduboy arduboy;
Stars stars;
Bullets bullets;


int x=0; //Ship x
int y=0; //Ship y
int enemyX = 80; //enemy x
int enemyY = 25; //enemy y
int enemyWidth = 21;
int enemyHeight = 15;
int shipSpeed=3;
int score=0;
uint8_t bulletCounter = 0;
bool canShoot = true;
uint8_t frameCount = 1;
String scoreString = "Score: ";

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

  //Show Score
  arduboy.setCursor(40, 5);
  String scoreValue = scoreString+score;
  arduboy.print(scoreValue);

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
    if(canShoot) {
      shoot();
    }
  }

  if(arduboy.notPressed(A_BUTTON)) {
    canShoot = true;
  }

  //Check Bullet Collisions
  checkCollisions();

  arduboy.drawBitmap(x, y, bitmap_ship, 20, 10, WHITE);

  //Enemy Movement
  if(arduboy.everyXFrames(2)) {
    enemyX--;
    if(enemyX+enemyWidth < -10) {
      enemyX = 130;
      enemyY = random(5,50); 
    }
  }

  if(frameCount%4 == 0) {
    arduboy.drawBitmap(enemyX, enemyY, bitmap_enemy_1, enemyWidth, enemyHeight, WHITE);
  } else if(frameCount%4 == 1) {
    arduboy.drawBitmap(enemyX, enemyY, bitmap_enemy_2, enemyWidth, enemyHeight, WHITE);
  } else if(frameCount%4 == 2) {
    arduboy.drawBitmap(enemyX, enemyY, bitmap_enemy_3, enemyWidth, enemyHeight, WHITE); 
  } else {
    arduboy.drawBitmap(enemyX, enemyY, bitmap_enemy_2, enemyWidth, enemyHeight, WHITE);
  }
    
  if (arduboy.everyXFrames(6)) {
    frameCount++;
    if(frameCount > 11) {
      frameCount = 0;
    }
  }

  arduboy.display();
  arduboy.clear();
}

void shoot() {
  canShoot = false;
  bullets.bullets[bulletCounter].x = x+10;
  bullets.bullets[bulletCounter].y = y+4;
  bulletCounter++;
  if(bulletCounter > 16) {
    bulletCounter = 0;
  }
}

void checkCollisions() {
  for(int i = 0; i < 16; i++) {
    if(doesIntersect(bullets.bullets[i].x,bullets.bullets[i].y, 3,1,enemyX,enemyY,enemyWidth,enemyHeight)) {
      enemyX = -30;
      enemyY = 0;
      score++;
    }
  }
}


bool doesIntersect(int x1, int y1,int width1,int height1,int x2,int y2,int width2,int height2) {
  if(x1 < x2 + width2 && x1 + width1 > x2 && y1 < y2 + height2 && y1 + height1 > y2) {
    return true;
  }
  return false;
}

void intro()
{
  for(int i = -8; i < 28; i = i + 2)
  {
    arduboy.clear();
    arduboy.setCursor(30, i);
    arduboy.print("ArduBoyShmup");
    arduboy.display();
  }

  //arduboy.tunes.tone(987, 160);
  delay(160);
  //arduboy.tunes.tone(1318, 400);
  delay(2000);
}
