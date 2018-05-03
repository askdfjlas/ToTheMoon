#include <Arduboy2.h>
#include "edgyText.h"
#include "Sprites.h"
#include "Landscape.h"
#include "Player.h"
#include "Draw.h" 
#include "Input.h"
#include "Collision.h"

// Main file

#define FPS 30
#define TEXTSPEED 40

Arduboy2 arduboy;
Sprites Sprite; 

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

  arduboy.display(); 
}
