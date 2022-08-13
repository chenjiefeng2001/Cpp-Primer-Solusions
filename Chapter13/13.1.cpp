#include <iostream>
#include <vector>
#include <string>
#include <memory>
/**
 * @brief 拷贝控制
 * 当定义一个类时，我们显式或隐式地指定在此类型的对象拷贝、移动、赋值和销毁时做什么。一个类通过定义五种特殊的成员函数来控制这些操作:
 * - 拷贝构造函数
 * - 拷贝赋值运算符
 * - 移动构造函数
 * - 移动赋值函数
 * - 析构函数
 */
class Foo
{
private:
    /* data */
public:
    Foo();
    ~Foo();
};
/**
 * @brief 合成拷贝构造函数
 * 如果我们没有为一个类定义拷贝构造函数，那么编译器会为我们定义一个，与合成默认构造函数不同，即使我们定义了其他构造函数
 * 编译器也会为我们合成一个拷贝构造函数
 */
Foo::Foo(const Foo &) //拷贝构造函数
{
    // 拷贝构造函数的第一个参数必须是一个引用类型
}

Foo::~Foo()
{
}
class Sales_data
{
    friend Sales_data add(const Sales_data &, const Sales_data &);
    friend std::istream &read(std::istream &, Sales_data &);
    friend std::ostream &print(std::ostream &, const Sales_data &);

private:
    double avg_price() const
    {
        return units_sold ? revenue / units_sold : 0;
    }
    std::string bookNO;
    unsigned units_sold = 0;
    double revenue = 0.0;

public:
    Sales_data(/* args */) = default;
    Sales_data(const std::string &s, unsigned n, double p) : bookNO(s), units_sold(n), revenue(p * n) {}
    Sales_data(const std::string &s) : bookNO(s) {}
    Sales_data(std::istream &);
    std::string isbn() const { return bookNO; }
    Sales_data &combine(const Sales_data &);
    Sales_data(const Sales_data &); //与合成地拷贝构造函数等价的拷贝构造函数的声明
    ~Sales_data();
};
Sales_data add(const Sales_data &, const Sales_data &);
std::istream &read(std::istream &, Sales_data &);
std::ostream &print(std::ostream &, const Sales_data &);

Sales_data::Sales_data(const Sales_data &orig) : bookNO(orig.bookNO),         //使用string的拷贝构造函数
                                                 units_sold(orig.units_sold), //拷贝orig.units_sold
                                                 revenue(orig.revenue)        //拷贝orig.revenue
{
}
Sales_data::Sales_data(/* args */)
{
}

Sales_data::~Sales_data()
{
}