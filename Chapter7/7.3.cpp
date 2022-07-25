#include <iostream>
#include <vector>
using namespace std;
//可变数据成员永远不会是const，即使它是const对象的成员
//但是可变数据成员一般只使用在不经常变动的或者拿来记录一些重要的可变数据
class Screen
{
public:
    Screen(/* args */) = default; //因为Screen已经有一个构造函数了，所以必须
    typedef std::string::size_type pos;
    Screen(pos ht, pos wd, char c) : height(ht), width(wd), contents(ht * wd, c) {}
    char get() const { return contents[cursor]; } //下面进行了重载
    inline char get(pos ht, pos wd) const;
    Screen &move(pos r, pos c);
    ~Screen();
    Screen &set(char);
    Screen &set(pos r, pos col, char ch);

private:
    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;
};
class Window_mgr
// window_mgr 的作用是追踪Screen
{
private:
    /* data */
    std::vector<Screen> screens{Screen(24, 80, ' ')};
    //默认情况下，一个window_mgr包含一个标准尺寸的空白Screen
    //类内初始值必须使用=的初始化形式，要么就是花括号括起来的
public:
    Window_mgr(/* args */);
    ~Window_mgr();
};
inline Screen &Screen::set(char c)
{
    contents[cursor] = c;
    return *this;
}
inline Screen &Screen::set(pos r, pos col, char ch)
{
    contents[r * width + col] = ch;
    return *this;
}
Window_mgr::Window_mgr(/* args */)
{
}

Window_mgr::~Window_mgr()
{
}

inline Screen &Screen::move(pos c, pos r)
{
    pos row = r * width; //计算行的位置
    cursor = row + c;    //在行内将光标移动到指定的列
    return *this;        //以左值的形式返回对象
}
char Screen::get(pos r, pos c) const //在类的内部声明成inline
{
    pos row = r * width;
    return contents[row + c];
}
Screen::Screen(/* args */)
{
}

Screen::~Screen()
{
}

int main()
{
    return 0;
}