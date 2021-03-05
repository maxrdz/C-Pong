# ===========================
#
#     C-Pong | Makefile
#
#   Written for Windows OS
#
# ---------------------------
#
#  Run 'make all' to build.
#
# ===========================

CC = gcc
SRC = source

all: build compile clean

# ----- Compile ----- #

compile:
	$(CC) main.o -o bin/cpong-win32.exe

# ----- Build ------ #

build: main.o

main.o:
	$(CC) -c $(SRC)/main.c

# ----- Clean ------ #

clean:
	del *.o