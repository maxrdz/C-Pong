/*
    Pong.c Header File
*/

#ifndef INCLUDED
#define INCLUDED

// Game Variables
bool game_start = false;
bool start_txt = true;
int tick_counter = 0;
int lives = 3;

// Ball Properties //
const int ball_radius = 20;
const int ball_sectors = 24;
float ball_x = WIN_WIDTH / 2;
float ball_y = WIN_HEIGHT / 2;

double b_color[4] = {
	1.0, 1.0, 1.0, 1.0
};

int ball_state[2] = {1, 1};

// Paddle Properties //
const int y_margin = 25;
const int pad_w = 20;
const int pad_h = 100;

int pad_x = WIN_WIDTH / 1.1;
int pad_y = WIN_HEIGHT / 2;

// Text Objects
S2D_Text *title;
S2D_Text *play;
S2D_Text *fun_tag;
S2D_Text *fun_text;
S2D_Text *version_tag;
S2D_Text *lives_count;

// Debug Function
void debug(char input[]);

// Simple2D Functions
void render();
void update();
void input(S2D_Event event);

// Check Flags
void read_flags(int argc, char *argv[]);

// Key Actions
void key_actions(char key, int state);

// Ball Color Animation
int chain_track = 0;
const float chain[10][4] = {
    {1.0, 0.1, 0.0, 1.0}, // Red
    {1.0, 0.3, 0.0, 1.0}, // Red / Orange
    {1.0, 0.7, 0.0, 1.0}, // Orange / Yellow
    {0.9, 1.0, 0.0, 1.0}, // Yellow
    {0.5, 1.0, 0.0, 1.0}, // Green
    {0.0, 1.0, 0.7, 1.0}, // Cyan
    {0.0, 0.5, 1.0, 1.0}, // Cyan / Blue
    {0.0, 0.0, 1.0, 1.0}, // Blue
    {0.5, 0.0, 1.0, 1.0}, // Purple
    {0.9, 0.0, 0.8, 1.0}  // Purple / Red
};

#endif