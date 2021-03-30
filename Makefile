# =============================
#
#      C-Pong | Makefile
#
# -----------------------------
#
#  Run 'make build' to build.
#
#   Run 'make test' to test.
#
# -----------------------------
#
#    Required Dependencies
#
#    - Simple2D Library
#    - Valgrind Tool
#
# =============================

CC = gcc
CFLAGS = -D_REENTRANT

.SILENT:

build: link clean
test: memtest

# Simple2D Dependency
S2DPATH = /usr/include/SDL2
LIBS = -lsimple2d -lSDL2 -lGL -lm -lSDL2_image -lSDL2_mixer -lSDL2_ttf


# ----- Build Source ------ #

link: pong.o
	$(CC) bin/pong.o -I$(S2DPATH) $(LIBS) $(CFLAGS) -o bin/cpong-x86_64

pong.o:
	$(CC) -c src/pong.c -o bin/pong.o

# ----- Memory Leak Test ----- #

memtest:
	valgrind --tool=memcheck bin/cpong-x86_64 && rm vgcore*

# ----- Clean ----- #

clean:
	rm bin/*.o && echo "[OK]: Build Success!"