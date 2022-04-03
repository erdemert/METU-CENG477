#include "z_Transformation.h"

Vec3 translate(Translation *trs, Vec3 point){

   Vec3 result = point;
   result.x += trs->tx;
   result.y += trs->ty;
   result.z += trs->tz;
   return result;
}

double convert(double degree){ 
    return (degree * (M_PI / 180));
}

Vec3 rotate(Rotation *rtn, Vec3 point){
    // Rotation around an arbitrary axis 
    Vec3 axis = Vec3(rtn->ux, rtn->uy, rtn->uz, 0);

    //Get Rx(theta) matrix
    Matrix4 rx = getIdentityMatrix();
    double degree = convert(rtn->angle);
    rx.val[1][1] = cos(degree);
    rx.val[1][2] = -1 * sin(degree);
    rx.val[2][1] = sin(degree);
    rx.val[2][2] = cos(degree);

    //Orthonormal basis
    Vec3 unit = normalizeVec3(axis);
    double x = fabs(axis.x), y = fabs(axis.y), z = fabs(axis.z);

    Vec3 v;
    if(x <= y && x <= z){
        v = Vec3(0, -1*axis.z, axis.y, 0);
    } else if(y <= x && y <= z){
        v = Vec3(-1*axis.z, 0, axis.x, 0);
    } else if(z <= x && z <= y){
        v = Vec3(-1*axis.y, axis.x, 0, 0);
    }

    v = normalizeVec3(v);
    Vec3 w = crossProductVec3(unit, v);
    w = normalizeVec3(w);

    //M and M^-1
    Matrix4 mttm1 = getIdentityMatrix();
    mttm1.val[0][0] = unit.x;
    mttm1.val[0][1] = v.x;
    mttm1.val[0][2] = w.x;
    mttm1.val[1][0] = unit.y;
    mttm1.val[1][1] = v.y;
    mttm1.val[1][2] = w.y;
    mttm1.val[2][0] = unit.z;
    mttm1.val[2][1] = v.z;
    mttm1.val[2][2] = w.z;

    Matrix4 m = getIdentityMatrix();
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            m.val[i][j] = mttm1.val[j][i];

    //Rotation transform
    Matrix4 rotation = multiplyMatrixWithMatrix(mttm1, multiplyMatrixWithMatrix(rx, m));

    //Rotate and return
    Vec4 pt4 = Vec4(point.x, point.y, point.z, 1, 0);
    Vec4 helper = multiplyMatrixWithVec4(rotation, pt4);
    Vec3 result = Vec3(helper.x, helper.y, helper.z, point.colorId);
    return result;
}

Vec3 scale(Scaling *scl, Vec3 point){
    Vec3 result = point;
    result.x *= scl->sx;
    result.y *= scl->sy;
    result.z *= scl->sz;
    return result;
}