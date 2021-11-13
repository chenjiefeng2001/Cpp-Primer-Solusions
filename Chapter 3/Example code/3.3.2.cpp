#include <iostream>
#include <vector>
using namespace std;
using std::vector;
int main()
{
    vector<string> svec;
    //空vector的作用：可以在程序运行之后快速的向里边添加元素，如果在程序运行之前你没想好初始化的值，或者没必要，那么就可以创建一个这种类型的vector
    vector<string> articles = {"a", "an", "the"};
    //使用圆括号初始化是数量，使用花括号初始化的是值
    // 向vector中添加元素使用的是成员函数push_back向其中添加，该成员函数把一个值当成vector对象的尾元素push到vector对象的back
    //examplecode
    vector<int> v2;
    for (int i = 0; i != 100; i++)
        v2.push_back(i); //依次把整数值放到v2尾端
    //循环结束之后v2有100个元素，值从0到99
    return 0;

/**
 * vector 对象高效增长
 * C++标准要求vector对象能在运行时高效的快速添加元素。因此既然vector对象能够高效地增长，那么在定义vector对象的时候设定其大小就显得多余了（事实上要是真的设定了大小，性能反而可能会差一些）。当然，这也有例外——所有的元素值都一样的情况下预先设定好是最快地
 * 向vector对象添加元素的假定
 * 必须保证所写的循环（添加元素的）正确无误，特别是在循环有可能改变vector对象容量的时候
 */
}
