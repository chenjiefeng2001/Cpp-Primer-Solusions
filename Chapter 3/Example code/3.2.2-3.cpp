#include <iostream>
#include <string>
using namespace std;
int main()
{
    stringf line;
    while (getline(cin,line))
    {
        if (!line.empty())
            {
                cout<<line<<endl;
            }
    }
    
}