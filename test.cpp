#include <iostream>
#include <vector>
#include <cstdlib>
#include <climits>
#include <cmath>
#include "kirkpatrick_seidel.h"
#include "jarvis.h"
#include "GrahamScan.cpp"

int main(){
    //Initializing the points
    srand(14);
    vector<struct point> points;
    vector<int> points_idx;
    int range=5000;
    int num_point=0;
    while(num_point!=range){
        double x=3*((double)(rand()%range))/((rand()%range));
        double y=3*((double)(rand()%range))/((rand()%range));
        if(isinf(x) || isinf(y)){
            cout<<num_point<<endl;
            cout<<"Infinity found in input: "<<x<<", "<<y<<endl;
            continue;
            //exit(0);
        }
        /*if(x*x+y*y>3){
            continue;
        }*/
        //cout<<x<<","<<y<<endl;
        int idx=num_point;
        num_point++;
        //cin>>x>>y;
        struct point p;
        p.x=x;
        p.y=y;
        points.push_back(p);
        points_idx.push_back(idx);
        //cout<<"idx: "<<idx<<" point: x:"<<p.x<<", y:"<<p.y<<endl;
    }
    //Testing the median finding algorithm
    //int med_idx=calculate_median(points_idx,points);
    //cout<<"med_idx: "<<med_idx<<endl;

    //Creating the class and initializig the points
    Kirkpatrick_Seidel MyKPS(points);
    //Testing the Upper hull
    MyKPS.put_a_hull_on_points();

    /*GrahamScan *obj = new GrahamScan(points);
    obj->runGrahamScan(points)*/;

    //Testing the Jarvis March
    /*Jarvis *ob = new Jarvis(points);
    ob->runJarvisMarch();
*/
    //Testing the Grahm Scan


    return 0;
}
