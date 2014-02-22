#include "Grid.h"      //num_nodes, n_lrzcs, Nodes, GetIlrzcsFromIx    !, GetShapeFromIx
#include "Vector.h"    //Dir,num_dir
#include "DS_Mol.h"    //getAllNeigh
#include "Dam.h"       //n_dam, AddDamNode, DistanceToDam
#include "Common.h"    //len, E_cut, n_Minima, ix_Minima, NodeType, dE
#include "Search_Mol.h"//List_OnSurf , list_ToVisit , list_Visitin , n_OnSurf ,n_ToVisit ,n_Visitin, &
                       //list_OnSurf2, n_OnSurf2,n_ToVisit2,n_Visitin2

void SearchMM(float& E_surf){

    int:: ind[5,2], ix, ix1, ix2, ix_min        ! 
    Node *pN, *pN1;
    int Ilrzcs[5],Il;    
    float cm12;
    int i,k,n,n1,i_min,m;
    int ix_Nbs(num_dir),n_NBs;;
    int icount;

    int n_Wet, n_Wet2, n_dam_candi, n_dam_new;
    int dam_candi[2000];
    bool b_adj_to_dam, b_adj_to_pool2;
    bool distance, distance1 = 9;

    dE = 0.1                            ! modified

    E_surf += 2.5*dE
L0: while(true){                                    // loop over different water levels
        E_surf += dE;
        write(*,'(a,f10.3,a,i6)') "E_surf = ",E_surf, "   n_dam = ",n_dam;
        if(E_surf>E_cut) stop 'In Search_MM: E_surf>E_cut'
// _________________________ pool 1 _____________________________________
        
        list_Visitin (1:n_OnSurf,1) = list_OnSurf (1:n_OnSurf)
        n_Visitin= n_OnSurf;
        n_Onsurf  = 0;
        n_ToVisit = 0;
        n_dam_candi= 0;

L1:     while(true){                                // visit all nodes between level L and L+1
            for (m = 0 ; m<n_dam_candi; m++){
                ix = dam_candi(m)
                write(*,*) m, Nodes(ix).Il, Nodes(ix).E
            }
            cout << "n_Visitin = " << n_Visitin << n_dam_candi << E_surf

L11:        for ( i = 0; i<n_Visitin; i++){             
                ix = list_Visitin(i,1)
                pN => Nodes(ix);
                if(pN.wet_tag.b_dam) {
                    continue;
                }
                GetAllNeigh(ix,len,n_NBs,ix_NBs);
                icount = 0;
                b_adj_to_pool2 = false;        // is node ix ajacent to pool 2
                b_adj_to_dam   = false;       // is node ix ajacent to existing dam
                // ---
                for (k = 0; k<n_NBs; k++) {            // loop over all neighbors of node ix
                    ix1 = ix_NBs[k];
                    pN1 => Nodes[ix1];
                    if( pN1.E>E_Surf ){
                        continue;
                    }
                    if(pN1.wet_tag.b_dam ) b_adj_to_dam = true
                    if( pN1.wet_tag.b_Wet2) b_adj_to_pool2 = true;
                }

                if(b_adj_to_pool2) {
                    if(b_adj_to_dam){
                        AddDamNode(ix);
                        Ilrzcs(:)= GetIlrzcsFromIx(Ix); 
                      // write(*,'(a,i,f10.3,5i3)')'dam', n_dam, pN.E,Ilrzcs(:)
                    } else {
                        n_dam_candi++:
                        write(60,*)"n_dam_candi = ",n_dam_candi, ix,pN.E,E_surf
                        dam_candi(n_dam_candi) = ix
                    }
                } else {
                    for ( k = 1; k < n_NBs; k++) {            // loop over all neighbors of node ix
                        ix1 = ix_NBs(k)
                        pN1 => Nodes(ix1)

                        if( pN1.E>E_Surf ) continue;
                        icount++:
                        if (pN1.wet_tag.b_dam ) continue;

   			if( !pN1.wet_tag.b_included ){
                            pN1.wet_tag.b_Wet = true;
                            n_wet++;
                            pN1.wet_tag.b_included = .true.
                            n_ToVisit++;
                            list_ToVisit(1,n_ToVisit) = ix1
                        }
                    }
                    if(icount !=n_NBs) {
                        n_OnSurf++;
                        list_OnSurf(n_OnSurf) = ix;
                    }
                }
            }// L11

            if(n_ToVisit==0) { 
                exit L1        ! go to next water level
            } else {
                list_Visitin(1:n_ToVisit,1) = list_ToVisit(1,1:n_ToVisit);
                n_Visitin = n_ToVisit;
                n_ToVisit = 0;
            }
       }//   enddo L1
!
        n_dam_new = 0
LA:     for( n = 0;; n =){
            for ( i = 1 ; i<n_dam_candi; i++){
                ix = dam_candi(i)
                pN =>Nodes(ix)
                if(pN.wet_tag.b_dam) {    // The i-th candidate node has already been identified as a dam point
                    continue;
                }                
                DistanceToDam(ix,distance,ix1);
                if(distance<distance1){    // if candidate ix is neighboring to a dam node
                    AddDamNode(ix);
                    n++;
                    n_dam_new++;
                }
            }
            if(n_dam_new==n_dam_candi) {
                exit LA;    // all the candidates have been identified as dam nodes
            }
            if(n==0) { //no new dam nodes have been found during the last scan, which means the residual candidates must come from a new barrier
                cout << " extra barrier found";
//                exit L0
                ResultSummary();
                read*;
                exit LA;
            }
                
        }
//_________________________ pool 2 _____________________________________

        list_Visitin[1:n_OnSurf2,2] = list_OnSurf2[1:n_OnSurf2]
        n_Visitin2= n_OnSurf2;    
        n_Onsurf2  = 0;
        n_ToVisit2 = 0;

L2:     while(true){                                // visit all nodes between level L and L+1
            for( i = 1,n_Visitin2){
                    ix = list_Visitin(i,2);
                    pN => Nodes(ix);
                    if( pN.wet_tag.b_Wet){
                        stop "debug error: in Search_MM: pN.b_Wet -------------****";
                    }
                    GetAllNeigh(ix,len,n_NBs,ix_NBs);
                    icount = 0;

                    for ( k = 0; k < n_NBs; k++){        // loop over all neighbors of node ix
                        ix1 = ix_NBs(k);
                        pN1 => Nodes(ix1);
                        if( pN1.E>E_Surf ){
                            continue;
                        }
                        icount++:
                        if (pN1.wet_tag.b_dam ) continue;
                        if( pN1.wet_tag.b_Wet) {
                            stop "debug error: in Search_MM: pN1.b_Wet -------------****";
                        }
                        if( !pN1.wet_tag.b_included ){
                            pN1.wet_tag.b_Wet2 = true;
                            n_wet2++:
                            pN1.wet_tag.b_included = true;
                            n_ToVisit2++:
                            list_ToVisit(2,n_ToVisit2) = ix1;
                        }
                    }

                    if(icount != n_NBs) {
                        n_OnSurf2++;
                        list_OnSurf2i[n_OnSurf2] = ix;
                    }
                }
                if(n_ToVisit2 == 0) { 
                    break L2;       // go to next water level
                } else {
                    list_Visitin[1:n_ToVisit2,2] = list_ToVisit[2,1:n_ToVisit2];
                    n_Visitin2 = n_ToVisit2;
                    n_ToVisit2 = 0;
                }
            }//        enddo L2
        } //    enddo L0

        std::cout << "Press any key to call ResultSummary" << '\n';
        stop
    }
}

