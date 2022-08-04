#include <iostream>
#include <algorithm>
#include <numeric>
#include <functional>
using namespace std::placeholders;
using namespace std;
/**
 * @brief 再探迭代器
 * 除了为每个容器定义的迭代器之外，标准库在头文件iterator中还定义了额外几种迭代器
 * - 插入迭代器:这些迭代器被绑定到一个容器上，可用来向容器插入元素
 * - 流迭代器:这些迭代器被绑定到输入或者输出流上，可用来遍历所关联的IO流
 * - 反向迭代器: 这些迭代器向后而不是向前移动。除了forward_list之外的标准库容器都有反向迭代器
 */
//插入迭代器
/**
 * @brief 插入迭代器操作
 * it=t                 在it指定的当前位置插入t。假定c是it绑定的容器，依赖于插入迭代器的不同种类，此赋值会分别调用
 *                      c.push+back(t)、c.push_front(t)、c.insert(t,p)，其中p为传递给inserter的迭代器位置
 * *it,++it,it++        这些操作虽然存在，但不会对it做任何事情。每个操作都返回it
 */