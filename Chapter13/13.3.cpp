#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include <string>

class HasPtr
{
    friend void swap(HasPtr &, HasPtr &);

public:
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0), use(new std::size_t(1)) {} //对ps指向的string，每个HasPtr对象都有自己的拷贝
    HasPtr(const HasPtr &p) : ps(new std::string(*p.ps)), i(p.i), use(p.use) { ++*use; }
    HasPtr &operator=(const HasPtr );
    ~HasPtr() { delete ps; }

private:
    std::string *ps;
    int i;
    std::size_t *use;
};
inline void swap(HasPtr &lhs, HasPtr &rhs)
{
    //编写自己的swap函数
    using std::swap; //加上了限定，这个说明调用的是类内的swap，而不是std::swap
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, rhs.i);
}
HasPtr &HasPtr::operator=(HasPtr rhs)
{
    swap(*this, rhs);
    return *this;
    //使用拷贝和交换的赋值运算符自动就是异常安全的，且能够正确处理自赋值
}

HasPtr::~HasPtr()
{
    if (--*use == 0)
    {
        delete ps;
        delete use;
    }
}
using namespace std;
int main()
{
    HasPtr p1("Hiya!");
    HasPtr p2(p1);
    HasPtr p3(p1);
    //交换操作
    /**
     * 除了定义拷贝控制成员，管理资源的类通常还定义一个名为swap的函数。对于那些与重拍元素顺序的算法一起使用的类，定义
     * swap是十分重要的，因为这类算法在需要交换两个元素时会使用
     */
    //我们可以交换指针从而达成交换元素的目的

    return 0;
}