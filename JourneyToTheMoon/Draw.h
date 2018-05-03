#ifndef DRAW_H
#define DRAW_H

// All tiles are 8x8, this is unlikely to change
#define TILEWIDTH 8 
#define TILEHEIGHT 8

// File to handle all drawing of objects

void draw(); 
void drawLand();
void drawBlockLand(int x, int y, int w, int h); 
void drawPlayer();
void drawGround();

#endif
