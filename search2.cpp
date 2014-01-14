#include "Grid.h" //, only: num_nodes, n_lrzcs, Nodes, GetIlrzcsFromIx, GetShapeFromIx
#include "Vector.h" //, only: num_dir
#include "DS_Mol.h" //, only: getAllNeigh
#include "Common.h" // only: OUT, E_cut, n_Minima_MAX, n_minima, ix_Minima, NodeType, E_surf0, dE, b_Multi_Modal
#include "Search_Mol.h" //, only: initAlgorithm, raiseWater, printIfWet, initWater,    setWet, &
                    // addToVisit, setOnSurf, initNewLevel, isDam,    isWet, useToVisit, setStartin, &
                    // List_OnSurf , list_ToVisit , list_Visitin , n_ToVisit ,n_Visitin, n_Wet
#include "Mod_Dam.h.h"  // , only: n_dam, AddDamNode
void Search2(){

//!!! delete for non-multi-modal case =====>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//! - index -
    int ix, ix1, ix2, ix_min    //!,ix_debug        ! 
                       //  ! depth, length
    bool b_minimum  //  !    ,b_debug,b_debug2                    
    int Ilrzcs(5),Il //   !,Ilrzcs_debug(5),Ilrzcs_debug2(5)
    float E_surf

    int i,j,k,n,i_min, i_min2 //
    int ix_Nbs(num_dir),n_NBs;       // ! n: number of neighbors
    int n_Wet_NBs;

//! ¨€¨€#####------------------- 1 minimua -----------------------#####¨€¨€

    allocate( ix_Minima(n_Minima_MAX) );
    i_min = 0
    for(Ix = 0; ix < num_nodes) {       // ! Energy <= Ecut
        IdentifyMin(Ix,b_minimum);
        if(b_minimum) {
            i_min++;                    //    ! number of minina
            ix_Minima(i_min) = Ix    
        }
    }
    n_Minima = i_min;

//! - display -

    cout << "number of minimums = " << n_Minima << endl;
    cout << "NO.      E          Ilrzcs          cm12"
    for(i_min = 0; i<n_minima; i++){
        ix   = ix_Minima(i_min)
        write(* ,'(i3,f10.3,2X,5i3,f10.3)')i_min,nodes(ix).E, GetIlrzcsFromIx(Ix), Nodes(ix).cm12
        write(50,'(i3,f10.3,2X,5i3,f10.3)')i_min,nodes(ix).E, GetIlrzcsFromIx(Ix), Nodes(ix).cm12
    }

//! ¨€¨€####---------------------- initialize  -----------------########¨€¨€

    initAlgorithm();

//! - starting point -
    cout << "Select the entry & the exit: "
    read(*,*) i_min, i_min2

    setStartin(1,ix_Minima(i_min));
    setStartin(2,ix_Minima(i_min2));

//! - initial state -
    bool b_pools_connected = false;
    bool b_barrier_found = false;
    int iloop = 0;

//! ¨€¨€####---------------------- iteration -----------------########¨€¨€

    E_surf = initWater(ix_Minima(i_min), ix_Minima(i_min));        write(*,'(a,f10.3)') 'E_surf ',E_surf

L1: while (true) {                               // ! over water levels
        iloop++;
L11:    for (i = 0; i<2; i++){                   // ! over two water pools
            initNewLevel(i)

L21:        for(;;) {                           //     ! visit all nodes between level L and L+1
L21i:           for( j = 0;j<n_Visitin[i];j++){ 
                    ix = list_Visitin[j,i];
                    GetAllNeigh(ix,n_NBs,ix_NBs);
                    n_Wet_NBs = 0;
//                ! -
Lk:                 for (k = 0; k<n_NBs; k++){        //! loop over all neighbors of node ix
                        ix1 = ix_NBs(k)

                        if( nodes(ix1).E>E_Surf ) continue;
                        n_Wet_NBs++:

                        if (isDam(ix1)) {
                            continue;
                        }
                        if( isWet(3-i,ix1)) {
                            b_pools_connected = true;
                            //! if we add both ix and ix2 as dam, things may get better
                            AddDamNode(ix);            //!    write(*,*) 'pN.E/ix:',Nodes(ix).E, ix, 'Nodes(ix1).E/ix:',Nodes(ix1).E,ix1,' (1)'
                                                            //!    write(*,'(5i3,2x,5i3,\)') GetIlrzcsFromIx(Ix), GetIlrzcsFromIx(Ix1)
                            exit Lk
                        } else {
                            if(!isWet(i,ix1)){
                                addToVisit(i,ix1);
                                setWet(i,ix1);
                            }
                        }
                    }

                    if(n_Wet_NBs<n_NBs.and..not.isDam(ix)) call setOnSurf(i,ix)

                }

                if(n_ToVisit(i)==0) {
                    exit L21;        //! go to next water level
                }
                useToVisit(i);
            }
        }

//! __________________ check if the barrier have been found ______________

        printIfWet();                             //     ! - writeout -
//    ! - 
        if(b_pools_connected) {
            if(iloop<=1) {
                stop 'Error: Barrier<E_surf0. Please decrease E_surf0'
            }
            b_barrier_found = true;
            write(*,'(a,f,a,f,a)') 'Barrier  : (', E_surf-dE    ,',',E_surf     ,')'
            break L1;
        }
                                                                            //! write(*,*)'n_OnSurf2 = ',n_OnSurf2
        call raiseWater(E_surf);                                            write(*,'(a,f10.3)') 'E_surf ',E_surf

//! ______________________________________________________________________

    }//enddo L1

//!!! delete for non-multi-modal case =====>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    if(b_Multi_Modal.and.b_barrier_found){
        if(n_dam>50) {
            stop 'too many initial dam nodes, please decrease dE'        
        }
        cout << "All the initial dam nodes:" << endl;
        j = 0
        for ( ix = 0; ix < num_nodes; ix++){
            if(Nodes(ix).wet_tag.b_dam) {
                j++:
                Ilrzcs(:)= GetIlrzcsFromIx(Ix); 
                write(*,'(i,f10.3,5i3)') j,Nodes(ix).E,Ilrzcs(:);
                write(OUT,'(a,i,f10.3,5i3)') 'Initial Dam:',j,Nodes(ix).E,Ilrzcs(:);
            }
        }
        cout << "press any key to continue with searchMM" << endl;
        read*;
//!        call SearchMM(E_surf)
    }
//!!! =====================================<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    stop 'Search2: ********88 ?>??'
}

