// Space Knife game for Arduboy
// https://github.com/streetalchemist/SpaceKnife
// Alex Porter 2016
// alex@streetalchemy.com

#include "Arduboy.h"
#include "bitmaps.h"
#include "Stars.h"
#include "Bullets.h"
#include "Enemies.h"
#include "Squawk.h"
//#include "tunes.h"
#include <EEPROM.h>
#include "localEEPROM.h"

SQUAWK_CONSTRUCT_ISR(SQUAWK_PWM_PIN5)

Arduboy arduboy;
AbPrinter text(arduboy);
Stars stars;
Bullets bullets;
Enemies enemies;
ArduboyEeprom savedData;

int retVal;

int x=5; //Ship x
int y=20; //Ship y
int shipSpeed=3;
int score=0;
int gameState = 1;
uint8_t bulletCounter = 0;
bool canShoot = true;
//uint8_t frameCount = 1;
String scoreString = "Score: ";
String highScoreString = "High Score: ";
uint8_t savedScore;

#define X_MAX (WIDTH - 20)

#define Y_MAX (HEIGHT - 10)

void setup() {
  
  // Set up Squawk to generate samples at 32kHz.
  // Squawk always steals Timer1 for sample crunching.
  //Squawk.begin(32000);
  // Begin playback of melody.
  //Squawk.play(TheOriginalSquawk);
  // Tune the song to something more suitable for a piezo
  //Squawk.tune(2.0);
  // Lower the tempo ever so slightly
  //Squawk.tempo(48);
  // Setup High Score Saving
  //  if ((retVal = savedData.EEPROM_BEGIN) != 0) {
  //    if (retVal == EEPROM_ALLOCATED) {
  //      //EMPTY REGISTER
  //      //savedData.write(0, score);
  //      savedScore = savedData.read(0);
  //    }
  //    else {
  //      text.print("Allocate Error: ");
  //      text.println(retVal);
  //    }
  //  }
  //  else {
  //    //savedScore = savedData.read(0);
  //    savedData.write(0, score);
  //  }
  // put your setup code here, to run once:
  arduboy.begin();
  arduboy.setFrameRate(40);
  arduboy.display();
  intro();
  enemies.setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!(arduboy.nextFrame())) {
    return;
  }

  //Show Score
  text.setCursor(40, 5);
  String scoreValue = scoreString+score;
  text.print(scoreValue);

  //active background starz
  stars.activate(&arduboy);

  if(gameState == 1) {
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
  }
  
  //Enemy Movement
  enemies.activate(&arduboy);

  //Game Over Screen Game State
  if(gameState == 2) {
    text.setCursor(37, 30);
    text.print("GAME OVER");

    //Print High Score
    //text.setCursor(25, 40);
    //String highScoreValue;
    //highScoreValue = highScoreString+savedScore;
    //text.print(highScoreValue);

    text.setCursor(11, 53);
    text.print("press A to restart");

    if(arduboy.pressed(B_BUTTON)) {
      restart();
    }
    
  }

  arduboy.display();
  arduboy.clear();
}

void restart() {
  score = 0;
  x = 5;
  y = 20;
  gameState = 1;
  enemies.setup();
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
  for(int enemyIndex = 0; enemyIndex < 8; enemyIndex++) {
    for(int bulletIndex = 0; bulletIndex < 16; bulletIndex++) {
      if(doesIntersect(bullets.bullets[bulletIndex].x,bullets.bullets[bulletIndex].y, 3,1,enemies.enemiesArr[enemyIndex].x,enemies.enemiesArr[enemyIndex].y,enemies.enemyWidth,enemies.enemyHeight)) {
        enemies.reset(enemyIndex);
        score++;
        bullets.bullets[bulletIndex].x = -50;
      }
    }

    if(doesIntersect(x,y,20,10,enemies.enemiesArr[enemyIndex].x, enemies.enemiesArr[enemyIndex].y, enemies.enemyWidth, enemies.enemyHeight)) {
      x = -100;
      //setHighScore();
      gameState = 2;
    }
    
  }
}


bool doesIntersect(int x1, int y1,int width1,int height1,int x2,int y2,int width2,int height2) {
  if(x1 < x2 + width2 && x1 + width1 > x2 && y1 < y2 + height2 && y1 + height1 > y2) {
    return true;
  }
  return false;
}

//void setHighScore() {
//    if(score > savedScore) {
//      savedData.write(0, score);
//      savedScore = score;
//    }
//}

void intro()
{

  arduboy.clear();
  arduboy.drawBitmap(0, 0, bitmap_streetalchemist, 128, 64, WHITE);
  arduboy.display();
  delay(3000);


  arduboy.clear();
  arduboy.drawBitmap(0, 0, bitmap_intro_screen, 128, 64, WHITE);
  arduboy.display();

  delay(3000);
}
