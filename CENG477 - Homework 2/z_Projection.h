#include "Translation.h"
#include "Rotation.h"
#include "Scaling.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Matrix4.h"
#include "Helpers.h"
#include "Camera.h"
#include <math.h>

Matrix4 camtrans(Camera &cam);
Matrix4 ortographic(Camera &cam);
Matrix4 perspective(Camera &cam);
Matrix4 viewport(Camera &cam);