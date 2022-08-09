#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
//使用头文件memory
#include <memory>
#include <string>
using namespace std;
/**
 * @brief 动态内存
 * 除了自动和static对象外，C++还支持动态分配对象。动态分配的对象的生存期与它们在哪里创建
 * 是无关的，只有当显式地被释放时，这些对象才会被销毁
 */
/**
 * 除了静态内存和栈内存，每个程序还拥有一个内存池。这部分内存被称作自由空间或堆。程序用堆来存储动态分配的对象
 */

/**
 * @brief 智能指针
 * 为了更容易地使用动态内存，新标准提供了两种智能指针类型来管理动态对象。
 * 智能指针的行为类似常规指针，区别在于它负责自动释放所指向的对象。新标准库提供的这两种
 * 智能指针的区别在于管理底层指针的方式：
 * - shared_ptr允许多个指针指向同一个对象
 * - unique_ptr则"独占"所指向的对象
 * 除了这两种之外，还定义了一个weak_ptr对象，它是一种弱引用，指向shared_ptr所管理的对象
 */
shared_ptr<string> p1;    // shared_ptr，可以指向string
shared_ptr<list<int>> p2; // shared_ptr，可以指向int的list
//在默认初始化中每个智能指针中都会保存有一个空指针
//智能指针与普通指针使用方式类似。解引用一个智能指针返回它所指向的对象。如果在一个条件判断中使用
//智能指针，则可以检测是否为空指针
class StrBlob
{
public:
    typedef std::vector<std::string>::size_type size_type;
    StrBlob(/* args */);
    StrBlob(std::initializer_list<std::string> il);
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    void push_back(const std::string &t) { data->push_back(t); }
    void pop_back();
    std::string &front();
    std::string &back();
    ~StrBlob();

private:
    std::shared_ptr<std::vector<std::string>> data;
    //如果data[i]不合法，则抛出一个异常
    void check(size_type i, const std::string &msg) const;
};

StrBlob::StrBlob(/* args */) : data(make_shared<vector<string>>())
{
}
StrBlob::StrBlob(initializer_list<string>(il)) : data(make_shared<vector<string>>(il))
{
}
StrBlob::~StrBlob()
{
}

void StrBlob::check(size_type i, const string &msg) const
{
    if (i >= data->size())
        throw out_of_range(msg);
}
string &StrBlob::front()
{
    //如果vector为空，check会抛出一个异常·1
    check(0, "front on empty StrBlob");
    return data->front();
}
string &StrBlob::back()
{
    check(0, "back on the empty StrBlob");
    return data->back();
}
void StrBlob::pop_back()
{
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}
// data(make_shared<vector<string>>(il));
// {
//     /* data */
// };
// vector<string> v1;
// {
//     vector<string> v2 = {"a", "an", "the"};
// }
int main()
{
    if (p1 && p1->empty())
        *p1 = "Hi"; //如果p1指向一个空string，解引用p1,将一个新值赋予string
    /**
     * shared_ptr和unique_ptr都支持的操作
     * shared_ptr<T> sp;        智能空指针，可以指向类型为T的对象
     * unique_ptr<T> up;
     * p                        将p用作一个条件判断，若p指向一个对象，则为true
     * *p                       解引用p，获得它指向的对象
     * p-> mem                  等价于(*p).mem
     * p.get()                  返回p中保存的指针。（要小心使用，因为如果智能指针已经释放了对象，则返回的指针所指向的对象是没有的）
     * swap(p,q)                交换p和q中的指针
     * p.swap()
     *
     * shared_ptr独有的操作
     * make_shared<T>(args)     返回一个shared_ptr,指向一个动态分配的对象。使用args初始化对象
     * shared_ptr<T>p(q)        p是一个shared_ptr q的拷贝；此操作会递增q中的计数器。q中的指针必须能转换为T*
     * p=q                      p和q都是shared_ptr，所保存的指针必须能够互相转换。此操作会递减p的引用计数，递增q的引用计数；若p的引用计数变为0，则会将其管理的原内存释放
     * p.unique()               若p.use_count()为1，返回true，否则返回false
     * p.use_count()            返回与p共享对象的智能指针的数量；(主要用于调试，不建议用在release上，因为实在是太慢了)
     */
    //指向一个值为42的int的shared_ptr
    shared_ptr<int> p3 = make_shared<int>(42);
    // p4指向一个值为"9999999"的string
    shared_ptr<string> p4 = make_shared<string>(10, '9');
    // p5指向一个值初始化的int
    shared_ptr<int> p5 = make_shared<int>();
    // p6指向一个动态分配的空vector<string>
    auto p6 = make_shared<vector<string>>();
    // shared_ptr 的拷贝和赋值
    /**
     * 当进行拷贝或者赋值操作时，每个shared_ptr都会记录有多少个其他shared_ptr
     * 指向相同的对象
     */
    auto p = make_shared<int>(42);
    auto q(p); // p和q都指向相同的对象，此对象有两个引用者
    //递增引用计数器的方法:
    /**
     * - 用一个shared_ptr去初始化另一个shared_ptr
     * - 将它作为参数传递给一个函数
     * 作为参数的返回值
     */
    //当一个shared_ptr的引用计数器变为0，则自动释放指向的对象
    auto r = make_shared<int>(42); // r指向的int只有一个引用者
    r = q;                         //给r赋值，令它指向另一个地址
                                   //递增q指向的对象的引用计数
                                   //递减r原来指向的对象的引用计数
                                   // r原来指向的对象已经没有引用者，所以会自动释放
                                   //到底是一个计数器还是其他数据结构来记录有多少指针共享对象，完全由标准库的具体实现来决定，这并不是重点，关键是
                                   //是智能指针类能记录有多少个shared_ptr指向相同的对象，并能够在恰当的时候自动释放对象
    // shared_ptr自动销毁所管理的对象
    // factory返回一个shared_ptr，指向一个动态分配的对象
    // shared_ptr<Foo> factory(T arg)
    // {
    //     //恰当地处理arg
    //     // shared_ptr 负责释放内存
    //     return make_shared<Foo>(arg)
    // }
    /**
     * @brief shared_ptr自动摧毁所管理的对象
     * 当指向一个对象的最后一个shared_ptr被摧毁时，shared_ptr类会自动销毁此对象。(这是通过析构函数来完成的)
     * 析构函数通常用来释放对象所分配的资源
     * shared_ptr的析构函数会递减它所指向的对象的引用计数。当变为0时就会释放
     *
     * 当然，他也会自动释放相关联的内存，当该对象不再使用时，shared_ptr会自动释放所占的对象
     * 由于在最后一个shared_ptr销毁内存之前都不会释放，所以应该保证shared_ptr在无用之后不再保留就非常重要了。
     * 如果你忘记销毁程序不再需要的shared_ptr，程序仍会正确执行，但是内存会被浪费掉
     *
     * shared_ptr在无用之后仍然保留的一种情况:
     * 你将shared_ptr存放在一个容器中，随后重排了容器，从而不再需要某些元素。在这种情况下，你应该确保用erase删除那些不再需要的shared_ptr元素
     */

    /**
     * @brief 使用了动态生存期的资源的类
     * 使用原因：
     * - 程序不知道自己需要使用多少对象
     * - 程序不知道所需对象的准确类型
     * - 程序需要在多个对象之间共享数据
     */

    return 0;
}