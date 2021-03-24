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

// Check Program Flags
void read_flags(int argc, char *argv[]);

#endif