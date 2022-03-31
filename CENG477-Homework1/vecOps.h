#include <vector>
#include <math.h>
#include "parser.h"

parser::Vec3f multiplyVecbyConstant(parser::Vec3f &vec, float constant);
parser::Vec3f vec3fCrossProduct(parser::Vec3f a, parser::Vec3f b);

float vec3fDotProduct(parser::Vec3f &a, parser::Vec3f &b);
float computeDist(parser::Vec3f &a, parser::Vec3f &b);
float vec3fDeterminant(float matrix[3][3]);

void normalize(parser::Vec3f &vec);