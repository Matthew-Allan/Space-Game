#include <glad/glad.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "shader.h"

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
        "SpaceGame",                                       // Window title
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

// Set up a vertex array object that the game board should be rendered on.
void setupCubeVAO() {
    float verticies[] = {
         1,  1, -1,
         1, -1, -1,
         1,  1,  1,
         1, -1,  1,
        -1,  1, -1,
        -1, -1, -1,
        -1,  1,  1,
        -1, -1,  1
    };

    unsigned int indices[] = {
        5, 3, 1,
        3, 8, 4,
        7, 6, 8,
        2, 8, 6,
        1, 4, 2,
        5, 2, 6,
        5, 7, 3,
        3, 7, 8,
        7, 5, 6,
        2, 4, 8,
        1, 3, 4,
        5, 1, 2
    };

    // Generate a vertex array object.
    GLuint VAO;
    glGenVertexArrays(1, &VAO);

    // Bind the vertex array object.
    glBindVertexArray(VAO);

    // Generate buffer objects.
    GLuint VBO, EBO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind the virtual and element buffer objects.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // Send the vertex and index data to the buffer objects.
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Tell the shader how to interpret the VBO.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    // Enable the attribute.
    glEnableVertexAttribArray(0);
}

// Run the game and gameloop in the given window.
int runGame(SDL_Window *window) {

    // Compile the shaders into a program.
    GLuint shader;
    if(buildShader(&shader, "shaders/vert.glsl", "shaders/frag.glsl") == -1) {
        return -1;
    }
    glUseProgram(shader);

    // Create a vertex object that covers the screen where the game is displayed.
    setupCubeVAO();

    // Set the time in ms that the game starts.
    uint64_t prev_time = SDL_GetTicks64();

    // Main game loop
    int running = 1;
    while(running) {
        // Loop until enough time has passed for the fps to be correct.
        uint64_t time_value;
        while((time_value = SDL_GetTicks64()) - prev_time < (1000 / fps)) {
            SDL_Event event;
            while(SDL_PollEvent(&event)) {
                switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;
                }
            }

            SDL_Delay(1);
        }
        // Work out time between last frame and this one.
        // uint64_t delta_time = time_value - prev_time;
        prev_time = time_value;

        // Clear the screen and draw the grid to the screen.
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Swap the buffers.
        SDL_GL_SwapWindow(window);
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
