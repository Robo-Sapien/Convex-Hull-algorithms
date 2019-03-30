#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
#include <cstdlib>
#include "convex_hull_utility.h"
using namespace std;

class Kirkpatrick_Seidel: public ConvexHull{
private:
    //Extremum points variable
    unsigned int pu_min_idx;     //index of uppermost minimum x-coord point
    unsigned int pu_max_idx;     //index of uppermost maximum x-coord point
    unsigned int pl_min_idx;     //index of lowermost min x-coord point
    unsigned int pl_max_idx;     //index of lowermost max x-coord point

    ///////////////////////////////////////////////////////////////////
    /*               GENEREAL UTILITY FUNCTION                      */
    //////////////////////////////////////////////////////////////////
    //Function for finding the extremum points
    void get_extremum_points(){
        cout<<"Finding the extremum points"<<endl;
        //Initializing the min and max value of x-coordinate of points
        int min_x=INT_MAX;
        int max_x=INT_MIN;

        for(unsigned int i=0;i<points.size();i++){
            //Finding the minimum bound of the points
            if(points[i].x<min_x){
                //Updating the estimate of minumum x-coordinate
                min_x=points[i].x;
                //Updating the new minimum x-coordiante index
                pu_min_idx=i;
                pl_min_idx=i;
            }
            else if(points[i].x==min_x){
                //if there are multiple points at same minumum x-coordinate
                if(points[pu_min_idx].y<points[i].y){
                    //If the current point is above the pu_min_idx's y
                    pu_min_idx=i;
                }
                else if(points[pl_min_idx].y>points[i].y){
                    //if the current point is even below pl_min_idx's y
                    pl_min_idx=i;
                }
            }

            //Finding the maximum bounds of the points
            if(points[i].x>max_x){
                //Updating the estimate of the maximum value
                max_x=points[i].x;
                //Changing the max-x coordinate index
                pu_max_idx=i;
                pl_max_idx=i;
            }
            else if(points[i].x==max_x){
                //if two points are on the same x-coordinate farthest
                if(points[pu_max_idx].y<points[i].y){
                    //if the upper max point is below the current point
                    pu_max_idx=i;
                }
                else if(points[pl_max_idx].y>points[i].y){
                    //the the lower max point is above current point
                    pl_max_idx=i;
                }
            }
        }
        //Printing the bounding points
        cout<<"pu_min_";print_point(pu_min_idx);
        cout<<"pl_min_";print_point(pl_min_idx);
        cout<<"pu_max_";print_point(pu_max_idx);
        cout<<"pl_max_";print_point(pl_max_idx);cout<<endl;
    }
    //Function to calculate the slope give the index of the points
    float calculate_p2p_slope(int idx1,int idx2){
        /*
        DESCRIPTION:
            This function will calcualte the slope from the x-axis
            from the line made by the points at idx1 and idx2;
        USAGE:
            INPUT:
                idx1    : the index of the first point
                idx2    : the index of the second point
            OUTPUT:
                slope   :the slope of the line connecting idx1 nad idx2
        */
        float slope=(points[idx2].y-points[idx1].y)/\
                    (points[idx2].x-points[idx1].x);
        return slope;
    }
    //Function to get the candidate points to run the upper hull
    vector<int> get_candidates_idx(unsigned int cur_pu_min_idx,
                                    unsigned int cur_pu_max_idx){
        /*
        Description:
            This fucntion will give us the candidate points index on
            which we have to run the hull algorithm.

            Idea:
                All the points which are above the min-max connecting
                line will be candidate (ie. greater min-point slope
                as compared to the min-max slope).
        USAGE:
            INPUT:
                cur_pu_min_idx  : the minmum bound on the x-coordinate
                cur_pu_max_idx  : the maximum bound on the x-coordinate
            OUTPUT:
                cand_idx    : the index of the candidate points relative
                                to the points vector.
        */
        //calculating the min-max line slope
        float nx_slope=calculate_p2p_slope(cur_pu_min_idx,
                                            cur_pu_max_idx);

        //Creating the cand-idx vector
        vector<int> cand_idx;
        //Pushing the min and max points
        cand_idx.push_back(cur_pu_min_idx);
        cand_idx.push_back(cur_pu_max_idx);

        //Now traversing through points to get min-point line slope
        for(unsigned int i=0;i<points.size();i++){
            //Calculating the min-to-point line slope
            if(i==cur_pu_min_idx || i==cur_pu_max_idx){
                continue;
            }
            //Leaving the points who are outside this bound
            if(points[i].x>points[cur_pu_max_idx].x ||
                        points[i].x<points[cur_pu_min_idx].x){
                continue;
            }
            float np_slope=calculate_p2p_slope(cur_pu_min_idx,i);

            //Accepting or rejecting the points
            if(np_slope>=nx_slope){
                cand_idx.push_back(i);
            }
        }

        return cand_idx;
    }


