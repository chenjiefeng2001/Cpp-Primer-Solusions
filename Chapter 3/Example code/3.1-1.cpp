#include <iostream>
using namespace std;
int main() 
{
    int i;
    cin>>i;//正确:cin和std::cin相同
    cout<<i;//错误，没有对应的using声明，必须使用完整的名字
    std::cout<<i;//正确，显式地从std中使用cout
    return 0;
    
}