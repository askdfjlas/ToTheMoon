#ifndef ENEMY_H
#define ENEMY_H

#define NUMENEMIES 15
#define IFRAMES 4

typedef struct bullet {
  const int PROGMEM dmg; 
  const byte w PROGMEM; 
  const byte h PROGMEM;
  const byte type PROGMEM; 
  const byte active PROGMEM;
  const int range PROGMEM;
  const byte start PROGMEM; 

  byte bulletFrames;
  int xVel, yVel;
  int x, y; 
}Bullet;

typedef struct enemy {
  const unsigned char* PROGMEM spriteW;
  const unsigned char* PROGMEM spriteB;
  const byte w PROGMEM;
  const byte h PROGMEM;
  const void PROGMEM(*move)(struct enemy* myEnemy, int leftBound, int rightBound); 
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
void manageBullets(Enemy* E); 

Bullet myDadsLoveForMe = {0, 0, 0, 0, 0, 0, 0}; 
Bullet simpleSeek = {10, 8, 8, 1, 60, 100, 30};
Bullet kill = {100, 8, 8, 2, 40, 200, 20}; 

Bullet bullets[NUMENEMIES] = {myDadsLoveForMe, myDadsLoveForMe, myDadsLoveForMe, simpleSeek, myDadsLoveForMe, myDadsLoveForMe, simpleSeek, myDadsLoveForMe
,myDadsLoveForMe, myDadsLoveForMe, simpleSeek, kill, kill, kill, kill}; 

Enemy roamer = {E1W, E1B, 10, 10, moveRandomBounded, 1, 5, 2}; 
Enemy shooter = {E2, NULL, 15, 15, moveRandomBounded, 1, 12, 10}; 
Enemy killer = {E3, NULL, 20, 20, moveRandomBounded, 2, 200, 25}; 

const int yPos[NUMENEMIES] PROGMEM = {0, 50, 24, 0, 32, 32, 32, 32, 32, 32, 0, 0}; 
const int boundaries[NUMENEMIES*2] PROGMEM = {30, 120, 258, 312, 450, 520, 550, 600, 650, 670, 700, 720, 740, 750, 760, 770, 770, 780, 780, 790, 925, 925, 1100, 1200, 1100, 1200, 1100, 1200, 1200, 1300}; 
Enemy enemies[NUMENEMIES] = {roamer, roamer, roamer, shooter, roamer, roamer, shooter, roamer, roamer, roamer, shooter, killer, killer, killer, killer}; 

#endif
