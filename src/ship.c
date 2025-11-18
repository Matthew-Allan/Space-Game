#include "ship.h"

#include <stddef.h>

void applyVelocity(ShipData *ship) {
    vec3Add(ship->trans.offset, ship->velocity, ship->trans.offset, 1);
}

void applyForce(ShipData *ship, vec3 force) {
    vec3Add(ship->velocity, force, ship->velocity, 1);
}

void initShip(ShipData *ship) {
    initTrans(&ship->trans, ORIGIN_VEC, NULL);
    setVec3(ship->velocity, 0, 0, 0);
}

void uploadShipMat(ShipData *ship, GLuint modelLoc) {
    mat4 model;
    transMat(&ship->trans, model);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, marr(model));
}