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
LIB = `simple2d --libs`

all: build

# ----- Build ------ #

build:
	$(CC) src/main.c $(LIB) -o bin/cpong-win32.exe