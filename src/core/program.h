#ifndef PROGRAM_H
#define PROGRAM_H

#include <glad/glad.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "config.h"

typedef struct Program {
    SDL_Window *window;
    uint64_t prev_time;
    uint64_t delta_time;
    float frames;
    int running;
} Program;

SDL_Window *createWindow();
int createProgram(Program *program);
void waitForFrame(Program *program);

#endif