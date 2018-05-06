#include "Enemy.h"

void moveRandomBounded(struct enemy* myEnemy, int leftBound, int rightBound) {
  arduboy.initRandomSeed();

  // only change directions when its moving frame counter is 0
  if(myEnemy->movingFrames == 0) {
    int increment = random(0, 2); 
    if(increment == 0) {
      myEnemy->xVel = myEnemy->S;
    }
    else {
      myEnemy->xVel = -myEnemy->S;
    }
    myEnemy->movingFrames = 25;
  }

  myEnemy->x += myEnemy->xVel;
 
  if(myEnemy->x < leftBound) {
    myEnemy->x = leftBound; 
  }
  if(myEnemy->x > rightBound) {
     myEnemy->x = rightBound; 
  }

  myEnemy->movingFrames--;
}

void initEnemies() {
  for(int i = 0; i < NUMENEMIES; i++) {
    initEnemy(enemies + i, i); 
  }
}

void initEnemy(Enemy* E, int index) {
  E->init = 1;
  E->movingFrames = 0; 
  E->invincibleFrames = 0;
  
  E->x = (pgm_read_word(boundaries + index*2) + pgm_read_word(boundaries + index*2 + 1))/2; 
  E->y = pgm_read_word(yPos + index); 
  E->HP = E->MAXHP; 
  E->xVel = -E->S;
}

void updateEnemies() {
  Weapon w = ahri.myWeapon;
  Rect swordRect;
  
  switch(ahri.facing) {
      case RIGHT: 
        swordRect = {TRUEX + PWIDTH + 1, w.H1, w.w, w.h};
        break;
      case LEFT: 
        swordRect = {TRUEX - 1 - w.Hi, w.H1, w.w, w.h};
        break;
  }
  
  for(int i = 0; i < NUMENEMIES; i++) {
    // death/offscreen
    if(enemies[i].init != 1) continue; 
    
    if(enemies[i].invincibleFrames != 0) {
      enemies[i].invincibleFrames--;
    }
    
    // hitstun!
    if(enemies[i].invincibleFrames != 0) {
      continue; 
    }
    
    (enemies[i]).move(enemies + i, pgm_read_word(boundaries + i*2), pgm_read_word(boundaries + i*2 + 1)); 
    Rect enemyRect = {TRUEX + enemies[i].x - ahri.x, enemies[i].y + TRUEY + ahri.y - PHEIGHT, enemies[i].w, enemies[i].h};
        
    if(enemyHit(swordRect, enemyRect) && ahri.frameCount <= w.activeStart && ahri.frameCount >= w.activeEnd) {
      enemies[i].HP -= ahri.attack*w.multiplier; 
      enemies[i].invincibleFrames = IFRAMES;
    }

    if(enemies[i].HP <= 0) {
      enemies[i].init = 2;
      ahri.experience += enemies[i].EXP; 
    }
  }
}

