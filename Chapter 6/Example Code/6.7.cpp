#include <iostream>
using namespace std;
bool lengthCompare(const string &, const string &);
bool (*pf)(const string &, const string &);
int main(int argc, char const *argv[])
{
    pf = lengthCompare;//pf指向名为lengthCompare的函数
    //pf=&lengthCompare     等价于赋值语句，因为取地址符是可选的
    //同时，还可以使用指向函数的指针来调用该函数，并且无需提前解引用指针
    return 0;
    //TODO: 完成函数指针部分的示例代码

}
