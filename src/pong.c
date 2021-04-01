/*
  ============ C-Pong =============

    A 2D pong game written in C.

     Tested on a Linux system.

  ---------------------------------

     Author: 	Max Rodriguez
     Created: 	3-3-2021
     Revised: 	3-30-2021

  Copyright (C) 2020 Max Rodriguez

    Licensed under Apache 2.0.

  ---------------------------------
*/

#define VERSION "1.1"
#define FPS_MAX 60
#define VSYNC true
#define WIN_WIDTH 640
#define WIN_HEIGHT 480

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <simple2d.h>
#include "pong.h"

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
	window -> icon = "res/icon.png";
	window -> on_key = input;

	// Launch Window Loop
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
	while((now-then) < pause) now = clock();

}

/* S2D Render Function */

void render() {

	// Game Title Text //
	title = S2D_CreateText(
		"res/Blippo-Bold.ttf",
		"PONG", 150
	);

	title -> x = WIN_WIDTH / 4.6;
	title -> y = WIN_HEIGHT / 5.5;

	title -> color.r = 1.0;
	title -> color.g = 0.9;
	title -> color.b = 0.0;

	// Press Start Text //
	play = S2D_CreateText(
		"res/Press-Start-2P.ttf",
		"Press A To Start", 20
	);

	play -> x = WIN_WIDTH / 3.9;
	play -> y = WIN_HEIGHT / 1.74;

	play -> color.r = 1.0;
	play -> color.g = 1.0;
	play -> color.b = 1.0;

}

/* S2D Update Function */

void update() {

	// Ticks Reset (avoids overflow) //
	if (tick_counter == 30) tick_counter = 0;

	// Main Game States //
	if (game_start == false) {

		S2D_DrawText(title);

		switch (start_txt) {

			case true:

				S2D_DrawText(play);

				if (tick_counter % 30 == 0) {
					debug("Start Text Drawn.\n");
					start_txt = false;
				}
				break;

			case false:

				S2D_FreeText(play);

				if (tick_counter % 30 == 0) {
					debug("Start Text Freed.\n");
					start_txt = true;
				}
				break;
		}

		if (fun_mode) {

			fun_tag = S2D_CreateText(
				"res/Press-Start-2P.ttf",
				"Fun Mode ON!", 15
			);

			fun_tag -> x = WIN_WIDTH / 1.55;
			fun_tag -> y = WIN_HEIGHT / 160;
			fun_tag -> rotate = 10;

			fun_tag -> color.r = 1.0;
			fun_tag -> color.g = 0.5;
			fun_tag -> color.b = 1.0;

			if (tick_counter % 2 == 0)
			fun_tag -> color.a = 2.0;
			else fun_tag -> color.a = 0.1;

			S2D_DrawText(fun_tag);
			
		}

	} else {

		/* ----- Regular Features ----- */

		

		/* ----- Fun Mode Features ----- */

		if (fun_mode) {

			// TODO: Make Fun mode lol
			fun_text = S2D_CreateText(
				"res/Press-Start-2P.ttf",
				"Fun Mode - Work In Progress", 14
			);

			fun_text -> x = WIN_WIDTH / 4.8;
			fun_text -> y = WIN_HEIGHT / 30;
			S2D_DrawText(fun_text);

		}

		/* ------ Draw Objects ------ */

		S2D_DrawCircle(
			ball_x, ball_y, ball_radius,
			1, ball_color[0], ball_color[1],
			ball_color[2], ball_color[3]
		);

	}

	/* ------ Following Drawn On Top ------ */

	// Game Version Tag //
	char _version_string[12];
	snprintf(_version_string, 12, "Version %s", VERSION);

	version_tag = S2D_CreateText(
		"res/Press-Start-2P.ttf",
		_version_string, 10
	);

	version_tag -> x = WIN_WIDTH / 40;
	version_tag -> y = WIN_HEIGHT / 1.04;
	S2D_DrawText(version_tag);

	tick_counter++; // Add tick

}

/* S2D On Key Callback */

void input(S2D_Event event) {

	switch (event.type) {

		case S2D_KEY_DOWN:
			debug("Key Pressed!\n");
			key_actions(*event.key, S2D_KEY_DOWN);
			break;

		case S2D_KEY_UP:
			debug("Key Released!\n");
			key_actions(*event.key, S2D_KEY_UP);
			break;

	}
}

/* Key Stroke Actions */

void key_actions(char key, int state) {

	switch (key) {

		case 'A':

			if (game_start == false) {
				debug("Game START!\n");
				game_start = true;
			}
			break;

		case 'U':

			// Paddle Go Up
			break;

		case 'D':

			// Paddle Go Down
			break;

	}

}