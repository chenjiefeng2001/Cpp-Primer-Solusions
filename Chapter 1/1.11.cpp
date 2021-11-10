#include <iostream>
int main(int argc, char const *argv[])
{
    int var1, var2;
    std::cout << "Enter two numbers" << std::endl;
    std::cin >> var1 >> var2;
    if (var1 > var2)
    {
        while (var2 <= var1)
        {
            var2++;
            std::cout << var2 << std::endl;
        }
    }
    else
    {
        while (var1 <= var2)
        {
            var1++;
            std::cout << var1 << std::endl;
        }
    }
    return 0;
}
