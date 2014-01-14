#include <iostream>

float E_infinit = 1000;

class Node{
    float  E;
    float  cm12;          // distance of centers of mass
    int Il;
    int ind[5][2];                   // -128 ~ 127

        //  - for Moller only -

    WetTagType   wet_tag;

   //     ! - for waterflow only -

    int  BasinId;
    int vd_ix;               // ! water flow direction. 
    int n_CB;           //! number of connected Basins by looking down
    int* CB[] = NULL;            //! connected basins. CB(0:n) - CB(0) is the basin it belongs to; CB(1:n) are other connected basins
    int* ix_CB[] = NULL;           //! connected node belonging to a certain adjacent Basin
    bool isCol;     
    public:
        Node(); //Constructor
        ~Node(); //Destructor

};


Node::Node()
{
    E = E_infinit;
    vd_Ix = -1;
    n_CB = 0;
    cm12 = 0.0;
    Il = -1;
    isCol = false;
    BasinId = 0;
}


/*
int len;
cin>>len;
//用指针p指向new动态分配的长度为len*sizeof(int)的内存空间
int *p = new int[len];
...........
delete[]p;
return0;
*/
