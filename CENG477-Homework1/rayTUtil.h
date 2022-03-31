#include <vector>
#include <math.h>
#include <iostream>
#include "vecOps.h"
#include "parser.h"

#define INT_MAX 2147483647
#define EPS 0.00001

class Intersection
{
    public:
        float t;
        char typ;
        int index;
        bool isMirror;
        parser::Vec3f mirrorness;
        parser::Triangle meshTri;
};

void normalize(parser::Vec3f &vec);
void ambient(char typ, int &index, parser::Vec3f &color, parser::Scene &scene);
void diffuse(char typ, int &index, int &pli, float &theta, float &d2, parser::Vec3f &colorD, parser::Scene &scene);
void specular(char typ, int &index, int &pli, float &alpha, float &d2, parser::Vec3f &colorS, parser::Scene &scene);
void ambientM(parser::Triangle &meshtri, parser::Vec3f &color, parser::Scene &scene);
void diffuseM(int &pli, float &theta, float &d2, parser::Triangle &meshtri, parser::Vec3f &colorD, parser::Scene &scene);
void specularM(int &pli, float &alpha, float &d2, parser::Triangle &meshtri, parser::Vec3f &colorS, parser::Scene &scene);
void colorHelper(char &typ, int &pli, int index, float &t, parser::Vec3f &color, parser::Ray &ray, parser::Scene &scene);
void colorHelperM(int &pli, float &t, parser::Triangle &mtri, parser::Vec3f &color, parser::Ray &ray, parser::Scene &scene);

parser::Ray pixelCenterDetection(int i, int j, parser::Camera &camera);
parser::Vec3i computeColor(parser::Ray &ray, parser::Scene &scene);
parser::Vec3f mirrorHelper(char typ, int depthCount, int oldIndex, parser::Vec3f &oldCamPos, parser::Vec3f &oldIsctPt, parser::Scene &scene, Intersection &oldIsct);
parser::Vec3f mirrorColor(parser::Ray &ray, parser::Scene &scene, int depth);

Intersection detectIntersection(parser::Ray &ray, parser::Scene &scene);
Intersection mirrorIntersection(parser::Ray &ray, parser::Scene &scene);

float intersectSphere(char typ, float sre, parser::Sphere &sph, parser::Ray &ray, parser::Vec3f &sphCoord);
float intersectTriangle(char typ, parser::Scene &scene, parser::Triangle &tri, parser::Ray &ray);

bool inShadow(bool sit, parser::Vec3f &intersectPt, parser::Vec3f &normal, parser::Vec3f &ptLight, parser::Vec3f &wi, parser::Scene &scene);