#include "Translation.h"
#include "Rotation.h"
#include "Scaling.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Matrix4.h"
#include "Helpers.h"
#include <math.h>

double convert(double degree);
Vec3 translate(Translation *trs, Vec3 point);
Vec3 rotate(Rotation *rtn, Vec3 point);
Vec3 scale(Scaling *scl, Vec3 point);