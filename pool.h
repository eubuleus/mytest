class NodeList{
    Nodes* list[];
    Nodes* p_tail;
    int size;

    void Reset(){
        p_tail = NULL;
        size = 0;
    }

    void Append(Node* p_node){
        p_tail++;
        *p_tail = p_node;
        size++;
    }

}

class Pool{
    float energy_surface;
    float energy_cut;

    NodeList list_visiting;
    NodeList list_to_visit;
    NodeList list_on_surface;
    Pool* p_neighbor_pool;

    void InitNewLevel(){
        NodeList list_tmp = list_on_surface;
        list_visiting = list_on_surface;
        list_on_surface = list_tmp;
        list_on_surface.Reset();
        list_to_visit.Reset();
    }

    void RaiseWater(float dE)
        energy_surface += dE
        if(energy_surface > energy_cut){
            stop "Error: Barrier>Ecut. Please increase E_cut"
        }
    }

    void AddToVisit(Node* p_node){
        if(!p_node->wet_tag.b_wet(i)){
            list_to_visit.Append(p_node);
        }
    }

    void SetOnSurface(Node* p_node){
        list_on_surface.Append(p_node);
    }

}

