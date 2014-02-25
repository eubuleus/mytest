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
    const int num_dir = 10+40+80+80+(32+80);     //= 322. number of neighbors of all lengths
    int num_dir_len[5];                          //num_dir_len(i): number of directions whose norm squared are less than or equal to i
    int Dir[5][num_dir];

    void init_Mod_Vector(INP_n_lrzcs);

}

void Vector::init_Mod_Vector(INP_n_lrzcs)
{
    int,intent(in):: INP_n_lrzcs(5)
    int i1,i2,i3,i4,i5,ii(5),l,len;

    int i = 0
    for(len = 1;len<=5;len++){
        for(int i1=-2;i1<2;i1++){
            for(int i2=-2;i2<2;i2++){
                for(int i3=-2;i3<2;i3++){
                    for(int i4=-2;i4<2;i4++){
                        for(int i5=-2;i5<2;i5++){
                            ii[:] = (/i1,i2,i3,i4,i5/)
                            l = i1*i1 +i2*i2 +i3*i3 +i4*i4 +i5*i5        
                            if( l/=len || (l==4.and.maxval(abs(ii))==2)) {
                                continue;           // exclude vectors like (2,0,0,0,0)
                            }
                            i++;        
                            Dir(:,i) = ii(:);
                        }
                    }
                }
            }
        }
        num_dir_len[len] = i;
        cout << num_dir_len[len]  << endl;
    }
        cout << "num_dir = " << num_dir << endl;
}
