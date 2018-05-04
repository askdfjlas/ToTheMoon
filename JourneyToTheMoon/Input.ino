#include "Input.h"

void getInputs() {
  if(arduboy.pressed(RIGHT_BUTTON)) {
    ahri.x += SPEED;
    horizontalCollide(RIGHT);
    if(ahri.frameCount == 0) {
      ahri.facing = RIGHT;
    }
  }
  if(arduboy.pressed(LEFT_BUTTON)) {
    ahri.x -= SPEED;
    horizontalCollide(LEFT);
    if(ahri.frameCount == 0) {
      ahri.facing = LEFT;
    }
  }
  // Fastfalling
  if(arduboy.pressed(DOWN_BUTTON) && ahri.yVel > MINYVEL) {
    ahri.yVel -= 2;
  }
  if(arduboy.pressed(A_BUTTON) && ahri.airborn == 0) {
    ahri.yVel = JUMP;
  }
  if(arduboy.pressed(B_BUTTON) && ahri.frameCount == 0) {
    ahri.frameCount = (ahri.myWeapon).lagFrames;
  }
}

