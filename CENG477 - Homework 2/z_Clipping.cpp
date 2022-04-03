#include "z_Clipping.h"

vector<Vec3> CS_clipping(Vec3 begpt, Vec3 endpt, int x_min, int y_min, int x_max, int y_max, bool &is_rejected){
    vector<Vec3> result;
    Vec3 resbegpt = begpt, resendpt = endpt;
    is_rejected = 0;
    double slope;
    if(!(ABS(endpt.x - begpt.x) < EPSILON))
        slope = (endpt.y - begpt.y) / (endpt.x - begpt.x);
    else
        slope = INT32_MAX;

    bool flag = 0;

    while(!flag){
        resbegpt = begpt;
        resendpt = endpt;

        int beg = 0, end = 0; // for bitwise operations
        if(begpt.x < x_min){
            beg += 1; // 0001
        }
        if(begpt.x > x_max){
            beg += 2; // 0010
        }
        if(begpt.y < y_min){
            beg += 4; // 0100
        }
        if(begpt.y > y_max){
            beg += 8; // 1000
        }

        if(endpt.x < x_min){
            end += 1;
        }
        if(endpt.x > x_max){
            end += 2;
        }
        if(endpt.y < y_min){
            end += 4;
        }
        if(endpt.y > y_max){
            end += 8;
        }
        
        if(beg == 0 && end == 0){
            result.push_back(resbegpt);
            result.push_back(resendpt);
            return result;
        } else if(beg & end){
            is_rejected = 1;
            return result;
        }

        if(begpt.x < x_min){
            begpt.y = begpt.y + slope * (x_min - begpt.x);
            begpt.x = x_min;
        }
        else if(begpt.x > x_max){
            begpt.y = begpt.y - slope * (begpt.x - x_max);
            begpt.x = x_max;
        }
        else if(begpt.y < y_min){
            begpt.x = begpt.x + (y_min - begpt.y) / slope;
            begpt.y = y_min;
        }
        else if(begpt.y > y_max){
            begpt.x = begpt.x - (begpt.y - y_max) / slope;
            begpt.y = y_max;
        }
        else if(endpt.x < x_min){
            endpt.y = endpt.y + slope * (x_min - endpt.x);
            endpt.x = x_min;
        }
        else if(endpt.x > x_max){
            endpt.y = endpt.y - slope * (endpt.x - x_max);
            endpt.x = x_max;
        }
        else if(endpt.y < y_min){
            endpt.x = endpt.x + (y_min - endpt.y) / slope;
            endpt.y = y_min;
        }
        else if(endpt.y > y_max){
            endpt.x = endpt.x - (endpt.y - y_max) / slope;
            endpt.y = y_max;
        }
    }
}