#include <iostream>
#include <string>
using namespace std;
string::size_type find_char(const string &s, char c,
                            string::size_type &occure)
{
    auto ret = s.size(); //设置第一次出现的位置
    occure = 0;          //设置出现次数的形参值
    for (decltype(ret) i = 0; i != s.size(); ++i)
    {
        if (s[i] == c)
        {
            if (ret == s.size())
            {
                ret = i;
            }
            ++occure; //每出现一次就加1
        }
    }
    return ret; //调用次数通过occurs隐式的返回，当然，这里也可以写return语句返回
}
int main(int argc)
{

    auto index = find_char(s, 'o', ctr);
}