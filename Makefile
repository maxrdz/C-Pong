# =============================
#
#      C-Pong | Makefile
#
#      Written for Linux.
#
# -----------------------------
#
#   Run 'make all' to build.
#
# =============================

CC = gcc
CFLAGS = -D_REENTRANT

# Simple2D Dependency
S2DPATH = /usr/include/SDL2
LIBS = -lsimple2d -lSDL2 -lGL -lm -lSDL2_image -lSDL2_mixer -lSDL2_ttf

all: build

# ----- Build Source ------ #

build:
	$(CC) src/main.c -I$(S2DPATH) $(LIBS) $(CFLAGS) -o bin/cpong-amd64