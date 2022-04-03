#include "z_Projection.h"

Matrix4 camtrans(Camera &cam){
    Matrix4 result = getIdentityMatrix();
    result.val[0][0] = cam.u.x;
    result.val[0][1] = cam.u.y;
    result.val[0][2] = cam.u.z;
    result.val[0][3] = -dotProductVec3(cam.u, cam.pos);
    result.val[1][0] = cam.v.x;
    result.val[1][1] = cam.v.y;
    result.val[1][2] = cam.v.z;
    result.val[1][3] = -dotProductVec3(cam.v, cam.pos);
    result.val[2][0] = cam.w.x;
    result.val[2][1] = cam.w.y;
    result.val[2][2] = cam.w.z;
    result.val[2][3] = -dotProductVec3(cam.w, cam.pos);

    return result;
}

Matrix4 ortographic(Camera &cam){
    double r = cam.right;
    double l = cam.left;
    double b = cam.bottom;
    double t = cam.top;
    double f = cam.far;
    double n = cam.near;

    Matrix4 result = getIdentityMatrix();
    result.val[0][0] = 2 / (r-l);
    result.val[1][1] = 2 / (t-b);
    result.val[2][2] = -2 / (f-n);
    result.val[0][3] = -(r+l) / (r-l);
    result.val[1][3] = -(t+b) / (t-b);
    result.val[2][3] = -(f+n) / (f-n);

    return result;
}

Matrix4 perspective(Camera &cam){
    double f = cam.far;
    double n = cam.near;

    Matrix4 p2o;
    p2o.val[0][0] = n;
    p2o.val[1][1] = n;
    p2o.val[2][2] = f + n;
    p2o.val[2][3] = f * n;
    p2o.val[3][2] = -1;

    return p2o;
}

Matrix4 viewport(Camera &cam){
    int nx = cam.horRes;
    int ny = cam.verRes;

    Matrix4 result;
    result.val[0][0] = nx / 2.0;
    result.val[1][1] = ny / 2.0;
    result.val[2][2] = 1/2.0;
    result.val[2][3] = 1/2.0;
    result.val[0][3] = (nx - 1) / 2.0;
    result.val[1][3] = (ny - 1) / 2.0;

    return result;
}