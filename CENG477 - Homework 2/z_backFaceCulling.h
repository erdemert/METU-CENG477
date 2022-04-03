#include "Translation.h"
#include "Rotation.h"
#include "Scaling.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Matrix4.h"
#include "Helpers.h"
#include "Camera.h"
#include "Triangle.h"
#include "Scene.h"
#include <vector>
#include <math.h>

Vec3 calculateNormal(Vec3 a, Vec3 b, Vec3 c);
bool backFaceCulling(vector<Vec3> triangle, Camera camera);