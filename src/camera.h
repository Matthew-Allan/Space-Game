#ifndef CAMERA_H
#define CAMERA_H

#include <math.h>
#include <stdint.h>

#include "matrix.h"

typedef enum CameraMovement {
    CAM_FORWARD,
    CAM_BACKWARD,
    CAM_RIGHT,
    CAM_LEFT,
    CAM_UP,
    CAM_DOWN
} CameraMovement;

#define DFLT_YAW         -M_PI_2
#define DFLT_PITCH       M_PI
#define DFLT_SPEED       2.5f
#define DFLT_SENSITIVITY 0.002f
#define DFLT_FOV         M_PI_4

static vec3 DFLT_UP = vec3(0, 1, 0);
static vec3 ORIGIN = vec3(0, 0, 0);

typedef struct Camera {
    vec3 pos;
    vec3 front;
    vec3 up;
    vec3 right;
    vec3 world_up;
    float yaw;
    float pitch;
    float movement_speed;
    float mouse_sensitivity;
    float fov;
} Camera;

void init_cam(Camera *cam, vec3 pos, vec3 up, float yaw, float pitch);

void cam_move(Camera *cam, CameraMovement dir, uint64_t delta_time);
void cam_look(Camera *cam, int32_t xrel, int32_t yrel);
void cam_scroll(Camera *cam, int32_t scroll);

void cam_view(Camera *cam, mat4 mat);

#define init_cam_dflt(cam) init_cam(cam, varr(ORIGIN), varr(DFLT_UP), DFLT_YAW, DFLT_PITCH);

#endif