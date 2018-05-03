#ifndef EDGYTEXT_H
#define EDGYTEXT_H

// File to store data regarding text display

/* This "Library" isn't really recommended for use – there are many aspects which are poorly implemented such as the text boundaries, there's no 
 *  error checking, Arduboy2.h must be included, and the respective object must be named "arduboy". However, it should still suffice for my own game/use. 
 */

// Maximum Length of a single string of dialogue
#define MAXDIALOGUE 75

// Confusing macro, passing this for fps keeps the framerate the same in the edgyText function
#define DEFAULTFPS 0

// Various border types, which have their respective dimensions
enum borderTypes{BLANK, REGULAR, FULLREC}; 

// Reads in an array of strings, along with the length, then displays it at a specified framerate
void edgyText(char str[][MAXDIALOGUE], int len, byte fps, byte borderType); 

#endif
