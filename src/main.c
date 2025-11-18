#include "core/program.h"
#include "core/shader.h"
#include "core/camera.h"
#include "core/quaternion.h"

#include "objects.h"
#include "objectshad.h"
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

// Run the game and gameloop in the given window.
int runGame(Program *program) {
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // Compile the shaders into a program.
    ObjectShader shader;
    if(buildObjectShader(&shader) == -1) {
        return -1;
    }

    Camera cam;
    vec3 pos = vec3(0, 0, 10);
    initCam(&cam, pos);

    ShipData ship;
    initShip(&ship);

    ShipData child;
    initShip(&child);
    parentTrans(&child.trans, &ship.trans);
    child.trans.offset[vecY] = 1;

    VertexArrObj cubeVAO;
    createCube(&cubeVAO);

    vec3 force = vec3(0, 0, 0);

    // Main game loop
    while(program->running) {
        pollEvents(program);

        applyForce(&ship, force);
        applyVelocity(&ship);

        quaternion rotation;
        float angle = 0.0003f * program->delta_time;
        quatFromEuler(rotation, angle, angle, angle);
        quatMlt(ship.trans.orientation, rotation, ship.trans.orientation);

        uploadCamMat(&cam, shader.cam);
        uploadShipMat(&ship, shader.model);

        // Clear the screen and draw the grid to the screen.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        useShader(&shader);
        drawCube(&cubeVAO);
        uploadShipMat(&child, shader.model);
        drawCube(&cubeVAO);

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
