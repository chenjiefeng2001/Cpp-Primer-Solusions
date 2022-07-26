#include <iostream>
using namespace std;
/**
 * @brief 声明静态成员
 * 我们通过在成员的声明之前
 */
class Account
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
int main()
{
}