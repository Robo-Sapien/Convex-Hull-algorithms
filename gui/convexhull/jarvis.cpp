//#include <bits/stdc++.h>
#include <iostream>
#include <vector> 
#include <cmath>
#include <unistd.h>
#include "jarvis.h"


using namespace std;


void Jarvis::runJarvisMarch(vector<point> &points, MainWindow *w)
{
	int indexToBeSwapped = indexOfLeftMostPoint();

	vector<point> gui_points;

	int orientedPoints[points.size()];

	orientedPoints[0] = 0;
	gui_points.push_back(points[orientedPoints[0]]);

	orientedPoints[1] = secondPointIndex();
	gui_points.push_back(points[orientedPoints[1]]);
	w->clearLines();
    w->drawLines(gui_points);

	unsigned int i=1;
	double max_angle = 0;
	double angle;
	int nPointsInHull=1;
	struct point p0 = points[0];
	do
	{
		max_angle = 0;
		i++;
		//printf("%d\n",i);
		for (unsigned int j=0;j<points.size();j++)
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
	w->clearLines();
    w->drawLines(gui_points);
    sleep(1);


	nPointsInHull++;

	} while((points[orientedPoints[i]].x != p0.x) || (points[orientedPoints[i]].y != p0.y));
	
    for(int i=0;i<nPointsInHull;i++)
	{
		if(orientedPoints[i]==indexToBeSwapped)
		{
			orientedPoints[i]=0;
			break;
		}
	}
	orientedPoints[0] = indexToBeSwapped;

    for(int i=0;i<nPointsInHull;i++)
	{
		cout<<orientedPoints[i]<<" ";
	}
	cout<<endl;

	for(i=0;i<gui_points.size();i++)
    {
        cout<<gui_points[i].x<<" "<<gui_points[i].y<<endl;
    }

}

int Jarvis::secondPointIndex()
{

    int index=0;
	point randomUpper;
	randomUpper.x=points[0].x;
	randomUpper.y=points[0].y+1;
	double angle;
	double minAngle=4.14;

    for(unsigned int i=1;i<points.size();i++)
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

int Jarvis::indexOfLeftMostPoint()
{
	double next;
	double small = points[0].x;
	int index=0;

    for(unsigned int i=1;i<points.size();i++)
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


//int main()
//{
//	int n;
//	cin >> n;
//	vector<point> points;
//	double x, y;
//	for (int i = 0; i < n; i++)
//	{
//	  cin >> x >> y;
//	  struct point p;
//	  p.x = x;
//	  p.y = y;
//	  points.push_back(p);
//	 }
//	 cout<<endl;
//	 Jarvis *ob = new Jarvis(points);
//	 ob->runJarvisMarch(vector<point> &points, *w);

//	return 0;
//}
