#include "Input.h"

void getInputs() {
  if(arduboy.pressed(RIGHT_BUTTON)) {
    ahri.x += 4;
  }
  if(arduboy.pressed(LEFT_BUTTON)) {
    ahri.x -= 4;
  }
  if(arduboy.pressed(UP_BUTTON)) {
    ahri.y += 4;
  }
  if(arduboy.pressed(DOWN_BUTTON)) {
    ahri.y -= 4;
  }
}

