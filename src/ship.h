#ifndef SHIP_H
#define SHIP_H

#include "core/transform.h"

typedef struct ShipData {
    Transform trans;
    vec3 velocity;
} ShipData;

void applyVelocity(ShipData *ship);

void applyForce(ShipData *ship, vec3 force);

void initShip(ShipData *ship);

#endif