    ///////////////////////////////////////////////////////////////////
    /*               UPPER BRIDGE RELATED FUNCTIONS                 */
    ///////////////////////////////////////////////////////////////////
    //Initializing the p2p slope struct
    struct p2p_slope*get_p2p_slope_entry(int idx1,int idx2,float slope){
        /*
        DESCRIPTION:
            This functio will dynamically allocate the struct and assign
            appropriate field and return the pointer to the struct.
        USAGE:
            INPUT:
                idx1    : the index of the first point
                idx2    : the index of the second point
                slope   : the slope of line joint by these points
            OUTPUT:
                slope_ptr: the pointer to the p2p struct element.
        */
        //Dynamically allocating the strucut from ram's heap
        struct p2p_slope *slope_ptr=(struct p2p_slope*)\
                                        malloc(sizeof(p2p_slope));

        //Assigning the value
        slope_ptr->idx1=idx1;
        slope_ptr->idx2=idx2;
        slope_ptr->slope=slope;

        return slope_ptr;
    }
    //Calculating the slope of pair of points
    vector<p2p_slope*> get_pair_slopes(vector<int> &cand_idx,\
                                        vector<int> &new_cand_idx){
        /*
        Description:
            This is a utility function to be used by the upper bridge
            function to randomly pair up the point and calculate
            their corresponding slope.

            In the process this will directly reject some of the points
            and put some of them directly into new candidate idx.
        USAGE:
            INPUT:
                cand_idx    : the index of candidate points now.
                new_cand_idx: the index of candidate points for next itr.
            OUTPUT:
                pair_slopes : the pair of points with corresponding slope
        */
        //Initializing the p2p_slope struct
        vector<struct p2p_slope*> pair_slopes;

        //Randomly pairing up the points (will do consecutive pairing)
        for(unsigned int i=0;i<cand_idx.size();i++){
            int idx1=cand_idx[i];i++;
            //If we have odd number of points then dont pair it up
            if(i==cand_idx.size()){
                new_cand_idx.push_back(idx1);
                break;
            }
            int idx2=cand_idx[i];

            //Filtering the points if both the points lie on same x
            if(points[idx1].x==points[idx2].x){
                if(points[idx1].y>points[idx2].y){
                    cout<<"point pair is verticle: removing: "<<idx2;
                    new_cand_idx.push_back(idx1);
                }
                else{
                    cout<<"point pair is verticle: removing: "<<idx1;
                    new_cand_idx.push_back(idx2);
                }
                cout<<endl;
                continue;
            }

            //Calculating the point to point slope
            float slope=calculate_p2p_slope(idx1,idx2);
            //Printitng the pair and corresponding slope
            cout<<"Pairing: "<<idx1<<" and "<<idx2<<" slope: "<<slope;
            cout<<endl;
            //Adding the slope of point to the p2p_slope vector
            struct p2p_slope *slope_ptr=get_p2p_slope_entry(idx1,idx2,\
                                                            slope);
            pair_slopes.push_back(slope_ptr);
        }

        return pair_slopes;
    }
    //Function to calculate the median slope pair
    int fill_slope_bucket(vector<struct p2p_slope*> &pair_slopes,\
                            vector<int> &LARGE_SLOPE,\
                            vector<int> &EQUAL_SLOPE,\
                            vector<int> &SMALL_SLOPE){
        /*
        Description:
            This function will wrap the process of calcualtin of the
            median slope pair. Under the hood it will use the old calcuate
            median function for this median also.
            Its a hack.
        USAGE:
            INPUT:
                pair_slopes : the vector containg the slopes of each pair
                LARGE_SLOPE : the index of pairs with large slope
                EQUAL_SLOPE : the index of pairs with equal slope to med
                SMALL_SLOPE : the index of pairs with smallar slope
            OUTPUT:
                med_slope_idx: the index of the median slope guy in pairs
        */
        //Getting the median slope but first doing our hack
        //Creating a dummy "points" with slope in x value
        cout<<"Finding the median slope"<<endl;
        vector<point> slope_points;
        vector<int> points_idx;
        for(unsigned int i=0;i<pair_slopes.size();i++){
            struct point pt;
            pt.x=pair_slopes[i]->slope;
            slope_points.push_back(pt);
            points_idx.push_back(i);
        }
        //Now we are ready with out dummy points nad index(reuse the func)
        int med_slope_idx=calculate_median(points_idx,slope_points);
        float med_slope=pair_slopes[med_slope_idx]->slope;
        cout<<"Median slope is: "<<med_slope<<endl<<endl;

        //Now we will begin out splitting procedure of pairs into bucket
        for(unsigned int i=0;i<pair_slopes.size();i++){
            if(pair_slopes[i]->slope > med_slope){
                cout<<"Putting idx: "<<i<<" in LARGE_SLOPE"<<endl;
                LARGE_SLOPE.push_back(i);
            }
            else if(pair_slopes[i]->slope== med_slope){
                cout<<"Putting idx: "<<i<<" in EQUAL_SLOPE"<<endl;
                EQUAL_SLOPE.push_back(i);
            }
            else{
                cout<<"Putting idx: "<<i<<" in SMALL_SLOPE"<<endl;
                SMALL_SLOPE.push_back(i);
            }
        }

        return med_slope_idx;
    }
    //Function for filling the new cand_idx
    void generate_new_cand_idx(int leave_flag,\
                                        vector<int> &new_cand_idx,\
                                vector<struct p2p_slope*> &pair_slopes,\
                                        vector<int> &LARGE_SLOPE,\
                                        vector<int> &EQUAL_SLOPE,\
                                        vector<int> &SMALL_SLOPE){
        /*
        Description:
            This function will generate the new candidate points
            leaving 1/4th of them either from the LARGE or from
            SMALL SLOPE indexes based on the the condition mentioned
            int leave_flag.
        USAGE:
            INPUT:
                leave_flag  : 0/1 - if 0 then remove p from LARGE
                                    if 1 then remove q from the SMALL
                                    of the (p,q) sorted pair.
                rest of the arguments are same meaning.
            OUTPUT:
                new_cand_idx: the list will be filled with the
                                new candidate points for the next itr.
        */
        if(leave_flag!=0 && leave_flag!=1){
            cout<<"Wrong leave flag\n";
            exit(0);
        }
        cout<<"Generating the new pruned candidates\n";
        if(leave_flag==0){
            cout<<"CODE mh>mb : "<<endl;
            cout<<"Removing the p point of (p,q) pair from LARGE\n";
            //Remove the p from the LARGE slope ones
            for(unsigned int i=0;i<LARGE_SLOPE.size();i++){
                struct p2p_slope *ptr=pair_slopes[LARGE_SLOPE[i]];
                if(points[ptr->idx1].x<points[ptr->idx2].x){
                    cout<<"Adding idx: "<<ptr->idx2<<endl;
                    new_cand_idx.push_back(ptr->idx2);
                }
                else{
                    cout<<"Adding idx: "<<ptr->idx1<<endl;
                    new_cand_idx.push_back(ptr->idx1);
                }
            }
            cout<<"Removing the p point of (p,q) pair from EQUAL\n";
            //Removing p from the Equal also
            for(unsigned int i=0;i<EQUAL_SLOPE.size();i++){
                struct p2p_slope *ptr=pair_slopes[EQUAL_SLOPE[i]];
                if(points[ptr->idx1].x<points[ptr->idx2].x){
                    cout<<"Adding idx: "<<ptr->idx2<<endl;
                    new_cand_idx.push_back(ptr->idx2);
                }
                else{
                    cout<<"Adding idx: "<<ptr->idx1<<endl;
                    new_cand_idx.push_back(ptr->idx1);
                }
            }
            cout<<"Adding all point of (p,q) pair from SMALL\n";
            //Adding all of the SMALL ones
            for(unsigned int i=0;i<SMALL_SLOPE.size();i++){
                struct p2p_slope *ptr=pair_slopes[SMALL_SLOPE[i]];
                new_cand_idx.push_back(ptr->idx1);
                new_cand_idx.push_back(ptr->idx2);
            }
        }
        else{
            cout<<"CODE mh<mb : "<<endl;
            cout<<"Removing the p point of (p,q) pair from SMALL\n";
            //Removing q from the SMALL
            for(unsigned int i=0;i<SMALL_SLOPE.size();i++){
                struct p2p_slope *ptr=pair_slopes[SMALL_SLOPE[i]];
                if(points[ptr->idx1].x<points[ptr->idx2].x){
                    cout<<"Adding idx: "<<ptr->idx1<<endl;
                    new_cand_idx.push_back(ptr->idx1);
                }
                else{
                    cout<<"Adding idx: "<<ptr->idx2<<endl;
                    new_cand_idx.push_back(ptr->idx2);
                }
            }
            cout<<"Removing the p point of (p,q) pair from EQUAL\n";
            //Removing q from EQUAL also
            for(unsigned int i=0;i<EQUAL_SLOPE.size();i++){
                struct p2p_slope *ptr=pair_slopes[EQUAL_SLOPE[i]];
                if(points[ptr->idx1].x<points[ptr->idx2].x){
                    cout<<"Adding idx: "<<ptr->idx1<<endl;
                    new_cand_idx.push_back(ptr->idx1);
                }
                else{
                    cout<<"Adding idx: "<<ptr->idx2<<endl;
                    new_cand_idx.push_back(ptr->idx2);
                }
            }
            cout<<"Adding all point of (p,q) pair from LARGE\n";
            //Adding all of the LARGE
            for(unsigned int i=0;i<LARGE_SLOPE.size();i++){
                struct p2p_slope *ptr=pair_slopes[LARGE_SLOPE[i]];
                new_cand_idx.push_back(ptr->idx1);
                new_cand_idx.push_back(ptr->idx2);
            }

        }

        //Printing all the points in new cand_idx:
        for(unsigned int i=0;i<new_cand_idx.size();i++){
            cout<<"new UH-Cand: ";
            this->print_point(new_cand_idx[i]);
        }
    }
    //Finding the bridge points or the new reduced candidate points
    vector<int> get_bridge_or_candidate(float med_x,int med_slope_idx,\
                                        vector<int> &cand_idx,\
                                        vector<int> &new_cand_idx,\
                                vector<struct p2p_slope*> &pair_slopes,\
                                        vector<int> &LARGE_SLOPE,\
                                        vector<int> &EQUAL_SLOPE,\
                                        vector<int> &SMALL_SLOPE){
        /*
        DESCRIPTION:
            This function will find a supporting line with median slope
            and check if two points on the opposite side of median point
            lies on that line(if one on line we will use as bridge).
            Then return the index of both the point in the vector

            Otherwise make a reduced set of new_cand_idx and return
            empty vector to indicate applying recursion.
        USAGE:
            INPUT:
                med_x           : the x-coordinate of the median point
                med_slope_idx   : the index of pair with med slope
                rest of the arguments are as usual
            OUTPUT:
                bridge_point_idx: the vector of index of our bridge if
                                    it's possible in sorted order with
                                    x-coordinate.
        */
        //Retreiving the median slope
        float med_slope=pair_slopes[med_slope_idx]->slope;

        //Getting the maximum y-intercept possible with median slope
        cout<<"\nFinding the maximum intercept"<<endl;
        float max_intrcpt;
        for(unsigned int i=0;i<cand_idx.size();i++){
            float intrcpt=points[cand_idx[i]].y-\
                                med_slope*points[cand_idx[i]].x;
            if(i==0){
                max_intrcpt=intrcpt;
            }
            else if(intrcpt>max_intrcpt){
                max_intrcpt=intrcpt;
            }
        }
        cout<<"Maximum intercept is: "<<max_intrcpt<<endl<<endl;


        //Now getting the point with MAX intercept
        cout<<"Finding the points which makes that intercept";
        cout<<" i.e lies on this supporting line"<<endl;
        vector<int> MAX;
        for(unsigned int i=0;i<cand_idx.size();i++){
            float intrcpt=points[cand_idx[i]].y-\
                            med_slope*points[cand_idx[i]].x;

            //Here due to machine precision we could have problem
            //alternatively we could add tolerance here.
            if(intrcpt==max_intrcpt){
                cout<<"id of points lying on this support: "<<cand_idx[i];
                cout<<endl;
                MAX.push_back(cand_idx[i]);
            }
        }
        cout<<endl;
        //Now seeing x-coordinate of points on this line
        cout<<"Finding the min and max x of points lying on support\n";
        float min_x=points[MAX[0]].x;int min_idx=0;
        float max_x=points[MAX[0]].x;int max_idx=0;
        for(unsigned int i=1;i<MAX.size();i++){
            if(points[MAX[i]].x<min_x){
                min_x=points[MAX[i]].x;
                min_idx=MAX[i];
            }
            if(points[MAX[i]].x>max_x){
                max_x=points[MAX[i]].x;
                max_idx=MAX[i];
            }
        }
        cout<<"max idx: "<<max_idx<<" max_x: "<<max_x<<endl;
        cout<<"min idx: "<<min_idx<<" min_x: "<<min_x<<endl<<endl;


        //Now seeing if we have landed on the jackpot bridge points
        vector<int> bridge_point_idx;
        if(min_x<=med_x && max_x>med_x){
            cout<<"Jackpot! Got a Bridge Line!!"<<endl;
            bridge_point_idx.push_back(min_idx);
            bridge_point_idx.push_back(max_idx);
            return bridge_point_idx;
        }
        else if(max_x<=med_x){//the support line has point on left of med
            //So we could remove p from (p,q) whose slope is greater than
            //median slope, since mpq>mh>mb cuz on left.
            int leave_flag=0;
            generate_new_cand_idx(leave_flag,new_cand_idx,\
                                    pair_slopes,LARGE_SLOPE,\
                                    EQUAL_SLOPE,SMALL_SLOPE);
        }
        else{
            int leave_flag=1;
            generate_new_cand_idx(leave_flag,new_cand_idx,\
                                    pair_slopes,LARGE_SLOPE,\
                                    EQUAL_SLOPE,SMALL_SLOPE);
        }
        return bridge_point_idx;
    }
    //Function to calculate the upper bridge
    vector<int> get_upper_bridge(float med_x,vector<int> &cand_idx){
        /*
        DESCRIPTION:
            This function will give the pair of points which forms
            a bridge in candidate points,covering our head from above.
            This bridge will merge the two sub-problem split before.
        USAGE:
            INPUT:
                median_x    : the x-coordinate of the median point.
                cand_idx    : the index of points on which to get bridge.
            OUTPUT:
                bridge_point_idx  : the index in sorted order acc to
                                x-coordinate formning the bridge above.
                                (it could be only 2 point)
        */
        //Initializing the bridge vector
        vector<int> bridge_point_idx;

        //Handling the base case
        if(cand_idx.size()==2){
            if(points[cand_idx[0]].x<points[cand_idx[1]].x){
                bridge_point_idx.push_back(cand_idx[0]);
                bridge_point_idx.push_back(cand_idx[1]);
            }
            else{
                bridge_point_idx.push_back(cand_idx[1]);
                bridge_point_idx.push_back(cand_idx[0]);
            }
            return bridge_point_idx;
        }

        //Now getting the bridges from the set of upper points
        while(bridge_point_idx.size()!=2){
            //Calculating the slopes
            //Initializing the vector for the next set of candidaates idx
            vector<int> new_cand_idx;
            vector<struct p2p_slope*> pair_slopes;
            //Calculating the sloped of the points along with some new cand
            cout<<"\nPairing points and calculating slopes\n";
            pair_slopes=get_pair_slopes(cand_idx,new_cand_idx);
            //Have to free up the p2p_slope pointers from heap

            //Calcualting the median slopes index and making 3 slope buckets
            vector<int> LARGE_SLOPE;
            vector<int> EQUAL_SLOPE;
            vector<int> SMALL_SLOPE;
            //Calulating the median slope
            int med_slope_idx=fill_slope_bucket(pair_slopes,LARGE_SLOPE,\
                                                EQUAL_SLOPE,SMALL_SLOPE);

            //Now finding the new candidate indexes or the the bridge points
            bridge_point_idx=get_bridge_or_candidate(med_x,med_slope_idx,\
                                                cand_idx,new_cand_idx,\
                                                pair_slopes,LARGE_SLOPE,\
                                                EQUAL_SLOPE,SMALL_SLOPE);

            //Reinitializing the new candidate indexes as curr candidate
            cand_idx.assign(new_cand_idx.begin(),new_cand_idx.end());
            //Freeing up the point pairs
            for(unsigned int i=0;i<pair_slopes.size();i++){
                free(pair_slopes[i]);
            }
            cout<<"#################################"<<endl;
            cout<<"AN ITERATION OF UPPER BRIDGE DONE"<<endl;
            cout<<"#################################"<<endl<<endl;
        }
        return bridge_point_idx;
    }


