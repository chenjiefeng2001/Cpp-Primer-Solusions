#include <iostream>
#include <utility>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <list>
using namespace std;
/**
 * @brief 关联容器额外的类型别名
 * key_type             此容器类型的关键字类型
 * mapped_type          每个关键字关联的类型:只适用于map
 * value_type           对于set，与key_type相同
 *                      对于map，为pair<const key_type,mapped_type>
 */
set<string>::value_type v1;       // v1是一个string
set<string>::key_type v2;         // v2是一个string
map<string, int>::value_type v3;  // v2是一个pair<const string,int>
map<string, int>::key_type v4;    // v4是一个string
map<string, int>::mapped_type v5; // v5是一个int

/**
 * 与顺序容器一样，我们使用作用域运算符来提取一个类型的成员
 * 只有map类型(unordered_map,unordered_multimap,multimap和map)才定义了mapped_type
 */
int main()
{
    map<string, int> word_count;
    //获得指向word_count中的一个元素迭代器
    auto map_it = word_count.begin();
    //*map_it是指向一个pair<const string,size_t>对象的引用
    cout << map_it->first;         //打印此元素的关键字
    cout << " " << map_it->second; //打印此元素的值
    // map_it->first="new key";//错误，关键字是const的
    ++map_it->second; //正确，我们可以通过迭代器改变元素
    // set的迭代器是const的
    set<int> iset = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    set<int>::iterator set_it = iset.begin();
    if (set_it != iset.end())
    {
        // *set_it =42; //错误，set中的关键字是只读的
        cout << *set_it << endl; //正确:可以读关键字
    }
    /**
     * @brief 遍历关联容器
     * map和set类型都支持begin和end类型的操作。与往常一样，我们可以用这些函数获取迭代器，然后用迭代器来遍历容器
     */
    /**
     * 关联容器和算法
     * 通常不对关联容器使用泛型算法，因为关键字是const的，因此不能将关联容器传递给修改或重拍容器元素的算法，
     * 而set类型中的元素是const的，map中的元素是pair，其第一个成员是const的
     *
     * 因此我们只能使用只读算法来对关联容器进行处理，但是，这类算法都要搜索序列，
     * 但是由于关联容器中的元素不能通过它们的u按剪子进行快速查找，因此对其使用泛型算法是十分不明智的
     * 实际编程中，如果我们真要对一个关联容器使用算法，要么是将它当作一个源序列，要么当作一个目的位置。
     */
    //
    vector<int> ivec = {2, 4, 6, 8, 2, 4, 6, 8};
    set<int> set2;                           //空集合
    set2.insert(ivec.cbegin(), ivec.cend()); // set2现在有四个元素
    set2.insert({1, 3, 5, 7, 1, 3, 5, 7});   // set2现在有八个元素
    /**
     * insert有两个版本，分别接受一对迭代器，或是一个初始化列表，这两个版本的行为类似对应的构造函数
     * 对于一个给定的关键字，只有一个带此关键字的元素才被插入到容器中
     */
    //四种方法来插入一个pair
    word_count.insert({word, 1});
    word_count.insert(make_pair(word, 1));
    word_count.insert(pair<string, size_t>(word, 1));
    word_count.insert(map<string, size_t>::value_type(word, 1));
    /**
     * @brief 关联容器insert操作
     * c.insert(v)          v是value_type类型的对象;args用来构造一个元素
     * c.emplace(args)      对于map和set，只有当元素的关键字不在c中时才插入(或构造)元素。函数返回一个pair，包含一个迭代器，指向具有指定关键字的
     *                      元素，以及一个指示插入是否成功的bool值
     * c.insert(b,e)        b和e是迭代器，表示一个c::value_type类型值得范围;
     * c.insert(il)         il是这种值的花括号列表。函数返回void
     * c.insert(p,v)        类似insert(v)（或emplace(args)),但将迭代器p作为一个提示，指出哪里开始搜索新元素应该存储的位置。
     *                      返回一个迭代器，指向具有给定关键字的元素
     */
    //展开递增语句
    
    return 0;
}
