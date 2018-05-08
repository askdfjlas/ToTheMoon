#include <Arduboy2.h>
#include "edgyText.h"
#include "Sprites.h"
#include "Landscape.h"
#include "Player.h"
#include "Draw.h" 
#include "Input.h"
#include "Collision.h"
#include "weapon.h"
#include "Enemy.h"

// Main file

byte gameState = 0;

const char intro[7][MAXDIALOGUE] PROGMEM = {"There's spooky aliens out there. \0",
"Go and kill them. \0",
"Yeah. \0", 
"There's a lot of passive ones. \0",
"The other ones are kind   of brutal. \0",
"Did you know that a        healthy amount of sleep    is 6-8 hours? \0",
"I put that in for the     \"education\" theme. \0"}; 

const char death[5][MAXDIALOGUE] PROGMEM = {"Wow, you suck. \0",
"I can't believe you       actually died. \0",
"It's not like everything one-shots you in this      game. \0",
"Hahaha I'm so funny. \0",
"Well um, get back in        there, bud. \0"};

const char complete[4][MAXDIALOGUE] PROGMEM = {"Wowee, you beat my game. \0",
"I can't say I'm surprised. \0",
"Well um, if you're        feeling sadistic... \0",
"Then continue killing        stuff! \0"}; 

#define FPS 30
#define TEXTSPEED 40

Arduboy2 arduboy;
Sprites Sprite; 

Tinyfont tinyfont = Tinyfont(arduboy.sBuffer, Arduboy2::width(), Arduboy2::height());

// make an ArdBitmap instance that will use the given the screen buffer and dimensions
#define ARDBITMAP_SBUF arduboy.getBuffer()
#include <ArdBitmap.h>
ArdBitmap<WIDTH, HEIGHT> ardbitmap;

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(FPS); 
  arduboy.clear();
}

void loop() {
  if(!arduboy.nextFrame()) return; 
  arduboy.clear(); 
  
  // Game loop
  switch(gameState) {
    case 0: 
      edgyText(intro, 7, DEFAULTFPS, BLANK); 
      gameState = 1;
      ahri.x = 0; 
      ahri.y = PHEIGHT;
      ahri.health = ahri.maxHealth;

      initEnemies();
      break;
    case 1:
      getInputs();
      updatePlayer(); 
      updateWeapon();
      updateEnemies();
      manageBullets(); 
      draw();

      break;
    case 2: 
      edgyText(death, 5, DEFAULTFPS, BLANK); 
      gameState = 1;
      ahri.x = 0; 
      ahri.y = PHEIGHT;
      ahri.health = ahri.maxHealth;

      initEnemies();
      break;
    case 3:
      edgyText(complete, 4, DEFAULTFPS, BLANK);
      gameState = 1;
      ahri.x = 0; 
      ahri.y = PHEIGHT;
      ahri.health = ahri.maxHealth;

      initEnemies();
      break;
  }
   
  arduboy.display(); 
}
