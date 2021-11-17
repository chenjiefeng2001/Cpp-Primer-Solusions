#include <iostream>
#include <string>
using namespace std;
void fucn(const int i){} //fucn 能够通过读取i，但是不能向i赋值，即不能回写
void func2(int i){}  //重新定义了一个新的int值
int main()
{
    const int ci = 42; //不能改变ci,const是顶层的
    int i = ci;        //正确，拷贝ci时，忽略了它的顶层const
    int *const p = &i; //const 是顶层的，不能给p赋值
    *p = 0;            //正确。通过p改变对象的内容是允许的，现在i变成了0
}
