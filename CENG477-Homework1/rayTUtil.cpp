#include "rayTUtil.h"

using namespace parser;

/******************************************************************* COLORIZE *******************************************************************/

void ambient(char typ, int &index, Vec3f &color, Scene &scene)
{
    if(typ == 's'){
        color.x += ((scene.materials[scene.spheres[index].material_id - 1].ambient.x)*scene.ambient_light.x);
        color.y += ((scene.materials[scene.spheres[index].material_id - 1].ambient.y)*scene.ambient_light.y);
        color.z += ((scene.materials[scene.spheres[index].material_id - 1].ambient.z)*scene.ambient_light.z);
    }else if(typ == 't'){
        color.x += ((scene.materials[scene.triangles[index].material_id - 1].ambient.x)*scene.ambient_light.x);
        color.y += ((scene.materials[scene.triangles[index].material_id - 1].ambient.y)*scene.ambient_light.y);
        color.z += ((scene.materials[scene.triangles[index].material_id - 1].ambient.z)*scene.ambient_light.z);
    }
}

void ambientM(Triangle &meshtri, Vec3f &color, Scene &scene)
{
    color.x += ((scene.materials[meshtri.material_id - 1].ambient.x)*scene.ambient_light.x);
    color.y += ((scene.materials[meshtri.material_id - 1].ambient.y)*scene.ambient_light.y);
    color.z += ((scene.materials[meshtri.material_id - 1].ambient.z)*scene.ambient_light.z);
}

void diffuse(char typ, int &index, int &pli, float &theta, float &d2, Vec3f &colorD, Scene &scene)
{
    if(typ == 's'){
        colorD.x += scene.materials[scene.spheres[index].material_id-1].diffuse.x * theta * scene.point_lights[pli].intensity.x / d2;
        colorD.y += scene.materials[scene.spheres[index].material_id-1].diffuse.y * theta * scene.point_lights[pli].intensity.y / d2;
        colorD.z += scene.materials[scene.spheres[index].material_id-1].diffuse.z * theta * scene.point_lights[pli].intensity.z / d2;
    }else if(typ == 't'){
        colorD.x += scene.materials[scene.triangles[index].material_id-1].diffuse.x * theta * scene.point_lights[pli].intensity.x / d2;
        colorD.y += scene.materials[scene.triangles[index].material_id-1].diffuse.y * theta * scene.point_lights[pli].intensity.y / d2;
        colorD.z += scene.materials[scene.triangles[index].material_id-1].diffuse.z * theta * scene.point_lights[pli].intensity.z / d2;
    }
}

void diffuseM(int &pli, float &theta, float &d2, Triangle &meshtri, Vec3f &colorD, Scene &scene)
{
    colorD.x += scene.materials[meshtri.material_id-1].diffuse.x * theta * scene.point_lights[pli].intensity.x / d2;
    colorD.y += scene.materials[meshtri.material_id-1].diffuse.y * theta * scene.point_lights[pli].intensity.y / d2;
    colorD.z += scene.materials[meshtri.material_id-1].diffuse.z * theta * scene.point_lights[pli].intensity.z / d2;
}

void specular(char typ, int &index, int &pli, float &alpha, float &d2, Vec3f &colorS, Scene &scene)
{
    if(typ == 's'){
        colorS.x += scene.materials[scene.spheres[index].material_id-1].specular.x * pow(alpha,scene.materials[scene.spheres[index].material_id-1].phong_exponent) * scene.point_lights[pli].intensity.x / d2;
        colorS.y += scene.materials[scene.spheres[index].material_id-1].specular.y * pow(alpha,scene.materials[scene.spheres[index].material_id-1].phong_exponent) * scene.point_lights[pli].intensity.y / d2;
        colorS.z += scene.materials[scene.spheres[index].material_id-1].specular.z * pow(alpha,scene.materials[scene.spheres[index].material_id-1].phong_exponent) * scene.point_lights[pli].intensity.z / d2;
    }else if(typ == 't'){
        colorS.x += scene.materials[scene.triangles[index].material_id-1].specular.x * pow(alpha,scene.materials[scene.triangles[index].material_id-1].phong_exponent) * scene.point_lights[pli].intensity.x / d2;
        colorS.y += scene.materials[scene.triangles[index].material_id-1].specular.y * pow(alpha,scene.materials[scene.triangles[index].material_id-1].phong_exponent) * scene.point_lights[pli].intensity.y / d2;
        colorS.z += scene.materials[scene.triangles[index].material_id-1].specular.z * pow(alpha,scene.materials[scene.triangles[index].material_id-1].phong_exponent) * scene.point_lights[pli].intensity.z / d2;
    }
}

