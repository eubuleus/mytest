// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
	int i1,i2;
	std::cin>>i1>>i2;
	std::cout<<"-----"<<i1<<"============"<<i2<<std::endl;
	std::string str;

//------------------->>>>>>>>>>>>>>>>>>>

    use Mod_Common,    only: OUT, E_cut, E_surf0, dE
    use Mod_Vector    ,only: Init_Mod_Vector
    use Mod_Vector_Waterflow    ,only: Init_Mod_Vector_Waterflow
    use Mod_Grid    ,only: Init_Mod_Grid
//! ______________________________________________________________________

    float d_lrzcs(5), lrzcs_0(5)
    int  n_lrzcs(5)
    NameList /Grid/ d_lrzcs, n_lrzcs, lrzcs_0
    NameList /INPUT2/ E_cut, E_surf0, dE

    int IChoice_Search = 2;

    //! - dimensions -
    open(1,file='input.dat') 
    read(1,NML=Grid);    rewind(1)
    read(1,NML=INPUT2)
    close(1)

    open(1,file='SHellCor.txt')

	//! - only plot -
	if(IChoice_Search == 5) {
        projection(1,n_lrzcs)
		close(1)
		stop
	}
	if( IChoice_Search == 6) {
        projection2(1,n_lrzcs)
		close(1)
		stop
	}
    //! - Construct the grid -
    init_Mod_Grid  (1,lrzcs_0, d_lrzcs, n_lrzcs);
    close(1);

    //! - auxiliary vectors and operations -
    open(OUT,file='OUT.txt');
    call Init_Mod_Vector(n_lrzcs);

//    Well let's search for channels


switch(iChoice_Search) {
		case 1:
            init_Mod_Vector_WaterFlow(n_lrzcs)
            search_Prepare
            search

		case 2:
            Init_Mod_Vector_WaterFlow(n_lrzcs)
            Search_Prepare1()
            Search_2Barrier()
		case 3:
            Search_Slice()
		case 4:
            call Search2       // ! moller
		default:
            stop 'Error: main!'
	}

    stop 'OK, well done!!'



//-------------------<<<<<<<<<<<<<<<<<<<
	return 0;
}

class Grid {
public:
	Grid* getNext(){return NULL;};
	int get_i() const;
private:
	int i;
};

int Grid::get_i() const
{
	return 7;
}

