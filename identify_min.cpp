// modifying Nodes(ix).vd_ix as well as returning b_min
#include "Grid.h"   //,   only: nodes
#include "Vector.h" //, only: Dir,num_dir_len
#include "Common"   //, only: GridType,max_len
#include "DS_Mol"   //, only: GetNeighValue

bool IdentifyMin(Node* p_node) {

    Grid *p;
    float E0, E;
    int vec[5],vd,ind[5],[2],ind1[5],[2];

    ind= p_node->ind;
    E0 = p_node->E;
    for (int i = 0; i < num_dir_len[max_len]; i++){

        vec(:) = Dir(:,i);
        E = GetNeighValue(ind,vec);
        
        if(E < E0){
            return false;
        }
    }
    return true;
}
