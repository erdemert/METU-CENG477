#include "vecOps.h"
    
parser::Vec3f multiplyVecbyConstant(parser::Vec3f &vec, float constant)
{
    parser::Vec3f res;
    res.x = vec.x * constant;
    res.y = vec.y * constant;
    res.z = vec.z * constant;

    return res;
}

parser::Vec3f vec3fCrossProduct(parser::Vec3f a, parser::Vec3f b)
{
    parser::Vec3f res;
    res.x = a.y * b.z - a.z * b.y;
    res.y = a.z * b.x - a.x * b.z;
    res.z = a.x * b.y - a.y * b.x;

    return res;
}

float vec3fDotProduct(parser::Vec3f &a, parser::Vec3f &b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

float computeDist(parser::Vec3f &a, parser::Vec3f &b){
    return sqrt( pow(b.x - a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2) );
}

float vec3fDeterminant(float matrix[3][3]){
    
    float a = matrix[0][0],
    d = matrix[0][1],
    g = matrix[0][2],
    b = matrix[1][0],
    e = matrix[1][1],
    h = matrix[1][2],
    c = matrix[2][0],
    f = matrix[2][1],
    i = matrix[2][2];

    return a*(e*i - h*f) + b*(g*f - d*i) + c*(d*h - e*g);
}

void normalize(parser::Vec3f &vec)
{
    float length = sqrt( vec3fDotProduct(vec, vec) );
    vec.x /= length;
    vec.y /= length;
    vec.z /= length;
}