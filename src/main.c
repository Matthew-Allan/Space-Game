#include <seng/program.h>
#include <seng/shader.h>
#include <seng/camera.h>
#include <seng/quaternion.h>
#include <seng/vaos.h>
#include <seng/flags.h>

#include "objectshad.h"
#include "beltshad.h"
#include "ship.h"
#include "objects.h"

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

    VertexArrObj vaos[obj_count];
    if(loadVAOs(vaos, obj_paths, obj_count) == -1) {
        return -1;
    }

    // Main game loop
    while(program->running) {
        pollEvents(program);

        // Rotate planet.
        float angle = 0.0003f * program->prev_time;
        quatFromEuler(planet.orientation, angle, angle, angle);

        // Move the ship;
        handleInput(&ship, getInputFlags(program->keystate), program->delta_time);
        applyVelocity(&ship);

        float aspect = (float) program->width / program->height;

        // Clear the screen and draw the grid to the screen.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(obj_shader.program);
        uploadCamMat(&cam, obj_shader.cam, aspect);
        
        // Draw planet.
        uploadTransMat(&planet, obj_shader.model);
        drawVAO(&vaos[OBJ_Monkey]);

        // Draw asteroids.
        glUseProgram(belt_shader.program);
        uploadCamMat(&cam, belt_shader.cam, aspect);
        drawVAOInstanced(&vaos[OBJ_Cube], 20000);

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
