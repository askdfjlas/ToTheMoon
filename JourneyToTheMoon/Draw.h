#ifndef DRAW_H
#define DRAW_H

// All tiles are 8x8, this is unlikely to change
#define TILEWIDTH 8 
#define TILEHEIGHT 8

#include "Tinyfont.h"
#include "Enemy.h"

int expBuffer = -1;
byte expFrameCount = 0; 

// File to handle all drawing of objects

void draw(); 
void drawLand();
void drawBlockLand(int x, int y, int w, int h); 
void drawPlayer();
void drawWeapon();
void drawGround();
void drawEnemies(); 
void drawPlayerInfo();
void drawHPBar(int x, int y, int HP, int maxHP); 
void drawEXP();
void drawBullets(); 

#endif
