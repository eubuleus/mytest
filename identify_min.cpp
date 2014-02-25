// modifying Nodes(ix).vd_ix as well as returning b_min
#include "Grid.h"   //,   only: nodes
#include "Vector.h" //, only: Dir,num_dir_len
#include "Common"   //, only: GridType,max_len
#include "DS_Mol"   //, only: GetNeighValue

bool IdentifyMin(int ix) {

    Grid *p;
    float E0, E;
    int vec[5],vd,ind[5],[2],ind1[5],[2];

    ind= nodes[ix].Ind;
    E0 = nodes[ix].E;
    for (int i = 0; i < num_dir_len[max_len]; i++){

        vec(:) = Dir(:,i);
        E = GetNeighValue(ind,vec);
        
        if(E < E0){
            return false;
        }
    }
    return true;
}
