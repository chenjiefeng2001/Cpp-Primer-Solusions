#include <iostream>
/**
 * 
 * 简单函数
 * 读取两个函数，求他们的和
 */
int main()
{
    std::cout << "Enter two numbers:" << std::endl;
    int var1 = 0, var2 = 0; //保存读取的变量
    std::cin >> var1 >> var2;
    std::cout << "The sum of " << var1 << " and " << var2 << " is " << var1 + var2 << std::endl;
    return 0;
}