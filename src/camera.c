#include "camera.h"

void update_cam_vectors(Camera *cam) {
    // Front
    set_vec3(cam->front, cosf(cam->yaw) * cosf(cam->pitch), sinf(cam->pitch), sinf(cam->yaw) * cosf(cam->pitch));
    vec3_norm(cam->front, cam->front);

    // Right
    cross_product(cam->front, cam->world_up, cam->right);
    vec3_norm(cam->right, cam->right);

    // Up
    cross_product(cam->right, cam->front, cam->up);
    vec3_norm(cam->up, cam->up);
}

void init_cam(Camera *cam, vec3 pos, vec3 up, float yaw, float pitch) {
    set_vec3(cam->front, 0, 0, -1);
    cam->movement_speed = DFLT_SPEED;
    cam->mouse_sensitivity = DFLT_SENSITIVITY;
    cam->fov = DFLT_FOV;
    cpy_vec3(pos, cam->pos);
    cpy_vec3(up, cam->world_up);
    cam->yaw = yaw;
    cam->pitch = pitch;
    update_cam_vectors(cam);
}

void cam_move(Camera *cam, CameraMovement dir, uint64_t delta_time) {
    float displacement = (cam->movement_speed * delta_time) / 1000;
    vec3 lr_vec, fb_vec, ud_vec;
    vec3_mlt_slr(cam->front, displacement, fb_vec, 1);
    vec3_mlt_slr(cam->right, displacement, lr_vec, 1);
    vec3_mlt_slr(cam->up, displacement, ud_vec, 1);
    switch (dir) {
    case CAM_FORWARD: vec3_sub(cam->pos, fb_vec, cam->pos, 1);
        break;
    case CAM_BACKWARD: vec3_add(cam->pos, fb_vec, cam->pos, 1);
        break;
    case CAM_RIGHT: vec3_add(cam->pos, lr_vec, cam->pos, 1);
        break;
    case CAM_LEFT: vec3_sub(cam->pos, lr_vec, cam->pos, 1);
        break;
    case CAM_UP: vec3_add(cam->pos, ud_vec, cam->pos, 1);
        break;
    case CAM_DOWN: vec3_sub(cam->pos, ud_vec, cam->pos, 1);
        break;
    }
}

void cam_look(Camera *cam, int32_t xrel, int32_t yrel) {
    cam->pitch -= cam->mouse_sensitivity * yrel;
    cam->yaw += cam->mouse_sensitivity * xrel;

    if(cam->pitch < M_PI_2) {
        cam->pitch = M_PI_2;
    } else if(cam->pitch > M_PI + M_PI_2 - 0.00001) {
        cam->pitch = M_PI + M_PI_2 - 0.00001;
    }

    update_cam_vectors(cam);
}

void cam_scroll(Camera *cam, int32_t scroll) {
    cam->fov += cam->mouse_sensitivity * scroll;

    if(cam->fov < 0.001) {
        cam->fov = 0.001;
    } else if(cam->fov > M_PI_4) {
        cam->fov = M_PI_4;
    }
}

void cam_view(Camera *cam, mat4 mat) {
    mat4 look_at = mat4(
        vec4(cam->right[vecX], cam->up[vecX], cam->front[vecX], 0),
        vec4(cam->right[vecY], cam->up[vecY], cam->front[vecY], 0),
        vec4(cam->right[vecZ], cam->up[vecZ], cam->front[vecZ], 0),
        vec4(0, 0, 0, 1)
    );
    mat4 cam_trans = trans_mat(-cam->pos[vecX], -cam->pos[vecY], -cam->pos[vecZ]);
    mat4_mlt(look_at, cam_trans, mat, 1);
}