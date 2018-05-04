#include "Collision.h"

void verticalCollide(Rect object) {
  // Declare the player rect
  Rect player = {TRUEX, TRUEY, PWIDTH, PHEIGHT}; 

  // Check if we land on a platform
  if(ahri.yVel < 0 && arduboy.collide(player, object)) {
    ahri.yVel = 0; 

    if((TRUEY - object.y + PHEIGHT) > 2) {
      // Reset aerial!
      ahri.frameCount /= 2;
    }
    
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
  for(int i = leftIndex; i < rightIndex; i++) {
    int* addr = R1Rect + i*4; 
    
    int x = pgm_read_word(addr);
    int w = pgm_read_word(addr + 2); 
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
    if(PHEIGHT - ahri.y > 2) {
      // Reset aerial!
      ahri.frameCount /= 2;
    }
    ahri.y = PHEIGHT;  
    ahri.airborn = 0; 
  }
}

byte boundsChecking(int a, int b, int i) {
  if(a > 128) {
    rightIndex = i;
    return 0;
  }
  else if(b < 0) {
    leftIndex++; 
    return 1;
  }
  else {
    return 2; 
  }
}

