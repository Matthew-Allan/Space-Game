#include "vector.h"

typedef struct ShipData {
    vec3 position;
    vec3 velocity;
} ShipData;

void applyVelocity(ShipData *ship);

void applyForce(ShipData *ship, vec3 force);

void init_ship(ShipData *ship);