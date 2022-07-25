#include <iostream>
//改进的Sales_data类
struct Sales_data
{

    // number
    //常量成员函数
    //常量对象、以及常量对象的引用或指针都只能调用常量成员函数
    std::string isbn() const { return this->bookNO; }
    Sales_data &combinle(const Sales_data &rhs)
    {
        units_sold += rhs.units_sold; //把rhs的成员加到this对象的成员上
        revenue == rhs.revenue;
        return *this; //返回调用的函数对象
    }

    double avg_price() const; //在外部定义了，所以这部分不需要加上
    //这里的类成员可以在类成员函数后面是因为类内的编译是不按次序的，优先编译类成员再到类成员函数
    // data
    std::string bookNO;
    unsigned units_sold = 0;
    double revenue = 0.0;
    //构造函数
    //由于默认构造函数并不接受任何实参，所以定义这个构造函数的目的仅仅是我们既需要其他形式爹构造函数，也需要默认的构造函数。
    //在C++11 新标准中，如果我们需要默认行为
    Sales_data() = default;
    Sales_data(const std::string &s) : bookNO(s) {}
    //构造函数冒号后边的就是设置构造甘薯初始值，初始值就是括号里面的值，如果支持那么可以
    Sales_data(const std::string &s, unsigned n, double p) : bookNO(s), units_sold(n), revenue(p * n) {}
    Sales_data(const std::istream &);
    //花括号内定义了空函数体，而新出现的部分就是构造函数初始值列表，负责为新创建的对象的一个或者几个数据成员
};
//非成员接口函数得放在外边，而成员函数则可以放在类内部也可以放在外部

Sales_data add(const Sales_data &lhs, const Sales_data &rhs)
{
    Sales_data sum = lhs;
    sum.combinle(rhs);
    return sum;
}
std::ostream &printf(std::ostream &os, const Sales_data &item)
{
    os << item.isbn() << " " << item.units_sold << " " << item.revenue << " " << item.avg_price();
    return os;
}
std::istream &read(std::istream &is, Sales_data &item)
{
    double price = 0;
    is >> item.bookNO >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}
/**
 * @brief
 * 定义了一个avg_price函数，并且该函数在Sales_data作用域内
 * @return double
 */
double Sales_data::avg_price() const
{
    if (units_sold)
        return revenue / units_sold;
    else
        return 0;
}
using namespace std;
int main(int argc, char const *argv[])
{
    //这里的total和trans都默认初始化了，默认构造函数并没有任何实参s
    //这里的默认构造函数是编译器创建的，也成为合成的默认构造函数

    Sales_data total;
    if (read(cin, total))
    {
        Sales_data trans;
        while (read(cin, trans))
        {
            if (total.isbn() == trans.isbn())
                total.combinle(trans); //更新当前的值
            else
                printf(cout, total) << endl;
            total = trans;
        }
        printf(cout, total) << endl;
    }
    else
        cerr << "No data?!" << endl;
    return 0;
}
//只有没有声明任何的构造函数时，编译器才会默认自动地去生成默认构造函数