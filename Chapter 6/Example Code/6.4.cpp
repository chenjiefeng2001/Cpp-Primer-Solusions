#include <iostream>
#include <string>
#include <vector>
using namespace std;
// void print(const char *cp);
// void print(const int *beg, const int *end);
// void print(const int iap[], size_t size);
const string &shortString(const string &s1, const string &s2)
{
    return s1.size() <= s2.size() ? s1 : s2;
}

string &shortString(string &s1, string &s2)
{
    auto &r = shortString(const_cast<const string &>(s1),
                          const_cast<const string &>(s2));
    return const_cast<string &>(r);
}

int main()
{
    return 0;
    const string s1 = "test";
    const string s2 = "test2";
    auto r = shortString(s1, s2);
    cout << r.size() << endl;
    return 0;
}
