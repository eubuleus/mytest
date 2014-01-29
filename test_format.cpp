#include <iostream>
#include <iomanip> //不要忘记包含此头文件
using namespace std;
int main()
{ int a;
   cout<<"input a:";
   cin>>a;
   cout<<"dec:"<<dec<<a<<endl; //以上 进制形式输出整数
   cout<<"hex:"<<hex<<a<<endl; //以十 六进制形式输出整数a
   cout<<"oct:"<<setbase(8)<<a<<endl;//以八进制形式输出整数a
   char *pt="China";         //pt指向字符 串”China” 
   cout<<setw(10)<<pt<<endl; //指定 域宽为10，输出字符串
   cout<<setfill('*')<<setw(10)<<pt<<endl;//指定域宽10，输出字符串，空白处 以“*”填充
   double pi=22.0/7.0; //计算pi值
   cout<<setiosflags(ios::scientific)<<setprecision(8);//按指数形式输出，8位小数
   cout<<"pi="<<pi<<endl; //输出pi值
   cout<<"pi="<<setprecision(4)<<pi<<endl;//改为4位小数
   cout<<"pi="<<setiosflags(ios::fixed)<<pi<<endl;//改为小数形式输出

   cout << "-----------------------------\n";
   cout.fill(' ');
   cout << setw(7) << 11.2 <<endl;
   cout << setw(7) <<1111.2 <<endl;
   cout << setw(7) << 11.200 <<endl;
   cout << setw(7) << 11.12 <<endl;

   return 0; 
}

