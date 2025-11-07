#include "ship.h"

void applyVelocity(ShipData *ship) {
    vec3_add(ship->position, ship->velocity, ship->position, 1);
}

void applyForce(ShipData *ship, vec3 force) {
    vec3_add(ship->velocity, force, ship->velocity, 1);
}

void init_ship(ShipData *ship) {
    set_vec3(ship->position, 0, 0, 0);
    set_vec3(ship->velocity, 0, 0, 0);
}