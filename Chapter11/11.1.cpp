#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;
/**
 * @brief 关联容器
 * 关联容器与顺序容器有着根本的不同：关联容器中的元素是按关键字来保存和访问
 * 的。与之相对，顺序容器中的元素是按照他们在容器中的位置来顺序保存和访问的
 *
 * 关联容器支持搞笑的关键字查找和访问。两个主要的关联容器类型是map和set
 */
/**
 * 关联容器类型
 * 按关键字有序保存元素
 * map          关联数组:保存关键字-值对
 * set          关键字即值，即只保留关键字的容器
 * multimap     关键字可重复出现的map
 * multiset     关键字可重复出现的set
 * 无序集合
 * unordered_map        用哈希数组织的map
 * unordered_set        用哈希数组织的set
 * unordered_multimap   哈希组织的map;关键字可以重复出现
 * unordered_multiset   哈希组织的set;关键字可以重复出现
 */
//使用关联容器

int main()
{
    map<string, size_t> word_count;
    set<string> exclude = {"The", "But", "And", "Or", "An", "A"
                                                            "the",
                           "but", "and", "or", "an", "a"};
    string word;
    while (cin >> word)
    {
        if (exclude.find(word) == exclude.end())
        {
            ++word_count[word];
        }
    }
    for (const auto &w : word_count)
    {
        //打印结果
        cout << w.first << " occurs " << w.second
             << ((w.second > 1) ? " times " : " time ") << endl;
    }
    //此程序读取输入，报告每个单词出现多少次
}