/*
  =========== C-Pong ============

   A 2D pong game written in C.

  -------------------------------

    Author: 	Max Rodriguez
    Created: 	3-3-2021
    Revised: 	3-4-2021

  -------------------------------

*/

//#include "../deps/simple2d/include/simple2d.h"
#include "../include/cpong.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Debugging Mode */
#define DEBUG 1

#if (DEBUG == 1)
	const char* debug(char input[]) {
		printf("%s", input);
	}
#else
	const char* debug(char* input) {
		// No Debug Output
	}
#endif

void debugmode() {
	char str[] = "----- Debugging Mode -----\n";
	debug(str);
}

int main() {

	debugmode();

	return EXIT_SUCCESS;

}