/*
    Pong.c Header File
*/

#ifndef INCLUDED
#define INCLUDED

// Paddle Properties
const int paddle_x = 550;
const int paddle_h = 60;
const int paddle_w = 20;

// Ball Properties
const int ball_radius = 20;

// Screen Objects
S2D_Text *title;
S2D_Text *play;

// Debug Function
void debug(char input[]);

// Delay Function
void delay(int mseconds);

// Simple2D Functions
void render();
void update();
void input(S2D_Event event);

// Check Flags
void read_flags(int argc, char *argv[]);

// Key Actions
void key_actions(char key, int state);

// Miscellaneous Variables
bool start_txt = true;
int txt_cooldown = 0;

#endif