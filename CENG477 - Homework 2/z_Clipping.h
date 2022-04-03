#include "Translation.h"
#include "Rotation.h"
#include "Scaling.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Matrix4.h"
#include "Helpers.h"
#include "Camera.h"
#include "Triangle.h"
#include <math.h>
#include <vector>

vector<Vec3> CS_clipping(Vec3 begpt, Vec3 endpt, int x_min, int y_min, int x_max, int y_max, bool &is_rejected);