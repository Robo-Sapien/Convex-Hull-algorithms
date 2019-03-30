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
Describing the data structure to hold the slope of pair of points
*/
struct p2p_slope{
    int idx1;
    int idx2;
    float slope;
};

/*
Defining the class which will serve as template to all the three
implementation of the Convex Hull algorithm
*/
class ConvexHull{
protected:
    //All subclasses will inherit this variable
    vector<struct point> points;
    vector<int> hull_point_idx;
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

/*
Defining the template for the Min and Max Heap class which will be used
for finding the Median of a range of points according to their when they
are ordered according to their x-coordinate.
*/
class Heap{
private:
    int *idx_heap;            //the heap having the index of point
    float *val_heap;          //value to compare while heapifying
    int last_pos;             //saving the position of last entry

    void swap_elements(int pos1,int pos2);
public:
    char heap_type;                 //x: max_heap; n: min_heap
    int heap_size;                  //default size of the heap

    //Defining the constructor and destructor
    Heap(char heap_type,int heap_size);
    ~Heap();

    //Defining the function supported in the heap.
    //Function to insert an element to the heap and then heapify
    void insert_into_heap(int idx,float value);
    //Function to remove the topmost element from the heap and heapify
    int pop_from_heap();
    //Function for printing the heap, for debugging purpose
    void print_heap();
};

/*
Function for finding the median element using the heap in O(N)
*/
int calculate_median(vector<int> &points_idx,\
                        vector<struct point>&points);
