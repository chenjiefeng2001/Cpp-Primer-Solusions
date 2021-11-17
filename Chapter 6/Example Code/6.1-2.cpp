#include <iostream>
//局部静态对象

size_t count_calls()
{
    static size_t ctr = 0;
    return 0;
}
using namespace std;
int main()
{
    for (size_t i = 0; i != 10; i++)
        cout << count_calls() << endl;
    return 0;
}