#include<iostream>
using namespace std;
int main()
{
    int *p;
    int len;
    cin >> len;
    //用指针 p 指向 new 动态分配的长度为 len*sizeof(int)的内存空间
    p = new int[len];

    for(int i=0; i<len; i++){
        p[i] = i+1;
    }

    cout << "--------" << endl;
    cout << sizeof(p) << endl;// 8 on amd64
    cout << "--------" << endl;
    for(int i=0; i<len+1; i++){
        cout << p[i] << endl;
    }

    delete[] p;
    return 0;
}

