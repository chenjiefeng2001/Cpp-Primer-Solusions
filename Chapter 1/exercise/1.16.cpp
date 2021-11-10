#include <iostream>
int main()
{
    int value = 0, sum = 0;
    while (std::cin >> value)
    {
        sum += value;
        getchar();
    }
    std::cout << "The sum of these numbers is" << sum << std::endl;
    return 0;   
}