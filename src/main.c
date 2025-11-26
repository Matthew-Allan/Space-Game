#include "core/program.h"
#include "core/shader.h"
#include "core/camera.h"
#include "core/quaternion.h"
#include "core/vaos.h"
#include "core/flags.h"

#include "objectshad.h"
#include "beltshad.h"
#include "ship.h"

int pollEvents(Program *program) {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            program->running = 0;
            break;
        case SDL_WINDOWEVENT:
            if(event.window.event == SDL_WINDOWEVENT_RESIZED) {
                updateViewport(program);
            }
        case SDL_KEYDOWN:
            if(event.key.keysym.scancode == SDL_SCANCODE_P) {
                toggleFullscreen(program);
            }
        }
    }
    return 0;
}

#define SCD(key) SDL_SCANCODE_ ## key
const enum SDL_Scancode input_order[] = {
    SCD(W), SCD(S), SCD(A), SCD(D), SCD(R), SCD(F),
    SCD(UP), SCD(DOWN), SCD(RIGHT), SCD(LEFT), SCD(E), SCD(Q)
};

SHIP_Flags getInputFlags(const Uint8 *keystate) {
    SHIP_Flags flags = 0;
    for(int i = 0; i < 12; i++) {
        flags |= keystate[input_order[i]] << i;
    }
    return flags;
}

// Run the game and gameloop in the given window.
int runGame(Program *program) {
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // Set clear colour to black.
    glClearColor(0.05, 0.05, 0.05, 1.0f);

    // Compile the shaders into a program.
    ObjectShader obj_shader;
    if(buildObjectShader(&obj_shader) == -1) {
        return -1;
    }
    BeltShader belt_shader;
    if(buildBeltShader(&belt_shader) == -1) {
        return -1;
    }

    Camera cam;
    vec3 pos = vec3(0, 0, 0);
    initCam(&cam, pos);

    Transform planet;
    initTrans(&planet, ORIGIN_VEC, NULL);

    ShipData ship;
    initShip(&ship);
    parentTrans(&cam.trans, &ship.trans);

    VertexArrObj cube_VAO, station_VAO;
    if(loadVAO(&cube_VAO, "models/Cube.obj") == -1) {
        return -1;
    }
    if(loadVAO(&station_VAO, "models/Monkey.obj") == -1) {
        return -1;
    }

    const Uint8 *keystate;

    // Main game loop
    while(program->running) {
        pollEvents(program);
        keystate = SDL_GetKeyboardState(NULL);

        // Rotate planet.
        float angle = 0.0003f * program->prev_time;
        quatFromEuler(planet.orientation, angle, angle, angle);

        // Move the ship;
        handleInput(&ship, getInputFlags(keystate), program->delta_time);
        applyVelocity(&ship);

        float aspect = (float) program->width / program->height;

        // Clear the screen and draw the grid to the screen.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(obj_shader.program);
        uploadCamMat(&cam, obj_shader.cam, aspect);
        
        // Draw planet.
        uploadTransMat(&planet, obj_shader.model);
        drawVAO(&station_VAO);

        // Draw asteroids.
        glUseProgram(belt_shader.program);
        uploadCamMat(&cam, belt_shader.cam, aspect);
        drawVAOInstanced(&cube_VAO, 20000);

        // Swap the buffers.
        SDL_GL_SwapWindow(program->window);
        waitForFrame(program);
    }

    return 0;
}

int main(int argc, char const *argv[]) {
    // Create the window
    Program program;
    if(createProgram(&program) == 0) {
        runGame(&program);
    }

    // Quit and return.
    SDL_Quit();
    return 0;
}
