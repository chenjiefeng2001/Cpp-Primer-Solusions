#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
struct PersonInfo
{
    string name;
    vector<string> phones;
};

int main(int argc, char const *argv[])
{
    /**
     * @brief string流
     * sstream头文件定义了三个类型来支持内存io，这些类型可以向string写入数据
     * istringstream 从string中读取数据
     * ostringstream 从string写入数据
     * stringstream  既可以从string读取数据也可以向string写数据
     */

    /**
     * @brief stringstream特有的操作
     * sstream strm     strm是一个未绑定的stringstream对象。sstream是头文件sstream中定义的一个类型
     * sstream strm(s)  strm是一个sstream对象，保存string s的一个拷贝。此构造函数是explicit的
     * strm.str()       返回strm所保存的string拷贝
     * strm.str(s)      将string s拷贝到strm中。返回void
     */
    string line, word;         //分别保存来自输入的一行和单词
    vector<PersonInfo> people; //保存来自输入的所有记录
    //逐行读取数据，直至cin遇到文件末尾
    while (getline(cin, line))
    {
        PersonInfo info;
        istringstream record(line);
        record >> info.name;
        while (record >> word)
        {
            info.phones.push_back(word);
        }
        people.push_back(info);
    }
    //使用ostringstream
    for (const auto &entry : people)
    {
        //对people中的每一项
        ostringstream formatted, badNums;
        for (const auto &nums : entry.phones)
        {
            if (!valid(nums))
                badNums << " " << nums;
        }
        else
        {
            formatted << " " << format(nums);
        }
    }
    return 0;
}
