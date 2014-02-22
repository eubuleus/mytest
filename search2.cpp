#include <iostream>
#include <iomanip>
#include "grid.h"      //num_nodes, n_lrzcs, Nodes, GetIlrzcsFromIx, GetShapeFromIx
#include "vector.h"    //num_dir
#include "DS_Mol.h"    //getAllNeigh
#include "common.h"    //OUT, E_cut, n_Minima_MAX, n_minima, ix_Minima, NodeType, E_surf0, dE, b_Multi_Modal
#include "search_mol.h"// initAlgorithm, raiseWater, printIfWet, initWater,    setWet, &
                       // addToVisit, setOnSurf, initNewLevel, isDam,    isWet, useToVisit, setStartin, &
                       // List_OnSurf , list_ToVisit , list_Visitin , n_ToVisit ,n_Visitin, n_Wet
#include "mod_dam.h"   //n_dam, AddDamNode

void Search2(){

    int ix, ix1, ix2, ix_min; //index
    bool b_minimum;
    int Ilrzcs[5],Il;
    float E_surf;

    int i,j,k,n,i_min, i_min2;
    int ix_Nbs[num_dir],n_NBs;  //  n: number of neighbors
    int n_Wet_NBs;

//------------------- 1 minimua ----------------------

    allocate( ix_Minima(n_Minima_MAX) );
    i_min = 0;
    for(ix = 0; ix < num_nodes; ix++) {       // ! Energy <= Ecut
        IdentifyMin(ix,b_minimum);
        if(b_minimum) {
            i_min++;                    //    ! number of minina
            ix_Minima(i_min) = ix;    
        }
    }
    n_Minima = i_min;

// display 

    cout << "number of minimums = " << n_Minima << endl;
    cout << "NO.      E          Ilrzcs          cm12 \n";
    for(i_min = 0; i<n_minima; i++){
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

    SetStartin(1,ix_Minima(i_min));
    SetStartin(2,ix_Minima(i_min2));

//initial state 
    bool b_pools_connected = false;
    bool b_barrier_found = false;
    int iloop = 0;

//---------------------- iteration -----------------######

    E_surf = initWater(ix_Minima(i_min), ix_Minima(i_min));
    cout << "E_surf " << setw(10) << setprecision(3) << fixed << E_surf << endl;

L1: while (true) {                               // ! over water levels
        iloop++;
L11:    for (i = 0; i<2; i++){                   // ! over two water pools
            InitNewLevel(i);

L21:        for(;;) {                           // visit all nodes between level L and L+1
L21i:           for( j = 0; j < num_visiting[i]; j++){ 
                    ix = list_Visitin[j],[i];
                    GetAllNeigh(ix,n_NBs,ix_NBs);
                    n_wet_NBs = 0;

                    // loop over all neighbors of node ix
Lk:                 for (k = 0; k<n_NBs; k++){
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
                                                 // write(*,"(5i3,2x,5i3,\)") GetIlrzcsFromIx(Ix), GetIlrzcsFromIx(Ix1)
                            exit Lk;
                        } else {
                            if(!isWet(i,ix1)){
                                AddToVisit(i,ix1);
                                SetWet(i,ix1);
                            }
                        }
                    }

                    if(n_Wet_NBs<n_NBs && !isDam(ix)) setOnSurf(i,ix);
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

//!!! delete for non-multi-modal case =====>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    if(b_Multi_Modal && b_barrier_found){
        if(n_dam>50) {
            stop "too many initial dam nodes, please decrease dE"        
        }
        cout << "All the initial dam nodes:" << endl;
        j = 0
        for ( ix = 0; ix < num_nodes; ix++){
            if(Nodes(ix).wet_tag.b_dam) {
                j++:
                Ilrzcs(:)= GetIlrzcsFromIx(Ix); 
                write(*,"(i,f10.3,5i3)") j,Nodes(ix).E,Ilrzcs(:);
                write(OUT,"(a,i,f10.3,5i3)") "Initial Dam:",j,Nodes(ix).E,Ilrzcs(:);
            }
        }
        cout << "press any key to continue with searchMM" << endl;
        read*;
    }

    stop "Search2: ********88 ?>??"
}


