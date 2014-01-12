class Vector{
    use Mod_Common,only: R_G, max_len
/*    ! There are:
    !   10 vectors of length 1 like (1,0,0,0,0),
    !   40 vectors of length 2 like (1,1,0,0,0),
    !   80 vectors of length 3 like (1,1,1,0,0),
    !   80 vectors of length 4 like (1,1,1,1,0),
    !   32 vectors of length 5 like (1,1,1,1,1), and
    !   80 vectors of length 5 like (2,1,0,0,0).
*/
    const int num_nb_len[max_Len] = {10, 40, 80, 80, 32+80} 
    const int num_dir = 10+40+80+80+(32+80);     //! = 322. number of neighbors of all lengths
    int num_dir_len[5];                          //! num_dir_len(i): number of directions whose norm squared are less than or equal to i
    int Dir[5][num_dir];

    void init_Mod_Vector(INP_n_lrzcs);

}
