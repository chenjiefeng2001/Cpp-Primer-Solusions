#include <iostream>
#include <string>
#include <vector>
/**
 * @brief 访问控制与继承
 * 受保护的成员
 * 一个类中使用protected关键字来声明的对象，这些对象希望与派生类分享，但是不希望被其他公共访问的成员
 * - 和私有成员类似，不可以被公有成员访问
 * - 和公有成员类似，受保护的成员对派生类的成员和友元来说是可访问的
 * - 派生类的成员和友元只能通过派生类对象来访问基类中的受保护成员。派生类对于一个基类对象中的受保护的成员
 *
 *
 */
/**
 * 某个类对其继承而来的成员的访问权限受到两个因素的影响:
 * - 在基类种该成员的访问说明符
 - 在派生类的列表中访问说明符
 */
class Base
{
protected:
    int prot_mem; // protected 成员
    std::size_t n;

public:
    void pub_mem(); // public成员
    std::size_t size() const { return n; }

private:
    char priv_mem; // private成员
};
class Derived : private Base
{
public:
    //保持对象尺寸相关的成员的访问级别
    using Base::size;

protected:
    using Base::n;
    //派生类只能为那些它可以访问的名字提供using声明
};
// class Sneaky : public Base
// {
//     friend void clobber(Sneaky &); //能访问Sneaky::prot_mem
//     int j;                         // private成员
// };
// void clobber(Sneaky &s) { s.j = s.prot_mem = 0; } //正确，因为
// void clobber(Base &b){b.prot_mem=0;}错误，不存在这样的访问方式
struct Pub_Derv : public Base
{
    int f()
    {
        return prot_mem; //正确，派生类能访问protected成员
    }
    // char g() { return priv_mem; //错误 private成员对于派生类来说是不可访问的
    // }
};
struct Priv_Deri : private Base
{
    /* data */
    // private不影响派生类的访问权限
    int f1() const { return prot_mem; }
};
/**
 * @brief 派生类向基类转换的可访问性
 * 派生类向基类的转换是否可访问由其使用的该转换的代码来决定，同时派生类的派生访问说明符也会有影响。这里假定D继承自B
 * - 只有当D公有地继承B时，用户代码才能使用派生类向基类的转换；如果D继承B的方式时受保护或者私有的，则用户代码不能使用该转换
 * - 不论D以什么方式继承B，D的成员函数和友元都能使用派生类向基类的转换；派生类向其直接基类的类型转换对于派生类的成员和友元来说永远是可访问的
 * - 如果D继承B的方式是公有的或受保护的，则D的派生类的成员和友元可以使用D向B的类型转换；反之，如果D继承B的方式是私有的，则不能使用
 *
 * 对于代码中某个给定节点来说，如果基类的公有成员是可访问的，则派生类向基类的类型转换也是可访问的；反之则不行
 */
/**
 * @warning 关键概念:类的设计与受保护成员
 * 不考虑继承的话，我们可以认为一个类有两种不同的用户:普通用户和实现者。
 * 其中，普通用户编写的代码使用类的对象，这部分代码只能访问类的公有(接口)成员；
 * 实现者则负责编写类的成员和友元的代码
 * 成员和友元既可以访问公有部分，也可以访问私有部分
 *
 * 如果进一步考虑继承，那么就会有派生类，基类希望派生类能使用部分声明成受保护的，普通用户不能访问的受保护成员，而派生类及其友元仍旧不能访问私有成员
 *
 * 和其他类一样，基类应该将其接口成员声明为公有的；同时将属于其实现部分分成两组：
 * - 一组可供派生类访问
 * - 另一组只能由基类及基类的友元访问
 *
 * 不能继承友元关系；每个类负责控制各自成员的访问权限
 */

using namespace std;
//派生访问说明符的目的是控制派生类用户(包括派生类的派生类在内)对于基类成员的访问权限
int main()
{
    Pub_Derv d1;  //继承自Base的成员是public的
    Priv_Deri d2; //继承自Base的成员是private的
    d1.pub_mem(); //正确:pub_mem成员在派生类中是public的
    // d2.pub_mem() //错误，pub_mem在派生类中是private的
}