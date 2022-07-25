#include <iostream>
#include <cassert>
//使用assert
using namespace std;
/**
 * @brief 
 * 四个对于程序调试很常用的名字：
 * __FILE__     存放文件名的祖父穿字面值
 * __LINE__     存放当前行号的整型字面值
 * __TIME__     存放文件编译时间的字符串字面值
 * __DATE__     存放摁键编译日期的字符串字面值
 * @param ia 
 * @param size 
 */
void print(const int ia[], size_t size)
{
#ifndef NDEBUG
    cerr << __func__ << "array size is " << size << endl;
#endif
}
constexpr int new_sz() { return 42; }
//函数的返回类型及所有的形参类型都得是字面值类型，并且整个函数有且只有一条返回语句
constexpr size_t scale(size_t cnt) { return new_sz() * cnt; }
int main(int argc, char const *argv[])
{
    constexpr int foo = new_sz();
    return 0;
}
//和其他函数不一样，内联函数和constexpr都是可以在程序中多次定义的。但是对于某个给定的内联函数或者constexpr函数来说，它的多个定义必须完全一致。
/**
 * @brief 调试帮助
 * 预处理功能：assert&NDEBUG
 * 1. assert预处理宏是一个预处理变量，行为类似内联函数，使用一个表达式作为条件：
 *
 * assert(expr);
 *
 *预处理的名字由预处理器而非编译器管理
 *宏名在程序内必须唯一。
 * assert宏用于检查"不能发生的条件"；
 * 而assert依赖于一个名为NDEBUG的宏，如果定义了NDEBUG，那么assert什么也不做。
 */