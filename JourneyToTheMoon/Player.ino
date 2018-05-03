#include "Player.h"

void updatePlayer() {
  if(ahri.yVel > MINYVEL) {
    ahri.yVel -= GRAVITY; 
    ahri.airborn = 1;
  }

  ahri.y += ahri.yVel;

  groundCollide(); 
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

    Rect Land = {x - ahri.x + TRUEX, -y + ahri.y + TRUEY, w*TILEWIDTH, h*TILEHEIGHT}; 
    verticalCollide(Land); 
  }
}

