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

# Installed S2D Libraries
LIBPATH = /usr/include/SDL2
LIBS = -lsimple2d -lSDL2 -lGL -lm -lSDL2_image -lSDL2_mixer -lSDL2_ttf

all: build

# ----- Build Source ------ #

build:
	$(CC) src/main.c -I$(LIBPATH) $(LIBS) $(CFLAGS) -o bin/cpong-amd64