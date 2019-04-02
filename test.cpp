#include <iostream>
#include <vector>
#include <cstdlib>
#include <climits>
#include "kirkpatrick_seidel.h"

int main(){
    //Initializing the points
    srand(14);
    vector<struct point> points;
    vector<int> points_idx;
    int range=100000;
    for(int i=0;i<range;i++){
        double x=((double)(rand()%range))/(3.0);//*(rand()%100));
        double y=((double)(rand()%range))/(3.0);//*(rand()%100));
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
