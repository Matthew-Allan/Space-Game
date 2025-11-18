#include "camera.h"

#include <stddef.h>

void initCam(Camera *cam, vec3 pos) {
    cam->fov = M_PI_4;
    initTrans(&cam->trans, pos, NULL);
}

void uploadCamMat(Camera *cam, GLuint camLoc) {
    mat4 cam_mat;
    invTransMat(&cam->trans, cam_mat);

    mat4 projection = perspMat(cam->fov, 1, 0.1, 100);
    mat4Mlt(projection, cam_mat, cam_mat, 1);

    glUniformMatrix4fv(camLoc, 1, GL_FALSE, marr(cam_mat));
}