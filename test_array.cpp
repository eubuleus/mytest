/*
A two dimensional array is a vector of vectors. 
The vector contructor can initialize the length of the array and set the initial value.
*/
#include <iostream>
#include <vector>

using namespace std;


//a vector of vectors to represent a two dimensional array: 
void test_2d_array()
{
   // Declare size of two dimensional array and initialize.
   vector< vector<int> > vI2Matrix(3, vector<int>(2,0));   
 
   vI2Matrix[0][0] = 0;
   vI2Matrix[0][1] = 1;
   vI2Matrix[1][0] = 10;
   vI2Matrix[1][1] = 11;
   vI2Matrix[2][0] = 20;
   vI2Matrix[2][1] = 21;
 
   cout << "Loop by index:" << endl;
 
   int ii, jj;
   for(ii=0; ii < 3; ii++)
   {
      for(jj=0; jj < 2; jj++)
      {
         cout << vI2Matrix[ii][jj] << "  " ;
      }
      cout << endl;
   }
}


int main (int argc, char **argv)
{
   test_2d_array(); 
}
/*
Example of iterators used with a two dimensional vector.
*/
void test_2d_vector_iterator()
{
   vector< vector<int> > vI2Matrix;    // Declare two dimensional array
   vector<int> A, B;
   vector< vector<int> >::iterator iter_ii;
   vector<int>::iterator                 iter_jj;
 
   A.push_back(10);
   A.push_back(20);
   A.push_back(30);
   B.push_back(100);
   B.push_back(200);
   B.push_back(300);
 
   vI2Matrix.push_back(A);
   vI2Matrix.push_back(B);
 
   cout << endl << "Using Iterator:" << endl;
 
   for(iter_ii=vI2Matrix.begin(); iter_ii!=vI2Matrix.end(); iter_ii++)
   {
      for(iter_jj=(*iter_ii).begin(); iter_jj!=(*iter_ii).end(); iter_jj++)
      {
         cout << *iter_jj << endl;
      }
   }
}

