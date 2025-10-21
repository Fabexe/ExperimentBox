/*
main_sdl.c
Simple SDL3 program that opens a white window and runs an event loop.
Build (Unix with pkg-config):
    gcc -std=c11 main_sdl.c -o main_sdl `pkg-config --cflags --libs sdl3`

Build (Windows MinGW, assuming SDL3 headers/libs are in c/movements):
    gcc -std=c11 -I..\include -L..\lib -o main_sdl.exe main_sdl.c -lSDL3

Run:
    ./main_sdl

This program tries to use SDL3 headers in the repo's include/SDL3 directory if available.
*/

#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char **argv) {
    (void)argc; (void)argv;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init error: %s\n", SDL_GetError());
        return 1;
    }

    /* SDL3: SDL_CreateWindow(title, w, h, flags)
     * Use 0 flags (window will be shown with SDL_ShowWindow)
     */
    SDL_Window *win = SDL_CreateWindow("SDL White Window",
                                       800, 600,
                                       0);
    if (!win) {
        fprintf(stderr, "SDL_CreateWindow error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    /* Ensure the window is shown (SDL_CreateWindow may create a hidden window depending on flags) */
    SDL_ShowWindow(win);

    /* SDL3: SDL_CreateRenderer(window, const char *name)
     * Pass NULL for the default renderer driver.
     */
    SDL_Renderer *ren = SDL_CreateRenderer(win, NULL);
    if (!ren) {
        fprintf(stderr, "SDL_CreateRenderer error: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    bool running = true;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            /* SDL3 event names use SDL_EVENT_* */
            if (e.type == SDL_EVENT_QUIT) running = false;
            if (e.type == SDL_EVENT_KEY_DOWN) {
                /* SDL3 keyboard event: scancode is directly on e.key.scancode */
                if (e.key.scancode == SDL_SCANCODE_ESCAPE) running = false;
            }
        }

        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        SDL_RenderClear(ren);

        SDL_RenderPresent(ren);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
