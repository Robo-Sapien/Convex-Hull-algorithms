#include <iostream>
#include <algorithm>
#include <climits>
#include "convex_hull_utility.h"
using namespace std;

class Kirkpatrick_Seidel: public inherit ConvexHull{
private:
    //Extremum points variable
    int pu_min_idx;     //index of uppermost minimum x-coordinate point
    int pu_max_idx;     //index of uppermost maximum x-coordinate point
    int pl_min_idx;     //index of lowermost min x-coord point
    int pl_max_idx;     //index of lowermost max x-coord point

    //Function for finding the extremum points
    void get_extremum_points(){
        //Initializing the min and max value of x-coordinate of points
        int min_x=INT_MAX;
        int max_x=INT_MIN;

        for(unsigned int i=0;i<points.size();i++){
            //Finding the minimum bound of the points
            if(points[i].x<min_x){
                //Updating the estimate of minumum x-coordinate
                min_x=points[i].x;
                //Updating the new minimum x-coordiante index
                pu_min_idx=i;
                pl_min_idx=i;
            }
            else if(points[i].x==min_x){
                //if there are multiple points at same minumum x-coordinate
                if(points[pu_min_idx].y<points[i].y){
                    //If the current point is above the pu_min_idx's y
                    pu_min_idx=i;
                }
                else if(points[pl_min_idx].y>points[i].y){
                    //if the current point is even below pl_min_idx's y
                    pl_min_idx=i;
                }
            }

            //Finding the maximum bounds of the points
            if(points[i].x>max_x){
                //Updating the estimate of the maximum value
                max_x=points[i].x;
                //Changing the max-x coordinate index
                pu_max_idx=i;
                pl_max_idx=i;
            }
            else if(points[i].x==max_x){
                //if two points are on the same x-coordinate farthest
                if(points[pu_max_idx].y<points[i].y){
                    //if the upper max point is below the current point
                    pu_max_idx=i;
                }
                else if(points[pl_max_idx].y>points[i].y){
                    //the the lower max point is above 
                }
            }

        }
    }
public:
    //Defining the constructor
    Kirkpatrick_Seidel(vector<struct point> points):ConvexHull(points){
        cout<<"Points Initialized"<<endl;
    }


}
