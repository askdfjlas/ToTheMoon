#include "Input.h"

void getInputs() {
  if(arduboy.pressed(RIGHT_BUTTON)) {
    ahri.x += SPEED;
    horizontalCollide(RIGHT);
  }
  if(arduboy.pressed(LEFT_BUTTON)) {
    ahri.x -= SPEED;
    horizontalCollide(LEFT);
  }
  if(arduboy.pressed(A_BUTTON) && ahri.airborn == 0) {
    ahri.yVel = JUMP;
  }
}

