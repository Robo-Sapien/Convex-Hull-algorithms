#include <iostream>
#include <stack>
#include <vector>
#include <stdlib.h>

using namespace std;

struct point{
  float x;
  float y;
};

struct point origin;

/*
Find the reference point (bottommost leftmost point)
*/
void findReferencePointAndSwap(vector<point> &points){
  int ymin = points[0].y, min = 0; 
    for (int i = 1; i < points.size(); i++) 
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
    origin = points[0];
    return;
}

// finds square of distance between 2 points
int distanceSq(point p1, point p2) 
{ 
  return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y); 
} 

/*
Find the orientation of th 2 points with respect to the center
it returns 0 if they are collinear, 1 if they are clockwise
(angle p1 is greater than p2) and 2 if they are anti-clockwise
(angle p2 is greater than p1)
*/
int findOrientation(point a, point b, point c){
  int o = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
  if(o == 0){
    return 0; // collinear
  }
  if(o > 0){
    return 2; // counter-clockwise
  } else {
    return 1; // clockwise
  }
}

/*
custom caomparison function for sorting the points according to the polar angle.
*/
int compare(const void *v1, const void *v2){
  
  // Type cast from void to point*
  point *p1 = ( point* )v1;
  point *p2 = ( point* )v2;

  int orientation = findOrientation( origin, *p1, *p2 );
  if ( orientation == 0 ) {
    if( distanceSq( origin, *p1 ) <= distanceSq( origin, *p2) ){
      return 1;
    } else {
      return -1;
    }
  } else if ( orientation == 1 ) {
    return -1;
  } else {
    return 1;
  }
  
  
}

/*
runs the graham's scan algorithm on the vector of points and displays the
convexhull in the GUI.
*/
void runGrahamScan(vector<point> &points){
  
  findReferencePointAndSwap(points);
  
  // sort the points according to the polar angle with respect to the center
  // and line parallel to x-axis.
  qsort(&points, points.size(), sizeof(point), compare);

}

/*
main function that takes input points from the user
*/
int main(int argc, char const *argv[]) {
  int n;
  cin >> n;
  vector<point> points;
  float x, y;
  for (size_t i = 0; i < n; i++) {
    cin >> x >> y;
    struct point p;
    p.x = x;
    p.y = y;
    points.push_back(p);
  }

  return 0;
}
