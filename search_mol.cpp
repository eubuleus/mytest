#include "grid.h"              //     use Mod_Grid,        only: num_nodes, n_lrzcs, Nodes, GetIlrzcsFromIx, GetShapeFromIx
#include "vector.h"            //    use Mod_Vector,        only: Dir,num_dir_len,num_dir
#include "common.h"            //    use Mod_Common,        only: E_cut, n_Minima_MAX, n_minima, ix_Minima, NodeType, E_surf0, dE

class SearchMol{
    int list_on_surface [][],list_to_visit[][],list_visiting[][];
    int num_wet[2], num_on_surface[2] , num_to_visit[2] , num_visiting[2];

    void InitAlgorithm(){

        list_on_surface = new int[num_nodes][2];
        list_to_visit = new int[num_nodes][2];
        list_visiting = new int[num_nodes][2];
        num_on_surface(:) = 0;
        num_to_visit(:)= 0;
        num_visiting(:)= 0;
        num_wet(:) = 0
    }

    void SetStartin(int i, int ix){
        SetWet(i,ix);
        SetOnSurf(i,ix);
    }

    float InitWater(int ix1, int ix2){
        float e = max(nodes[ix1].E, nodes[ix2].E, E_surf0);
        if(e>E_cut) {
            stop 'Error: max(nodes[ix1].E, nodes[ix2].E, E_surf0)> E_cut';
        }
        return e;
    }

    void RaiseWater(float& E_surf)
        E_surf += dE
        if(E_surf>E_cut){
            stop 'Error: Barrier>Ecut. Please increase E_cut'
        }
    }

    void UseToVisit(int i){              //  i = 1 or 2
        list_visiting(1:num_to_visit(i),i) = list_to_visit(1:num_to_visit(i),i)
        num_visiting[i]++;
        num_to_visit[i] = 0;
    }


    void SetWet(int i, int ix){
        nodes[ix].wet_tag.b_Wet(i) = true;    
        n_wet[i]++;
    }

    void addToVisit(int i, int ix){
        if(nodes[ix].wet_tag.b_wet(i)){
            return   // already included
        }
        num_to_visit[i]++;
        list_to_visit(num_to_visit(i),i) = ix
    }

    void setOnSurf(int i,int ix){
        num_on_surface[i]++;
        list_on_surface(num_on_surface(i),i) = ix
    }

    void initNewLevel(int i){ // i = 1 or 2
        list_visiting (1:num_on_surface[i],i) = list_on_surface (1:num_on_surface[i],i)
        num_visiting[i] = num_on_surface[i];
        n_Onsurf[i]  = 0;
        num_to_visit[i] = 0;
    }
    
    
    bool function isDam(int ix){
        return nodes[ix].wet_tag.b_dam;
    }

    bool function IsWet(int i, int ix){
        return nodes[ix].wet_tag.b_Wet(i);
    }


    void printIfWet(){
        int i_min, ix;
        cout << "Minima under surface:" <<endl;
        for (int i = 0; i++: i<2) {
            cout << "Pool" << setw(4) << i << ":";
            for (i_min = 1; i<n_minima; i++){
                ix = ix_Minima(i_min)
                if( nodes[ix].wet_tag.b_Wet(i)) {
                    cout << setw(4)  << i_min;
                }
            }	
            cout << endl;
        }
    }
}
