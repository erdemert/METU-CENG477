#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "ppm.h"
#include "parser.h"
#include "vecOps.h"
#include "rayTUtil.h"

using namespace parser; // this might be deleted

#define currCam scene.cameras[index]

void writePPM(Vec3i **image, int nx, int ny)
{
	int i,j;
	FILE *fp;
	
	fp = fopen("output.ppm","w");
	
	fprintf(fp,"P3\n");
	fprintf(fp,"#output.ppm\n");
	fprintf(fp,"%d %d\n",nx,ny);
	fprintf(fp,"255\n");
	for (j=0;j<ny;j++)
	{
		for (i=0;i<nx;i++)
		{
			fprintf(fp,"%d %d %d\t",image[i][j].x,image[i][j].y,image[i][j].z);
		}
		fprintf(fp,"\n");
	}
	//system("convert output.ppm output.png");
	//system("rm output.ppm");
	
}


int main(int argc, char* argv[])
{
    // getting the scene file
    parser::Scene scene;
    scene.loadFromXml(argv[1]); 

    int width, height;
    int camera_number = scene.cameras.size();

    for(int index=0; index<camera_number; index++){
        width = currCam.image_width;
        height = currCam.image_height;
        int nx = width, ny = height;

        unsigned char* image = new unsigned char [width * height * 3];
        
        int k = 0;
        for(int j=0; j<height; j++){
            for(int i=0; i<width; i++){
                parser::Ray currRay = pixelCenterDetection(i, j, currCam);
                
                Vec3i temp = computeColor(currRay, scene);
                image[k++] = temp.x;
                image[k++] = temp.y;
                image[k++] = temp.z;
            }
        }
            write_ppm(scene.cameras[index].image_name.c_str(), image, width, height);
    }
}
