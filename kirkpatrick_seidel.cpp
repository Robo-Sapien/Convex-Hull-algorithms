#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
#include <cstdlib>
#include "convex_hull_utility.h"
using namespace std;

class Kirkpatrick_Seidel: public ConvexHull{
private:
    //Extremum points variable
    int pu_min_idx;     //index of uppermost minimum x-coordinate point
    int pu_max_idx;     //index of uppermost maximum x-coordinate point
    int pl_min_idx;     //index of lowermost min x-coord point
    int pl_max_idx;     //index of lowermost max x-coord point

    //Function for finding the extremum points
    void get_extremum_points(){
        cout<<"Finding the extremum points"<<endl;
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
                    //the the lower max point is above current point
                    pl_max_idx=i;
                }
            }
        }
        //Printing the bounding points
        cout<<"pu_min_";print_point(pu_min_idx);
        cout<<"pl_min_";print_point(pl_min_idx);
        cout<<"pu_max_";print_point(pu_max_idx);
        cout<<"pl_max_";print_point(pl_max_idx);
    }

    //Function to generate the upper hull
    void get_upper_hull(vector<int> live_idx){
        /*
        DESCRIPTION:
            This function will generate the upper hull of from the given
            set of living points. This function will recursively call
            itself each time it partition the problem into two half
            and joining them by finding the upper bridge.
        USAGE:
            INPUT:
                live_idx    : a.dtype = vector<int>
                              b. the points on which to run the upper
                                hull algorithm.
            OUTPUT:

        */
        //Creating a vector for the live points
        //vector<
    }

public:
    //Defining the constructor
    Kirkpatrick_Seidel(vector<struct point> points):ConvexHull(points){
        cout<<"\nPoints Initialized"<<endl;
        get_extremum_points();
    }

    //printing the index and location of point
    void print_point(int idx){
        cout<<"idx:"<<idx<<" at location: ";
        cout<<points[idx].x<<","<<points[idx].y<<endl;
    }


};

int main(){
    //Initializing the points
    srand(14);
    vector<struct point> points;
    vector<int> points_idx;
    for(int i=0;i<10;i++){
        float x=rand()%100;
        float y=rand()%200;
        int idx=i;
        // cin>>x>>y;
        struct point p;
        p.x=x;
        p.y=y;
        points.push_back(p);
        points_idx.push_back(idx);
        cout<<"idx: "<<idx<<" point: x:"<<p.x<<", y:"<<p.y<<endl;
    }

    //Creating the class and initializig the points
    Kirkpatrick_Seidel MyKPS(points);
    //Testing the median finding algorithm
    int med_idx=calculate_median(points_idx,points);
    cout<<"med_idx: "<<med_idx<<endl;
}
