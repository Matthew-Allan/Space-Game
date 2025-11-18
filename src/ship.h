#ifndef SHIP_H
#define SHIP_H

#include "core/transform.h"

#include <glad/glad.h>

typedef struct ShipData {
    Transform trans;
    vec3 velocity;
} ShipData;

void applyVelocity(ShipData *ship);

void applyForce(ShipData *ship, vec3 force);

void initShip(ShipData *ship);

void uploadShipMat(ShipData *ship, GLuint modelLoc);

#endif