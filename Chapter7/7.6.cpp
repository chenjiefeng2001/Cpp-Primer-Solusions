#include <iostream>
using namespace std;
/**
 * @brief 声明静态成员
 * 我们通过在成员的声明之前加上关键字stactic使得与类关联在一起。和其他成员一样
 * 静态成员可以是public的或private的。静态数据成员的类型可以是常量、引用、指针】类类型等。
 */
class Account
//成员函数不通过作用域运算符就能直接使用静态成员
{
public:
    void calculate()
    {
        amount += amount * interestRate;
    }
    static double rate()
    {
        return interestRate;
    }
    static void rate(double);

private:
    std::string owner;
    double amount;
    static double interestRate;
    static double initRate;
};
//定义静态成员
void Account::rate(double newRate)
{
    //和其他成员函数一样，我们既可以在类的内部也可以在类的外部定义静态成员函数
    //当在外部定义静态成员时，不能重复static关键字，该关键字吃能出现在类内部
    interestRate = newRate;
}
int main()
{
    double r;
    r = Account::rate();
    Account ac1;
    Account *ac2 = &ac1;
    r = ac1.rate();  //通过Account的对象或引用
    r = ac2->rate(); //通过指向Account对象的指针
}
//i静态类成员可以是不完全类型