#include <iostream>
#include <iomanip> 
using namespace std;
int main() { 

    int a;
    cout<<"input a:";
    cin>>a;
    cout<< setw(10)<<a <<20 <<endl;          //指定域宽为10
    cout<< "dec:" <<dec <<a<<endl;       //以10进制形式输出
    cout<< "hex:" <<hex <<a<<endl;       //以16进制形式输出
    cout<< "oct:" <<setbase(8)<<a<<endl;//以 8进制形式输出

    char *pt="China";                 //pt指向字符 串”China” 
    cout<<setw(10)<<pt<<endl;         //指定域宽为10，输出字符串
    cout<<setfill('*')<<setw(10)<<pt<<endl;//指定域宽10，输出字符串，空白处填充"*"

    double pi=22.0/7.0; 
    cout<<setiosflags(ios::scientific)<<setprecision(8);//按指数形式输出，8位小数
    cout<<"pi="<<pi<<endl; //输出pi值
    cout<<"pi="<<setprecision(4)<<pi<<endl;//改为4位小数
    cout<<"pi="<<setiosflags(ios::fixed)<<pi<<endl;//改为小数形式输出
 
    cout << "-----------------------------\n";
    cout.fill(' ');
    cout << setw(9) << 11.2 <<endl;
    cout << setw(9) <<1111.2 <<endl;
    cout << setw(9) << 11.200 <<endl;
    cout << setw(9)<< setprecision(4) <<fixed <<11.12 <<endl;
 
    return 0; 
}

/*
other references:
http://blog.csdn.net/cloudhsu/article/details/5818607
*/
