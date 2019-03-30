#ifndef GRAHAMSCAN
#define GRAHAMSCAN

#include "mainwindow.h"
#include <QApplication>

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include "convex_hull_utility.h"
#include "customStack.h"

using namespace std;
struct point referencePoint;


class GrahamScan : public ConvexHull{
  private:
    /*
    Find the reference point (bottommost leftmost point)
    */
    void findReferencePointAndSwap(vector<point> &points){
      float ymin = points[0].y, min = 0; 
      for (unsigned int i = 1; i < points.size(); i++)
      { 
        float y = points[i].y; 
        if ((y < ymin) || (ymin == y && points[i].x < points[min].x)){
          ymin = points[i].y;
          min = i;
        }
      } 
      // Place the bottom-most point at first position
      point temp = points[0];
      points[0] = points[min];
      points[min] = temp;
      referencePoint = points[0];
      return;
    }

    // finds square of distance between 2 points
    static float distanceSq(point p1, point p2) { 
      return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y); 
    } 

    /*
    Find the orientation of th 2 points with respect to the center
    it returns 
    0 if they are collinear, 
    1 if they are clockwise (angle p1 is greater than p2) and 
    2 if they are anti-clockwise (angle p2 is greater than p1)
    */
    static int findOrientation(point a, point b, point c){
      int o = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
      if(o == 0){
        return 0; // collinear
      }
      if(o < 0){
        return 2; // counter-clockwise
      } else {
        return 1; // clockwise
      }
    }

    /*
    custom caomparison function for sorting the points according to the polar angle.
    returns -1 if v1 < v2, and 1 if v1 > v2
    */
    static int compare(const void *v1, const void *v2){
      
      // Type cast from void to point*
      point *p1 = ( point* )v1;
      point *p2 = ( point* )v2;

      int orientation = findOrientation( referencePoint, *p1, *p2 );
      if ( orientation == 0 ) {
        if( distanceSq( referencePoint, *p2 ) >= distanceSq( referencePoint, *p1) ){
          return -1;
        } else {
          return 1;
        }
      } else if ( orientation == 1 ) {
        return 1;
      } else {
        return -1;
      } 
    }

    /*
    If two points mak the same polar angle with the eference point, 
    remove the one with the smaller distance from reference point
    */
    void removeCollinearPoints(vector<point> &points){
      for(vector<point>::iterator i = (points.begin()+1); i != points.end(); ++i)
      {
        while (i+1 != points.end() && findOrientation(referencePoint, *i, *(i+1)) == 0){
          points.erase(i);
          i++;
        }
      }

      // for(size_t i = 0; i < points.size(); i++)
      // {
      //   cout << points[i].x << " " << points[i].y << endl;  
      // }
      
    }

  public:

    GrahamScan(vector<struct point> points):ConvexHull(points){

    }

    /*
    runs the graham's scan algorithm on the vector of points and displays the
    convexhull in the GUI.
    */
    void runGrahamScan(vector<point> &points, MainWindow *w){
      
      findReferencePointAndSwap(points);
      
      // sort the points according to the polar angle with respect to the center
      // and line parallel to x-axis.
      qsort(&points[1], points.size() - 1, sizeof(point), compare);

      removeCollinearPoints(points);

      customStack<point> convexHull;
      convexHull.push(points[0]);
      convexHull.push(points[1]);
      convexHull.push(points[2]);
      for(unsigned int i = 3; i < points.size(); i++)
      {
        while( findOrientation(convexHull.getElementBelowTop(), convexHull.getTopElement(), points[i]) != 2){
          convexHull.pop();
        }
        convexHull.push(points[i]);
      }
      
//      w->drawLine(convexHull.getPoints());
      convexHull.getPoints();

    }

};

#endif

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

////    int n;
////    cin >> n;
////    vector<point> points;
////    float x, y;
////    for (size_t i = 0; i < n; i++) {
////      cin >> x >> y;
////      struct point p;
////      p.x = x;
////      p.y = y;
////      points.push_back(p);
////    }
////    cout<<endl;
////    GrahamScan *obj = new GrahamScan(points);
////    obj->runGrahamScan(points);

//    return a.exec();
//}
