#include <iostream>
#include <vector>
#include <string>
#include <memory>

class Quote
{
public:
    Quote() = default;
    Quote(const std::string &book, double sales_price) : bookNo(book), price(sales_price) {}
    std::string isbn() const { return bookNo; }
    virtual double net_price(std::size_t n) const
    {
        return n * price;
    }
    virtual ~Quote() = default;

private:
    std::string bookNo;

protected:
    double price = 0.0;
};

class Bulk_quote : public Quote
{

public:
    Bulk_quote() = default;
    Bulk_quote(const std::string &, double, std::size_t, double);
    double net_price(std::size_t) const override;

private:
    std::size_t min_qty = 0;
    double discount = 0.0;
};
class Base
{

public:
    static void statmem();

private:
};
class Derivated : public Base
{

    Derivated();
    ~Derivated();
    void f(const Derivated &);
};

class NoDerived final
{
};
class Last final : Base
{
};

using namespace std;

double Bulk_quote::net_price(size_t cnt) const
{

    if (cnt >= min_qty)
    {
        return cnt * (1 - discount) * price;
    }
    else
    {
        return cnt * price;
    }
}
void Derivated::f(const Derivated &derivated_obj)
{

    Base::statmem();      //正确，Base定义了statmem
    Derivated::statmem(); //正确，Derivated 继承了statmem
    //正确，派生类的对象能访问基类的静态成员
    derivated_obj.statmem(); //通过Derivated访问
    statmem();               //通过this指针进行访问
}
//派生类中的虚函数
//当我们在派生类中覆盖了某个虚函数时，可以再一次使用virtual 关键字指出该函数的性质。然而这么做非必须，因为一旦某个函数被声明成虚函数，在所有的派生类中都是虚函数
//若覆盖了某个继承而来的虚函数，则它的形参类型必须与被它覆盖的基类函数完全一致
// 同理，派生类中的虚函数的返回类型也必须与基类函数匹配。但是该规则存在一个例外，当类的虚函数返回类型是本身的指针或引用时，上述规则无效

// 基类中的虚函数在派生类中隐含地也是一个虚函数。当派生类覆盖了某个虚函数时，该函数在基类中地形参也必须与派生类中地形参严格匹配
struct B
{
    virtual void f1(int) const;
    virtual void f2();
    void f3();
};
struct D1 : B
{
    void f1(int) const override; //正确，f1与基类中的f1匹配
    // void f2(int) override;       //错误，B没有形如f2(int)的函数
    void f2();
    void f3();
};
/**
 * @brief 虚函数与默认实参
 * 和其他函数咿呀，虚函数也可以拥有默认实参。如果某次函数调用使用了默认实参，则
 * 该实参值由本次调用多个静态类型决定
 *
 * 如果虚函数默认使用实参，则基类和派生类中定义的默认实参最好一致
 */
//回避虚函数的机制
//在某些情况下，我们希望虚函数的调用不要进行动态绑定，而是强迫其执行虚函数的某个特定版本
//可以使用作用域运算符实现这一目的

using namespace std;
double print_total(std::ostream &os, const Quote &item, size_t n)
{
    //根据传入的item形参的对象类型调用Quote::net_price
    //或者Bulk_quote::net_price
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn()
       << "# sold: " << n << " total due: " << ret << std::endl;
    return ret;
}
int main()
{
    Quote base;
    Bulk_quote bulk;
    Quote("0-201-82470-1", 50);
    Quote *itemP = &bulk;
    Quote *baseP = &base;
    print_total(cout, base, 10);
    Bulk_quote Derivated("0-201-82470-1", 50, 5, .19);
    print_total(cout, Derivated, 10);
    //动态绑定只有在当我们通过指针或引用调用虚函数时才会发生
    //当我们通过一个具有普通类型的表达式调用虚函数时，在编译时就会将调用的版本确定下来
    base = Derivated; //把derivated的Quote部分拷贝给base
    base.net_price(20);
    /**
     * @brief C++的多态性
     * OOP的核心思想是多态性。我们把继承关系的多个类型成为多态类型，因为我们使用这些类型的的"多种形式"而无须在意他们的差异
     * 引用或指针的静态类型与动态类型不同这一事实正是C++语言支持多态性的根本存在
     *
     * 当且仅当对通过指针或调用虚函数时，才会在运行时解析该引用，也只有在这种情况下对象的动态类型才有可能与静态类型不同
     */
    double undiscounted = baseP->Quote::net_price(42);
    //该代码强行调用Quote的net_price函数，而不管baseP实际只想的对象类型到底是什么
    //在通常情况下，只有成员函数(或友元)中的代码才需要使用作用域运算符来回避虚函数的机制
    return 0;
}