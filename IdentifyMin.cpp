// modifying Nodes(ix).vd_ix as well as returning b_min
#include "Grid.h"   //,   only: Nodes
#include "Vector.h" //, only: Dir,num_dir_len
#include "Common"   //, only: GridType,max_len
#include "DS_Mol"   //, only: GetNeighValue,GetNode,IndexShift

void IdentifyMin(int ix, int b_min) {

    Grid *p;
//    integer,intent(out):: b_min

    float E0, E;
    int i,vec[5],vd,ind[5,2],ind1[5,2];

    ind= Nodes[Ix].Ind;
    E0 = Nodes[Ix].E;
    b_min = true;
    for (int i = 0; i < num_dir_len(max_len);i++){

        vec(:) = Dir(:,i);
        E = GetNeighValue(ind,vec);
        
        if(E<E0) {
            b_min = false;
            return;
        }
    }
}
