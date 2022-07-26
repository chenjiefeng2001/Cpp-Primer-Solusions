#include <iostream>
// class和struct的区别在于默认的访问权限，class是可以做区分的，但是struct都是public的
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
    Sales_data(/* args */) = default;
    Sales_data(const std::string &s, unsigned n, double p) : bookNO(s), units_sold(n), revenue(p * n) {}
    Sales_data(const std::string &s) : bookNO(s) {}
    Sales_data(std::istream &);
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
using namespace std;
int main()
{
    Screen myscreen;
}