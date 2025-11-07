#include <glad/glad.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "shader.h"
#include "objects.h"
#include "camera.h"
#include "ship.h"

#define SCREEN_WIDTH 600    // Width of the screen in window points (not in pixels).
#define SCREEN_HEIGHT 600   // Height of the screen in window points (not in pixels).

#define GL_MAJOR_VER 3  // The OpenGL major version number to target.
#define GL_MINOR_VER 3  // The OpenGL minor version number to target.

// Flags for when creating a window. Use OpenGL and allow high DPI.
#define WINDOW_FLAGS SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI

// Set the target FPS.
#define fps 60

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
        "SpaceGame",                                    // Window title
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

int pollEvents() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            break;
        }
    }
    return 0;
}

// Run the game and gameloop in the given window.
int runGame(SDL_Window *window) {
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    // Compile the shaders into a program.
    GLuint shader;
    if(buildShader(&shader, "shaders/vert.glsl", "shaders/frag.glsl") == -1) {
        return -1;
    }
    glUseProgram(shader);

    Camera cam;
    init_cam_dflt(&cam);

    ShipData ship;
    init_ship(&ship);

    GLuint modlLoc = glGetUniformLocation(shader, "model");
    GLuint viewLoc = glGetUniformLocation(shader, "view");
    GLuint projLoc = glGetUniformLocation(shader, "projection");

    VertexArrObj cubeVAO;
    createCube(&cubeVAO);

    // Set the time in ms that the game starts.
    uint64_t prev_time = SDL_GetTicks64();
    vec3 force = vec3(0, -0.000001, -0.00001);

    // Main game loop
    int running = 1;
    while(running) {
        applyForce(&ship, force);
        applyVelocity(&ship);

        mat4 view;
        cam_view(&cam, view);
        mat4 projection = persp_mat(cam.fov, 1, 0.1, 100);
        mat4 model = trans_mat(ship.position[vecX], ship.position[vecY], ship.position[vecZ]);

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, marr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, marr(projection));
        glUniformMatrix4fv(modlLoc, 1, GL_FALSE, marr(model));

        // Clear the screen and draw the grid to the screen.
        glClear(GL_COLOR_BUFFER_BIT);
        drawCube(&cubeVAO);

        // Swap the buffers.
        SDL_GL_SwapWindow(window);
        
        // Loop until enough time has passed for the fps to be correct.
        uint64_t time_value;
        while((time_value = SDL_GetTicks64()) - prev_time < (1000 / fps)) {
            pollEvents();
            SDL_Delay(1);
        }
        // Work out time between last frame and this one.
        // uint64_t delta_time = time_value - prev_time;
        prev_time = time_value;
    }

    return 0;
}

int main(int argc, char const *argv[]) {
    // Create the window
    SDL_Window *window = createWindow();

    // If window created, run the game.
    if(window) {
        runGame(window);
    }

    // Quit and return.
    SDL_Quit();
    return 0;
}
