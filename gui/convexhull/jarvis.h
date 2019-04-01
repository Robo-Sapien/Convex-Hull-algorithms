#ifndef JARVIS
#define JARVIS

#include <iostream>
#include <vector> 
#include <cmath>
#include "convex_hull_utility.h"
#include "mainwindow.h"
#include <QApplication>

class Jarvis: public ConvexHull 
{

private:
	int indexOfLeftMostPoint(vector<point> &points);
	double findAngle(point a, point b, point c);
	int secondPointIndex(vector<point> &points);
	int findOrientation(point a, point b, point c);

public:
	Jarvis(vector<struct point> points):ConvexHull(points)
	{

	}
    void runJarvisMarch(vector<point> &points, MainWindow *w);
};


#endif 
