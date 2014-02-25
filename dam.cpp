#include Common.h               // only: NodeType
#include Grid                   //  only: Nodes,Dim_G

class Dam{

    int n_dam = 0;        // n_dam_new = 0
    int list_dam(4000);   // list_dam_new(100)

    void AddDamNode(int ix){
        nodes[ix].wet_tag.b_dam = true;
        n_dam++;
        list_dam(n_dam) = ix;
    }

    void DistanceToDam(int ix0,distance,ix1){
        integer,intent(out):: distance,ix1
        int Ilrzcs0(5),d;
        int ix,Ilrzcs1(5),vec(5);
        Node *p;
        
        p => Nodes(ix0)
        Ilrzcs0(:) = p.ind(:,1)*Dim_G(:,2)+p.ind(:,2)
        distance = 1000
        for(int i = 0; i<n_dam; i++){
            ix = list_dam[i]
            p => Nodes(ix);
            Ilrzcs1(:) = p.ind(:,1)*Dim_G(:,2)+p.ind(:,2);
            vec = Ilrzcs0 - Ilrzcs1 ;
            d = dot_product(vec,vec)
            if(d<distance) {
                distance = d
                ix1 = ix
            }
        }
    }
}
