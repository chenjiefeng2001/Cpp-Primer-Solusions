#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <processthreadsapi.h>
//抽象基类
/**
 * 纯虚函数
 * 关键问题:不知道如何定义net_price，并且不希望用户创建一个Disc_quote对象
 * 我们可以将net_price定义成纯虚函数从而令程序实现我们的设计意图，这样做可以清晰明了地告诉用户当前这个
 * net_price函数是没有意义的。和普通的虚函数不一样，一个纯虚函数无需定义
 */

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

class Bulk_quote : public Disc_quote
/**
 * 直接基类是Disc_quote
 * 间接基类是Quote
 * Bulk_quote包含三个部分:
 * - Bulk_quote 部分
 * - Disc_quote 部分
 * - Quote 子对象
 *
 */
{
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string &book, double price, std::size_t qty, double disc) : Disc_quote(book, price, qty, disc) {}
    //覆盖基类中的函数版本以实现一种新的折扣策略
    double net_price(std::size_t) const override;

private:
    std::size_t min_qty = 0;
    double discount = 0.0;
    double price = 0.0;
};
/**
 * @brief 关键概念 重构
 * 在Quote的继承体系中增加Disc_quote类是重构的一个典型示例
 * 重构负责重新负责设计类的体系以便将操作和/或数据
 *
 */
class Base
{

public:
    static void statmem();

private:
protected:
    int prot_mem; // protected成员
};
class Sneaky : public Base
{
    friend void clobber(Sneaky &); //能访问Sneaky::prot_mem
    
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
    statmem();
}

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
class Disc_quote : public Quote
/**
 * @brief Disc_quote 也分别定义了一个默认构造函数和一个接受四个参数的构造函数。
 * 尽管我们不能直接定义这个类的对象，但是Disc_quote的派生类构造函数将会使用Disc_quote的构造函数来构建各个派生类对象的
 * Disc_quote部分。
 *
 * 值得我们注意的是，我们也可以为纯虚函数提供定义，不过函数体必须定义在类的外部。也就是说，我们不能在类的内部为一个=0的函数提供函数体
 */
{
public:
    Disc_quote() = default;
    Disc_quote(const std::string &book, double price, std::size_t qty, double disc) : Quote(book, price), quantity(qty), discount(disc) {}
    double net_price(std::size_t) const = 0;
    //把net_price定义成纯虚函数，在函数体的位置书写=0即可将其转为纯虚函数

protected:
    std::size_t quantity = 0; //折扣适用的购买量
    double discount = 0.0;    //表示折扣的小数值
};
//含有纯虚函数的类是抽象基类
/**
 * 含有(或者未经覆盖直接继承)纯虚函数的类是抽象基类。抽象基类负责定义接口，而后续的其他类可以覆盖该接口。我们不能(直接)
 * 创建一个抽象基类的对象，但是我们可以定义Disc_quote的派生类对象，前提是这些类覆盖了net_price函数
 *
 */
using namespace std;
int main()
{
    return 0;
}