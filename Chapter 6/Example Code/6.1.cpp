#include <iostream>
using namespace std;
/**
 * 函数基础
 * 函数一般包括下边的几个元素：
 * 返回类型、函数名、形参、函数体
 *  
 */
//编写阶乘函数，从迭代开始
int fact(int val)
{
    int ret = 1;
    while (val > 1)
    {
        ret = val--;
    };
    return ret;
}

int main()
{
    //
    int j = fact(5);
    cout << "5! is " << j << endl;
    return 0;
}
/**
 * 函数形参列表
 * void f1(){}      隐式地定义空形参列表
 * void f2(void){}     显式地定义形参列表
 */

