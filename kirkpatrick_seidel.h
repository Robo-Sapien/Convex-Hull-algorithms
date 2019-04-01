#include <vector>
#include <iostream>
#include "convex_hull_utility.h"
using namespace std;

class Kirkpatrick_Seidel: public ConvexHull{
public:
    //Defining the constructor
    Kirkpatrick_Seidel(vector<struct point> points):ConvexHull(points){
        cout<<"\nPoints Initialized"<<endl;
        this->get_extremum_points();
    }
    //printing the index and location of point
    void print_point(int idx);
    //Function for printing the pair of points on HULL
    void print_pairs_on_hull();
    //Public function to generate the convex hull
    void put_a_hull_on_points();

private:
    //Extremum points variable
    unsigned int pu_min_idx;     //index of uppermost min x-coord point
    unsigned int pu_max_idx;     //index of uppermost max x-coord point
    unsigned int pl_min_idx;     //index of lowermost min x-coord point
    unsigned int pl_max_idx;     //index of lowermost max x-coord point

    ///////////////////////////////////////////////////////////////////
    /*               GENEREAL UTILITY FUNCTION                      */
    //////////////////////////////////////////////////////////////////
    //Function for finding the extremum points
    void get_extremum_points();
    //Function to calculate the slope give the index of the points
    double calculate_p2p_slope(int idx1,int idx2);
    //Function to get the candidate points to run the upper hull
    vector<int> get_candidates_idx(unsigned int cur_pu_min_idx,
                                    unsigned int cur_pu_max_idx);

    ///////////////////////////////////////////////////////////////////
    /*               UPPER BRIDGE RELATED FUNCTIONS                 */
    ///////////////////////////////////////////////////////////////////
    //Initializing the p2p slope struct
    struct p2p_slope*get_p2p_slope_entry(int idx1,int idx2,double slope);
    //Calculating the slope of pair of points
    vector<p2p_slope*> get_pair_slopes(vector<int> &cand_idx,\
                                        vector<int> &new_cand_idx);
    //Function to calculate the median slope pair
    int fill_slope_bucket(vector<struct p2p_slope*> &pair_slopes,\
                            vector<int> &LARGE_SLOPE,\
                            vector<int> &EQUAL_SLOPE,\
                            vector<int> &SMALL_SLOPE);
    //Function for filling the new cand_idx
    void generate_new_cand_idx(int leave_flag,\
                                vector<int> &new_cand_idx,\
                                vector<struct p2p_slope*> &pair_slopes,\
                                vector<int> &LARGE_SLOPE,\
                                vector<int> &EQUAL_SLOPE,\
                                vector<int> &SMALL_SLOPE);
    //Finding the bridge points or the new reduced candidate points
    vector<int> get_bridge_or_candidate(double med_x,int med_slope_idx,\
                                vector<int> &cand_idx,\
                                vector<int> &new_cand_idx,\
                                vector<struct p2p_slope*> &pair_slopes,\
                                vector<int> &LARGE_SLOPE,\
                                vector<int> &EQUAL_SLOPE,\
                                vector<int> &SMALL_SLOPE);
    //Function to calculate the upper bridge
    vector<int> get_upper_bridge(double med_x,vector<int> &cand_idx);

    //////////////////////////////////////////////////////////////////
    /*                  UPPER HULL RELATED FUNCTION                 */
    //////////////////////////////////////////////////////////////////
    //Function to append the bridge point to actual hull point
    void append_bridge_point_to_hull(vector<int> &bridge_idx);
    //Function to generate the upper hull
    void get_upper_hull(vector<int> &cand_idx,\
                            unsigned int min_x_idx,\
                            unsigned int max_x_idx);

    /////////////////////////////////////////////////////////////////
    /*                  LOWER HULL RELATED FUNCTION                */
    /////////////////////////////////////////////////////////////////
    //Function for transforming out lower hull to upper hull
    void transform_lowers_to_upper();

};
