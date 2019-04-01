#include <iostream>
#include <vector>
#include <cstdlib>
#include <climits>
#include "kirkpatrick_seidel.h"

int main(){
    //Initializing the points
    srand(4);
    vector<struct point> points;
    vector<int> points_idx;
    int range=100000;
    for(int i=0;i<range;i++){
        float x=((float)(rand()%range))/7.0;
        float y=((float)(rand()%range))/7.0;
        int idx=i;
        //cin>>x>>y;
        struct point p;
        p.x=x;
        p.y=y;
        points.push_back(p);
        points_idx.push_back(idx);
        //cout<<"idx: "<<idx<<" point: x:"<<p.x<<", y:"<<p.y<<endl;
    }

    //Creating the class and initializig the points
    Kirkpatrick_Seidel MyKPS(points);

    //Testing the median finding algorithm
    //int med_idx=calculate_median(points_idx,points);
    //cout<<"med_idx: "<<med_idx<<endl;

    //Testing the Upper hull
    MyKPS.put_a_hull_on_points();
}
