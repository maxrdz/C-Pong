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
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <simple2d.h>

#define WIN_WIDTH 640
#define WIN_HEIGHT 480
#define FPS_MAX 60
#define VSYNC true

bool debug_mode = false;
bool fun_mode = false;


int main(int argc, char *argv[]) {

	// Check Invoked Flags
	read_flags(argc, argv);

	debug("\n------------ C-Pong ------------\n");
	debug("\nCopyright (C) 2020 Max Rodriguez \n\n");

	// Initialize Window
	S2D_Window *window = S2D_CreateWindow(
    	"C-Pong", WIN_WIDTH, WIN_HEIGHT,
		update, render, 0
  	);

	// Window Properties
	window -> fps_cap = FPS_MAX;
	window -> vsync = VSYNC;

	// Launch Window
  	S2D_Show(window);

	// Program Exit
	S2D_Close(window);
	S2D_FreeWindow(window);
	return EXIT_SUCCESS;

}

void read_flags(int argc, char *argv[]) {

	for (int i = 1; i < argc; i++) {

		if (strcmp(argv[i], "-d") == 0) {

			debug_mode = true;

		} else if (strcmp(argv[i], "-f") == 0) {

			fun_mode = true;

		}
	}
}

void debug(char input[]) {

	if (debug_mode == true) {
		printf("%s", input);
	}

}

void render() {

	

}

void update() {
	


}