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
	// All on update()
}

/* S2D Update Function */

void update() {

	// Ticks Reset (avoids overflow) //
	if (tick_counter == 30) tick_counter = 0;

	// Define Version Tag
	char version_string[12];
	snprintf(version_string, 12, "Version %s", VERSION);

	version_tag = S2D_CreateText(
		"res/Press-Start-2P.ttf",
		version_string, 10);

	version_tag -> x = WIN_WIDTH / 40;
	version_tag -> y = WIN_HEIGHT / 1.04;

	// Define Lives Counter
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

	// --- Main Game States --- //

	if (game_start == false) {

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

		switch (start_txt) {

			case true:

				play -> color.a = 1.0;

				if (tick_counter % 30 == 0) {
					debug("Start Text Drawn.\n");
					start_txt = false;
				}
				break;

			case false:

				play -> color.a = 0.0;

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

		// Draw Text Objects
		S2D_DrawText(title);
		S2D_DrawText(play);

	} else {

		/* ----- Global Features ----- */

		// Create Catch Counter
		char counter_string[10];
		sprintf(counter_string, "%i - %i", ai_catches, plr_catches);

		catch_counter = S2D_CreateText(
			"res/Press-Start-2P.ttf",
			counter_string, 20);

		catch_counter -> x = WIN_WIDTH / 2.35;
		catch_counter -> y = WIN_HEIGHT / 30;

		// Update the Player Paddle
		int *p_plr_x = &plr_x;
		int *p_plr_y = &plr_y;
		paddle_update(plr_paddle, p_plr_x, p_plr_y);

		// Update the AI Paddle
		int *p_ai_x = &ai_x;
		int *p_ai_y = &ai_y;
		paddle_update(ai_paddle, p_ai_x, p_ai_y);

		// Ball Positioning & Bouncing


		/* ----- Fun Mode Features ----- */

		if (fun_mode) {

			// Define Enabled Text
			fun_text = S2D_CreateText(
				"res/Press-Start-2P.ttf",
				"Fun Mode Enabled", 10);

			fun_text -> x = WIN_WIDTH / 2.6;
			fun_text -> y = WIN_HEIGHT / 1.04;

			fun_text -> color.g = 0.0;
			fun_text -> color.b = 0.7;

			// Ball color loop (every third tick)
			if (tick_counter % 3) {

				// Reset Ball Color Step
				if (chain_track == 10) chain_track = 0;

				// Set Next Ball Color
				b_color[0] = chain[chain_track - 1][0];
				b_color[1] = chain[chain_track - 1][1];
				b_color[2] = chain[chain_track - 1][2];
				b_color[3] = chain[chain_track - 1][3];
				chain_track++;

			}
		}

		/* ------ Draw Objects ------ */

		S2D_DrawQuad( // Plr Pad
			plr_paddle[0][0], plr_paddle[0][1], 1.0, 1.0, 1.0, 1.0,
			plr_paddle[1][0], plr_paddle[1][1], 1.0, 1.0, 1.0, 1.0,
			plr_paddle[2][0], plr_paddle[2][1], 1.0, 1.0, 1.0, 1.0,
			plr_paddle[3][0], plr_paddle[3][1], 1.0, 1.0, 1.0, 1.0);

		S2D_DrawQuad( // AI Pad
			ai_paddle[0][0], ai_paddle[0][1], 1.0, 1.0, 1.0, 1.0,
			ai_paddle[1][0], ai_paddle[1][1], 1.0, 1.0, 1.0, 1.0,
			ai_paddle[2][0], ai_paddle[2][1], 1.0, 1.0, 1.0, 1.0,
			ai_paddle[3][0], ai_paddle[3][1], 1.0, 1.0, 1.0, 1.0);

		S2D_DrawCircle( // Ball
			ball_x, ball_y, ball_radius,
			ball_sectors, b_color[0], b_color[1],
			b_color[2], b_color[3]);

	}

	/* ------ Following Drawn On Top ------ */

	// Last Drawn to Screen
	S2D_DrawText(version_tag);
	S2D_DrawText(lives_count);
	S2D_DrawText(fun_text);
	S2D_DrawText(catch_counter);

	tick_counter++; // Add tick

}

/* Update Paddles */

void paddle_update(int pad[4][2], int *x, int *y) {

	// Paddle 'Y' Position Margin
	if (*y < y_margin)
		*y = y_margin;
	else if (*y > WIN_HEIGHT - y_margin)
		*y = WIN_HEIGHT - y_margin;

	// Create Updated Paddle Position
	pad[0][0] = (*x + (pad_w / 2));
	pad[0][1] = (*y + (pad_h / 2));

	pad[1][0] = (*x - (pad_w / 2));
	pad[1][1] = (*y + (pad_h / 2));

	pad[2][0] = (*x - (pad_w / 2));
	pad[2][1] = (*y - (pad_h / 2));

	pad[3][0] = (*x + (pad_w / 2));
	pad[3][1] = (*y - (pad_h / 2));

}

/* S2D On Key Callback */

void input(S2D_Event event) {

	switch (event.type) {

		case S2D_KEY_DOWN:
			debug("Key Pressed!\n");
			key_actions(*event.key, S2D_KEY_DOWN);
			break;

		case S2D_KEY_HELD:
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
			} break;

		case 'U':
			if (game_start) plr_y = plr_y - 2; break;

		case 'D':
			if (game_start) plr_y = plr_y + 2; break;

		case 'W':
			if (game_start) ai_y = ai_y - 2; break;

		case 'S':
			if (game_start) ai_y = ai_y + 2; break;

	}
}