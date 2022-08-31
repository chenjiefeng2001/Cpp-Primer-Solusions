#include <iostream>
#include <vector>
#include <map>
#include <string>
//定义基类和派生类
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
    virtual ~Quote() = default; //析构函数进行动态绑定
    //作为继承关系中根节点的类通常会定义一个虚析构函数
    //基类通常都应该定义一个虚析构函数，即使该函数不执行任何实际操作也是如此
private:
    std::string bookNo;

protected:
    double price = 0.0; //代表普通状态下不打折的价格
};
/**
 * @brief 成员函数与继承
 * 派生类可以继承其基类的成员，而当遇到如net_price这样与类型相关的操作时，派生类必须重新对其进行定义
 * 即使用重载从基类继承而来的成员
 * 在C++中，基类必须将他的两种成员区分开来
 * - 一种是基类希望其派生类进行覆盖的函数
 * - 另一种是积累希望派生类直接继承而不要改变的函数
 * 对于第一种，基类通常将其定义为虚函数。基类通过在其成员函数声明语句加上关键字virtual 使得该函数执行动态绑定
 * 任何构造函数之外的非静态函数都可以是虚函数，如果成员函数没有被声明为虚函数，则其解析过程发生在编译时而非运行时
 */
class Bulk_quote : public Quote
{
    /**
     * @brief 派生类中的虚函数
     * 派生类经常需要覆盖它继承的虚函数。如果派生类没有覆盖其基类中的某个虚函数，则该虚函数
     * 的行为类似于其他的普通成员，派生类会直接继承其在基类中的版本。
     *
     * 派生类对象及派生类向基类的类型转换
     * 一个派生类对象包含多个组成部分:一个含有派生类自己定义的(非静态)成员的子对象，以及一个与该派生类继承的基类对应的子对象，
     * 如果有多个基类，那么这样的子对象也有多个。
     */
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string &, double, std::size_t, double);
    double net_price(std::size_t) const override;
    //覆盖基类的函数版本以实现基于大量购买的折扣政策
private:
    std::size_t min_qty = 0; //适用折扣政策的最低购买量
    double discount = 0.0;   //以小数表示的折扣额
};
class Base
{
    /**
     * @brief Construct a new Derivated object
     * 如果基类定义了一个静态类成员，则在整个继承体系中只存在该成员的唯一定义。不论从基类中派生出来多少个派生类
     * 对于每个静态成员来说都只存在唯一的实例
     */
    //继承与静态成员
public:
    static void statmem();
    //静态成员遵循通用访问控制规则，如果基类中的成员是private的，那么派生类也无权访问，

private:
};
class Derivated : public Base
{

    Derivated();
    ~Derivated();
    void f(const Derivated &);
};
//防止继承的发生
// 有时候我们需要定义一个不希望其他类继承的类，或者不想考虑它是否合适作为一个基类，我们可以使用final关键字阻止其继承
class NoDerived final
{ /*code here*/
};
class Last final : Base
{ /*code here*/
};
/**
 * @brief 不存在从基类向派生类的隐式类型转换
 * 之所以存在派生类向基类的类型转换是因为每个派生类对象都包含一个基类部分，而基类
 * 的引用或指针可以绑定到该基类部分上。一个基类的对象既可以以独立的形式存在，也可以作为派生类对象的一部分存在。
 * 如果基类对象不是派生类对象的一部分，则它只含有基类定义的成员，而不含有派生类定义的成员
 */
//在对象
using namespace std;
//派生类使用基类成员
//如果达到了购买书籍的某个最低限定的量值，就可以享受折扣价格了
double Bulk_quote::net_price(size_t cnt) const
{
    //该函数产生一个打折后的价格
    //派生类的作用域嵌套在基类的作用域内
    if (cnt >= min_qty)
    {
        return cnt * (1 - discount) * price;
    }
    else
    {
        return cnt * price;
    }
    /**
     * @brief 关键概念，遵循基类的接口
     * 必须明确一点:每个类负责定义各自的接口。要想与类的对象交互必须使用该类的接口，即使这个对象是派生类的基类部分也是如此。
     * 因此，派生类对象不能直接初始化基类成员。尽管从语法上来说我们可以在派生类构造体函数内给它的公有或受保护的基类成员赋值，
     * 但是最好不要这么做。和使用基类的其他场合一样，派生类应该遵循基类的接口，并且通过调用基类的构造函数来初始化那些从基类
     * 中继承而来的成员
     */
}
void Derivated::f(const Derivated &derivated_obj)
{
    /**
     * 也就是说，既可以通过基类去访问statmem，也可以通过Derivated去访问
     */
    Base::statmem();      //正确，Base定义了statmem
    Derivated::statmem(); //正确，Derivated 继承了statmem
    //正确，派生类的对象能访问基类的静态成员
    derivated_obj.statmem(); //通过Derivated访问
    statmem();               //通过this指针进行访问
}
//直接基类和间接基类
//继承关系中，如果直接由一个基类继承来的类成为直接基类，而通过其他方式继承的称为间接基类
/**
 * @brief 静态基类与动态类型
 * 当我们使用存在继承关系的类型时，必须将一个变量或其他表达式的静态类型与该表达式表示对象的动态类型区分开来
 * 表达式是静态类型在编译时总是已知的，它是变量声明时的类型或者表达式生成的类型；动态类型则是变量或表达式表
 * 示的内存中的对象的类型。动态类型直到运行时才可知
 */
//基类的指针或引用的静态类型可能与其动态类型不一致
int main()
{
    //因为在派生类对象含有与其基类对应的组成部分，所以我们能把派生类的对象当成基类来使用
    //这种转换通常称为派生类到基类的类型转换，但是反过来是不行的，因为基类无派生类的部分
    // 隐含事实:在派生类对象中含有基类对应的组成部分
    Quote item;       //基类对象
    Bulk_quote bulk;  //派生类对象
    Quote *p = &item; // p指向Quote对象
    p = &bulk;        // p指向bulk的Quote部分
    Quote &r = bulk;  // r绑定到bulk的Quote部分
    Bulk_quote bulk;
    Quote *itemP = &bulk; //正确:动态类型是Bulk_quote
    Quote item = (bulk);  //使用Quote::Quote(const Quote&)构造函数
    item = bulk;          //调用Quote::operator=(const Quote&)
}

