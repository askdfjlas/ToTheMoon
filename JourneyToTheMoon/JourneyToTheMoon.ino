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

  initEnemies();
}

void loop() {
  if(!arduboy.nextFrame()) return; 
  arduboy.clear(); 
  
  // Game loop
  getInputs();
  updatePlayer(); 
  updateWeapon();
  updateEnemies(); 
  draw();
   
  arduboy.display(); 
}
