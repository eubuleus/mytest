#include <vector>

//!    integer(1): -2**( 7) ~ 2**( 7)-1, i.e. -128  ~127
//!    integer(2): -2**(15) ~ 2**(15)-1, i.e. -32768~32767
//!    integer(4): -2**(31) ~ 2**(31)-1, i.e. around -2.15E10~2.15E10
const int R_G = 5;                      //
const int OUT = 25;                     // output file
const int n_Minima_MAX = 100;
const int max_len = R_G;
const int E_infinit = 1.e4;             //
float E_cut = 3.;
bool b_E_Ground = false;        //! .true. if E_Ground is used.
int len = 5;
bool b_Multi_Modal = false;
const int DIM[] = {2,2,2,2,2};


std::vector<int> ix_Minima;

class Common {
   public:

    float E_surf0;
    float dE;
    float E_Ground, cm12_Ground;
    int n_Minima;
};


class GridType{
    float E; // = E_infinit;            //! E>100 means E hasn't been calculated or E is greater than E_cut
    int   Ix; //= -1;                   //
    //GridType G[DIM[0]][DIM[1]][DIM[2]][DIM[3]][DIM[4]]; //
    GridType* G[2][2][2][3][4]; //
    
};

class WetTagType{
    bool b_Wet[2]; // = false;
    bool b_dam;  //    = false;
};