void specularM(int &pli, float &alpha, float &d2, Triangle &meshtri, Vec3f &colorS, Scene &scene)
{
    colorS.x += scene.materials[meshtri.material_id-1].specular.x * pow(alpha,scene.materials[meshtri.material_id-1].phong_exponent) * scene.point_lights[pli].intensity.x / d2;
    colorS.y += scene.materials[meshtri.material_id-1].specular.y * pow(alpha,scene.materials[meshtri.material_id-1].phong_exponent) * scene.point_lights[pli].intensity.y / d2;
    colorS.z += scene.materials[meshtri.material_id-1].specular.z * pow(alpha,scene.materials[meshtri.material_id-1].phong_exponent) * scene.point_lights[pli].intensity.z / d2;
}

/******************************************************************* COLORIZE *******************************************************************/

/*********************************************************************************************************************************************************************************************************************************************/
/*********************************************************************************************************************************************************************************************************************************************/
/*********************************************************************************************************************************************************************************************************************************************/

/***************************************************************** INTERSECTIONS *****************************************************************/

Ray pixelCenterDetection(int i, int j, Camera &camera)
{
    Ray result;

    float l = camera.near_plane.x,
    r = camera.near_plane.y,
    b = camera.near_plane.z,
    t = camera.near_plane.w;

    Vec3f v = camera.up;
    Vec3f u = vec3fCrossProduct(camera.gaze, camera.up);
    Vec3f m = camera.position + multiplyVecbyConstant(camera.gaze, camera.near_distance);
    Vec3f q = m + multiplyVecbyConstant(u, l) + multiplyVecbyConstant(v, t);
    
    float su = (i + 0.5)*(r-l)/camera.image_width;
    float sv = (j + 0.5)*(t-b)/camera.image_height;

    Vec3f s = q + multiplyVecbyConstant(u, su) - multiplyVecbyConstant(v, sv);

    result.o = camera.position;
    result.d = s - result.o;

    return result;
}

float intersectSphere(char typ, float sre, Sphere &sph, Ray &ray, Vec3f &sphCoord)
{
    float t, t1, t2;
    float A, B, C, delta;
    Vec3f d = ray.d;
    Vec3f o_minus_c = ray.o - sphCoord;

    A = vec3fDotProduct(d, d);
    B = 2 * vec3fDotProduct(d, o_minus_c);
    C = vec3fDotProduct(o_minus_c, o_minus_c) - sph.radius*sph.radius;
    delta = B*B - 4*A*C;

    if(typ == 'p')
    {
        if(delta < 0)
            t = -1;
        else if(delta == 0)
        {
            t = -B / (2*A);
        }
        else
        {
            t1 = (-B + sqrt(delta)) / (2*A);
            t2 = (-B - sqrt(delta)) / (2*A);
            
            if(t1 > 1 && t2 > 1)
            {
                if(t1 < t2) t = t1; else t = t2;
            }
            else if(t1 > 1 && t2 < 1)
            {
                t = t1;
            }
                        
            else if(t1 < 1 && t2 > 1)
            {
                t = t2;
            }
            else
            {
                t = -1;
            }
        }
    }else if(typ == 's')
    {
        if(delta < 0)
            t = -1;
        else if(delta == 0)
        {
            t = -B / (2*A);
        }
        else
        {
            t1 = (-B + sqrt(delta)) / (2*A);
            t2 = (-B - sqrt(delta)) / (2*A);
            
            if(sre < t1 && t1 < 1)
            {
                if(sre < t2 && t2 < 1)
                {
                    if(t1 < t2) t = t1; else t = t2;
                }else
                {
                    t = t1;
                }
            } else if(sre < t2 && t2 < 1)
            {
                t = t2;
            } else
            {
                t = -1;
            }
        }
    }else if(typ == 'r'){
        if(delta < 0)
            t = -1;
        else if(delta == 0)
        {
            t = -B / (2*A);
        }
        else
        {
            t1 = (-B + sqrt(delta)) / (2*A);
            t2 = (-B - sqrt(delta)) / (2*A);
            
            if(t1 > sre && t2 > sre)
            {
                if(t1 < t2) t = t1; else t = t2;
            }
            else if(t1 > sre && t2 < sre)
            {
                t = t1;
            }
                        
            else if(t1 < sre && t2 > sre)
            {
                t = t2;
            }
            else
            {
                t = -1;
            }
        }
    }

    return t;
}