void ResultSummary(){
    int distance, j, Ilrzcs1(5)

    cout << "distance from New dam to old dam" << '\n';
    j = 0;
    for (int i = 1; i < n_dam_candi; i++) {            ! - loope over new dam nodes -
        ix = dam_candi(i);
        if(nodes(ix).wet_tag.b_dam) cycle

        j++;
        DistanceToDam(ix,distance,ix1);
        Ilrzcs = GetIlrzcsFromIx(ix); 
        Ilrzcs1= GetIlrzcsFromIx(ix1); 

        write(*,'(i4,i6,f10.3,5i3,2x,5i3)') j, distance, Nodes(ix).E, Ilrzcs(:),Ilrzcs1(:);
        AddDamNode(ix);
    }

    cout << "E_surf = " << E_surf;
    cout << "n_dam_candi = " << n_dam_candi;

    if(false) {
        cout << "  E        Ilrzcs   old/new barrier";
        cout << " -- old dam nodes --";
        for(int i = 0; i < n_dam_candi; i++){
            ix = dam_candi(i);
            if(nodes(ix).wet_tag.b_dam) {
                Ilrzcs(:)= GetIlrzcsFromIx(Ix); 
                write(*,'(f10.3,5i3,a)') Nodes(ix).E,Ilrzcs(:),'  old';
            }
        }
        // display old dam nodes 
        cout << " -- all dam nodes --";
        i = 0;
        for (ix = 0; ix < num_nodes; ix++){
            if(Nodes(ix).wet_tag.b_dam) {
                i++;
                Ilrzcs(:)= GetIlrzcsFromIx(Ix); 
                write(*,'(i,f10.3,5i3)') i,Nodes(ix).E,Ilrzcs(:);
            }
        }
    }
}
