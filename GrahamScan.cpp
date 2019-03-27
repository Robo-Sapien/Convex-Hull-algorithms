#include <iostream>
#include <stack>
#include <vector>
#include <stdlib.h>

using namespace std;

struct point{
  float x;
  float y;
};

struct point center;

/*
finds the centroid of the 3 points
*/
struct point getCentroid(point A, point B, point C){
  struct point centroid;
  centroid.x = ( A.x + B.x + C.x ) / 3;
  centroid.y = ( A.y + B.y + C.y ) / 3;
  return centroid;
}

/*
custom caomparison function for sorting the points according to the polar angle.
*/
int compare(){}

/*
runs the graham's scan algorithm on the vector of points and displays the
convexhull in the GUI.
*/
void runGrahamScan(vector<point> &points){
  // find the reference point
  center = getCentroid(points[0], points[1], points[2]);

  // sort the points according to the polar angle with respect to the center
  // and line parallel to x-axis.
  qsort(points, points.size(), sizeof(point), compare);

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
