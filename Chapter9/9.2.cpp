#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <forward_list>
using namespace std;
/**
 * @brief 迭代器测试
 * 迭代器和容器一样有着公共的接口——一个迭代器提供某个操作，那么所有提供相同操作的迭代器对这个操作的实现方式都是相同的
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char const *argv[])
{
    /** 迭代器范围，由一对迭代器表示，两个迭代器分别指向同一个容器中的于是怒或者是尾元素之后的位置。这两个迭代器通常被成为
     * begin和end
     * 或者是first和last，这两个标记了容器中元素的一个范围
     */
    //注：第二个迭代器并不会指向的是尾部元素，而是指向尾部元素之后的位置，迭代器范围中的元素包含first所表示元素以及从first到last之间的所有元素
    //这种元素的范围被称为左闭合区间
    /**
     * @brief 对构成范围的迭代器的要求
     * 如果满足如下条件，两个迭代器begin和end构成一个迭代器范：
     * - 它们指向同一个容器中的元素，或者是容器最后一个元素之后的位置
     * - 我们可以通过反复递增begin来达到end。
     * 使用左闭合范围蕴含的编程假定
     * 标准库使用左闭合范围是因为这种范围有三种方便的性质。假定begin和end构成一个合法的迭代器范围，则
     * - 如果begin和end相等，则范围为空
     * - 如果begin和end不相等，则至少包含一个元素，且begin指向该范围中的第一个元素
     * - 我们可以对begin递增若干次，使得begin==end
     */
    // vector<int> v;
    // while (v.begin() != v.end())
    // {
    //     *begin = val;
    //     ++begin;
    // }
    // iter是通过list<string>定义的一个迭代器类型
    /**
     * @brief 容器定义和初始化
     * 每个容器类型都定义了一个默认构造函数。除了array之外，其他容器的默认构造函数都会创建一个指定类型的空容器，且都可以接受指定容器大小和元素的初始值参数
     * 容器定义和初始化
     * C c;             默认构造函数。如果C是一个array，则c中元素按默认方式初始化；否则c为空
     * C c1(c2);        c1初始化为c2的拷贝。c1和c2必须是相同的类型(若对于array，则还必须拥有相同的大小)
     * C c{a,b,c...}    c初始化为初始化列表中元素的拷贝。列表中元素的类型必须与C的元素类型相容。对于array类型，列表中的元素数目必须等于或者小于array的大小，任何遗漏的元素都可能直接进行值初始化
     * C c(b,e)         c初始化为迭代器b和e指定范围中的元素的拷贝。范围中元素的类型必须与C的元素类型相容
     * 
     * 只有顺序容器的构造函数才能接受大小参数
     * C seq(n)     seq包含n个元素，这些元素进行了值初始化；此构造函数是explicit的
     * C seq(n,t)   seq包含n个初始化为值t的元素
     */
    //将一个容器初始化为另一个容器的拷贝
    list<string> authors={"Millton","Shakespeare","Austen"};
    vector<const char*>articles={"a","an","the"};
    list<string> list2(authors);//类型匹配，所以可以正确初始化
    // deque<string> authlist(authors);    //类型不匹配
    // vector<string> words(articles);     //类型不匹配
    forward_list<string> words(articles.begin(),articles.end());    //可以将const char*元素转换为string
    //当将一个容器初始化为另一个容器的拷贝时，两个容器的容器类型和元素类型都必须相同
    // deque<string> authlist(authors.begin(),it);//拷贝元素，直到（但不包括）it指向的元素

    //列表初始化
    //在新标准中，我们可以对一个容器进行列表初始化，当这样做时，我们就显式地指定了容器中每个元素的值。对于除array之外的容器类型，初始化列表还隐含
    //地指定了容器的大小:  容器将包含与初始值一样多的元素
    list<string>::iterator iter;
    //count是通过vector<int>定义的一个difference_type类型
    vector<int>::difference_type count;
    
    //与顺序容器大小相关的构造函数
    /**
     * @brief 除了与关联容器相同的构造函数外，顺序容器还提供另一个构造函数，它接受一个容器大小和一个（可选的）元素初始值
     * 如果我们不提供元素初始值，则标准库会创建一个初始化容器
     */
    vector<int> ivec(10,-1);        //10个int元素，每个都初始化为-1
    list<string> svec(10,"hi!");    //10个strings;每个都初始化为"hi"
    forward_list<int> ivec(10);     //10个元素，每个都初始化为0
    deque<string> svec(10);         //10个元素，每个都是空string
    //只有顺序容器才的构造函数才能接受大小参数，关联容器并不支持
    
    return 0;   
}
