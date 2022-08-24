#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
/**
 * 当运算符被用于类类型的对象时，C++允许我们为其指定新的含义；同时，我们也能定义类类型之间
 * 得到转换规则。和内置类型的转换一样，类类型转换隐式地将一种类型地对象转换成另一种我们所需类型的对象。
 */
//基本概念
/**
 * 重载的运算符是具有特殊名字的函数:它们地名字由关键字operator和其后要定义的运算符号
 * 共同组成。和其他函数一样，重载运算符也包含返回类型、参数列表以及函数体。
 *
 * 如果一个运算符函数是成员函数，则它第一个左侧运算对象绑定到隐式地this指针上，因此，成员运算符
 * 函数的(显式)参数数量比运算符的运算对象总数少一个
 *
 * 当一个重载的运算符是成员函数时，this绑定到左侧运算对象。成员运算符函数的(显式)参数数量比运算对象的数量少一个
 */
using namespace std;
/**
 * @brief 可以被重载的运算符
 * + - * / % ^ & | ~ ! , = < > <= >= ++ -- << >> == !=
 * && || += -= /= %= ^= &= }= *= <<= >>= [] () -> ->* new
 * new[] delete delete[]
 *不可被重载的运算符
 :: .* . ? :
 * @return int
 */
class algo
{
public:
    algo() = default;
    algo(const string &s);
    algo(string &&s);
    operator+();
};
int main()
{
    int data1, data2;
    data1 + data2;                 //普通的表达式
    algo::operator+(data1, data2); // operator+时非成员函数，传入data1作为第一个实参，data2作为第二个实参

    return 0;
}