#include <bits/stdc++.h> 
#include <cmath>

using namespace std;

struct point
{
	double x;
	double y;
};

void indexOfLeftMostPoint(vector<point> &points);
double findAngle(point a, point b, point c);

void runJarvisMarch(vector<point> &points)
{
	indexOfLeftMostPoint(points);

	//vector< pair<int,int> > hull_point_pairs;

	//find next point
	//push (0,nextpoint) pair 

	int orientedPoints[points.size()];

	orientedPoints[0] = 0;
	orientedPoints[1] = ;


	int i=1;
	double max_angle = 0;
	double angle;
	struct point p0 = points[0];
	do
	{
		max = 0;
		i++;
		for (int j=0;j<points.size();j++)
		{
			angle = findAngle(points[orientedPoints[i-2]],points[orientedPoints[i-1]],points[orientedPoints[j]]);
			if(angle > max_angle)
			{
				max_angle = angle;
				orientedPoints[i] = points[j];

			}

		}
	} while((orientedPoints[i].x != p0.x) && (orientedPoints[i].y != p0.y));



}

double findAngle(point a, point b, point c)
{
	double vector1_icap = a.x-b.x;
	double vector1_jcap = a.y-b.y;
	double vector2_icap = c.x-b.x;
	double vector2_jcap = c.y-b.y;

	double prodOfNorms = sqrt((pow(vector1_icap,2)+pow(vector1_jcap,2))*(pow(vector2_icap,2)+pow(vector2_jcap,2)));

	double angle = acos((vector1_icap*vector2_icap + vector1_jcap*vector2_jcap)/prodOfNorms);

	return angle;
}

void indexOfLeftMostPoint(vector<point> &points)
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

	return;
}

int findOrientation(point a, point b, point c)
{
  int value = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
  if(value == 0)
  {
    return 0; // collinear
  }
  if(value < 0)
  {
    return 2; // counter-clockwise
  } 
  else 
  {
    return 1; // clockwise
  }
}

int main()
{
	int n;
	cin >> n;
	vector<point> points;
	double x, y;
	for (int i = 0; i < n; i++) 
	{
	  cin >> x >> y;
	  struct point p;
	  p.x = x;
	  p.y = y;
	  points.push_back(p);
	 }
	 cout<<endl;

	return 0;
}