#include "Translation.h"
#include "Rotation.h"
#include "Scaling.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Matrix4.h"
#include "Helpers.h"
#include "Camera.h"
#include "Scene.h"
#include <math.h>
#include <vector>

void draw( vector< vector<Color> > &image, int x, int y, Vec3 c);
void line_rasterization(Scene &scene, Vec3 begpt, Vec3 endpt);
void tri_rasterization(Scene &scene, Camera &cam, vector<Vec4> &vertex, vector<Color> &colors);
Vec3 colorRound(Vec3 col);