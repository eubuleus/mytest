
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
