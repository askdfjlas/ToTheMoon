#include "Draw.h"

// General draw handling, this is the only one which is called outside
void draw() {
  // Clear the screen to white
  arduboy.fillRect(0, 0, 128, 64, WHITE); 

  // Draw BG
  drawBG(); 

  // Draw Land
  drawLand(); 
}

// Draw the land
void drawLand() {
  for(int i = 0; i < R1LEN; i++) {
    int* addr = R1Rect + i*4; 
    drawBlockLand(pgm_read_word(addr), pgm_read_word(addr + 1), pgm_read_word(addr + 2), pgm_read_word(addr + 3)); 
  }
}

// Draw each individual block of land
void drawBlockLand(int x, int y, int w, int h) {
  for(int i = 0; i < w; i++) {
    for(int j = 0; j < h; j++) {
      arduboy.drawBitmap(x + i*TILEWIDTH - ahri.x, y + j*TILEHEIGHT + ahri.y, T1, TILEWIDTH, TILEHEIGHT, BLACK); 
    }
  }
}

// Uses parallax to create a cool effect
void drawBG() {
  int xOffset = ahri.x/3 % 48;
  int yOffset = ahri.y/2 - 30; 

  for(int i = -1; i < 4; i++) {
    arduboy.drawBitmap(-xOffset + i*48, yOffset, BG, 48, 100, BLACK);
  }
}

