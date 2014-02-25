#include "vector.h"      //    use Mod_Vector,        only: Dir,num_dir_len,num_dir
#include "common.h"    //OUT, E_cut, n_Minima_MAX, n_minima, ix_Minima, NodeType, E_surf0, dE
#include <iostream>
#include <iomanip>
#include "grid.h"      //num_nodes, n_lrzcs, Nodes, GetIlrzcsFromIx, GetShapeFromIx
#include "DS_Mol.h"    //getAllNeigh
#include "search_mol.h"// initAlgorithm, raiseWater, printIfWet, initWater,    setWet, &
                       // addToVisit, setOnSurf, initNewLevel, isDam,    isWet, useToVisit, setStartin, &
                       // List_OnSurf , list_ToVisit , list_Visitin , n_ToVisit ,n_Visitin, n_Wet
#include "mod_dam.h"   //n_dam, AddDamNode
#include "pool.h"

class AlgorithmMoller{
    int list_on_surface [][],list_to_visit[][],list_visiting[][];
    int num_wet[2], num_on_surface[2] , num_to_visit[2] , num_visiting[2];
    Pool pools[] = new Pool[2];

    void Init(){

        list_on_surface = new int[num_nodes][2];
        list_to_visit = new int[num_nodes][2];
        list_visiting = new int[num_nodes][2];
        num_on_surface[] = 0;
        num_to_visit[]= 0;
        num_visiting[]= 0;
        num_wet[] = 0
    }

    void SetStarting(int i, int ix){
        SetWet(i,ix);
        SetOnSurf(i,ix);
    }

    float InitWater(int ix1, int ix2){
        float e = max(nodes[ix1].E, nodes[ix2].E, E_surf0);
        if(e>E_cut) {
            stop "Error: max(nodes[ix1].E, nodes[ix2].E, E_surf0)> E_cut";
        }
        return e;
    }

    void UseToVisit(int i){              //  i = 1 or 2
        list_visiting(1:num_to_visit(i),i) = list_to_visit(1:num_to_visit(i),i)
        num_visiting[i]++;
        num_to_visit[i] = 0;
    }


    void SetWet(int i, Node* p_node){
        p_node->is_wet(i) = true;    
        n_wet[i]++;
    }

    bool function IsDam(Node* p_node){
        return p_node->b_dam;
    }

    bool function IsWet(int i, Node* p_node){
        return p_node->is_wet(i);
    }


    void printIfWet(){
        int i_min, ix;
        cout << "Minima under surface:" <<endl;
        for (int i = 0; i++: i<2) {
            cout << "Pool" << setw(4) << i << ":";
            for (i_min = 1; i<n_minima; i++){
                ix = ix_Minima(i_min)
                if( nodes[ix].is_wet(i)) {
                    cout << setw(4)  << i_min;
                }
            }	
            cout << endl;
        }
    }


    void Searchrx2(){

        int ix, ix1, ix2, ix_min; //index
        int Ilrzcs[5],Il;
        float E_surf;
 
        int i,k,n,i_min, i_min2;
        int ix_Nbs[num_dir],n_NBs;  //  n: number of neighbors
        int n_Wet_NBs;
 
        AlgorithmMoller algthrithm
        //------------------- 1 minimua ----------------------
 
        allocate( ix_Minima(n_Minima_MAX) );
        i_min = 0;
        for(Node* p_node = nodes; p_node != NULL; p_node++) {       // ! Energy <= Ecut
            if(IdentifyMin(p_node)) {
                i_min++;                    //    ! number of minina
                ix_Minima(i_min) = p_node;    
            }
        }
        n_Minima = i_min;
 
        // display 
 
        cout << "number of minimums = " << n_Minima << endl;
        cout << "NO.      E          Ilrzcs          cm12 \n";
        for(i_min = 0; i < n_minima; i++){
            ix = ix_Minima(i_min);
            cout << setw(3)  << i_min 
                 << setw(10) << setprecision(3) << fixed << nodes(ix).E 
                 << setw(10) << GetIlrzcsFromIx(Ix) // 2X,5i3, TODO
                 << setw(10) << setprecision(3) << fixed << nodes(ix).cm12 << endl;
            write(50,"(i3,f10.3,2X,5i3,f10.3)")i_min,nodes(ix).E, GetIlrzcsFromIx(Ix), Nodes(ix).cm12;
        }
 
        initAlgorithm();
 
        cout << "Select the entry & the exit: "
        cin >> i_min >> i_min2;
 
        SetStarting(1,ix_Minima(i_min));
        SetStarting(2,ix_Minima(i_min2));
 
        //initial state 
        bool b_pools_connected = false;
        bool b_barrier_found = false;
        int iloop = 0;
 
        //---------------------- iteration 
 
        E_surf = initWater(ix_Minima(i_min), ix_Minima(i_min));
        cout << "E_surf " << setw(10) << setprecision(3) << fixed << E_surf << endl;

L1:     while (true) {                               // over water levels
            iloop++;
L11:        for (i = 0; i<2; i++){                   // over two water pools
                Pool pool = pools[i];
                pool.InitNewLevel();

L21:            for(;;) {                           // visit all nodes between level L and L+1
L21i:               for(Node* p_node_visiting = list_Visiting; p_node_visiting != NULL; p_node_visiting++){ //j
                        Node* p = *p_node_visiting;
                        GetAllNeigh(pnode, n_NBs, ix_NBs);
                        n_wet_NBs = 0;
           
                        // loop over all neighbors of node ix
Lk:                     for (k = 0; k<n_NBs; k++){
                            ix1 = ix_NBs(k);
 
                            if( nodes(ix1).E > E_Surf ){
                                continue;
                            }
                            n_Wet_NBs++:
 
                            if (isDam(ix1)) {
                                continue;
                            }
                            if( isWet(3-i,ix1)) {
                                b_pools_connected = true;
                                // if we add both ix and ix2 as dam, things may get better
                                AddDamNode(ix);      // cout << "pN.E/ix:" << nodes(ix).E << ix <<  "Nodes(ix1).E/ix:" << nodes(ix1).E << ix1 <<" (1)\n";  
                                exit Lk;
                            } else {
                                if(!isWet(i,ix1)){
                                    pool.AddToVisit(ix1);
                                    pool.SetWet(i,ix1);
                                }
                            }
                        }
 
                        if(n_Wet_NBs<n_NBs && !isDam(p_node)){
                            pool.SetOnSurf(p_node);
                        }
                    }
 
                    if(num_to_visit[i]==0) {
                        exit L21;        // go to next water level
                    }
                    UseToVisit(i);
                }
            }
 
            // check if the barrier have been found
 
            printIfWet();
 
            if(b_pools_connected) {
                if(iloop <= 1) {
                    stop "Error: Barrier<E_surf0. Please decrease E_surf0";
                }
                b_barrier_found = true;
                cout << "Barrier  : (" << E_surf-dE << "," << E_surf << ")";
                break L1;
            }
 
            // cout << "n_OnSurf2 = " << n_OnSurf2 << endl;
            RaiseWater(E_surf);   
            cout << "E_surf " << setw(10) << setprecision(3) << fixed << E_surf << endl;
 
        }//enddo L1
 
    }

}
