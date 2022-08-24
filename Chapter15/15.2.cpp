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

private:
    std::string bookNo;

protected:
    double price = 0.0; //代表普通状态下不打折的价格
};