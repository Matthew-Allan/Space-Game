#ifndef SHIP_H
#define SHIP_H

#include "core/transform.h"

typedef struct ShipData {
    Transform trans;
    vec3 velocity;
} ShipData;

void applyVelocity(ShipData *ship);

void applyForce(ShipData *ship, vec3 force);

void shipThrust(ShipData *ship, vec3 direction, float magnitude);

void handleInput(ShipData *ship, uint16_t flags, uint64_t delta_time);

void initShip(ShipData *ship);

#endif