float intersectTriangle(char typ, Scene &scene, Triangle &tri, Ray &ray)
{
    float A[3][3];
    float B[3][3];
    float G[3][3];
    float t[3][3];

    Vec3f a, b, c;
    a = scene.vertex_data[tri.indices.v0_id-1];
    b = scene.vertex_data[tri.indices.v1_id-1];
    c = scene.vertex_data[tri.indices.v2_id-1];

    A[0][0] = a.x - b.x;
    A[0][1] = a.x - c.x;
    A[0][2] = ray.d.x;
    A[1][0] = a.y - b.y;
    A[1][1] = a.y - c.y;
    A[1][2] = ray.d.y;
    A[2][0] = a.z - b.z;
    A[2][1] = a.z - c.z;
    A[2][2] = ray.d.z;

    B[0][0] = a.x - ray.o.x;
    B[0][1] = a.x - c.x;
    B[0][2] = ray.d.x;
    B[1][0] = a.y - ray.o.y;
    B[1][1] = a.y - c.y;
    B[1][2] = ray.d.y;
    B[2][0] = a.z - ray.o.z;
    B[2][1] = a.z - c.z;
    B[2][2] = ray.d.z;

    G[0][0] = a.x - b.x;
    G[0][1] = a.x - ray.o.x;
    G[0][2] = ray.d.x;
    G[1][0] = a.y - b.y;
    G[1][1] = a.y - ray.o.y;
    G[1][2] = ray.d.y;
    G[2][0] = a.z - b.z;
    G[2][1] = a.z - ray.o.z;
    G[2][2] = ray.d.z;

    t[0][0] = a.x - b.x;
    t[0][1] = a.x - c.x;
    t[0][2] = a.x - ray.o.x;
    t[1][0] = a.y - b.y;
    t[1][1] = a.y - c.y;
    t[1][2] = a.y - ray.o.y;
    t[2][0] = a.z - b.z;
    t[2][1] = a.z - c.z;
    t[2][2] = a.z - ray.o.z;

    float A_det, B_det, G_det, t_det, beta, gama, t2;
    A_det = vec3fDeterminant(A);
    B_det = vec3fDeterminant(B);
    G_det = vec3fDeterminant(G);
    t_det = vec3fDeterminant(t);

    beta = B_det / A_det;
    gama = G_det / A_det;
    t2 = t_det / A_det;

    if(typ == 'p'){
        if(t2>1 && t2<INT_MAX){ // I've changed it to INT_MAX for now, it might not be that
            if(beta+gama <= 1){
                if(beta >= 0 && gama>= 0){
                    return t2;
                }
            }
        }
    }else if(typ == 's'){
        if(t2>EPS && t2<1){
            if(beta+gama <= 1){
                if(beta >= 0 && gama>= 0){
                    return t2;
                }
            }
        }
    }else if(typ == 'r'){
        if(t2>scene.shadow_ray_epsilon){
            if(beta+gama <= 1){
                if(beta >= 0 && gama>= 0){
                    return t2;
                }
            }
        }        
    }
    return -1; 
}

