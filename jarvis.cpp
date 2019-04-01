#include <bits/stdc++.h> 
#include <cmath>

using namespace std;

struct point
{
	double x;
	double y;
};

int indexOfLeftMostPoint(vector<point> &points);
double findAngle(point a, point b, point c);
int secondPointIndex(vector<point> &points);
int findOrientation(point a, point b, point c);

void runJarvisMarch(vector<point> &points)
{
	int indexToBeSwapped = indexOfLeftMostPoint(points);

	//vector< pair<int,int> > hull_point_pairs;

	//find next point
	//push (0,nextpoint) pair 

	int orientedPoints[points.size()];

	orientedPoints[0] = 0;
	orientedPoints[1] = secondPointIndex(points);
	//orientedPoints[1] = 1;


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

				//printf("%d\n",j);
			}

		}
	nPointsInHull++;
	//printf("%f\n",points[orientedPoints[i]].x);	
	} while((points[orientedPoints[i]].x != p0.x) || (points[orientedPoints[i]].y != p0.y));

	//printf("%d\n",nPointsInHull);
	
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
		printf("%d ",orientedPoints[i]);
	}

}

int secondPointIndex(vector<point> &points)
{
	//point second_Point;
	int index;

	for(int i=1;i<points.size();i++)
	{	
		int count = 0;
		for(int j=0;j<points.size();j++)
		{
			int orientation = findOrientation(points[0],points[i],points[j]);
			if(orientation ==0 || orientation==1)
				count++;
		}
		if(count == points.size())
		{
			index = i;
			break;
		}
	}
	//second_Point = points[i];
	return index;
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

int indexOfLeftMostPoint(vector<point> &points)
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

	 runJarvisMarch(points);

	return 0;
}