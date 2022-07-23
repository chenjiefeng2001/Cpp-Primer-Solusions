#include <iostream>
using namespace std;
/**
 * @brief 无返回值的函数
 *
 *
 */
void swap(int &v1, int &v2)
{
    //如果两个值是相等的，那么不需要交换，直接exit
    if (v1 == v2)
    {
        return;
    }
    int tmp = v2;
    v2 = v1;
    v1 = tmp;
    //无须显式的return语句
}

bool str_subrange(const string &str1, const string &str2)
{
    if (str1.size() == str2.size())
        return str1 == str2; //正确，==返回的布尔值
    auto size = (str1.size() < str2.size())
                    ? str1.size()
                    : str2.size();
    //检查两个string对象的字符串是否相等，以较短的字符串长度为限
    for (decltype(size) i = 0; i != size; ++i)
    {
        if (str1[i] != str2[i])
            return ; //错误，这里没返回值
    }
}
int main()
{
    const string s1 = "test";
    const string s2 = "test";
    bool tset = str_subrange(s1, s2);
    return 0;
}