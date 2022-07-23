#include <iostream>
#include <vector>
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
            return false; //错误，这里没返回值
    }
}
//引用返回左值
char &get_val(string &str, string::size_type ix)
{
    return str[ix];
}
vector<string> process()
{
    string except;
    string actual = ;
    if (except.empty())
        return {}; //返回一个空的vector对象
    else if (except == actual)
        return {"FucntionX", "Okay"}; //返回列表初始化的对象
}
int main()
{
    // const string s1 = "test";
    // const string s2 = "test";
    // bool tset = str_subrange(s1, s2);
    // //左结合律
    // return 0;
    // string s("a value");
    // cout << s << endl;
    // get_val(s, 0) = 'A';
    // cout << s << endl;
    // return 0;
    auto func(int i)->int(*)[10];
    //尾置返回类型，任何函数都可以改成这种，但是对复杂的函数有很大的作用(例如返回的是数组的指针或者数组的引用)
    // func接受一个int类型的实参，并且返回一个指针
    int odd[] = {1, 3, 5, 7, 9};
    int even[] = {2, 4, 6, 8, 0};
    decltype(odd) *arrPtr(int i)
    {
        return (i % 2) ? &odd : &even; //返回一个指向数组的指针
    }
    return 0;
}