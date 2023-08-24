#include <iostream>  
#include "md5.hpp"  
  
using namespace std;  
  
int main(int argc, char *argv[])  
{
    string str = "所有通过A题的人中A题提交次数最多的"; 
    cout << "md5 of this string: " << MD5::md5(str)<<endl;  
    return 0;  
}