#include <iostream>
// class和struct的区别在于默认的访问权限，class是可以做区分的，但是struct都是public的
using namespace std;
class Sales_data
{

    //友元
    friend Sales_data add(const Sales_data &, const Sales_data &);
    friend std::istream &read(std::istream &, Sales_data &);
    friend std::ostream &print(std::ostream &, const Sales_data &);
    /**
     * @brief 友元的声明
     * 友元声明仅仅制定了访问的权限，而非通常意义上的函数声明
     * 因此有必要再函数体外再进行一次声明
     */
private:
    double avg_price() const
    {
        return units_sold ? revenue / units_sold : 0;
    }
    std::string bookNO;
    unsigned units_sold = 0;
    double revenue = 0.0;

public:
    //默认构造函数
    Sales_data(/* args */) = default;
    //非委托构造函数
    Sales_data(std::string s, unsigned cnt, double price) : bookNO(s), units_sold(cnt), revenue(cnt * price) {}
    //其余构造函数全都委托给另一个构造函数
    Sales_data() : Sales_data("", 0, 0) {}
    Sales_data(std::string s) : Sales_data(s, 0, 0) {}
    Sales_data(std::istream &is) : Sales_data() { read(is, *this); }

    // Sales_data(const std::string &s, unsigned n, double p) : bookNO(s), units_sold(n), revenue(p * n) {}
    // Sales_data(const std::string &s) : bookNO(s) {}
    // Sales_data(std::istream &);
    std::string isbn() const { return bookNO; }
    Sales_data &combine(const Sales_data &);
    ~Sales_data();
};
Sales_data add(const Sales_data &, const Sales_data &);
std::istream &read(std::istream &, Sales_data &);
std::ostream &print(std::ostream &, const Sales_data &);

Sales_data::Sales_data(/* args */)
{
}

Sales_data::~Sales_data()
{
}
/**
 * @brief
 *  封装的两个重要优点；
 * - 确保用户代码不会无意间破坏封装对象的状态
 * - 被封装的类的具体实现细节可以随时改变，而无需调整用户级别的代码。
 */
int main()
{
    return 0;
}
/**
 * @brief 默认构造函数的作用
 * 默认初始化在以下的情况发生：
 * - 当我们在块作用域内不使用任何初始值定义一个非静态变量
 * - 当一个类本身含有类类型的成员且使用合成的默认构造函数时
 * - 当类类型的成员没有在构造函数初始值列表中显式地初始化时
 * 值的初始化在一下情况发生:
 * - 在数组初始化的过程中如果我们提供的初始值数量少于数组大小时
 * - 当我们不使用初始值定义一个局部静态变量时
 * - 当我们通过书写形如T()的表达式显式地请求值初始化时
 */

/**
 * @brief 隐式的类类型转换
 * 如果构造函数只接受一个实参，则它实际上定义了转换为此类类型的隐式转换机制，这种构造函数也被称为转换构造函数
 * 
 * 当然，我们也可以选择抑制函数定义的隐式转换，因为有的时候我们并不想让他自动转变数值
 * 使用关键字explicit可以阻止这种隐式转换
 */
