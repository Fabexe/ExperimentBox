# Makefile to build SDL example in c/movements/src
# Targets: all (uses pkg-config if present), windows (MinGW), clean

CC = gcc
CFLAGS = -std=c11 -O2 -Wall
SRC = main_sdl.c
OUT = main_sdl

.PHONY: all windows clean

all: pkgconfig

pkgconfig:
	@echo "Building using pkg-config (sdl3) if available..."
	@if command -v pkg-config >/dev/null 2>&1 && pkg-config --exists sdl3; then \
		$(CC) $(CFLAGS) $(shell pkg-config --cflags sdl3) $(SRC) -o $(OUT) $(shell pkg-config --libs sdl3); \
	else \
		echo "pkg-config sdl3 not found — falling back to ../include and ../lib"; \
		$(CC) $(CFLAGS) -I../include -L../lib $(SRC) -o $(OUT) -lSDL3; \
	fi

windows:
	@echo "Building for Windows (MinGW) using ../include and ../lib"
	$(CC) $(CFLAGS) -I../include -L../lib $(SRC) -o $(OUT).exe -lSDL3

clean:
	rm -f $(OUT) $(OUT).exe
