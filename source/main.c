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

//#include "../deps/simple2d/include/simple2d.h"
#include "../include/cpong.h"

#include <stdio.h>
#include <stdlib.h>

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

int main() {

	debug("----- Debugging Mode -----\n");

	return EXIT_SUCCESS;

}