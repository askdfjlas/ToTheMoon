#ifndef PLAYER_H
#define PLAYER_H

// Width and height
#define PWIDTH 10
#define PHEIGHT 10

// True coordinates
#define TRUEX 59
#define TRUEY 30

// Gravity
#define GRAVITY 1
#define MINYVEL -6
#define JUMP 10

#define SPEED 4

#include "weapon.h"
#include "input.h"

// File to manage the player state

typedef struct player {
  int x, y; 
  float yVel;
  byte airborn;
  int lvl; 
  int experience; 
  byte facing;
  byte frameCount;

  Weapon myWeapon; 
}Player;

// No one loves me lol
 
Player ahri = {0, PHEIGHT, 0, 1, 1, 0, RIGHT, 0, stick}; 

#endif