    //////////////////////////////////////////////////////////////////
    /*                  UPPER HULL RELATED FUNCTION                 */
    //////////////////////////////////////////////////////////////////
    //Function to append the bridge point to actual hull point
    void append_bridge_point_to_hull(vector<int> &bridge_idx){
        /*
        DESCRITPION:
            This function will append the bridge points found out
            by the upper bridge method to the hull points.
            This will not add if the poit already exist on hull.
        USAGE:
            INPUT:
                bridge_idx  : the vecotr containing the index of bridge
        */
        cout<<"Appending the bridge point to the hull points\n";
        //Appending the points on the bridge to the final hull idx
        for(unsigned int i=0;i<bridge_idx.size();i++){
            //Checking the existance of the bridge point in hull
            bool not_exist;
            not_exist=find(bridge_idx.begin(),
                bridge_idx.end(),bridge_idx[i])==bridge_idx.end();

            //Appending to the hull idx vec if dont exist
            if(not_exist){
                this->hull_point_idx.push_back(bridge_idx[i]);
            }
        }
    }
    //Function to generate the upper hull
    void get_upper_hull(vector<int> &cand_idx){
        /*
        DESCRIPTION:
            This function will generate the upper hull of from the given
            set of living points. This function will recursively call
            itself each time it partition the problem into two half
            and joining them by finding the upper bridge.
        USAGE:
            INPUT:
                cand_idx    : a.dtype = vector<int>
                              b. the points on which to run the upper
                                hull algorithm.(candidates)
            OUTPUT:

        */
        //Handling the base case here itself, otherwise infinite loop
        if(cand_idx.size()==2){
            //Directly appending the points to the final hull
            this->append_bridge_point_to_hull(cand_idx);
            return;
        }


        /*         MERGING STEP OF DIVIDE AND CONQUER          */
        //Finding the median element among the live candidate ones
        cout<<"Finding the median x coordinate"<<endl;
        int med_idx=calculate_median(cand_idx,this->points);
        float median_x=points[med_idx].x;
        cout<<"Median Index is: "<<med_idx<<" at x-coord: "<<median_x;
        cout<<endl;

        //Now we have to calculate the upper bridge
        vector<int> bridge_point_idx;
        bridge_point_idx=get_upper_bridge(median_x,cand_idx);
        //Appending the point to the final hull index list
        this->append_bridge_point_to_hull(bridge_point_idx);


        /*       DIVISION STEP OF DIVIDE AND CONQUER             */

        //SOLVING LEFT SUB-PROBLEM
        //Calculating the new candidate for the left sub problem
        vector<int> left_cand_idx;
        unsigned int left_pu_max_idx=bridge_point_idx[0];
        cout<<"\nSolving the left sub-problem"<<endl;
        if(this->pu_min_idx!=left_pu_max_idx){
            //Getting the index of probable point on left bridge
            left_cand_idx=this->get_candidates_idx(this->pu_min_idx,\
                                                    left_pu_max_idx);
            //Printing the candidate indexes
            for(unsigned int i=0;i<left_cand_idx.size();i++){
                cout<<"UH-Cand: ";
                this->print_point(left_cand_idx[i]);
            }
            //Calling this function recursively to solve left part
            this->get_upper_hull(left_cand_idx);
        }

        //SOLVING RIGHT SUB-PROBLEM
        //Calculating the new candidates for right side
        vector<int> right_cand_idx;
        unsigned int right_pu_min_idx=bridge_point_idx[1];
        cout<<"\nSolving the right sub-problem"<<endl;
        if(right_pu_min_idx!=this->pu_max_idx){
            //Getting the new candidates for the right side
            right_cand_idx=this->get_candidates_idx(right_pu_min_idx,\
                                                    this->pu_max_idx);
            //Printing the candidate indexes
            for(unsigned int i=0;i<right_cand_idx.size();i++){
                cout<<"UH-Cand: ";
                this->print_point(right_cand_idx[i]);
            }
            //Calling this function recursively to solve right side
            this->get_upper_hull(right_cand_idx);
        }
        return;
    }


public:
    //Defining the constructor
    Kirkpatrick_Seidel(vector<struct point> points):ConvexHull(points){
        cout<<"\nPoints Initialized"<<endl;
        this->get_extremum_points();
    }

