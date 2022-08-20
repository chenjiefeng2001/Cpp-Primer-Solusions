#include <iostream>
#include <set>
#include <string>
#include <memory>
#include <algorithm>
#include <vector>

class Message
{
    friend class Folder;

public:
    // folder被隐式初始化为空集合
    explicit Message(const std::string &str = " ") : contents(str) {}
    //拷贝控制成员，用来管理指向本message的指针
    Message(const Message &);
    Message &operator=(const Message &);
    ~Message();
    //从给定的Folder中添加，删除本Message
    void save(Folder &);
    void remove(Folder &);

private:
    std::string contents;       //实际文本消息
    std::set<Folder *> folders; //包含本Message的folder
    //拷贝构造函数，拷贝赋值运算符和析构函数所使用的工具函数
    //将本message添加到指向参数的folder中
    void add_to_Folders(const Message &);
    //从folder中的每个Folder中删除本Message
    void remove_from_Folders();
};

class Folder
{
    // folder用于增加和删除消息？
public:
    Folder() {}
    ~Folder();
    Folder addMsg() {}
    Folder remMsg() {}

private:
};
void Message::add_to_Folders(const Message &m)
{
    for (auto f : m.folders)
        f->addMsg(this);
}
void Message::save(Folder &f)
{
    folders.insert(&f);
}
void Message::remove(Folder &f)
{
    for (auto f : folders)
        f->remMsg(this);
}
Message::~Message()
{
    remove_from_Folders();
}
Message &Message::operator=(const Message &rhs)
{
    remove_from_Folders();   //更新已有的Folder
    contents = rhs.contents; //从rhs拷贝消息内容
    folders = rhs.folders;   //从rhs拷贝Folder指针
    add_to_Folders(rhs);     //将Message添加到那些Folder中
    return *this;
}
void swap(Message &lhs, Message &rhs)
{
    using std::swap;
    for (auto f : lhs.folders)
        f->remMsg(&rhs);
    for (auto f : rhs.folders)
        f->remMsg(&rhs);
    //交换contents和Folder指针set
    swap(lhs.folders, rhs.folders);
    swap(lhs.contents, rhs.contents);
    for (auto f : lhs.folders)
        f->addMsg(lhs);
    for (auto f : rhs.folders)
        f->addMsg(&rhs);
}

using namespace std;
int main()
{
}