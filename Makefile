# =============================
#
#      C-Pong | Makefile
#
#     Written for Windows.
#
# -----------------------------
#
#   Run 'make all' to build.
#
# =============================

CC = gcc

# Installed S2D Libraries
LIBPATH = C:\MinGW\include
LIB = simple2d

all: build

# ----- Build Source ------ #

build:
	$(CC) src/main.c -L$(LIBPATH) -l$(LIB) -o bin/cpong-win32.exe