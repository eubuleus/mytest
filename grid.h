#include "common.h"

class Grid {
//    use Mod_common,only: GridType, NodeType, R_G, E_cut
    int Dim_G[R_G][2];
    int UB_G[R_G][2];                  // upper bound. Lower bounds are set zero.
    int UB1[R_G],UB2[R_G];             // upper bound

    Grid *p_root;         //points to root node
    Grid *pG[][][][][];  //points to 1st Level Grid

    float d_lrzcs[5], lrzcs_0[5];
    int n_lrzcs[5]
                                            // Nodes(i).vd_ix == 0 indicates a minimum
    Node *nodes[];

    void init(int IU,INP_lrzcs_0, INP_d_lrzcs, INP_n_lrzcs);    
    Ilrzcs[5] GetShapeFromIx(int ix);
    Ilrzcs[5] GetIlrzcsFromIx(int ix);
    int GetIlFromIx(int ix);

}

void Grid::init(int IU,INP_lrzcs_0, INP_d_lrzcs, INP_n_lrzcs) {
    float INP_d_lrzcs[5], INP_lrzcs_0[5]
    int INP_n_lrzcs[5]

    Grid* p;

    int i1,i2,i3,i4,i5,i,ii[5];
    int j1,j2,j3,j4,j5,j;
    int n,ix;

    float shape_para[5]
    float Edef, Eld, Esh, Eshn, Eshp, cm12, AH
    int icount_cut, ind[5,2]

    GridType* Grid(:,:,:,:,:)

    d_lrzcs(:) = INP_d_lrzcs(:);
    lrzcs_0(:) = INP_lrzcs_0(:);
    n_lrzcs(:) = INP_n_lrzcs(:);

    Dim_G[:,2] = 2;
    Dim_G[:,1] = n_lrzcs[:]/Dim_G[:,2]+1;

    UB_G[:,:] = Dim_G[:,:] - 1;

    cout << "Rank of grid0 "<< R_G << endl;
    cout << " Upper bounds                           Dim_G    "<< endl;
    for (i = 0; i++; i<2) {
        cout << UB_G[1:5,i] << '     ' << Dim_G[1:5,i] << endl;
    }
    cout << 'n_lrzcs = ', n_lrzcs;

    UB1[:] = UB_G[:,1];                //upper bounds
    UB2[:] = UB_G[:,2];                //upper bounds

// set up grid

    p_Root = new Grid;
    new p_root.G[UB1[1], UB1[2], UB1[3], UB1[4], UB1[5]];
    pG => p_Root.G;
    pG[:,:,:,:,:].E = 1000.;

    icount_cut = 0;
    read(IU, *);   
    read(IU, *);
    while(true){  
        read(IU, *,end=50) cm12, ii[1:5], shape_para[1:5], Edef, Eld, Esh, AH ;   
//      read(IU, *,end=50) cm12, ii(1:5), shape_para(1:5), Edef, AH    
        if (Edef > E_cut){
	    continue;
        }
        icount_cut++;
//	write(*,*) icount_cut, Edef, E_cut
    }

50  num_nodes = icount_cut
    cout <<  "num_nodes = "<< num_nodes;

//! create an array containing pointers associated with each low enengy node on L2 grid.
    new Nodes[num_nodes];

    ix = 0;
    rewind(IU)
    read(IU, *);
    read(IU, *);
    while(true) {
        read(IU, *,end=100) cm12, ii[1:5], shape_para[1:5], Edef, Eld, Esh, AH;
//		read(IU, *,end=100) cm12, ii(1:5), shape_para(1:5), Edef, AH   
        if (Edef>E_cut) cycle
        ix++;

//!        if(ix>82340)write(*,*)ix,Edef
//!        if(ix>82342)stop

        ind[:,1] = ii[:]/Dim_G[:,2]
        ind[:,2] = mod(ii[:],Dim_G[:,2]);

        i1 = ind[1,1];
        i2 = ind[2,1];
        i3 = ind[3,1];
        i4 = ind[4,1];
        i5 = ind[5,1];
        j1 = ind[1,2]; 
        j2 = ind[2,2]; 
        j3 = ind[3,2]; 
        j4 = ind[4,2]; 
        j5 = ind[5,2]; 

        if(ALL(ind[:,2]==0)) pG[i1,i2,i3,i4,i5].E = Edef;
        p = &pG[i1][i2][i3][i4][i5];            //! node on 1st grid
        if(!associated(p.G)){
            new p.G[UB2[1], UB2[2], 0:UB2[3], 0:UB2[4], 0:UB2[5]];
            p.G(:,:,:,:,:).E = 10000.;
	}
        p.G[j1][j2][j3][j4][j5].E = Edef;
        
        Nodes[ix].E = Edef;
        Nodes[li].Il = i1;
        Nodes[Ix].ind = ind;
        Nodes[Ix].cm12 = cm12;
        p.G[j1][j2][j3][j4][j5].ix = ix;
    }
100 cout << "size of array InxL2_cut" << Ix << num_nodes << endl;
	
}
    
Ilrzcs[5] Grid::GetShape(Node* pN){
    int Ilrzcs[5];
    float lrzcs[5];

    Ilrzcs[:] = *pN->ind[:,1]*Dim_G[:,2]+nodes(Ix).ind[:,2];
    lrzcs[:] = lrzcs_0[:] + d_lrzcs[:]*Ilrzcs[:];
    return lrzcs;
}

Ilrzcs[5] Grid::GetIlrzcsFromIx(Node* pN){
    return Ilrzcs(:) = *pN->ind[:,1]*Dim_G[:,2]+Nodes(ix).ind[:,2];
}

int Grid::GetIlFromIx(int ix){
    return Nodes(Ix).ind[1,1]*Dim_G[1,2]+Nodes[ix].ind[1,2];
}
