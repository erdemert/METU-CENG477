#ifndef __HW1__PARSER__
#define __HW1__PARSER__

#include <string>
#include <vector>

namespace parser
{
    //Notice that all the structures are as simple as possible
    //so that you are not enforced to adopt any style or design.

    class Vec3f
    {
        
        public:
            float x, y, z;

            Vec3f(){
                x = 0;
                y = 0;
                z = 0;
            }

            Vec3f(float a, float b, float c){
                x = a;
                y = b;
                z = c;
            }

            Vec3f operator+(Vec3f b);
            Vec3f operator-(Vec3f b);
    };

    class Vec3i
    {
        public:
            int x, y, z;
    };

    class Vec4f
    {
        public:
            float x, y, z, w;
    };

    class Ray
    {
        public:
            Vec3f o, d;
    };

    class Camera
    {
        public:
            Vec3f position;
            Vec3f gaze;
            Vec3f up;
            Vec4f near_plane;
            float near_distance;
            int image_width, image_height;
            std::string image_name;
    };

    class PointLight
    {
        public:
            Vec3f position;
            Vec3f intensity;
    };

    class Material
    {
        public:
            bool is_mirror;
            Vec3f ambient;
            Vec3f diffuse;
            Vec3f specular;
            Vec3f mirror;
            float phong_exponent;
    };

    class Face
    {
        public:
            int v0_id;
            int v1_id;
            int v2_id;
    };

    class Mesh
    {
        public:
            int material_id;
            std::vector<Face> faces;
    };

    class Triangle
    {
        public:
            int material_id;
            Face indices;
    };

    class Sphere
    {
        public:
            int material_id;
            int center_vertex_id;
            float radius;
    };

    class Scene
    {
        public:
            //Data
            Vec3i background_color;
            float shadow_ray_epsilon;
            int max_recursion_depth;
            std::vector<Camera> cameras;
            Vec3f ambient_light;
            std::vector<PointLight> point_lights;
            std::vector<Material> materials;
            std::vector<Vec3f> vertex_data;
            std::vector<Mesh> meshes;
            std::vector<Triangle> triangles;
            std::vector<Sphere> spheres;

            //Utility
            void loadFromXml(const std::string &filepath);            
    };
}

#endif