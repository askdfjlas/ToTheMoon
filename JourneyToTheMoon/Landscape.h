#ifndef LANDSCAPE_H
#define LANDSCAPE_H

// Number of chunks in respective regions
#define R1LEN 15

// PROGMEM ruined my childhood and gave me depression

// File to manage land

// Region 1
const int R1Rect[R1LEN*4] PROGMEM = {-50, 64, 3, 8, 40, 30, 8, 1, 140, 16, 2, 2, 172, 32, 2, 4, 204, 48, 2, 6, 220, 16, 1, 2, 250, 16, 10, 2, 258, 50, 8, 1, 350, 48, 3, 6,
400, 24, 3, 3, 450, 24, 12, 3, 640, 32, 20, 4, 875, 24, 3, 3, 950, 48, 3, 6, 1000, 24, 3, 3}; 

// Boundaries to make drawing and collision faster
int leftIndex;
int rightIndex;

#endif
