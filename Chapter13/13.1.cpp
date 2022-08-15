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
// class HasPtr
// {
//     HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) {}
//     ~HasPtr() { delete ps; }
// };
class Foo
{
private:
    /* data */
public:
    // 当我们在类内使用=default时，合成的函数将隐式的声明为内联的。如果我们不希望合成的成员是内联函数，应该只对成员的类外定义使用=default
    //我们也只能对具有合成版本的成员函数使用=default
    Foo() = default; //使用default
    ~Foo() = default;
    Foo &operator=(const Foo &) = default; //赋值运算符,
    /**
     * 为了与内置类型的赋值保持一致，赋值运算符通常饭hi一个指向其左侧运算对象的引用
     * 另外值得注意的是，标准库通常要求保存在容器中的类型要具有赋值运算符，其返回值是左侧运算对象的调用
     * 赋值运算符通常会返回一一个指向其左侧运算对象的引用
     */
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

Sales_data &
Sales_data::operator=(const Sales_data &rhs)
{
    bookNO = rhs.bookNO;         //调用string::operator=
    units_sold = rhs.units_sold; //使用内置的int赋值
    revenue = rhs.revenue;       //使用内置的double值
    return *this;                //返回一个此对象的引用
}
// Sales_data::Sales_data(const Sales_data &orig) : bookNO(orig.bookNO),         //使用string的拷贝构造函数
//                                                  units_sold(orig.units_sold), //拷贝orig.units_sold
//                                                  revenue(orig.revenue)        //拷贝orig.revenue
// {                                                                             //空函数体
// }
Sales_data::Sales_data(/* args */)
{
}
/**
 * @brief 析构函数
 * 析构函数执行与构造函数相反的操作：构造函数初始化对象的非static数据成员，还可能做一些其他的工作:
 * - 析构函数释放对象使用的资源，并销毁对象的非static数据成员
 */
Sales_data::~Sales_data()
{
    /**
     * @brief 调用析构函数的场合
     * - 变量在离开其作用域时
     * - 当一个对象被摧毁时
     * - 容器被销毁时，其元素也会被销毁
     * - 对于动态分配的对象，当对指向它的指针应用delete运算符时被销毁
     * - 对于临时对象，当创建它的完整表达式结束时被摧毁
     * 析构函数是自动运行的，我们可以按需分配资源而无需担心何时被释放
     */
}
//参数和返回值
vector<int> v1(10); //正确:直接初始化
// vector<int> v2= 10; //错误，接受大小参数的构造函数是explicit的
void f(std::vector<int>); // f的参数进行靠被初始化
// f(10);                    //错误，不能用一个explicit的构造函数拷贝一个实参
struct NoCopy
{
    NoCopy() = default;                         //使用合成的默认构造函数
    NoCopy(const NoCopy &) = delete;            //阻止拷贝
    NoCopy &operator=(const NoCopy &) = delete; //阻止赋值
    // 使用=delete通知编译器我们不希望定义这些成员，但是使用=delete必须出现在函数第一次声明的时候
    ~NoCopy() = default; // 使用合成的析构函数
    // 与=default的另一个不同之处是，我们可以对任何函数指定=delete。虽然删除函数的主要用途是禁止拷贝控制成员，
    // 但实际当我们希望引导函数匹配过程时，删除函数也是一个不错的选择
};
struct NoDtor
{
    NoDtor() = default; //使用合成默认构造函数
    ~NoDtor();          //= delete; //我们不能销毁NoDtor类型的对象
};
/**
 * @brief 合成的拷贝控制成员可能是删除的
 * 如果我们未定义拷贝控制成员，编译器会为我们定义合成的版本，类似的，如果一个类未定义构造函数，编译i去会为其合成
 * 一个默认构造函数。对某些类来说，编译器将这些合成的成员定义为删除的函数:
 * - 如果类的某个成员的析构函数是删除的或者不可访问的，则类的合成析构函数被定义为删除的
 * - 如果类的某个成员的拷贝函数是删除的或是不可访问的，则类的合成拷贝构造函数被定义为删除的。如果类的某个成员的析构函数是删除的或者
 *   不可访问的，则类合成的拷贝构造函数也被定义为删除的
 * - 如果类的某个成员的拷贝赋值运算符是删除的或不可访问的，或是类有一个const的或引用成员，则类的合成拷贝复制运算符被定义为删除的
 * - 如果类的某个成员的析构函数是删除的或不可访问的，或是有一个引用成员，它没有类内初始化器，或是有一个const成员，它没有类内初始化器
 *   并且其类型未显式定义默认构造函数，则该类型的默认构造函数被定义为删除的
 * 本质上，这些规则的含义是:如果一个类有数据成员不能默认构造、拷贝、复制或销毁，则对应的成员函数将被定义为删除的
 */

class PrivateCopy
//这是在新标准发布之前的做法，现在可能不太适用了，还是建议使用=delete而不是声明成private
{ //无访问说明符;接下来的成员默认为private的
    //拷贝控制成员是private的，因此普通用户代码无法访问
    PrivateCopy(const PrivateCopy &);
    PrivateCopy &operator=(const PrivateCopy &); //其他成员
public:
    PrivateCopy() = default; //使用合成的默认构造函数
    ~PrivateCopy();          //用户可以定义此类型的对象，但无法拷贝他们
};

using namespace std;
int main()
{
    // NoDtor nd;                          //错误，已被删除，无论怎么样都无法创建
    string dots(10, '.');               //直接初始化
    string s(dots);                     //直接初始化
    string s2 = dots;                   //拷贝初始化
    string null_book = "9-999-99999-9"; //拷贝初始化
    string nines = string(100, '9');    //拷贝初始化
    //当使用直接初始化时，我们实际上是要求编译器使用普通函数匹配来选择与我们提供的参数最匹配的构造函数
    //当我们使用拷贝初始化时，我们要求编译器将最右侧的运算对象拷贝到正在创建的对象之中，如果需要的话还需要类型转换
    /**
     * 拷贝初始化的不仅再我们用"="定义变量时会发生，在下列情况下也会发生
     * - 将一个对象作为实参传递给一个非引用类型的形参
     * - 从一个返回类型为非引用类型的函数返回一个对象
     * - 用花括号列表初始化一个数组中的元素或聚合类中的成员
     *
     * 某些类类型还会对它们所分配的对象使用拷贝初始化。
     */
    f(std::vector<int>(10)); //正确:从一个int直接构造一个临时的vector
    //编译器可以绕过拷贝构造函数
    /**
     * 在靠被初始化的过程中，编译器可以(但不是必须)跳过拷贝/移动构造函数，直接创建对象。
     * 但是即使编译器略过了拷贝/移动构造函数，但是在这个程序点上，拷贝/移动构造函数必须是存在且可访问的
     */
    //拷贝赋值运算符
    //与类控制其对象如何初始化一样，类也可以控制其对象如何赋值
    Sales_data trans, accum;
    trans = accum; //使用Sales_data的拷贝赋值运算符
    //与拷贝构造函数一样，如果类未定义自己的拷贝赋值运算符，那么编译器会自动合成一个
    {                                        //新作用域
        Sales_data *p = new Sales_data;      // p是一个内置指针
        auto p2 = make_shared<Sales_data>(); // p2是一个shared_ptr
        Sales_data item(*p);                 //拷贝构造函数将*p拷贝到item中
        vector<Sales_data> vec;              //局部对象
        vec.push_back(*p2);                  //拷贝p2指向的对象
        delete p;                            //对p指向的对象执行析构函数
    }
    /**
     * 退出局部作用域;对item、p2和vec调用方析构函数
     * 销毁p2会递减其他引用计数;如果引用计数为0，对象被释放
     * 销毁vec会销毁它的元素
     */
    //当指向一个对象的引用或指针离开作用域时，析构函数不会执行
    /**
     * @brief 合成析构函数
     * 当一个类未定义自己的析构函数时，编译器会维塔定义一个合成析构函数。类似拷贝构造函数和拷贝赋值运算符，对于某些类，合成析构函数
     * 的函数体就为空
     */
    //三/五法则
    // 三个基本操作可以控制类的拷贝操作:拷贝构造函数、拷贝赋值运算符和析构函数
    /**
     * @brief 需要析构函数的类也需要拷贝和赋值操作
     * 当我们决定一个类是否要定义它自己版本的拷贝控制成员时，一个基本原则是
     * 首先确定这个类是否需要一个析构函数。如果这个类需要一个析构函数，那么我们也可以基本确定它也需要一个拷贝构造函数和拷贝赋值运算符
     *
     */
    //需要拷贝操作的类也需要赋值操作，反之亦然
    //虽然很多类需要定义所有拷贝控制成员，但某些类需要完成的工作，只需要拷贝或者赋值操作，不需要析构函数
    //使用=default

    return 0;
}