/*
    Pong.c Header File
*/

#ifndef INCLUDED
#define INCLUDED

// Debug Function
void debug(char input[]);

// Delay Function
void delay(int mseconds);

// Simple2D Functions
void render();
void update();
void on_key(S2D_Event event);

// Check Program Flags
void read_flags(int argc, char *argv[]);

// Screen Objects
S2D_Text *title;
S2D_Text *play;

#endif