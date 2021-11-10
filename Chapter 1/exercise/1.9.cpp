#include <iostream>
int main()
{
    int var = 50, sum;
    while (var <= 100)
    {
        sum += var;
        var++;
    }
    std::cout << "The sum from 50 to 100 is" << sum << endl;
    return 0;
}