//#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "jarvis.h"


using namespace std;


/**
Description: Runs the Jarvis March algorithm using the vector of
struct point inherited from ConvexHull class.
*/
void Jarvis::runJarvisMarch()
{
	int indexToBeSwapped = indexOfLeftMostPoint();

	vector<point> gui_points; //vector to store

	int orientedPoints[points.size()]; //stores the indices of points on convex hull in clockwise fashion

	orientedPoints[0] = 0;
	gui_points.push_back(points[orientedPoints[0]]);

	orientedPoints[1] = secondPointIndex();
	gui_points.push_back(points[orientedPoints[1]]);

	int i=1;
	double max_angle = 0;
	double angle;
	int nPointsInHull=1;
	struct point p0 = points[0];
	do
	{
		max_angle = 0;
		i++;
		//printf("%d\n",i);
		for (int j=0;j<points.size();j++)
		{
			//printf("%d\n",i);
			angle = findAngle(points[orientedPoints[i-2]],points[orientedPoints[i-1]],points[j]);
			if(angle > max_angle)
			{
				max_angle = angle;
				orientedPoints[i] = j;
			}

		}
	gui_points.push_back(points[orientedPoints[i]]);


	nPointsInHull++;

	} while((points[orientedPoints[i]].x != p0.x) || (points[orientedPoints[i]].y != p0.y));

	for(i=0;i<nPointsInHull;i++)
	{
		if(orientedPoints[i]==indexToBeSwapped)
		{
			orientedPoints[i]=0;
			break;
		}
	}
	orientedPoints[0] = indexToBeSwapped;

	for(i=0;i<nPointsInHull;i++)
	{
		cout<<orientedPoints[i]<<" ";
	}
	cout<<"Num on HULL:"<<nPointsInHull<<endl;

	for(i=0;i<gui_points.size();i++)
    {
        cout<<gui_points[i].x<<" "<<gui_points[i].y<<endl;
    }

}

/**
Description: Helper function which finds the index (in the vector of points)
of the second point on the convex hull (clockwise).
@return index: index of the 2nd point on the convex hull (clockwise)
*/
int Jarvis::secondPointIndex()
{

	int index;
	point randomUpper;
	randomUpper.x=points[0].x;
	randomUpper.y=points[0].y+1;
	double angle;
	double minAngle=4.14;

	for(int i=1;i<points.size();i++)
	{
		angle = findAngle(randomUpper,points[0],points[i]);
		if(minAngle > angle)
		{
			minAngle = angle;
			index = i;
		}
	}

	return index;
}

/**
Description: Helper function finds the smaller angle between the
displacement vectors joining the 3 given points.

@param a: 1st point
@param b: 2nd point (middle point)
@param c: 3rd point
@return angle: angle between vectors (a-b) & (a-c)
*/
double Jarvis::findAngle(point a, point b, point c)
{
	double vector1_icap = a.x-b.x;
	double vector1_jcap = a.y-b.y;
	double vector2_icap = c.x-b.x;
	double vector2_jcap = c.y-b.y;

	double prodOfNorms = sqrt((pow(vector1_icap,2)+pow(vector1_jcap,2))*(pow(vector2_icap,2)+pow(vector2_jcap,2)));

	double angle = acos((vector1_icap*vector2_icap + vector1_jcap*vector2_jcap)/prodOfNorms);

	return angle;
}

/**
Description: Helper function the index (in the vector of points)
of the leftmost point
@return index: index of the leftmost point on the convex hull
*/
int Jarvis::indexOfLeftMostPoint()
{
	double next;
	double small = points[0].x;
	int index=0;

	for(int i=1;i<points.size();i++)
    {
    	next = points[i].x;
    	if(small > next)
    	{
    		small = next;
    		index = i;
    	}
    }

    struct point temp = points[0];
  	points[0] = points[index];
  	points[index] = temp;

	return index;
}


// int main()
// {
// 	int n;
// 	cin >> n;
// 	vector<point> points;
// 	double x, y;
// 	for (int i = 0; i < n; i++)
// 	{
// 	  cin >> x >> y;
// 	  struct point p;
// 	  p.x = x;
// 	  p.y = y;
// 	  points.push_back(p);
// 	 }
// 	 cout<<endl;
// 	 Jarvis *ob = new Jarvis(points);
// 	 ob->runJarvisMarch();
//
// 	return 0;
// }
