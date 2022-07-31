/**
 * @brief 顺序容器
 * 顺序容器类型
 * vector       可变大小数组。支持快速随机访问。在尾部之外的位置插入或者删除元素可能很慢
 * deque        双端队列。支持快速速记访问。在头尾位置插入、删除速度很快
 * list         双向链表。只支持双向顺序访问。在list中任何位置进行插入、删除操作速度都很快
 * forward_list 单向链表。只支持单项顺序访问。在链表任何位置进行插入、删除操作速度都很快
 * array        固定大小数组。支持快速随机访问。不能添加或者删除元素
 * string       与vector相似的容器，但专门用于保存字符。随机访问快。在尾部插入、删除速度快
 */
//除了固定大小的array外，其他容器都提供高效、灵活的内存管理
// 容器保存元素的策略对容器操作的效率有着固有的，有时是重大的影响。
/**
 * @brief 选择容器的基本原则
 * - 除非你有很好的理由选择其他的容器，否则应该使用vector
 * - 如果你的程序有很多小的元素，并且空间的额外开销很厉害，那么请不要使用list或者forward_list
 * - 如果程序要求在容器中随机的访问元素，请使用vector或者deque
 * - 如果程序需要在头尾位置插入或删除元素，但不会在中间位置进行插入或删除操作，则可以使用deque
 * - 如果程序只有在读取输入时才需要在容器的中间位置插入元素，随后需要随机访问元素，则
 *      - 首先，确定是否真的需要在容器中间位置添加元素。当处理输入数据时，通常可以很容易地向vector中追加数据，然后再调用标准库的sort函数进行重排，从而避免在中间位置添加元素
 *      - 如果必须在中间位置插入元素，考虑在输入阶段使用list，一旦输入完成，将list中的内容拷贝到一个vector中
 *
 */
#include <iostream>
#include <vector>
#include <list>
#include <deque>
using namespace std;
struct Sales_data
{
    /* data */
};

int main(int argc, char const *argv[])
{
    list<Sales_data>; //保存Sales_data对象地list
    deque<double>;    //保存double地deque
    //顺序容器几乎可以保存任意类型地元素。特别是，我们可以定义一个容器，其元素地类型是另一个容器。这种容器的定义与任何其他类型
    //完全一样:在尖括号中指定元素类型
    vector<vector<string>> lines; // vector的vector
                                  /**
                                   * @brief 容器操作
                                   * 类型别名
                                   * iteratior                  此容器类型的迭代器类型
                                   * const_iterator             可以去读元素，但不能修改元素的迭代器类型
                                   * size_type                  无符号整数类型，足够保存此种容器类型最大可能容器的大小
                                   * difference_type            带符号整数类型，足够保存两个迭代器之间的距离
                                   * value_type                 元素类型
                                   * reference                  元素的左值类型；与value_type&含义相同
                                   * const_reference元素的      元素的const左值类型
                                   * 构造函数
                                   * C c;                       默认构造函数，构造空容器
                                   * C c1(c2);                  构造c2的拷贝c1
                                   * C c(b,e);                  构造c，将迭代器b和e指定的2范围内的元素拷贝到c(array不支持)
                                   * C c{a,b,c,...};            列表初始化c
                                   * 赋值与swap
                                   * c1=c2;                     将c1中的元素替换为c2中的元素
                                   * c1={a,b,c,...};            将c1中的元素替换为列表中的元素(不适用于array)
                                   * a.swap(b);                 交换a与b中的元素
                                   * swap(a,b);                 与a.swap(b)等价
                                   * 大小
                                   * c.size()                   c中的元的数目
                                   * c.max_size()               c可保存的最大元素数目
                                   * c.empty()                  若c中存储了元素，返回false，否则返回true
                                   * 添加、删除元素(不适用于array)
                                   * c.insert(args)             将args中的元素拷贝进c
                                   * c.emplace(inits)           使用inits构造c中的一个元素
                                   * c.erase(args)              删除args指定的元素
                                   * c.clear()                  删除c中的所有元素，返回void
                                   * 关系运算符
                                   * ==，!=                     所有容器都支持相等、不相等运算符
                                   * <,<=,>,>=                  关系运算符（无序关联容器不支持）
                                   * 获取迭代器
                                   * c.begin(),c.end()          返回指向c的首元素和尾元素之后位置的迭代器
                                   * c.cbegin(),c.cend()        返回const_iterator
                                   * 反向容器的额外成员(不支持forward_list)
                                   * reverse_iterator           按逆寻址元素的迭代器
                                   * const_reverse_iterator     不能修改元素的逆序迭代器
                                   * c.rbegin(),c.rend()        返回指向c的尾元素和首元素之前位置的迭代器
                                   * c.crbegin(),c.crend()      返回const_reverse_iterator
                                   */

    return 0;
}
