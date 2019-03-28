#include <iostream>
#include <vector>
#include <cstdlib>
#include "convex_hull_utility.h"
using namespace std;


/*
implementing the heap related function as defined in header file
*/
//Defining the constructor function
Heap::Heap(char heap_type,int heap_size){
    /*
    Description:
        The constructor for creating the heap.
    USAGE:
        INPUT:
            heap_type   : char to specify the type of the heap
            heap_size   : integer to define the specify of the heap
    */
    //Assigning the type and size to the heap
    if(heap_type!='n' && heap_type!='x'){
        cout<<"Wrong Heap type specified\n";
        exit(0);
    }
    this->heap_type=heap_type;
    this->heap_size=heap_size;
    this->last_pos=-1;          //nothing in the heap

    //Initializing the heap array to contain the index of the
    idx_heap=(int *)malloc(sizeof(int)*heap_size);
    val_heap=(float *)malloc(sizeof(float)*heap_size);
}
//Implementing the insertion function
void Heap::insert_into_heap(int idx,float value){
    /*
    Description:
        This function will insert an elemnt into heap and then heapify
        to maintain all the proterty of the heap.
    USAGE:
        INPUT:
            idx     : index of the point being entered (useful sometimes)
            value   : the value which will be consulted while heapifying.
    */
    //Incrementing the last pos which is being entered right now
    this->last_pos++;

    //Now inserting the element into the heap
    idx_heap[this->last_pos]=idx;
    val_heap[this->last_pos]=value;

    //Now cleaning up the house after the party
    int cid=this->last_pos;
    //Going bottom up to heapify the last elemet inserted
    while(cid>0){
        //getting the parent index
        int pid=(cid-1)/2;

        //Now depending on the type of the heap we will heapify different
        //If the heap is a max heap and the parent is smallar than child
        if(this->heap_type=='x' && val_heap[cid]>val_heap[pid]){
            //Putting the parent to children position
            //And putting the children(curr point) as parent pos
            this->swap_elements(cid,pid);
        }
        else if(this->heap_type=='n' && val_heap[cid]<val_heap[pid]){
            //if the heap is min and the child is smallar than parent
            //Putting the parent to child position
            //And putting the current point at the parent pos
            this->swap_elements(cid,pid);
        }
        else{
            //Nothing is wrong so break
            break;
        }
        //Updating the new position of the current point to check up
        cid=pid;
    }
}
void Heap::swap_elements(int pos1,int pos2){
    /*
    This function will swap the elements present in at pos1 and pos2
    in both idx and val heap simultaneously.
    */
    //Saving the temporary
    int temp_idx=idx_heap[pos1];
    int temp_val=val_heap[pos1];

    //Swapping the pos2 in pos1
    idx_heap[pos1]=idx_heap[pos2];
    val_heap[pos1]=val_heap[pos2];
    //Putting the value of pos1 at pos2 from the temp entry
    idx_heap[pos2]=temp_idx;
    val_heap[pos2]=temp_val;
}
//Implementing the deletion function
int Heap::pop_from_heap(){
    /*
    Description:
        This function will pop the first element from the heap and
        do the cleanup after that. Also it returns the index of the
        point being popped.
    */
    //saving the index of top of heap for returning
    int pop_idx=idx_heap[0];

    //Removing the top of the heap
    idx_heap[0]=idx_heap[this->last_pos];
    val_heap[0]=val_heap[this->last_pos];

    //Decrementing the count of the heap
    this->last_pos--;

    //Now cleaning up the house after the party by heapifying top down.
    int pid=0;
    int cid1=2*pid+1;
    int cid2=2*pid+2;

    //Now going down until we exceed the last_pos
    while(this->last_pos>0){
        //Retreiving the value of parent and its child
        int valp=val_heap[pid];

        //if this is max heap and parent's val is less than either of
        //child
        if(cid1>this->last_pos){
            //if the first child is out of bound then no child exist
            break;
        }
        else if(cid2>this->last_pos){
            //if one first child exist and second dont
            int val1=val_heap[cid1];
            //If this is max heap and the value of child is greater
            if(this->heap_type=='x' && valp<val1){
                this->swap_elements(cid1,pid);
            }
            else if(this->heap_type=='n' && valp>val1){
                //If this is min heap and value of parent is less
                this->swap_elements(cid1,pid);
            }
            break;
        }
        int val1=val_heap[cid1];
        int val2=val_heap[cid2];
        if(this->heap_type=='x' && (valp<val1 || valp<val2)){
            //Now swappping the parent with the max valued child
            if(val1>val2){
                //Swapping parent with the first child
                //Putting the parent at the children's pos
                this->swap_elements(cid1,pid);
                pid=cid1;
            }
            else{
                //if second child is greater than parent and first
                //Putting the parent to second's children position
                this->swap_elements(cid2,pid);
                pid=cid2;
            }
        }
        else if(this->heap_type=='n' && (valp>val1 || valp>val2)){
            if(val1<val2){
                //if child1's value is less than the child2 then let up.
                this->swap_elements(cid1,pid);
                pid=cid1;
            }
            else{
                this->swap_elements(cid2,pid);
                pid=cid2;
            }
        }
        else{
            break;
        }
    }
    return pop_idx;
}

/*
Median calculation function using the mean heap
*/
int calculate_median(vector<struct point> points){
    /*
    Description:
        This function calcualte the median point according to x_coord
        in O(N) using the max and min heap.
    USAGE:
        INPUT:
            points  : the vector containing all the points which we
                        want to get median from.
        OUTPUT:
            med_idx : the index of the median element in the points
                        vector.
    */
    //Handling the base case when only two elements are present
    if(points.size()==1 ||points.size()==2){
        return 0;
    }

    //Initializing one min and one max heap
    Heap min_heap('n',points.size());
    Heap max_heap('x',points.size());

    //Iterating over the points vector
    for(int i=0;i<points.size();i++){
        //Inserting an element into max heap and heapifying
        max_heap.insert_into_heap(i,points[i].x);i++;
        //If we reach to the end of the points vector
        if(i==points.size()){
            break;
        }
        max_heap.insert_into_heap(i,points[i].x);

        //Poppoing the top of max heap to balance equal no. ele on
        //both side of the heap (left and right)
        int pop_idx=max_heap.pop_from_heap();
        //Pushing this element to the min heap
        min_heap.insert_into_heap(pop_idx,points[pop_idx].x);
    }
    //The the one at the top of the max heap is the median one
    int med_idx=max_heap.pop_from_heap();
    return med_idx;
}
