#include "Draw.h"

// General draw handling, this is the only one which is called outside
void draw() {
  // Clear the screen to white
  arduboy.fillRect(0, 0, 128, 64, WHITE); 
  // Draw BG
  drawBG(); 
  // Draw Land
  drawLand();   
  // Draw enemies
  drawEnemies();  
  // Draw player
  drawPlayer();
  // Draw weapon
  drawWeapon();
  // Draw ground
  drawGround();
  // Draw health bar, exp, etc.
  drawPlayerInfo();
}

// Draw the land
void drawLand() {
  for(int i = leftIndex; i < rightIndex; i++) {
    int* addr = R1Rect + i*4; 
    drawBlockLand(pgm_read_word(addr), pgm_read_word(addr + 1), pgm_read_word(addr + 2), pgm_read_word(addr + 3)); 
  }
}

// Draw each individual block of land
void drawBlockLand(int x, int y, int w, int h) {
  for(int i = 0; i < w; i++) {
    for(int j = 0; j < h; j++) {
      arduboy.drawBitmap(x + i*TILEWIDTH - ahri.x + TRUEX, -y + j*TILEHEIGHT + ahri.y + TRUEY, T1, TILEWIDTH, TILEHEIGHT, BLACK); 
    }
  }
}

// Uses parallax to create a cool effect
void drawBG() {
  int xOffset = ahri.x/3 % 48;
  int yOffset = ahri.y/3 - 40; 

  for(int i = -1; i < 4; i++) {
    arduboy.drawBitmap(-xOffset + i*48, yOffset, BG, 48, 100, BLACK);
  }
}

void drawPlayer() {
  arduboy.drawBitmap(TRUEX, TRUEY, PB, PWIDTH, PHEIGHT, BLACK);
  arduboy.drawBitmap(TRUEX, TRUEY, PW, PWIDTH, PHEIGHT, WHITE);
}

void drawWeapon() {
  Weapon w = ahri.myWeapon;
  byte x, y;
  
  if(ahri.frameCount <= w.activeStart && ahri.frameCount >= w.activeEnd) {
    // Attacking Weapon
    switch(ahri.facing) {
      case RIGHT: 
        x = TRUEX + PWIDTH + 1; 
        y = w.H2;
        ardbitmap.drawBitmap(x, w.H1, w.hitbox, w.w, w.h, BLACK, ALIGN_H_LEFT | ALIGN_V_TOP, MIRROR_NONE);
        break;
      case LEFT: 
        x = TRUEX - 1 - w.Hi; 
        y = w.H2;
        ardbitmap.drawBitmap(x, w.H1, w.hitbox, w.w, w.h, BLACK, ALIGN_H_LEFT | ALIGN_V_TOP, MIRROR_HORIZONTAL);
        break;
    }
    Sprites::drawOverwrite(x, y, w.spriteA, 0);
  }
  else {
    // Idle weapon
    switch(ahri.facing) {
      case RIGHT: 
        x = TRUEX + PWIDTH + 1; 
        y = w.H1;
        break;
      case LEFT: 
        x = TRUEX - 1 - w.Wi; 
        y = w.H1;
        break;
    }
    Sprites::drawOverwrite(x, y, w.sprite, 0);
  }
}

void drawGround() {
  int xOffset = ahri.x % TILEWIDTH;
  int yOffset = ahri.y + TRUEY;

  for(int j = 0; j < 4; j++) {
    for(int i = -1; i < 128/TILEWIDTH + 2; i++) {
      Sprites::drawOverwrite(-xOffset + i*TILEWIDTH, yOffset + j*TILEHEIGHT, T2, 0);
    }
  }
}

void drawEnemies() {
  for(int i = 0; i < NUMENEMIES; i++) {
    if(enemies[i].init != 1) continue;
    
    arduboy.drawBitmap(TRUEX + enemies[i].x - ahri.x, enemies[i].y + TRUEY + ahri.y - PHEIGHT, enemies[i].spriteW, enemies[i].w, enemies[i].h, WHITE);
    arduboy.drawBitmap(TRUEX + enemies[i].x - ahri.x, enemies[i].y + TRUEY + ahri.y - PHEIGHT, enemies[i].spriteB, enemies[i].w, enemies[i].h, BLACK);

    if(enemies[i].invincibleFrames != 0) {
      int x, y; 
      x = TRUEX + enemies[i].x - ahri.x - 8; 
      y = TRUEY + ahri.y - PHEIGHT - 10;
      tinyfont.setCursor(x + 9 - 3*log10((ahri.attack*(ahri.myWeapon).multiplier)), y + 7);
      arduboy.drawBitmap(x, y, dmg, 20, 20, BLACK); 
      tinyfont.print((int)(ahri.attack*(ahri.myWeapon).multiplier));
    }

    if(enemies[i].HP < enemies[i].MAXHP && enemies[i].invincibleFrames == 0) {
      drawHPBar(TRUEX + enemies[i].x - ahri.x + enemies[i].w/2 - 6, enemies[i].y + TRUEY + ahri.y - PHEIGHT - 4, enemies[i].HP, enemies[i].MAXHP);
    } 
  }
}

void drawPlayerInfo() {
  arduboy.fillRect(0, 0, 56, 10, BLACK); 
  tinyfont.setCursor(0, 0); 
  tinyfont.print("HP: ");
  tinyfont.print(ahri.health);
  tinyfont.print("/");
  tinyfont.print(ahri.maxHealth);
  tinyfont.setCursor(0, 5); 
  tinyfont.print("XP: "); 
  tinyfont.print(ahri.experience);
  tinyfont.print("/"); 
  tinyfont.print((int)(pow(ahri.lvl + 1, 2) - pow(ahri.lvl, 2))); 

  arduboy.fillRect(90, 0, 38, 5, BLACK);
  tinyfont.setCursor(91, 0); 
  tinyfont.print("LV: "); 
  tinyfont.print(ahri.lvl); 

}

void drawHPBar(int x, int y, int HP, int maxHP) { 
  arduboy.fillRect(x, y, 12, 1, BLACK); 
  arduboy.fillRect(x, y, 1, 3, BLACK); 
  arduboy.fillRect(x, y + 2, 12, 1, BLACK); 
  arduboy.fillRect(x + 12, y, 1, 3, BLACK); 
  arduboy.fillRect(x + 1, y + 1, 10, 1, WHITE); 

  arduboy.fillRect(x + 1, y + 1, ((float)HP/maxHP) * 10, 1, BLACK);
}

