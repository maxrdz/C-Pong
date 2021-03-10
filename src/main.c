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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
#define VSYNC true

void render() {

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

	debug("\n------------ C-Pong ------------\n");
	debug("\nCopyright (C) 2020 Max Rodriguez \n\n");

	// Initialize Window
	S2D_Window *window = S2D_CreateWindow(
    	"C-Pong",	// Win Title
		WIN_WIDTH, 	// Win Width
		WIN_HEIGHT, // Win Height
		update, 	// Update Function Reference
		render, 	// Render Function Reference
		0 			// Window Flags
  	);

	window -> fps_cap = FPS_MAX; // Window FPS Limit
	window -> vsync = VSYNC; // Vsync Mode

	// Launch Window
  	S2D_Show(window);

	// Program Exit
	S2D_Close(window);
	S2D_FreeWindow(window);
	return EXIT_SUCCESS;

}