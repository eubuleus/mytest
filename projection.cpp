#include "Common.h"   //, only: E_cut

void projection(int IU, int n_lrzcs) {
    float cm12,shape_para(5),Edef,AH;
	int n_dim;
	int ii(5),dim1,dim2,dim3, i_d1,i_d2,i_d3,size1,size2,size3;
	float E(:,:,:),l(:,:,:),r(:,:,:),z(:,:,:),c(:,:,:),s(:,:,:)
//_____________________________________________________________________

	cout << n_lrzcs;
//!	n_dim = 3
	n_dim = 2;
													//! For example, we wanna plot E(l,r)
	dim1 = 1;										//! l
	dim2 = 2;										//! r
	dim3 = 3;										//! z
    size1 = n_lrzcs(dim1)							//! 
    size2 = n_lrzcs(dim2)							//!
	size3 = n_lrzcs(dim3)
	if (n_dim == 2){
		size3 = 0;
	}

	allocate(E(0:size1,0:size2,0:size3))
	allocate(l(0:size1,0:size2,0:size3))
	allocate(r(0:size1,0:size2,0:size3))
	allocate(z(0:size1,0:size2,0:size3))
	allocate(c(0:size1,0:size2,0:size3))
	allocate(s(0:size1,0:size2,0:size3))
	E(:,:,:) = E_cut
	l(:,:,:) = 0.
	r(:,:,:) = 0.
	z(:,:,:) = 0.
	c(:,:,:) = 0.
	s(:,:,:) = 0.
	
	read(IU,*);
	for (::) {
        read(IU, *,end=100) cm12, ii(1:5), shape_para(1:5), Edef, AH;
		if(Edef>E_cut) {     						//! e.g. ii = (3,6,7,1,0)
			continue;
		}
		i_d1 = ii(dim1);								//! i_l = 3
		i_d2 = ii(dim2);								//! i_r = 6
		if(n_dim == 3) {
			i_d3 = ii(dim3);
		} else {
			i_d3=0
		}
		if(Edef < E(i_d1,i_d2,i_d3)) {				//! Edef < of E(3,6)
			E[i_d1,i_d2,i_d3] = Edef;
			l[i_d1,i_d2,i_d3] = shape_para[1];
			r[i_d1,i_d2,i_d3] = shape_para[2];
			z[i_d1,i_d2,i_d3] = shape_para[3];
			c[i_d1,i_d2,i_d3] = shape_para[4];
			s[i_d1,i_d2,i_d3] = shape_para[5];
		}
	}

100 continue
//	!***************************************************************
//	! writeout
    if(n_dim == 2) {
		do i_d2 = 0,size2
			write(60,'(100f8.3)') E(:,i_d2,0)
		enddo

		write(60,*);
		write(60,*)' - l - '
		do i_d2 = 0,size2
			write(60,'(100f8.3)') l(:,i_d2,0)
		enddo

		write(60,*)
		write(60,*)' - r - '
		do i_d2 = 0,size2
			write(60,'(100f8.3)') r(:,i_d2,0)
		enddo

		write(60,*)
		write(60,*)' - z - '
		do i_d2 = 0,size2
			write(60,'(100f8.3)') z(:,i_d2,0)
		enddo

		write(60,*)
		write(60,*)' - c - '
		do i_d2 = 0,size2
			write(60,'(100f8.3)') c(:,i_d2,0)
		enddo

		write(60,*)
		write(60,*)' - s - '
		do i_d2 = 0,size2
			write(60,'(100f8.3)') s(:,i_d2,0)
		enddo

	} else if(n_dim ==3) {

		do i_d1 = 0, size1
			write(60,*)' i_d1 =', i_d1
			do i_d2 = 0,size2
				write(60,'(100f8.3)') E(i_d1,i_d2,:)
			enddo
			write(60,*)
		enddo

		write(60,*) "*************************************"
		
		for (i_d1 = 0; i_d1 <= size1; i_d1++) {
			write(60,*)
			write(60,*)' i_d1 =', i_d1

			write(60,*)
			write(60,*)' - l -'
			do i_d2 = 0,size2
				write(60,'(100f8.3)') l(i_d1,i_d2,:)
			enddo

			write(60,*)
			write(60,*)' - r -'
			do i_d2 = 0,size2
				write(60,'(100f8.3)') r(i_d1,i_d2,:)
			enddo

			write(60,*)
			write(60,*)' - z -'
			do i_d2 = 0,size2
				write(60,'(100f8.3)') z(i_d1,i_d2,:)
			enddo

			write(60,*)
			write(60,*)' - c -'
			do i_d2 = 0,size2
				write(60,'(100f8.3)') c(i_d1,i_d2,:)
			enddo

			write(60,*)
			write(60,*)' - s -'
			do i_d2 = 0,size2
				write(60,'(100f8.3)') s(i_d1,i_d2,:)
			enddo

		}

	}

}
