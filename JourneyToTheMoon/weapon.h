#ifndef WEAPON_H
#define WEAPON_H

#include "Player.h"

typedef struct weapon{
  const unsigned char* PROGMEM sprite; 
  const unsigned char* PROGMEM spriteA; 

  const byte PROGMEM Wi; 
  const byte PROGMEM Hi;
  
  const byte PROGMEM H1;
  const byte PROGMEM H2; 

  const unsigned char* PROGMEM hitbox; 

  // hitbox rect
  const byte PROGMEM w;
  const byte PROGMEM h; 

  const byte PROGMEM lagFrames; 
  const byte PROGMEM activeStart;
  const byte PROGMEM activeEnd;

  const float PROGMEM multiplier;
}Weapon;

Weapon stick = {stickS, stickA, 3, 10, TRUEY - 4, TRUEY + 7, stickH, 10, 16, 15, 9, 7, 0.5}; 

void updateWeapon();

#endif