Intersection detectIntersection(Ray &ray, Scene &scene)
{
    Intersection res;
    float t;
    res.t = INT_MAX;
    res.typ = 'n';

    for(int si = 0; si < scene.spheres.size(); si++){
        Vec3f sphCoord = scene.vertex_data[scene.spheres[si].center_vertex_id - 1];
        t = intersectSphere('p', 0, scene.spheres[si], ray, sphCoord);
        if(t < res.t && t >= 1){
            res.t = t;
            res.index = si;
            res.typ = 's';
            res.isMirror = scene.materials[scene.spheres[si].material_id - 1].is_mirror;
            res.mirrorness = scene.materials[scene.spheres[si].material_id - 1].mirror;
        }
    }
    for(int ti = 0; ti < scene.triangles.size(); ti++){
        t = intersectTriangle('p', scene, scene.triangles[ti], ray);
        if(t < res.t && t >= 1){
            res.t = t;
            res.index = ti;
            res.typ = 't';
            res.isMirror = scene.materials[scene.triangles[ti].material_id-1].is_mirror;
            res.mirrorness = scene.materials[scene.triangles[ti].material_id-1].mirror;
        }
    }
    for(int mti = 0; mti < scene.meshes.size(); mti++){
        for(int mi = 0; mi < scene.meshes[mti].faces.size(); mi++){
            Triangle hTri;
            hTri.material_id = scene.meshes[mti].material_id;
            hTri.indices = scene.meshes[mti].faces[mi];
            t = intersectTriangle('p', scene, hTri, ray);
            if(t < res.t && t >= 1){
                res.t = t;
                res.meshTri = hTri;
                res.typ = 'm';
                res.isMirror = scene.materials[res.meshTri.material_id - 1].is_mirror;
                res.mirrorness = scene.materials[res.meshTri.material_id - 1].mirror;
            }
        }
    }
    
    return res;
}

/***************************************************************** INTERSECTIONS *****************************************************************/

/*********************************************************************************************************************************************************************************************************************************************/
/*********************************************************************************************************************************************************************************************************************************************/
/*********************************************************************************************************************************************************************************************************************************************/

/***************************************************************** SHADOWS *****************************************************************/

bool inShadow(Vec3f &intersectPt, Vec3f &normal, Vec3f &ptLight, Vec3f &wi, Scene &scene)
{
    Ray shadowRay;
    shadowRay.o = intersectPt + multiplyVecbyConstant(normal, scene.shadow_ray_epsilon);
    shadowRay.d = ptLight - shadowRay.o;
    float t;
    bool res = false;

    for(int si = 0; si < scene.spheres.size(); si++){
        Vec3f sphCoord = scene.vertex_data[scene.spheres[si].center_vertex_id - 1];
        t = intersectSphere('s', scene.shadow_ray_epsilon, scene.spheres[si], shadowRay, sphCoord);
        if(EPS < t && t < 1){
            res = true;
            break;
        }
    }
    if(!res)
        for(int ti = 0; ti < scene.triangles.size(); ti++){
            t = intersectTriangle('s', scene, scene.triangles[ti], shadowRay);
            if(EPS < t && t < 1){
                res = true;
                break;
            }
        }
    if(!res)
        for(int mti = 0; mti < scene.meshes.size(); mti++){
            for(int mi = 0; mi < scene.meshes[mti].faces.size(); mi++){
                Triangle hTri;
                hTri.material_id = scene.meshes[mti].material_id;
                hTri.indices = scene.meshes[mti].faces[mi];
                t = intersectTriangle('s', scene, hTri, shadowRay);
                if(EPS < t && t < 1){
                    res = true;
                    break;
                }
            }
            if(res) break;
        }

    return res;
}

