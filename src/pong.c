/*
  ============ C-Pong =============

    A 2D pong game written in C.
	Using the Simple2D library.

     Tested on a Linux system.

  ---------------------------------

     Author: 	Max Rodriguez
     Created: 	3-3-2021
     Revised: 	4-5-2021

  Copyright (C) 2020 Max Rodriguez

    Licensed under Apache 2.0.

  ---------------------------------
*/

#define VERSION "1.0"
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

			debug_mode = true; // Set Mode

		} else if (strcmp(argv[i], "-f") == 0) {

			fun_mode = true; lives = 999;

			paddle_speed = paddle_speed * 2;
			ball_speed = ball_speed * 1.7;

			srand(time(NULL));
			int result_x = rand() % 2;
			int result_y = rand() % 2;

			debug("\nBall Kick-Off 'x': ");
			switch (result_x) {
				case 1: debug("+1\n");
				ball_state[0] = 1; break;
				case 0: debug("-1\n");
				ball_state[0] = -1; break;
			}

			debug("Ball Kick-Off 'y': ");
			switch (result_y){
				case 1: debug("+1\n\n");
				ball_state[1] = 1; break;
				case 0: debug("-1\n\n");
				ball_state[1] = -1; break;
			}
		}
	}
}

/* Debug Output Function */

void debug(char input[]) {

	if (debug_mode == true) {
		printf("%s", input);
	}
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
	char life_str[3];
	sprintf(life_str, "%i", lives);

	char lives_string[12];
	snprintf(lives_string, 12, "%s Lives", life_str);

	lives_count = S2D_CreateText(
		"res/Press-Start-2P.ttf",
		lives_string, 13);
		
	lives_count -> x = WIN_WIDTH / 1.25;
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
				if (tick_counter % 30 == 0) start_txt = false;
				break;

			case false:
				play -> color.a = 0.0;
				if (tick_counter % 30 == 0) start_txt = true;
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
		sprintf(counter_string, "%i - %i", left_catches, right_catches);

		catch_counter = S2D_CreateText(
			"res/Press-Start-2P.ttf",
			counter_string, 20);

		catch_counter -> x = WIN_WIDTH / 2.35;
		catch_counter -> y = WIN_HEIGHT / 30;

		// Update the Right Paddle
		float *p_rx = &right_x;
		float *p_ry = &right_y;
		paddle_update(right_paddle, p_rx, p_ry);

		// Update the Left Paddle
		float *p_lx = &left_x;
		float *p_ly = &left_y;
		paddle_update(left_paddle, p_lx, p_ly);

		// Ball Vertical Bounce
		if (ball_y <= court_margin || 
			ball_y >= WIN_HEIGHT - court_margin) {

			debug("Ball Bounced on court margin!\n");
			ball_state[1] = ball_state[1] * (-1);
		}

		// Ball Horizontal Bounce [Right Paddle]
		if ((ball_x + ball_radius) >= (right_x - (pad_w / 2))) {

			if (ball_y <= (right_y + (pad_h / 2)) &&
				ball_y >= (right_y - (pad_h / 2))) {

				debug("Ball Bounced on right paddle!\n");
				ball_state[0] = ball_state[0] * (-1);

			} else {

				debug("Ball Missed!\n");
				if (lives > 0) lives = lives - 1;
				ball_x = WIN_WIDTH / 2;
				ball_y = WIN_HEIGHT / 2;
			}
		}

		// Ball Horizontal Bounce [Left Paddle]
		if ((ball_x - ball_radius) <= (left_x + (pad_w / 2))) {

			if (ball_y <= (left_y + (pad_h / 2)) &&
				ball_y >= (left_y - (pad_h / 2))) {

				debug("Ball Bounced on right paddle!\n");
				ball_state[0] = ball_state[0] * (-1);

			} else {

				debug("Ball Missed!\n");
				if (lives > 0) lives = lives - 1;
				ball_x = WIN_WIDTH / 2;
				ball_y = WIN_HEIGHT / 2;
			}
		}

		// Update Ball x/y Position
		ball_x += ball_state[0] * ball_speed;
		ball_y += ball_state[1] * ball_speed;

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
			if (tick_counter % 3 == 0) {

				// Reset Ball Color Step
				if (chain_track == 10) chain_track = 0;

				// Set Next Ball Color
				for (int i = 0; i <= 3; i++) {
					b_color[i] = chain[chain_track - 1][i];
				} chain_track++;
				
			}
		}

		/* ------ Draw Objects ------ */

		if (lives != 0) {

			S2D_DrawQuad( // Right Paddle
				right_paddle[0][0], right_paddle[0][1], 1.0, 1.0, 1.0, 1.0,
				right_paddle[1][0], right_paddle[1][1], 1.0, 1.0, 1.0, 1.0,
				right_paddle[2][0], right_paddle[2][1], 1.0, 1.0, 1.0, 1.0,
				right_paddle[3][0], right_paddle[3][1], 1.0, 1.0, 1.0, 1.0);

			S2D_DrawQuad( // Left Paddle
				left_paddle[0][0], left_paddle[0][1], 1.0, 1.0, 1.0, 1.0,
				left_paddle[1][0], left_paddle[1][1], 1.0, 1.0, 1.0, 1.0,
				left_paddle[2][0], left_paddle[2][1], 1.0, 1.0, 1.0, 1.0,
				left_paddle[3][0], left_paddle[3][1], 1.0, 1.0, 1.0, 1.0);

			S2D_DrawCircle( // Court Ball
				ball_x, ball_y, ball_radius,
				ball_sectors, b_color[0], b_color[1],
				b_color[2], b_color[3]);

		} else {

			// Game Over Text
			game_over = S2D_CreateText(
				"res/Press-Start-2P.ttf",
				"Game Over", 50);

			game_over -> color.g = 0.0;
			game_over -> color.b = 0.0;

			game_over -> x = WIN_WIDTH / 5.8;
			game_over -> y = WIN_HEIGHT / 2.5;

			switch (start_txt) {

				case true:
					game_over -> color.a = 1.0;
					if (tick_counter % 30 == 0) start_txt = false;
					break;

				case false:
					game_over -> color.a = 0.0;
					if (tick_counter % 30 == 0) start_txt = true;
					break;
			}

			S2D_DrawText(game_over);

		}
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

void paddle_update(int pad[4][2], float *x, float *y) {

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

/* S2D Render */
void render() {}

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
			if (game_start)
			right_y = right_y - paddle_speed; break;

		case 'D':
			if (game_start)
			right_y = right_y + paddle_speed; break;

		case 'W':
			if (game_start)
			left_y = left_y - paddle_speed; break;

		case 'S':
			if (game_start)
			left_y = left_y + paddle_speed; break;

	}
}