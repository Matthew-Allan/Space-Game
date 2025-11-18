#include "program.h"

// Create an SDL window and an OpenGL context.
SDL_Window *createWindow() {
    // Init SDL.
    printf("Initing SDL.\n");
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not init SDL: %s\n", SDL_GetError());
        return NULL;
    }

    // Set profile to core and version.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, GL_MAJOR_VER);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, GL_MINOR_VER);

    // Create the SDL window.
    printf("Creating window.\n");
    SDL_Window *window = SDL_CreateWindow(
        PROGRAM_NAME,                                   // Window title
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, // Center the x and y position on the screen.
        SCREEN_WIDTH, SCREEN_HEIGHT,                    // Set height and width.
        WINDOW_FLAGS                                    // (Flags) Open window useable with OpenGL context.
    );

    // Check that the window was created.
    if(!window) {
        printf("Failed to create window: %s\n", SDL_GetError());
        return NULL;
    }

    // Create a GL context.
    printf("Creating context.\n");
    SDL_GL_CreateContext(window);

    // Give glad the function loader specific to the OS.
    printf("Loading GL loader.\n");
    if(!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
        printf("Failed to load GL\n");
        return NULL;
    }

    // Set viewport to the correct width and height.
    int width, height;
    SDL_GetWindowSizeInPixels(window, &width, &height);
    glViewport(0, 0, height, width);

    // Set clear colour to black.
    glClearColor(0, 0, 0, 1.0f);

    // Return a pointer to the window.
    return window;
}

int createProgram(Program *program) {
    program->window = createWindow();
    program->running = 1;
    program->delta_time = 0;
    program->prev_time = SDL_GetTicks64();
    return program->window == NULL ? -1 : 0;
}

// Loop until enough time has passed for the fps to be correct.
void waitForFrame(Program *program) {
    uint64_t time_value;
    while((time_value = SDL_GetTicks64()) - program->prev_time < (1000 / fps)) {
        SDL_Delay(1);
    }
    // Work out time between last frame and this one.
    program->delta_time = time_value - program->prev_time;
    program->prev_time = time_value;
}