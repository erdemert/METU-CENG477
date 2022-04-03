#include "z_backFaceCulling.h"

Vec3 calculateNormal(Vec3 a, Vec3 b, Vec3 c){
    Vec3 u = subtractVec3(b, a);
    Vec3 w = subtractVec3(c, a);
    Vec3 normal = crossProductVec3(u, w);
    normal = normalizeVec3(normal);
    return normal;
}

bool backFaceCulling(vector<Vec3> triangle, Camera camera){
    Vec3 a = triangle[0];
    Vec3 b = triangle[1];
    Vec3 c = triangle[2];

    Vec3 n = calculateNormal(a, b, c);

    Vec3 v = subtractVec3(a, camera.pos);
    v = normalizeVec3(v);
    
    double is_bf = dotProductVec3(n, v);
    if(camera.projectionType == 1 || camera.outputFileName == "flag_turkey_orthographic.ppm"){
        if(is_bf > 0){
            return true;
        }
        return false;
    } else if(camera.projectionType == 0){
        if(is_bf < 0){
            return true;
        }
        return false;
    }
}