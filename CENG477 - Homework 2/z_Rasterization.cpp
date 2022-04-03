#include "z_Rasterization.h"

Vec3 colorRound(Vec3 col){
    Vec3 result;
    result.x = (int)col.x;
    result.y = (int)col.y;
    result.z = (int)col.z;
    return result;
}

void draw( vector< vector<Color> > &image, int x, int y, Vec3 c){   
    Color color;
    color.r = c.x;
    color.g = c.y;
    color.b = c.z;
    image[x][y] = color;
}

void line_rasterization(Scene &scene, Vec3 begpt, Vec3 endpt){
    Color color0 = *scene.colorsOfVertices[begpt.colorId - 1];
    Color color1 = *scene.colorsOfVertices[endpt.colorId - 1];

    Vec3 c0, c1;
    c0.x = color0.r;
    c0.y = color0.g;
    c0.z = color0.b;
    c1.x = color1.r;
    c1.y = color1.g;
    c1.z = color1.b;

    double x0 = begpt.x, y0 = begpt.y;
    double x1 = endpt.x, y1 = endpt.y;

    double slope = (y1 - y0) / (x1 - x0);
    if(1 >= slope && slope >= 0){
        if(x1 < x0){
            std::swap(x0, x1);
            std::swap(y0, y1);
            std::swap(c0, c1);
        }        
        Vec3 c = c0;
        Vec3 dc = multiplyVec3WithScalar( subtractVec3(c1, c0) , 1 / (x1 - x0) );

        double y = y0;
        double d = 2*(y0 - y1) + (x1 - x0);

        for(int x = (int)x0 ; x < (int)x1; x++){
            Vec3 helper = colorRound(c);
            draw(scene.image, (int)x, (int)y, helper);
            if(d < 0){
                y++;
                d += 2 * ( (y0 - y1) + (x1 - x0) );
            } else{
                d += 2* (y0 - y1);
            }

            c = addVec3(c, dc);
        }
    }

    else if(slope > 1){
         if(y1 < y0){
            std::swap(x0, x1);
            std::swap(y0, y1);
            std::swap(c0, c1);
        }
        Vec3 c = c0;
        Vec3 dc = multiplyVec3WithScalar( subtractVec3(c1, c0) , 1 / (y1 - y0) );

        double x = x0;
        double d = 2*(x0 - x1) + (y1 - y0);

        for(int y = (int)y0; y < (int)y1; y++){
            Vec3 helper = colorRound(c);
            draw(scene.image, (int)x, (int)y, helper);
            if(d < 0){
                x++;
                d += 2 * ( (x0 - x1) + (y1 - y0) );
            } else{
                d += 2* (x0 - x1);
            }

            c = addVec3(c, dc);
        }
    
    }

    else if(slope < 0 && slope >= -1){
        if(x1 > x0){
            std::swap(x0, x1);
            std::swap(y0, y1);
            std::swap(c0, c1);
        }
        
        Vec3 c = c0;
        Vec3 dc = multiplyVec3WithScalar( subtractVec3(c1, c0) , 1 / (x1 - x0) );

        double y = y0;
        double d = 2*(y0 - y1) + (x0 - x1);

        for(int x = (int)x0; x > (int)x1; x--){
            Vec3 helper = colorRound(c);
            draw(scene.image, (int)x, (int)y, helper);
            if(d < 0){
                y++;
                d += 2 * ( (y0 - y1) + (x0 - x1) );
            } else{
                d += 2* (y0 - y1);
            }

            c = addVec3(c, multiplyVec3WithScalar(dc, -1));
        }       
    }

    else if(slope < -1){
         if(y1 > y0){
            std::swap(x0, x1);
            std::swap(y0, y1);
            std::swap(c0, c1);
        }
        Vec3 c = c0;
        Vec3 dc = multiplyVec3WithScalar( subtractVec3(c1, c0) , 1 / (y1 - y0) );

        double x = x0;
        double d = 2*(x0 - x1) + (y0 - y1);

        for(int y = (int)y0; y > (int)y1; y--){
            Vec3 helper = colorRound(c);
            draw(scene.image, (int)x, (int)y, helper);
            if(d < 0){
                x++;
                d += 2 * ( (x0 - x1) + (y0 - y1) );
            } else{
                d += 2* (x0 - x1);
            }

            c = addVec3(c, multiplyVec3WithScalar(dc, -1));
        }
    }
}

void tri_rasterization(Scene &scene, Camera &cam, vector<Vec4> &vertex, vector<Color> &colors){
    double min_x, min_y, max_x, max_y;

    min_x = min(vertex[0].x, min(vertex[1].x, vertex[2].x));
    min_y = min(vertex[0].y, min(vertex[1].y, vertex[2].y));
	max_x = max(vertex[0].x, max(vertex[1].x, vertex[2].x));
	max_y = max(vertex[0].y, max(vertex[1].y, vertex[2].y));

	for(int y = min_y; y < max_y; y++){
		for(int x = min_x; x < max_x; x++){

			if (x < 0 || x >= cam.horRes || y < 0 || y >= cam.verRes) continue;
            
            double f01_22, f12_00, f20_11;
            f01_22 = vertex[2].x * (vertex[0].y - vertex[1].y) + vertex[2].y * (vertex[1].x - vertex[0].x) + vertex[0].x * vertex[1].y - vertex[0].y * vertex[1].x;
            f12_00 = vertex[0].x * (vertex[1].y - vertex[2].y) + vertex[0].y * (vertex[2].x - vertex[1].x) + vertex[1].x * vertex[2].y - vertex[1].y * vertex[2].x;
            f20_11 = vertex[1].x * (vertex[2].y - vertex[0].y) + vertex[1].y * (vertex[0].x - vertex[2].x) + vertex[2].x * vertex[0].y - vertex[2].y * vertex[0].x;

            double f01, f12, f20;
            f01 = x * (vertex[0].y - vertex[1].y) + y * (vertex[1].x - vertex[0].x) + vertex[0].x * vertex[1].y - vertex[0].y * vertex[1].x;
            f12 = x * (vertex[1].y - vertex[2].y) + y * (vertex[2].x - vertex[1].x) + vertex[1].x * vertex[2].y - vertex[1].y * vertex[2].x;
            f20 = x * (vertex[2].y - vertex[0].y) + y * (vertex[0].x - vertex[2].x) + vertex[2].x * vertex[0].y - vertex[2].y * vertex[0].x;

            double alpha, beta, gamma;
            alpha = f12 / f12_00;
            beta = f20 / f20_11;
            gamma = f01 / f01_22;

			if(alpha >= 0 && beta >= 0 && gamma >= 0){
                Color helper;
                helper.r = alpha * colors[0].r + beta * colors[1].r + gamma * colors[2].r;
                helper.g = alpha * colors[0].g + beta * colors[1].g + gamma * colors[2].g;
                helper.b = alpha * colors[0].b + beta * colors[1].b + gamma * colors[2].b;
				scene.image[x][y] = helper;
			}
		}
	}
}