    //printing the index and location of point
    void print_point(int idx){
        cout<<"idx:"<<idx<<" at location: ";
        cout<<points[idx].x<<","<<points[idx].y<<endl;
    }

    //Public function to generate the convex hull
    void put_a_hull_on_points(){
        /*
        DESCRIPTION:
            This function is the main iterface of talking for finding the
            convex world from the outside world.Internally it will call
            it's helper function to generate the convex hull and put the
            indexes of the points in the member variable hull_point_idx.
        USAGE:
            No Arguments and Return value
        */
        //First of all we will find the upper hull
        //Generating the candidate points which could form upper hull.
        cout<<"Generating the UPPER-HULL Candidates"<<endl;
        vector<int> cand_idx=get_candidates_idx(this->pu_min_idx,\
                                                this->pu_max_idx);
        //Printing the candidate indexes
        for(unsigned int i=0;i<cand_idx.size();i++){
            cout<<"UH-Cand: ";
            this->print_point(cand_idx[i]);
        }

        //Now calling the upper hull creator to get upper hull
        cout<<endl<<"Calling the Upper Hull function"<<endl;
        this->get_upper_hull(cand_idx);
    }

};

int main(){
    //Initializing the points
    srand(14);
    vector<struct point> points;
    vector<int> points_idx;
    for(int i=0;i<15;i++){
        float x;//=rand()%100;
        float y;//=rand()%200;
        int idx=i;
        cin>>x>>y;
        struct point p;
        p.x=x;
        p.y=y;
        points.push_back(p);
        points_idx.push_back(idx);
        cout<<"idx: "<<idx<<" point: x:"<<p.x<<", y:"<<p.y<<endl;
    }

    //Creating the class and initializig the points
    Kirkpatrick_Seidel MyKPS(points);

    //Testing the median finding algorithm
    //int med_idx=calculate_median(points_idx,points);
    //cout<<"med_idx: "<<med_idx<<endl;

    //Testing the Upper hull
    MyKPS.put_a_hull_on_points();
}
