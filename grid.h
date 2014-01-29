// - the Grid -
#include "common.h"

class Grid {
//    use Mod_common,only: GridType, NodeType, R_G, E_cut
    
    int num_nodes;
    int Dim_G[R_G][2];
    int UB_G[R_G][2];                   //! upper bound. Lower bounds are set zero.
    int UB1[R_G],UB2[R_G];             //! upper bound


    Grid *p_Root;         //! points to root node
    Grid *pG[][][][][];  //! points to 1st Level Grid

    float d_lrzcs[5], lrzcs_0[5];
    int n_lrzcs[5]
                                            // Nodes(i).vd_ix == 0 indicates a minimum
    Node *nodes[];

    void init(int IU,INP_lrzcs_0, INP_d_lrzcs, INP_n_lrzcs);    
    Ilrzcs[5] GetShapeFromIx(int ix);
    Ilrzcs[5] GetIlrzcsFromIx(int ix);
    int GetIlFromIx(int ix);

}
