#include "edgyText.h"

// Hidden Prototypes

// An input buffer which waits for the user to input A or B
void inputBuffer(); 

void drawBorder(byte borderType); 

const char testText[][MAXDIALOGUE] PROGMEM = {"Heya, press A or B to progress through text! \0",
"Did you know that you can do the same to go into buildings? \0",
"Like you should try that shop over there! \0",
"... \0", 
"My programmer only put me in here to tell you this. \0", 
"My existence is pitiful. \0", 
"... \0"};

void edgyText(char str[][MAXDIALOGUE], int len, byte fps, byte borderType) {
  // Boundaries which form a rectangle
  byte xLeft, xRight, yBottom, yTop; 
  
  // Sets the right boundaries according to the border type
  switch(borderType) {
    case BLANK: 
      xLeft = 0; 
      xRight = 120; 
      yTop = 0; 
      yBottom = 54; 
      
      break;
    case REGULAR: 
      xLeft = 4; 
      xRight = 116; 
      yTop = 40; 
      yBottom = 56; 

      break;
    case FULLREC: 
      xLeft = 10; 
      xRight = 110; 
      yTop = 10; 
      yBottom = 44; 
      
      break;
  }

  // Set the fps
  if(fps != DEFAULTFPS) {
    arduboy.setFrameRate(fps); 
  }

  // Clear the area before anything
  arduboy.fillRect(xLeft, yTop, (xRight - xLeft + 9), (yBottom - yTop + 13), BLACK); 
  
  int counter = 0; 

  // Iterate through every string in str
  for(int i = 0; i < len; i++) {   
    // Cursor location
    byte x = xLeft;
    byte y = yTop;

    // Draw the border
    drawBorder(borderType); 
    
    // Reads until a null terminator, strlen doesn't work well with PROGMEM stored strings
    while((char)pgm_read_byte(&str[i][counter]) != '\0') {    
      if(!arduboy.nextFrame()) continue; 
      arduboy.display(); 

      // Check if the cursor is out of bounds (x)
      if(x > xRight) { 
        // An extra punctuation mark can be printed
        if((char)pgm_read_byte(&str[i][counter]) == '.' || (char)pgm_read_byte(&str[i][counter]) == '!') { 
          arduboy.print((char)pgm_read_byte(&str[i][counter])); 
          counter++; 
          arduboy.display(); 
        }
      
        x = xLeft; 
        y += 10; 

        // Whitespaces and periods are ignored at the beginning of a newline (imo it looks ugly)
        while((char)pgm_read_byte(&str[i][counter]) == ' ' || (char)pgm_read_byte(&str[i][counter]) == '.') {
          counter++;
        }        
      }
      
      // Check if the cursor is out of bounds (y)
      if(y > yBottom) { 
        // Reset x and y and get user input
        x = xLeft; 
        y = yTop; 
        inputBuffer();     

        // Clear the area
        arduboy.fillRect(xLeft, yTop, (xRight - xLeft + 9), (yBottom - yTop + 13), BLACK); 

        // Redraw the border
        drawBorder(borderType); 

        // Print a "-" indicating continuation, then increment x
        arduboy.setCursor(x, y); 
        arduboy.print("-"); 
        counter; 
        x += 5; 
      }
      
      arduboy.setCursor(x, y); 

      // Print the character and move on to the next one
      arduboy.print((char)pgm_read_byte(&str[i][counter])); 

      // Update the cursor location
      x += 5; 
      
      // Move on to the next character
      counter++; 
    }

    // Wait until the user makes the appropriate button press
    inputBuffer(); 
    
    // Reset the counter and clear the text for the next loop iteration
    counter = 0; 
    arduboy.fillRect(xLeft, yTop, (xRight - xLeft + 9), (yBottom - yTop + 13), BLACK); 
  }
}

void inputBuffer() {
  // Buffer: If the user holds A or B, the next text isn't immediately moved on to
    byte inputBuffer = 0; 
    while(1) {
      // Wait until the user isn't holding either of the buttons
      if(!arduboy.pressed(A_BUTTON) && !arduboy.pressed(B_BUTTON)) {
        inputBuffer = 1; 
      }
      // Once this is the case, the user is allowed to progress
      if((arduboy.pressed(A_BUTTON) || arduboy.pressed(B_BUTTON)) && inputBuffer == 1) {
        return; 
      }
    }
}

void drawBorder(byte borderType) {
  // Draw a border depending on the type
  switch(borderType) {
    case BLANK: 
      // Nothing as the name implies
      break;
    case REGULAR: 
      arduboy.fillRect(0, 35, 128, 2, WHITE); 
      arduboy.fillRect(0, 62, 128, 2, WHITE); 
      arduboy.fillRect(0, 35, 2, 29, WHITE); 
      arduboy.fillRect(126, 35, 2, 29, WHITE); 

      break;
    case FULLREC:  
      // A rectangular border
      arduboy.fillRect(0, 0, 128, 5, WHITE); 
      arduboy.fillRect(0, 59, 128, 5, WHITE); 
      arduboy.fillRect(0, 0, 5, 64, WHITE); 
      arduboy.fillRect(123, 0, 5, 64, WHITE); 

      break;
  }
}