/***************************************************************** SHADOWS *****************************************************************/

/*********************************************************************************************************************************************************************************************************************************************/
/*********************************************************************************************************************************************************************************************************************************************/
/*********************************************************************************************************************************************************************************************************************************************/

/***************************************************************** MIRROR HELPERS *****************************************************************/

Intersection mirrorIntersection(Ray &ray, Scene &scene)
{
    Intersection res;
    float t;
    res.t = INT_MAX;
    res.typ = 'n';

    for(int si = 0; si < scene.spheres.size(); si++){
        Vec3f sphCoord = scene.vertex_data[scene.spheres[si].center_vertex_id - 1];
        t = intersectSphere('r', 0, scene.spheres[si], ray, sphCoord);
        if(t < res.t && t > EPS){
            res.t = t;
            res.index = si;
            res.typ = 's';
            res.isMirror = scene.materials[scene.spheres[si].material_id - 1].is_mirror;
            res.mirrorness = scene.materials[scene.spheres[si].material_id - 1].mirror;
        }
    }
    for(int ti = 0; ti < scene.triangles.size(); ti++){
        t = intersectTriangle('r', scene, scene.triangles[ti], ray);
        if(t < res.t && t > EPS){
            res.t = t;
            res.index = ti;
            res.typ = 't';
            res.isMirror = scene.materials[scene.triangles[ti].material_id-1].is_mirror;
            res.mirrorness = scene.materials[scene.triangles[ti].material_id-1].mirror;
        }
    }
    for(int mti = 0; mti < scene.meshes.size(); mti++){
        for(int mi = 0; mi < scene.meshes[mti].faces.size(); mi++){
            Triangle hTri;
            hTri.material_id = scene.meshes[mti].material_id;
            hTri.indices = scene.meshes[mti].faces[mi];
            t = intersectTriangle('r', scene, hTri, ray);
            if(t < res.t && t > EPS){
                res.t = t;
                res.meshTri = hTri;
                res.typ = 'm';
                res.isMirror = scene.materials[res.meshTri.material_id - 1].is_mirror;
                res.mirrorness = scene.materials[res.meshTri.material_id - 1].mirror;
            }
        }
    }
    
    return res;
}

Vec3f mirrorHelper(char typ, int depthCount, int oldIndex, Vec3f &oldCamPos, Vec3f &oldIsctPt, Scene &scene, Intersection &oldIsct)
{
    //termination here
    if(depthCount < 0 || !(oldIsct.isMirror)){
        Vec3f c;
        c.x = 0;
        c.y = 0;
        c.z = 0;
        return c;
    }

    Ray reflectionRay;
    Vec3f reflColor;
    Vec3f wo, wr, normal;
    wo = oldCamPos - oldIsctPt;

    if(typ == 's'){
        normal = oldIsctPt - scene.vertex_data[scene.spheres[oldIndex].center_vertex_id - 1];
    }else if(typ == 't'){
        Vec3f a, b, c;
        a = scene.vertex_data[scene.triangles[oldIndex].indices.v0_id - 1];
        b = scene.vertex_data[scene.triangles[oldIndex].indices.v1_id - 1];
        c = scene.vertex_data[scene.triangles[oldIndex].indices.v2_id - 1];
        normal = vec3fCrossProduct((a - b), (a - c));
    }
    else if(typ == 'm'){
        Vec3f a, b, c;
        a = scene.vertex_data[oldIsct.meshTri.indices.v0_id - 1];
        b = scene.vertex_data[oldIsct.meshTri.indices.v1_id - 1];
        c = scene.vertex_data[oldIsct.meshTri.indices.v2_id - 1];
        normal = vec3fCrossProduct((a - b), (a - c));
    }

    normalize(normal);
    normalize(wo);

    wr = multiplyVecbyConstant(wo, -1) + multiplyVecbyConstant(normal, 2 * vec3fDotProduct(normal, wo));
    normalize(wr);

    reflectionRay.o = oldIsctPt + multiplyVecbyConstant(normal, scene.shadow_ray_epsilon); // WARNING: is it okay to use s_r_epsilon here?
    reflectionRay.d = wr;
    Intersection newIsct = mirrorIntersection(reflectionRay, scene);
    if(newIsct.typ == 'n'){
        reflColor.x = 0; //scene.background_color.x * oldIsct.mirrorness.x;
        reflColor.y = 0; //scene.background_color.y * oldIsct.mirrorness.y;
        reflColor.z = 0; //scene.background_color.z * oldIsct.mirrorness.z;
        return reflColor;
    }else{
        reflColor = mirrorColor(reflectionRay, scene, depthCount);
        reflColor.x *= oldIsct.mirrorness.x;
        reflColor.y *= oldIsct.mirrorness.y;
        reflColor.z *= oldIsct.mirrorness.z;
        
        if(!(newIsct.isMirror)){
            return reflColor;
        }else{
            Vec3f newIsctPt = oldIsctPt + multiplyVecbyConstant(wr, newIsct.t);
            return reflColor + mirrorHelper(newIsct.typ, depthCount - 1, newIsct.index, oldIsctPt, newIsctPt, scene, newIsct);
        }
    }
}

