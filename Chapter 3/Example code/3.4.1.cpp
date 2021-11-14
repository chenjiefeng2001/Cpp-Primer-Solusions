#include <iostream>
#include <string>
#include <vector>
using std::vector;
using namespace std;
int main()
{
    string s("some arting");
    if (s.begin() != s.end())//判断首尾容器是否是相同，来确定是否非空
        auto it =s.end();
        *it = toupper(*it);//指向末尾元素
        return 0;
}
/**
 * 当然，迭代器也可以用于其他的操作，例如元素移位之类的操作。
 */

