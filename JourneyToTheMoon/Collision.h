#ifndef COLLISION_H
#define COLLISION_H

void verticalCollide(Rect object);
void horizontalCollide(byte dir); 
void groundCollide();
byte enemyHit(Rect swordRect, Rect enemyRect);
byte boundsChecking(int a, int b, int i);

#endif
