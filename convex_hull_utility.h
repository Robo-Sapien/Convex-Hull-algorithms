#include <vector>
using namespace std;
/*
Defining the structure to hold the point
*/
struct point{
    float x;
    float y;
};


/*
Defining the class which will serve as template to all the three
implementation of the Convex Hull algorithm
*/
class ConvexHull{
protected:
    //All subclasses will inherit this variable
    vector<struct point> points;
public:
    //Defining the constructor
    ConvexHull(vector<struct point> points){
        this->points=points;
    }
    //Defining the accessor function of the points
    vector<struct point> get_points(){
        return points;
    }
};
