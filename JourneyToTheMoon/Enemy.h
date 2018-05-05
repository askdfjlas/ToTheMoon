#ifndef ENEMY_H
#define ENEMY_H

#define NUMENEMIES 1
#define IFRAMES 4

typedef struct enemy {
  const unsigned char* PROGMEM spriteW;
  const unsigned char* PROGMEM spriteB;
  const byte w PROGMEM;
  const byte h PROGMEM;
  const void PROGMEM (*move)(struct enemy* myEnemy, int leftBound, int rightBound); 
  const byte S PROGMEM; // Speed
  const int MAXHP PROGMEM;
  const byte EXP PROGMEM;

  int x, y; 
  int xVel;
  int HP; 
  byte movingFrames;
  byte invincibleFrames;
  byte init;
}Enemy;

void moveRandomBounded(struct enemy* myEnemy, int leftBound, int rightBound);
void initEnemies();
void initEnemy(Enemy* E, int index);
void updateEnemies();

Enemy roamer = {E1W, E1B, 10, 10, moveRandomBounded, 1, 5, 2}; 
const int yPos[NUMENEMIES] PROGMEM = {0}; 
const int boundaries[NUMENEMIES*2] PROGMEM = {30, 120}; 
Enemy enemies[NUMENEMIES] = {roamer}; 

#endif
