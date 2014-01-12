#include "Grid.h"              //     use Mod_Grid,        only: num_nodes, n_lrzcs, Nodes, GetIlrzcsFromIx, GetShapeFromIx
#include "Vector.h"            //    use Mod_Vector,        only: Dir,num_dir_len,num_dir
#include "Common.h"            //    use Mod_Common,        only: E_cut, n_Minima_MAX, n_minima, ix_Minima, NodeType, E_surf0, dE

class Search_Mol{
    int list_OnSurf [][],list_ToVisit[][],list_Visitin[][];
    int n_Wet[2], n_OnSurf[2] , n_ToVisit[2] , n_Visitin[2];

    void initAlgorithm(){

        list_OnSurf = new int[num_nodes][2];
        list_ToVisit = new int[num_nodes][2];
        list_Visitin = new int[num_nodes][2];
        n_OnSurf(:) = 0;
        n_ToVisit(:)= 0;
        n_Visitin(:)= 0;
        n_Wet(:) = 0
    }

    void setStartin(int i, int ix){
        setWet(i,ix);
        setOnSurf(i,ix);
    }

    float initWater(int ix1, int ix2){
        initWater = max(nodes(ix1).E, nodes(ix2).E, E_surf0)
        if(initWater>E_cut) {
            stop 'Error: max(nodes(ix1).E, nodes(ix2).E, E_surf0)> E_cut'
        }
    }

    void raiseWater(E_surf)
        real,intent(out):: E_surf
        E_surf = E_surf+dE
        if(E_surf>E_cut){
            stop 'Error: Barrier>Ecut. Please increase E_cut'
        }
    }

    void useToVisit(int i){              //  i = 1 or 2
        list_Visitin(1:n_ToVisit(i),i) = list_ToVisit(1:n_ToVisit(i),i)
        n_Visitin[i]++;
        n_ToVisit[i] = 0;
    }


    void setWet(int i, int ix){
        nodes(ix).wet_tag.b_Wet(i) = true;    
        n_wet(i)++;
    }

    void addToVisit(int i, int ix){
        if(nodes(ix).wet_tag.b_wet(i)){
            return   // already included
        }
        n_ToVisit[i]++;
        list_ToVisit(n_ToVisit(i),i) = ix
    }

    void setOnSurf(int i,int ix){
        n_OnSurf(i)++;
        list_OnSurf(n_OnSurf(i),i) = ix
    }

    void initNewLevel(int i){ // i = 1 or 2
        list_Visitin (1:n_OnSurf(i),i) = list_OnSurf (1:n_OnSurf(i),i)
        n_Visitin(i) = n_OnSurf(i);
        n_Onsurf(i)  = 0        ;
        n_ToVisit(i) = 0        ;
    }
    
    
    bool function isDam(int ix){
        return nodes[ix].wet_tag.b_dam;
    }

    bool function isWet(int i, int ix){
        return nodes[ix].wet_tag.b_Wet(i);
    }


    void printIfWet(){
        int i_min, ix;
        write(*,*) 'Minima under surface:' 
        for (int i = 0; i++: i<2) {
            write(*,'(a,i4,a,\)') 'Pool',i,' :'
            for (i_min = 1; i<n_minima; i++){
                ix = ix_Minima(i_min)
                if( nodes(ix).wet_tag.b_Wet(i)) write(*,'(i4,\)') i_min
            }	
        write(*,*)
        }
    }
}
