#include <iostream>
#include <vector>
#include <cstdlib>
#include <climits>
#include <cmath>
#include "kirkpatrick_seidel.h"
#include "jarvis.h"

int main(){
    //Initializing the points
    srand(14);
    vector<struct point> points;
    vector<int> points_idx;
    int range=5000;
    for(int i=0;i<range;i++){
        double x=((double)(rand()%range))/(7.0*(rand()%range));
        double y=((double)(rand()%range))/(7.0*(rand()%range));
        if(isinf(x) || isinf(y)){
            cout<<i<<endl;
            cout<<"Infinity found in input: "<<x<<", "<<y<<endl;
            continue;
            //exit(0);
        }
        int idx=i;
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

    //Testing the Jarvis March
    // Jarvis *ob = new Jarvis(points);
    // ob->runJarvisMarch();

    return 0;
}