Vec3f mirrorColor(Ray &ray, Scene &scene, int depth)
{
    Vec3f color;
    Intersection isct = mirrorIntersection(ray, scene);

    if(isct.typ != 'n'){ // not null, so there's intersection
        int numPLs = scene.point_lights.size();
        if(isct.typ == 'm'){ // mesh
            ambientM(isct.meshTri, color, scene);
            for(int pli = 0; pli < numPLs; pli++){
                colorHelperM(pli, isct.t, isct.meshTri, color, ray, scene);
            }
        }else{ // triangle or sphere
            ambient(isct.typ, isct.index, color, scene);
            for(int pli = 0; pli < numPLs; pli++){
                colorHelper(isct.typ, pli, isct.index, isct.t, color, ray, scene);
            }
        }

        if(color.x > 255) color.x = 255;
        if(color.y > 255) color.y = 255;
        if(color.z > 255) color.z = 255;
        if(color.x < 0) color.x = 0;
        if(color.y < 0) color.y = 0;
        if(color.z < 0) color.z = 0;
    }else{
        color.x = 0;
        color.y = 0;   //BACKGROUND
        color.z = 0;
    }

    return color;
}


/***************************************************************** MIRROR HELPERS *****************************************************************/

/*********************************************************************************************************************************************************************************************************************************************/
/*********************************************************************************************************************************************************************************************************************************************/
/*********************************************************************************************************************************************************************************************************************************************/

/***************************************************************** COLOR HELPERS *****************************************************************/

void colorHelper(char &typ, int &pli, int index, float &t, Vec3f &color, Ray &ray, Scene &scene)
{
    Vec3f intersectPt = ray.o + multiplyVecbyConstant(ray.d, t);
    Vec3f point_light = scene.point_lights[pli].position;
    Vec3f wi, wo;

    wi = point_light - intersectPt;
    wo = ray.o - intersectPt;
    normalize(wi); 
    normalize(wo);
    Vec3f h = wi + wo;
    Vec3f normal;
    float d2 = pow(computeDist(intersectPt, point_light), 2);
    
    if(typ == 's'){ // sphere normal
        normal = intersectPt - scene.vertex_data[scene.spheres[index].center_vertex_id-1];
    }else if(typ == 't'){ // triangle normal
        Vec3f a, b, c;
        a = scene.vertex_data[scene.triangles[index].indices.v0_id-1];
        b = scene.vertex_data[scene.triangles[index].indices.v1_id-1];
        c = scene.vertex_data[scene.triangles[index].indices.v2_id-1];
        normal = vec3fCrossProduct((a - b), (a - c));
    }

    normalize(normal);
    bool shadow = inShadow(intersectPt, normal, point_light, wi, scene); // returns true if there's intersection between light and intersectPt
    if(!shadow)
    { // colorize if point not inShadow
        normalize(wi);
        

        float theta = vec3fDotProduct(wi, normal);

        if(theta > EPS){
            normalize(h);
            float alpha = vec3fDotProduct(normal, h);
            Vec3f specular_color;
            specular(typ, index, pli, alpha, d2, specular_color, scene);
            Vec3f diffuse_color;
            diffuse(typ, index, pli, theta, d2, diffuse_color, scene);
            color = color + specular_color + diffuse_color;
        }
    }
}

