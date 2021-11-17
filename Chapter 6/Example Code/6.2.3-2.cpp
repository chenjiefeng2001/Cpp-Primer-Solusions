#include <iostream>
#include <string>
using namespace std;
int main()
{
    int i = 42;
    const int *cp = &i; //正确，但是cp不能改变i
    const int &r = i;   //正确，但是r不能改变i
    const int &r2 = 42; //正确
    int *p = cp;        //错误，类型不匹配
    int &r3 = r;        //错误，类型不匹配
    int r4 = 42;        //错误，不能用字面值初始化一个非常量引用
    return 0;
}