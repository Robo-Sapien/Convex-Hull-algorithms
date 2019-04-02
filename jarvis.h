#ifndef JARVIS
#define JARVIS

#include <iostream>
#include <vector> 
#include <cmath>
#include "convex_hull_utility.h"
//#include "mainwindow.h"
//#include <QApplication>

class Jarvis: public ConvexHull 
{

private:
	int indexOfLeftMostPoint();
	double findAngle(point a, point b, point c);
	int secondPointIndex();

public:
	Jarvis(vector<struct point> points):ConvexHull(points)
	{

	}
	void runJarvisMarch();
};


#endif 