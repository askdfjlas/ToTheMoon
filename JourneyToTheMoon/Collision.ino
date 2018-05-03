#include "Collision.h"

void verticalCollide(Rect object) {
  // Declare the player rect
  Rect player = {TRUEX, TRUEY, PWIDTH, PHEIGHT}; 

  // Check if we land on a platform
  if(ahri.yVel < 0 && arduboy.collide(player, object)) { 
    ahri.yVel = 0; 
    ahri.y += TRUEY - object.y + PHEIGHT;
    ahri.airborn = 0; 
  }

  // Check if we bump our head
  if(ahri.yVel > 0 && arduboy.collide(player, object)) { 
    ahri.yVel = 0; 
    ahri.y -= object.y + object.height - TRUEY; 
  }
}

void horizontalCollide(byte dir) {
  for(int i = 0; i < R1LEN; i++) {
    int* addr = R1Rect + i*4; 
    
    int x = pgm_read_word(addr);
    int w = pgm_read_word(addr + 2);
    
    switch(boundsChecking(x - ahri.x + TRUEX, x - ahri.x + TRUEX + w*TILEWIDTH)) {
      case 0: 
        return;
      case 1:
        continue;
    }
    
    int y = pgm_read_word(addr + 1);
    int h = pgm_read_word(addr + 3); 
    Rect object = {x - ahri.x + TRUEX, -y + ahri.y + TRUEY, w*TILEWIDTH, h*TILEHEIGHT}; 
    Rect player = {TRUEX, TRUEY, PWIDTH, PHEIGHT}; 
    
    if(arduboy.collide(player, object)) {
      switch(dir) {
        case LEFT:
          ahri.x += (object.x + object.width) - TRUEX;
          break;
        case RIGHT: 
          ahri.x -= (TRUEX + PWIDTH) - object.x;
          break;
      }
    }
  }
}

void groundCollide() {
  if(ahri.y < PHEIGHT) {
    ahri.yVel = 0;
    ahri.y = PHEIGHT;  
    ahri.airborn = 0; 
  }
}

byte boundsChecking(int a, int b) {
  if(a > 128) {
    return 0;
  }
  else if(b < 0) {
    return 1;
  }
  else {
    return 2; 
  }
}

