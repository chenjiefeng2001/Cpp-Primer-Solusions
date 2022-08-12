#include <iostream>
#include <sstream>
#include <istream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <memory>
using namespace std;
//使用标准库:文本查询程序
/**
 * @brief 文本查询程序设计
 * - 当程序读取输入文件时，它必须记住单词出现的每一行。因此，程序需要逐行读取输入文件，并将每一行分解为独立的单词
 * - 当程序生成输出时:
 *      - 它必须能提取每个单词所关联的行号
 *      - 行号必须按升序出现并且不重复
 *      - 它必须能打印给定行号中的文本
 * 数据结构部分:
 *
 * @return int
 */
string make_plural(size_t ctr, const string &word, const string &ending)
{
    return (ctr > 1) ? word + ending : word;
} //简单的三目运算符，这个是书里没提及的部分
class QueryResult
{
    friend std::ostream &print(std::ostream &, const QueryResult &);

public:
    QueryResult(std::string string_text, std::shared_ptr<std::set<size_t>> ptr, std::shared_ptr<std::vector<std::string>> files) : sought(string_text), lines(ptr), file(files) {}

private:
    std::string sought;
    std::shared_ptr<std::set<size_t>> lines;
    std::shared_ptr<std::vector<std::string>> file;
}; //为了定义query的返回类型，这个定义是必须的
struct TextQuery
{
public:
    TextQuery(std::ifstream &);
    ~TextQuery() {}
    using line_no = std::vector<std::string>::size_type;
    QueryResult
    query(const std::string &) const;

private:
    shared_ptr<std::vector<std::string>> file;
    //每个单词到它所在的行号的集合的映射
    std::map<std::string, std::shared_ptr<std::set<line_no>>> Query;
};
//类函数定义
QueryResult
TextQuery::query(const string &sought) const
{
    //如果未找到sought，我们将返回一个指向此set的指针
    static shared_ptr<set<line_no>> nodata(new set<line_no>);
    auto loc = Query.find(sought);
    if (loc == Query.end())
        return QueryResult(sought, nodata, file); //未找到
    else
        return QueryResult(sought, loc->second, file);
}
ostream &print(ostream &os, const QueryResult &qr)
{
    //如果找到了单词，打印出现的次数和所有出现的位置
    os << qr.sought << " occurs " << qr.lines->size() << " " << make_plural(qr.lines->size(), " times ", "s") << endl;
    for (auto num : *qr.lines)
        os << "\t(line " << num + 1 << ")" << *(qr.file->begin() + num) << endl;
    return os;
}
TextQuery::TextQuery(ifstream &is) : file(new vector<string>)
{
    std::string text;
    while (getline(is, text)) //对文件中每一行
    {
        file->push_back(text);    //保存此文本
        int n = file->size() - 1; //当前行号
        istringstream line(text); //将文本分解为单词
        string word;
        while (line >> word)
        {
            //如果单词不在query中
            auto &lines = Query[word];
            if (!lines)
                lines.reset(new set<line_no>);
            lines->insert(n); //将此行号插入set中
        }
    }
}

int runQUeries(std::ifstream &infile)
{
    TextQuery tq(infile);
    //与用户交互:提示用户输入需要查询的单词，完成查询并打印结果
    while (true)
    {
        cout << "Enter word to look for, or q to quit: " << endl;
        string string_cin;
        if (!(cin >> string_cin) || string_cin == "q")
        {
            break;
        }
        print(cout, tq.query(string_cin)) << endl;
    }
}

int main() {}