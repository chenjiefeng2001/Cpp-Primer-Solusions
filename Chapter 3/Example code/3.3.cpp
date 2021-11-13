#include <iostream>
#include <vector>
using namespace std;
using std::vector;
vector<int> ivec; //ivec保存int类型的对象
//! vector是模板而非类型，由vector生成的类型必须包含vector中元素的类型，例如vector<int>
/**
 * 定义和初始化·1vector对象
 * vector<T> v1     v1是一个空的vector，它潜在的元素是T类型的，执行默认初始化
 * vector<T> v2(v1) v2中包含有v1的所有元素的副本
 * vector<T> v2=v1  等价于v2(v1)，v2中含有v2的所有元素的副本
 * vector <T> v3(n,val) v3包含了n个重复的元素，每个元素的值都是val
 * vector <T> v4(n)     v4包含了n个重复地执行了值初始化地对象
 * vector <T> v5(a,b,c,...) v5包含了初始值个数的元素，每个元素被赋予相应的初始值
 * vector <T> v5=(a,b,c,...)    等价于v5(a,b,c,...)
 */

vector<string> svec;
//空vector的作用：可以在程序运行之后快速的向里边添加元素，如果在程序运行之前你没想好初始化的值，或者没必要，那么就可以创建一个这种类型的vector
vector<string> articles = {"a", "an", "the"};
//使用圆括号初始化是数量，使用花括号初始化的是值
// 向vector中添加元素使用的是成员函数push_back向其中添加，该成员函数把一个值当成vector对象的尾元素push到vector对象的back
//examplecode
vector<int> v2;
for (int i = 0;i!=100;i++)
    v2.push_back(i);    //依次把整数值放到v2尾端
    //循环结束之后v2有100个元素，值从0到99
    