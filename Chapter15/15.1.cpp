/**
 * @file 15.1.cpp
 * @author chenjiefeng
 * @brief OOP概述
 * @version 0.1
 * @date 2022-08-23
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <string>
#include <vector>

//面向对象设计的核心思想:数据抽象、继承和动态绑定
/**
 * @brief 继承
 * 通过继承联系在一起的累构成一种层次关系。通常在层次关系的根部有一个基类，其他类则直接或间接的从基类继承而来，
 * 这些继承得到的类成为派生类。基类负责定义在层次结构中所有成员，而每个派生类定义各自特有的成员
 *
 * 在C++中，基类将类型相关的函数与派生类不做改变直接继承的函数区分对待。对于某些函数，基类希望它的派生类个自定义适合自身的版本，此时基类就将这些函数声明成
 * 虚函数
 *
 * 派生类必须使用派生类列表明确指出它是从哪个基类继承而来的。类的派生列表的形式是:
 * 首先是一个冒号，后面紧跟以逗号分割的基类列表，其中每个基类前面可以有访问说明符
 */
class Quote
{
public:
    std::string isbn() const;
    virtual double net_price(std::size_t n) const;
    //声明为虚函数
};
class Bulk_quote : public Quote
{ //派生自Quote
public:
    double net_price(std::size_t) const override; //重载new_price
};
//动态绑定
//通过使用动态绑定，我们能用同一段代码分别处理Quote和Bulk_Quote的对象
double print_total(std::ostream &os, const Quote &item, size_t n)
{
    //根据传入的item形参的对象类型调用Quote::net_price
    //或者Bulk_quote::net_price
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn()
       << "# sold: " << n << " total due: " << ret << std::endl;
    return ret;
}
using namespace std;
int main()
{
    Quote basic;
    Bulk_quote bulk;
    print_total(cout, basic, 20); //调用基类中的虚函数net_price
    print_total(cout, bulk, 20);  //调用Bulk_quote的net_price
    /**
     * @brief 结论
     * 因为函数print_total 的item形参是基类Quote的一个引用，出于一些原因，我们既能使用基类Quote的对象
     * 调用该函数，也能使用派生类Bulk_quote的对象调用它;又因为print_total是使用引用类型调用net_price函数的，
     * 世纪传入print_total的对象类型将决定到底执行net_price的哪个版本
     */
    
}