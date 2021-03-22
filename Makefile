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

.SILENT:

# Simple2D Dependency
S2DPATH = /usr/include/SDL2
LIBS = -lsimple2d -lSDL2 -lGL -lm -lSDL2_image -lSDL2_mixer -lSDL2_ttf

all: build clean

# ----- Build Source ------ #

build: pong.o
	$(CC) pong.o -I$(S2DPATH) $(LIBS) $(CFLAGS) -o bin/cpong-x86_64

pong.o:
	$(CC) -c src/pong.c -o pong.o

# ----- Clean ----- #

clean:
	rm *.o && echo "Build Success!"