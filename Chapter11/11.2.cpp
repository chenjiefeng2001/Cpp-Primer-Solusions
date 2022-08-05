#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <utility>
using namespace std;
/**
 * @brief 关联容器概述
 * 关联容器(有序的和无序的)都支持普通容器的操作，但是关联容器不支持顺序容器的位置相关的操作
 * 原因是关联容器中元素是根据关键字存储的，这些操作对关联容器没有意义。而且关联容器也不支持
 * 构造函数或插入操作这些接受一个元素值和一个数量值的操作
 * 除了与顺序容器相同的个操作之外，关联容器还支持一些顺序容器不支持的操作和类型别名
 * 此外，无序容器还提供一些用来调整哈希性能的操作
 * 关联容器得迭代器都是双向的
 */
/**
 * 定义关联容器
 */
map<string, size_t> word_count; //空容器
set<string> exclude = {"The", "But", "And", "Or", "An", "A",
                       "the", "but", "and", "or", "an", "a"};
map<string, string> authors = {{"Joyce", "James"},
                               {"Austen", "Jane"},
                               {"Dickens", "Charles"}};
/**
 * 与以往一样，初始化荣光其必须能转换为容器中元素的类型。
 * {key,value}
 */
//初始化multimap和multiset
pair<string, int> process(vector<string> &v)
{
    //处理v
    if (!v.empty())
        return {v.back(), v.back().size()}; //列表初始化
    else
        return pair<string, int>(); //隐含构造返回值
}
int main()
{
    vector<int> ivec; //空vector
    for (vector<int>::size_type i = 0; i != 10; ++i)
    {
        ivec.push_back(i);
        ivec.push_back(i); //每个数重复保存一次
    }
    // iset包含来自ivec的不重复的元素；miset包含所有20个元素
    set<int> iset(ivec.cbegin(), ivec.cend());
    multiset<int> miset(ivec.cbegin(), ivec.cend());
    cout << ivec.size() << endl;
    cout << iset.size() << endl;
    cout << miset.size() << endl;
    //关键字类型的要求
    /**
     * 关联容器对其关键字类型有一些限制。对于无序容器中关键字的要求，在后面会提到，对于有序容器，map,multimap,se,multiset
     * 关键字必须定义元素比较的方法。默认情况下，标准库使用关键字类型的<来比较两个关键字。
     * 在集合类型中。关键字类型就是元素类型；在映射类型中，关键字类型就是元素的第一部分的类型
     */
    /**
     * 有序容器的关键字类型
     * 可以向一个算法提供我们自己定义的比较操作，与之类似，也可以提供自己定义的操作来代替关键字上的<运算符。
     * 所提供的操作必须在关键字类型上定义一个严格弱序。
     * - 两个关键字不能同时"小于等于"对方
     * - 如果k1"小于等于"k2,k2"小于等于"k3,那么k1"小于等于"k3
     * - 如果存在两个关键字，任何一个都不"等于小于"另一个，那么我们称这两个关键字是"等价"的
     */
    //使用关键字类型的比较函数

    /**
     * @brief pair类型
     * 一个pair保存两个数据成员。类似容器，pair是一个用来生成特定类型的模板，当创建一个pair时
     * 我们必须提供两个类型名，pair的数据成员将具有对应的类型。两个类型不要求一样
     */
    pair<string, string> anon;        //保存两个string
    pair<string, size_t> words_count; //保存一个string和size_t
    pair<string, vector<int>> line;   //保存string和vector<int>
    /**
     * @brief pair上的操作
     * pair<T1,T2> p;                  p是一个pair，两个类型分别为T1和T2的成员都进行了值初始化
     * pair<T1,T2> p(v1,v2)            p是一个成员类型为T1和T2的pair:first和
     * pair<T1,T2> p={v1,v2};          等价于p(v1,v2)
     * make_pair(v1,v2)                返回一个用v1和v2初始化的pair。pair的类型从v1和v2的类型推断出来
     * p.first                         返回p的名为first的(公有)数据成员
     * p1 relop p2                     关系运算符(<,>,<=,>=)按字典序定义
     * p1 == p2                        当first和second成员分别相等时，两个pair相等。相等性
     * p1!=p2                          判断利用元素的==运算符实现
     */
    vector<int> word_count;
    return 0;
}