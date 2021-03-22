#include "../bset/rtw_bset.h"


typedef struct {
    int width;
    int height;
} Square;

//This is an comp_fn, to push variables into our binary search tree we need to
//define a comparasion function to identify how we compare our datas.
//In this example we will use "Square" struct for data.
//This comparasion function takes 2 const void * value and compares left hand side
//with right hand side. If left side is greater we should return 1
//If left side is smaller then we should return -1, if they are equal we should return 0.
int cmp_fun_struct(const void* lhs, const void* rhs){
    Square *d_lhs = (Square *) lhs;
    Square *d_rhs = (Square *) rhs;

    int left  = d_lhs->height * d_lhs->width;
    int right = d_rhs->height * d_rhs->width;

    if(left > right)
    {
        return 1;
    }
    else if(left < right)
    {
        return -1;
    }
    return 0;
}

void example_struct_fun(){
    //we have to create our binary set object with rtw_bset_init function.
    //It takes 1 parameter which is our predefined comparasion function.
    rtw_bset set = rtw_bset_init(&cmp_fun_struct);
    
    //Lets assume that we have 4 struct element and we want to push them to our queue.
    Square elem1;
    elem1.height = 5;
    elem1.width = 4;

    Square elem2;
    elem2.height = 3;
    elem2.width = 4;

    Square elem3;
    elem3.height = 6;
    elem3.width = 9;

    Square elem4;
    elem3.height = 6;
    elem3.width = 9;

    //To push object we are using rtw_bset_insert function.
    //It takes 2 argument, first one is address of our queue and second one is address of our data.
    //If data exists in our binary tree, that data does not added to our tree.

    rtw_bset_insert(&set,&elem1);
    rtw_bset_insert(&set,&elem2);
    rtw_bset_insert(&set,&elem3);
    rtw_bset_insert(&set,&elem4);

    if(rtw_bset_search(&set, &elem4))
        printf("elem4 found\n");
    else
        printf("elem4 couldn't found\n");

    rtw_bset_free(&set);
}

int main()
{
    example_struct_fun();
    /*
    rtw_bset set = rtw_bset_init(&personal_comp_func_int);
    
    int elem1 = 5;
    int elem2 = 6;
    int elem3 = 7;
    int elem4 = 7;
    rtw_bset_insert(&set,&elem1);
    rtw_bset_insert(&set,&elem2);
    rtw_bset_insert(&set,&elem3);
    rtw_bset_insert(&set,&elem4);
    
    int data_to_search1 = 7;
    if(rtw_bset_search(&set, &data_to_search1))
        printf("data found\n");
    else
        printf("data couldn2T fonud\n");
    

    rtw_bset_free(&set);
    return 0*/

}