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
    vec3 pos = vec3(0, 3, 900);
    initCam(&cam, pos);
    quatFromEuler(cam.trans.orientation, 0, -M_PI_4 / 2, 0);

    ShipData ship;
    initShip(&ship);
    
    Transform orbit;
    initTrans(&orbit, ORIGIN_VEC, NULL);
    parentTrans(&cam.trans, &orbit);

    VertexArrObj cubeVAO;
    createCube(&cubeVAO);

    vec3 force = vec3(0, 0, 0);

    // Main game loop
    while(program->running) {
        pollEvents(program);

        applyForce(&ship, force);
        applyVelocity(&ship);

        // quaternion rotation;
        float angle = 0.00003f * program->prev_time;
        quatFromEuler(ship.trans.orientation, angle, angle, angle);
        quatFromEuler(orbit.orientation, 0, angle, 0);

        // quatMlt(ship.trans.orientation, rotation, ship.trans.orientation);

        // Clear the screen and draw the grid to the screen.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(obj_shader.program);
        uploadCamMat(&cam, obj_shader.cam);
        uploadShipMat(&ship, obj_shader.model);
        drawCube(&cubeVAO);

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
