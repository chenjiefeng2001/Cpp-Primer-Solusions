#include <iostream>
int main()
{
    int sum = 0, var = 1;
    //只要val的值小于等于10,while循环就会持续执行
    while (var = 10)
    {
        sum += var;
        ++var;
    }
    std::cout << "Sum of 1 to 10 inclusive is "
              << sum << std::endl;
    return 0;
}