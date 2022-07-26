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
    //根据对象是否是const重载了display函数
    Screen &display(std::ostream &os)
    {
        do_display(os);
        return *this;
    }
    const Screen &display(std::ostream &os) const
    {
        do_display(os);
        return *this;
    }
    /**
     * @brief 为什么单独定义一个do_display函数而不是直接调用display函数
     * - 易于后期的修改，以及当类扩展时，方便进行调用
     * - 避免在多处都使用同一份代码，这样会造成程序的臃肿
     * - 这样不会有任何的开销
     */
private:
    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;
    void do_display(std::ostream &os) const { os << contents; }
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

Screen::~Screen()
{
}

int main()
{
    // Screen myscreen;
    // myscreen.move(4, 0).set('#');
    // return 0;
    Screen Screen(5, 3, 'X');
    Screen.move(4, 0).set('#').display(cout);
    cout << "\n";
    Screen.display(cout);
    cout << "\n";

    return 0;
}
/**
 * @brief 类的声明
 * 类的声明有两种，一种为前向声明，即仅仅声明类而暂时不定义它，而这种在未定义前的状态是一种不完全声明。
 * 使用场景：可以定义指向这种类型的指针或者引用，也可以声明以不完全类型作为参数或者返回类型的函数
 * 另一种就是完全声明，即定义和声明在一起的，这种也称为完全声明
 * 
 * 类之间的友元关系
 * 
 */