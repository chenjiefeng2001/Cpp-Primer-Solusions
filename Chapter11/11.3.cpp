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
// void woed_transform(ifstream &map_file, ifstream &input)
// {
//     auto trans_map = buildMap(map_file);
//     string text;
//     while (getline(input, text))
//     {
//         istringstream stream(text);

//     }
// }
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
    // word_count.insert({"word", 1});
    // word_count.insert(make_pair(word, 1));
    // word_count.insert(pair<string, size_t>(word, 1));
    // word_count.insert(map<string, size_t>::value_type(word, 1));
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
    multimap<string, string> authors;
    //插入第一个元素，关键字为Barth,John
    authors.insert({"Barth,John", "Sot-Weed Factor"});
    //添加第二个元素，关键字也是第一个元素
    authors.insert({"Barth John", "Lost in the Funhouse"});
    /**
     * @brief 删除元素
     * 关联容器定义了三个版本的erase，与顺序容器一样，我们可以通过传递给erase一个迭代器或一个迭代器对来删除一个元素或者一个
     *
     */
    string removal_word = "The";
    if (word_count.erase(removal_word))
        cout << "ok:" << removal_word << "removed\n";
    else
        cout << "oops:" << removal_word << " not found !\n";
    //对允许重复关键字的容器，删除元素可能大于1
    auto cnt = authors.erase("Barth,John");
    /**
     * @brief 从关联容器删除元素
     * c.erase(k)           从c中删除每个关键字为k的元素。返回一个size_type值
     *                      指出删除的元素的数量
     * c.erase(p)           从c中删除迭代器p指定的元素。p必须指向c中一个真实元素,
     *                      不能等于c.end()。返回一个指向p之后元素的迭代器，若p指
     *                      向p中的尾元素，则返回c.end()
     *c.erase(b,e)          删除迭代器对b和e所表示范围中的元素，返回e
     */
    // map的下标操作
    /**
     * map和unordered_map容器提供了下标运算符和一个对应的at函数，set类型不支持下标，因为set中
     * 没有与关键字相关联的"值"。元素本身就是关键字
     * 我们不能对一个multimap或一个unordered_multimap进行下标操作
     *
     *
     */
    map<string, size_t> word_count; // empty map
    //插入一个关键字为Anna的元素，关联值进行初始化；然后将1赋予它
    word_count["Anna"] = 1;
    /**
     * 以上会执行如下的操作
     * - 在word_count中搜索关键字为Anna的元素，未找到
     * - 将一个新的关键字-值对插入到word_count中。关键字是一个const string，保存Anna
     *   值进行初始化
     * - 提取出新插入的元素，并将值1赋予它
     *
     * map和unordered_map的下标操作
     * c[k]             返回关键字为k的元素:如果k不在c中，添加一个关键字为k的元素，对其进行值初始化
     * c.at(k)          访问关键字为k的元素，带参数检查;若k不在c中，抛出一个out_of_range异常
     */
    /**
     * 使用下标操作的返回值
     * map的下标运算与我们用过的其他下标运算符的另一个不同之处是其返回类型。通常
     * 情况下，解引用一个迭代器所返回的类型与下标运算符返回的类型是一样的。但是
     * map不一样，对其进行下标操作的时候，会得到一个map_value对象;但当解引用一
     * 个map迭代器时，会得到一个value_type对象
     */
    cout << word_count["Anna"];
    ++word_count["Anna"];
    cout << word_count["Anna"];
    /**
     * @brief 访问元素操作
     * 在一个关联容器中查找元素的操作
     * lower_bound和upper_bound不适用于无序容器
     * 下表和at操作只适用于非const的map和unordered_map
     * c.find(k)        返回一个迭代器，指向第一个关键字为k的元素，若k不在则返回尾后迭代器
     * c.count(k)       返回关键字等于k的元素数量。对于不允许重复关键字的容器，返回值永远是0或者1
     * c.lower_bound(k) 返回一个迭代器，指向第一个关键字不小于k的元素
     * c.upper_bound(k) 返回一个迭代器，指向第一个关键字大于k的元素
     * c.equal_range(k) 返回一个迭代器pair，表示关键字等于l的元素范围。若k不存在，则pair两个成员军等于c.end()
     */
    //对map使用find代替下标操作
    if (word_count.find("foobar") == word_count.end())
    {
        cout << "foobar is not in the map" << endl;
    }
    //在multimap或multiset中查找元素
    /**
     * 在一个不允许重复关键字的关联容器中查找一个元素是十分简单的事情——元素要么在容器中，要么不在
     * 但是对于允许重复关键字的容器来说，过程很复杂:在容器中可能有很多元素具有给定的关键字
     */
    string search_item("Alain de Botton");     //要查找的作者
    auto entries = authors.count(search_item); //元素的数量
    auto iter = authors.find(search_item);     //此作者的第一本书
    //用一个循环查找此作者的所有著作
    while (entries)
    {
        cout << iter->second << endl; //打印每个题目
        ++iter;                       //前进到下一本书
        --entries;                    //记录已经打印了多少本书
    }
    //当我们遍历一个multimap或multiset时，保证可以得到序列中所有具有给定关键字的元素
    /**
     * @brief 一种不同的，面向迭代器的解决方法
     * lower_bound返回的迭代器可能指向一个具有给定关键字的元素，但也可能不指向。如果关键字不在容器中，则lower_bound
     * 会返回关键字的第一个安全插入点——不影响容器中，则lower_bound会返回关键字的第一个安全插入点——不影响容器中元素顺
     * 序的插入位置
     */
    // authors 和search_item的定义，与前面的程序一样
    // beg和end表示对应此作作者的元素的范围
    for (auto beg = authors.lower_bound(search_item), end = authors.upper_bound(search_item); beg != end; ++beg)
        cout << beg->second << endl;
    //此程序使用count和find的版本完成相同的工作，但是独异于上面来说更直接。
    //如果没有元素给定关键字匹配，则lower_bound 和upper_bound会返回相等的迭代器——都指向给定关键字的插入点，能保持容器中元素顺序的插入位置
    //如果lower_bound 和upper_bound 返回相同的迭代器，则给定关键字不在容器中
    /**
     * @brief equal_range函数
     * 解决此问题的最后一种方法是三种方法中最直接的:不必再调用upper_bound 和lower_bound ，直接调用equal_range 即可
     * 此函数接受一个关键字，返回一个迭代器pair。若关键字存在，则第一个迭代器指向第一个与关键字匹配的元素，第二个迭
     * 代器指向最后一个匹配元素之后的位置。若未找到匹配元素，则两个迭代器都指向关键字可以插入的位置
     */
    // authors和search_item的定义，与前面的程序一样
    // pos保存迭代器对，表示关键字匹配的元素范围
    for (auto pos = authors.equal_range(search_item); pos.first != pos.second; ++pos.first)
    {
        cout << pos.first->second << endl;
    }
    //此程序本质上与前一个使用upper_bound 和lower_bound 的程序是一样的。不同之处就是，没有使用局部变量beg和end来保存元素范围，而是使用了
    // euqal_range 返回的pair。此pair的first成员保存的迭代器与lower_bound 返回的迭代器是一样的，而second中保存的与upper_bound 一致
    /**
     * @brief 一个单词转换的map
     *
     *
     */

    return 0;
}
