#include <Arduboy2.h>
#include "edgyText.h"
#include "Sprites.h"
#include "Landscape.h"
#include "Player.h"
#include "Draw.h" 
#include "Input.h"
#include "Collision.h"
#include "weapon.h"

// Main file

#define FPS 30
#define TEXTSPEED 40

Arduboy2 arduboy;
Sprites Sprite; 

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
  getInputs();
  updatePlayer(); 
  draw();
  updateWeapon();
  
  arduboy.display(); 
}
