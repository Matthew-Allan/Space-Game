#include "core/program.h"
#include "core/shader.h"
#include "core/camera.h"
#include "core/quaternion.h"

#include "objects.h"
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
        }
    }
    return 0;
}

#define SCD(key) SDL_SCANCODE_ ## key
const enum SDL_Scancode input_order[] = {
    SCD(W), SCD(S), SCD(A), SCD(D), SCD(R), SCD(F),
    SCD(UP), SCD(DOWN), SCD(RIGHT), SCD(LEFT), SCD(E), SCD(Q)
};

uint16_t getInputFlags(const Uint8 *keystate) {
    uint16_t flags = 0;
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

    VertexArrObj cubeVAO;
    createCube(&cubeVAO);

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

        // Clear the screen and draw the grid to the screen.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(obj_shader.program);
        uploadCamMat(&cam, obj_shader.cam);
        
        // Draw planet.
        uploadTransMat(&planet, obj_shader.model);
        drawCube(&cubeVAO);

        // Draw asteroids.
        glUseProgram(belt_shader.program);
        uploadCamMat(&cam, belt_shader.cam);
        drawCubes(&cubeVAO, 100000);

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
