#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <utility>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <list>
#include <unordered_map>
#include <unordered_set>
using namespace std;

map<string, int> word_count;
multimap<string, string> authors;
map<string, size_t> word_count;
void word_transform(ifstream &map_file, ifstream &input)
{
    auto trans_map = buildMap(map_file);
    string text;
    while (getline(input, text))
    {
        istringstream stream(input, text);
        string word;
        bool firstword = true; //判断是否需要打印空格
        while (stream >> word)
        {
            if (firstword)
                firstword = false;
            else
                cout << " ";
            // transform返回它的第一个参数或其转换之后的形式
            cout << transform(word, trans_map);
        }
        cout << endl; //完成一行的转换
    }
}
map<string, string> buildMap(ifstream &map_file)
{
    map<string, string> trans_map; //保存转换规则
    string key;                    //要转换的单词
    string value;                  //替换后的单词
    //读取第一个单词存入key中，行中剩余的内容存入value
    while (map_file >> key && getline(map_file, value))
    {
        if (value.size() > 1)
            trans_map[key] = value.substr(1);
        else
            throw runtime_error("no rule for " + key);
        return trans_map;
    }
}
const string &transform(const string &s, const map<string, string> &m)
{
    //实际的转换工作
    auto map_it = m.find(s);
    if (map_it != m.cend())
        return map_it->second;
    else
        return s;
}
/**
 * @brief 无序容器
 * 新标准定义了四个无序关联容器。这些容器不是使用比较运算符来组织元素，而是使用一个哈希函数
 * 和关键字类型的==运算符。在关键字类型的元素没有明显的序关系的情况下，无序容器是非常有用的
 * 在某些应用中，维护元素的序代价非常高昂，此时无序容器也很有用
 */
//如果关键字类型固有就是无序的，或者性能测试发现问题可以用哈希技术解决，就可以使用无序容器
//建立转换映射
/**
 * 函数buildMap读入给定文件，建立起转换映射
 *
 * 无序容器管理操作
 * 桶接口
 * c.bucket_count()             正在使用桶的项目
 * c.max_bucket_count()         容器能够容纳的最多的桶的元素
 * c.bucket_size(n)             第n个桶中有多少个元素
 * c.bucket(k)                  关键字为k的元素在哪个桶中
 * 桶迭代
 * local_iterator               可以用来访问桶中元素的迭代器类型
 * const_local_iterator         桶迭代器的const版本
 * c.begin(),c.end()            桶n的首元素迭代器和尾后迭代器
 * c.cbegin(n),c.cend()         与前两个桶类似，但返回const_local_iterator
 * 哈希策略
 * c.load_factor()              每个桶平均元素数量，返回float值
 * c.max_load_factor            c视图维护的平均桶大小，返回float值。c会在需要时添加新的桶
 *                              以使得load_factor<=max_load_factor
 * c.rehash(n)                  重组存储，使得bucket_count>=n且bucket_count>size/max_load_factor
 * c.reserve(n)                 重组存储，使得c可以保存n个元素且不必rehash
 */
//无序容器对关键字类型的要求
/**
 * 在默认情况下，无序容器使用关键字类型的==运算来比较元素，它们还使用一个has<key_type>类型的对象来生成每个元素的哈希值
 * 标准库为内置类型(包括指针)提供哈希模板。还未一些标准库模型，包括string和智能指针类型定义了哈希
 *
 *
 */
struct Sales_data
{
public:
    Sales_data();
    ~Sales_data();

private:
protected:
    /* data */
};

size_t hasher(const Sales_data &sd)
{
    return hash<string>()(sd.isbn());
}
bool eqOp(const Sales_data &lhs, const Sales_data &rhs)
{
    return lhs.isbn() == rhs.isbn();
}
int main()
{
    //统计出现次数，但单词不会按字典序排列
    unordered_map<string, size_t> word_count;
    string word;
    while (cin >> word)
        ++word_count[word]; //提取并递增word的计数器
    for (const auto &w : word_count)
        //打印结果
        cout << w.first << " occurs" << w.second << ((w.second > 1) ? " times " : " time ") << endl;
    return 0;
}