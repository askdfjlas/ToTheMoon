#ifndef COLLISION_H
#define COLLISION_H

void verticalCollide(Rect object);
void horizontalCollide(byte dir); 
void groundCollide();
byte boundsChecking(int a, int b);

#endif
