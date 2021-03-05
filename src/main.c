/*
  ============ C-Pong =============

    A 2D pong game written in C.

  ---------------------------------

     Author: 	Max Rodriguez
     Created: 	3-3-2021
     Revised: 	3-5-2021

  Copyright (C) 2020 Max Rodriguez

   Using the Simple2D Project,
   copyright at ../deps/simple2d.

  ---------------------------------

*/

#include <stdio.h>
#include <stdlib.h>
#include <simple2d.h>

/* Debugging Mode */
#define DEBUG 1

#if (DEBUG == 1)
	void debug(char input[]) {
		printf("%s", input);
	}
#else
	void debug(char input[]) {
		// Debug Output Disabled
	}
#endif

/* Window Properties */
#define WIN_WIDTH 640
#define WIN_HEIGHT 480
#define FPS_MAX 60

void properties() {

	// Set Window Icon
	S2D_SetIcon(window, "res/icon.png");

	// Set Window FPS Limit
	window -> fps_cap = FPS_MAX;

}

void render() {

	// Window Background Color
	window -> background.r = 1.0;
	window -> background.g = 0.5;
	window -> background.b = 0.8;
	window -> background.a = 1.0;

	// Draw a Triangle
	S2D_DrawTriangle (
		320,  50, 1, 0, 0, 1,
		540, 430, 0, 1, 0, 1,
		100, 430, 0, 0, 1, 1
	);

}

void update() {
	// Update Function
}

int main() {

	debug("----- Debugging Mode -----\n");

	// Initialize Window
	S2D_Window *window = S2D_CreateWindow (
    	"Copyright (C) 2020 Max Rodriguez",
		WIN_WIDTH, WIN_HEIGHT, NULL, render, 0
  	);

	// Apply Properties
	properties();

	// Launch Window
  	S2D_Show(window);

	// Program Exit
	S2D_Close(window);
	S2D_FreeWindow(window);
	return EXIT_SUCCESS;

}