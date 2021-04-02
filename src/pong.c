/*
  ============ C-Pong =============

    A 2D pong game written in C.
	Using the Simple2D library.

     Tested on a Linux system.

  ---------------------------------

     Author: 	Max Rodriguez
     Created: 	3-3-2021
     Revised: 	4-1-2021

  Copyright (C) 2020 Max Rodriguez

    Licensed under Apache 2.0.

  ---------------------------------
*/

#define VERSION "1.0"
#define FPS_MAX 60
#define VSYNC true
#define WIN_WIDTH 640
#define WIN_HEIGHT 480

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

/* S2D Render Function */

void render() {

	// Game Title Text //
	title = S2D_CreateText(
		"res/Blippo-Bold.ttf",
		"PONG", 150);

	title -> x = WIN_WIDTH / 4.6;
	title -> y = WIN_HEIGHT / 5.5;

	title -> color.r = 1.0;
	title -> color.g = 0.9;
	title -> color.b = 0.0;

	// Press Start Text //
	play = S2D_CreateText(
		"res/Press-Start-2P.ttf",
		"Press A To Start", 20);

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
				"Fun Mode ON!", 15);

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

		/* ----- Global Features ----- */

		// Keep Paddle 'y' within margin.
		if (pad_y < y_margin)
			pad_y = y_margin;
		else if (pad_y > WIN_HEIGHT - y_margin)
			pad_y = WIN_HEIGHT - y_margin;

		// Set new paddle pos, anchor at center.
		paddle[0][0] = (pad_x + (pad_w / 2));
		paddle[0][1] = (pad_y + (pad_h / 2));

		paddle[1][0] = (pad_x - (pad_w / 2));
		paddle[1][1] = (pad_y + (pad_h / 2));

		paddle[2][0] = (pad_x - (pad_w / 2));
		paddle[2][1] = (pad_y - (pad_h / 2));

		paddle[3][0] = (pad_x + (pad_w / 2));
		paddle[3][1] = (pad_y - (pad_h / 2));

		// Ball Positioning & Bouncing


		/* ----- Fun Mode Features ----- */

		if (fun_mode) {

			// TODO: Make Fun mode lol
			fun_text = S2D_CreateText(
				"res/Press-Start-2P.ttf",
				"Fun Mode - Work In Progress", 14);

			fun_text -> x = WIN_WIDTH / 4.8;
			fun_text -> y = WIN_HEIGHT / 30;
			S2D_DrawText(fun_text);

		}

		/* ------ Draw Objects ------ */

		S2D_DrawQuad(
			paddle[0][0], paddle[0][1], 1.0, 1.0, 1.0, 1.0,
			paddle[1][0], paddle[1][1], 1.0, 1.0, 1.0, 1.0,
			paddle[2][0], paddle[2][1], 1.0, 1.0, 1.0, 1.0,
			paddle[3][0], paddle[3][1], 1.0, 1.0, 1.0, 1.0);

		S2D_DrawCircle(
			ball_x, ball_y, ball_radius,
			ball_sectors, b_color[0], b_color[1],
			b_color[2], b_color[3]);

	}

	/* ------ Following Drawn On Top ------ */

	// Game Version Tag //
	char version_string[12];
	snprintf(version_string, 12, "Version %s", VERSION);

	version_tag = S2D_CreateText(
		"res/Press-Start-2P.ttf",
		version_string, 10);

	version_tag -> x = WIN_WIDTH / 40;
	version_tag -> y = WIN_HEIGHT / 1.04;

	// Lives Counter Text //
	char life_str[1];
	sprintf(life_str, "%i", lives);

	char lives_string[9];
	snprintf(lives_string, 9, "%s Lives", life_str);

	lives_count = S2D_CreateText(
		"res/Press-Start-2P.ttf",
		lives_string, 13);
	
	lives_count -> x = WIN_WIDTH / 1.23;
	lives_count -> y = WIN_HEIGHT / 1.04;

	lives_count -> color.g = 0.0;
	lives_count -> color.b = 0.0;

	// Draw to Screen
	S2D_DrawText(version_tag);
	S2D_DrawText(lives_count);

	tick_counter++; // Add tick

}

/* S2D On Key Callback */

void input(S2D_Event event) {

	switch (event.type) {

		case S2D_KEY_DOWN:
			debug("Key Pressed!\n");
			key_actions(*event.key, S2D_KEY_DOWN);
			break;

		case S2D_KEY_HELD:
			debug("Key Being Held!\n");
			key_actions(*event.key, S2D_KEY_HELD);
			break;

		case S2D_KEY_UP:
			debug("Key Released!\n");
			key_actions(*event.key, S2D_KEY_UP);
			break;

	}
}

/* Key Stroke Actions */

void key_actions(char key, int state) {

	// Not counting key release.
	if (state == 3) return;

	switch (key) {

		case 'A':

			if (game_start == false) {
				debug("Game START!\n");
				game_start = true;
			}
			break;

		case 'U':
			if (game_start) pad_y = pad_y - 2; break;

		case 'D':
			if (game_start) pad_y = pad_y + 2; break;

	}
}