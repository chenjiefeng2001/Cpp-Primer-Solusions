#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
//使用头文件memory
#include <memory>
#include <string>

using namespace std;
class StrBlob
{
public:
    std::shared_ptr<std::vector<std::string>> data;
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

struct Foo
{
public:
    Foo() = default;
};

class StrBlobPtr
{
public:
    StrBlobPtr();
    StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
    std::string &deref() const;
    StrBlobPtr &incr(); //前缀递增
private:
    std::shared_ptr<std::vector<std::string>> check(std::size_t, const std::string &) const;
    std::weak_ptr<std::vector<std::string>> wptr;
    std::size_t curr;
};
/**
 * @brief unique_ptr
 * 一个unique_ptr“拥有”它所指向的对象，与shared_ptr不同，某个时刻只能有一个unique_ptr指向一个给定的对象
 * 当unique_ptr被销毁时，它所指向的对象也会被销毁(也就是说，这个是一个映射指针，即一对一绑定的)
 * 与shared_ptr不同，没有类似make_shared的标准库函数返回一个unique_ptr。当我们定义了一个unique_ptr时，需要将其绑定到一个new返回的
 * 的指针上
 *
 */

unique_ptr<int>
    p1;                              //可以指向一个int的unique_ptr
unique_ptr<int> ptest2(new int(42)); // p2指向一个值为42
unique_ptr<string> ptest(new string("Stegosaurus"));
/**
 * @brief 删除器
 * 默认情况下，shared_ptr假定它们指向的是动态内存。因此当一个shared_ptr被销毁时，它默认地对它管理的指针进行delete操作。为了用shared_ptr来管理一个connection 我们必须写一个函数来管理
 * 而这个函数就叫做删除器
 */
//由于一个unique_ptr拥有它所指向的对象，因此unique_ptr不支持普通的拷贝或者赋值操作
/**
 * @brief unique_ptr支持的操作
 * unique_ptr<T> u1;        空unique_ptr，可以指向类型为T的对象，会使用delete来释放它的指针;
 * unique_ptr<T,D>  u2;     u2会使用一个类型为D的可调用对象来释放它的指针
 * unique_ptr<T,D> u(d);    空unique_ptr，指向类型为T的对象，用类型为D的对象来代替delete
 * u=nullptr;               释放u指向的对象，将u置为空
 * u.release();             u放弃对指针的控制权，返回指针，并将u置为空
 * u.reset();               释放u所指向的对象
 * u.reset(q);              如果提供了内置指针q，令u指向这个对象;否则置为空
 * u.reset(nullptr);
 */
//传递unique_ptr和返回unique_ptr
//不能拷贝unique_ptr的规则有个例外:我们可以拷贝或者赋值给一个将要被销毁的unique_ptr
unique_ptr<int> clone(int p)
{
    //正确:从int*创建一个unique_ptr<int>
    return unique_ptr<int>(new int(p));
}
int main()
{
    unique_ptr<string> p2(ptest.release()); //将控制权转移给p2
    unique_ptr<string> p3(new string("Trex"));
    // reset释放了
    p2.reset(p3.release());
    // release成员返回unique_ptr当前保存的指针并将其置为空。因此，p2被初始化为p1原来保存的指针，而p1被置为空
    /**
     * @brief weak_ptr
     * weak_ptr是一种不控制所指向的对象的生存周期地智能指针，它指向由一个shared_ptr管理的对象。
     * 将一个weak_ptr绑定到一个shared_ptr不会改变shared_ptr的引用计数。一旦最后一个指向对象的shared_ptr被销毁，对象就会被释放，而
     * 即使有weak_ptr指向对象，对象也还是会被释放
     */
    /**
     * @brief weak_ptr操作
     * weak_ptr<T>  w       空weak_ptr可以指向类型为T的对象
     * weak_ptr<T> w(sp)    与shared_ptr sp指向相同对象的weak_ptr。T必须能转换为sp指向的类型
     * w=p                  p可以是一个shared_ptr或者是一个shared_ptr。赋值后w与p共享一个对象
     * w.reset()            将w置为空
     * w.use_count()        与w共享对象的shared_ptr的数量
     * w.expired()          若w.use_count()为0,返回true，否则返回false
     * w.lock()             如果expired为true，返回一个空的shared_ptr，否则返回一个指向w的对象的shared_ptr
     */
    auto p = make_shared<int>(42);
    weak_ptr<int> wp(p); // wp弱共享p;p的引用计数不变
    //由于不能确保weak_ptr所指向的对象是否还存在，因此需要使用到lock()来检查
    if (shared_ptr<int> np = wp.lock()) //如果
    {
        //在if中，np与p共享对象
    }
    //检查指针类
}