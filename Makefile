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

# -> Simple 2D Library Paths
LIBPATH = C:\Users\maxrc\AppData\Local\simple2d
LIB = simple2d.lib

all: build

# ----- Build Source ------ #

build:
	$(CC) src/main.c -L$(LIBPATH) -l$(LIB) -o bin/cpong-win32.exe