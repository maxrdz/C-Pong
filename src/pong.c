/*
  ============ C-Pong =============

    A 2D pong game written in C.

     Tested on a Linux system.

  ---------------------------------

     Author: 	Max Rodriguez
     Created: 	3-3-2021
     Revised: 	3-10-2021

  Copyright (C) 2020 Max Rodriguez

    Licensed under Apache 2.0.

  ---------------------------------
*/

#include "pong.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <simple2d.h>

#define FPS_MAX 60
#define VSYNC true
#define WIN_WIDTH 640
#define WIN_HEIGHT 480
#define ICON "res/icon.png"

bool debug_mode = false;
bool fun_mode = false;


int main(int argc, char *argv[]) {

	// Check Invoked Flags
	read_flags(argc, argv);

	printf("\n------------ C-Pong ------------\n");
	printf("\nCopyright (C) 2020 Max Rodriguez \n\n");

	// Initialize Window
	S2D_Window *window = S2D_CreateWindow(
    	"C-Pong", WIN_WIDTH, WIN_HEIGHT,
		update, render, 0
  	);

	// Window Properties
	window -> fps_cap = FPS_MAX;
	window -> vsync = VSYNC;
	window -> icon = ICON;

	// Launch Window
  	S2D_Show(window);

	// Program Exit
	S2D_Close(window);
	S2D_FreeWindow(window);
	return EXIT_SUCCESS;

}

/* Parse Invoked Flags */

void read_flags(int argc, char *argv[]) {

	for (int i = 1; i < argc; i++) {

		if (strcmp(argv[i], "-d") == 0) {

			debug_mode = true;

		} else if (strcmp(argv[i], "-f") == 0) {

			fun_mode = true;

		}
	}
}

/* Debug Output Function */

void debug(char input[]) {

	if (debug_mode == true) {
		printf("%s", input);
	}

}

/* Delay Function */
void delay(int mseconds) {

	long pause;
	clock_t now,then;

	pause = mseconds * (CLOCKS_PER_SEC / 1000);
	now = then = clock();
	while( (now-then) < pause ) now = clock();

}

/* Game Variables */

bool game_start = false;

/* S2D Render Function */

void render() {

	/* ----- Draw Title Screen  ----- */

	S2D_Text *title = S2D_CreateText(
		"res/Blippo-Bold.ttf",
		"PONG", 150
	);

	title -> x = WIN_WIDTH / 4.6;
	title -> y = WIN_HEIGHT / 5.5;

	title -> color.r = 1.0;
	title -> color.g = 0.9;
	title -> color.b = 0.0;
	title -> color.a = 1.0;

	S2D_Text *play = S2D_CreateText(
		"res/Press-Start-2P.ttf",
		"Press A To Start", 20
	);

	play -> x = WIN_WIDTH / 4;
	play -> y = WIN_HEIGHT / 1.74;

	play -> color.r = 1.0;
	play -> color.g = 1.0;
	play -> color.b = 1.0;
	play -> color.a = 1.0;

	S2D_DrawText(title);
	S2D_DrawText(play);

	while (game_start == false) {
		
		S2D_FreeText(play); delay(1000);

		S2D_DrawText(play); delay(1000);

	}

}

/* S2D Update Function */

void update() {

	// Update Function

}