void colorHelperM(int &pli, float &t, Triangle &mtri, Vec3f &color, Ray &ray, Scene &scene)
{
    Vec3f intersectPt = ray.o + multiplyVecbyConstant(ray.d, t);
    Vec3f point_light = scene.point_lights[pli].position;
    Vec3f wi = point_light - intersectPt;
    Vec3f wo = ray.o - intersectPt;
    normalize(wi);
    normalize(wo);
    Vec3f h = wi + wo;
    Vec3f normal;
    float d2 = pow(computeDist(point_light, intersectPt), 2);
    
    Vec3f a, b, c;
    a = scene.vertex_data[mtri.indices.v0_id-1];
    b = scene.vertex_data[mtri.indices.v1_id-1];
    c = scene.vertex_data[mtri.indices.v2_id-1];
    normal = vec3fCrossProduct((a - b), (a - c));
    
    normalize(normal);
    bool shadow = inShadow(intersectPt, normal, point_light, wi, scene);
    if(!shadow)
    {

        float theta = vec3fDotProduct(wi, normal);

        if(theta > EPS){
            normalize(h);
            float alpha = vec3fDotProduct(normal, h);
            Vec3f specular_color;
            specularM(pli, alpha, d2, mtri, specular_color, scene);
            Vec3f diffuse_color;
            diffuseM(pli, theta, d2, mtri, diffuse_color, scene);
            color = color + specular_color + diffuse_color;
        }
    }
}

/***************************************************************** COLOR HELPERS *****************************************************************/


Vec3i computeColor(Ray &ray, Scene &scene)
{
    Vec3f color; // temporarily vec3f
    Vec3f camPos = ray.o;
    Intersection isct = detectIntersection(ray, scene);
    Vec3f isctPt = camPos + multiplyVecbyConstant(ray.d, isct.t); 

    if(isct.typ != 'n'){ // not null, so there's intersection
        int numPLs = scene.point_lights.size();
        if(isct.typ == 'm'){ // mesh
            ambientM(isct.meshTri, color, scene);
            for(int pli = 0; pli < numPLs; pli++){
                colorHelperM(pli, isct.t, isct.meshTri, color, ray, scene);
            }
        }else{ // triangle or sphere
            ambient(isct.typ, isct.index, color, scene);
            for(int pli = 0; pli < numPLs; pli++){
                colorHelper(isct.typ, pli, isct.index, isct.t, color, ray, scene);
            }
        }

        color = color + mirrorHelper(isct.typ, scene.max_recursion_depth, isct.index, camPos, isctPt, scene, isct);

        if(color.x > 255) color.x = 255;
        if(color.y > 255) color.y = 255;
        if(color.z > 255) color.z = 255;
        if(color.x < 0) color.x = 0;
        if(color.y < 0) color.y = 0;
        if(color.z < 0) color.z = 0;
    }else{
        color.x = scene.background_color.x;
        color.y = scene.background_color.y;
        color.z = scene.background_color.z;
    }

    Vec3i rescolor; // temporary vec3f -> vec3i
    rescolor.x = int(color.x+0.5);
    rescolor.y = int(color.y+0.5);
    rescolor.z = int(color.z+0.5);
    return rescolor;
}