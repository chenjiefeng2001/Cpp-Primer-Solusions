#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include <string>
//通常，管理类外资源的累必须定义拷贝控制成员，一旦一个类需要析构函数，那么它几乎肯定也需要一个拷贝构造函数和一个拷贝赋值运算符
/**
 * 为了提供类值的行为，对于类管理的资源，每个对象都应该拥有一份自己的拷贝。这意味着对于ps指向的string，每个HasPtr对象都必须拥有自己的拷贝
 * 为了实现类值行为，HasPtr需要:
 * - 定义一个拷贝构造函数，完成string的拷贝，而不是拷贝指针
 * - 定义一个析构函数来释放string
 * - 定义一个拷贝赋值运算符来释放当前的string，并从右侧运算对象拷贝string
 */
class HasPtr
{
public:
    //构造函数分配新的string和新的计数器，将计数器置为1

    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0), use(new std::size_t(1)) {} //对ps指向的string，每个HasPtr对象都有自己的拷贝
    HasPtr(const HasPtr &p) : ps(new std::string(*p.ps)), i(p.i), use(p.use) { ++*use; }
    HasPtr &operator=(const HasPtr &);
    ~HasPtr() { delete ps; }

private:
    std::string *ps;
    int i;
    std::size_t *use;
};
//类内拷贝赋值运算符
/**
 * 赋值运算符通常组合了析构函数和构造函数的操作。类似析构函数，赋值操作会销毁左侧运算对象的资源。
 * 类似拷贝构造函数，赋值操作会从右侧运算对象拷贝数据。但是，非常重要的一点是，这些操作都是以正确的顺序执行的
 */
HasPtr &HasPtr::operator=(const HasPtr &rhs)
{
    ++*rhs.use;//递增右侧运算符运算对象的引用计数
    if(--*use==0)
    {
        
    }
    // auto newp = new std::string(*rhs.ps); //从右侧运算对象拷贝数据到本对象
    // delete ps;                            //释放旧内存
    // ps = newp;                            //从右侧运算对象拷贝数据到本对象
    // i = rhs.i;
    // return *this; //返回本对象
    /**
     * @brief 赋值运算符
     * 当你编写赋值运算符时，有两点需要记住:
     * - 如果将一个对象赋予它自身，赋值运算符必须能够正确的工作
     * - 大多数赋值运算符组合了析构函数和拷贝构造函数的工作100左侧运算对象的现有成员就是安全的了
     *   一旦左侧运算对象的资源被销毁，就只剩下将数据临时拷贝到左侧运算对象的成员中了
     */
}
//定义行为像指针的类
/**
 * 引用计数
 * 引用计数的工作方式:
 * - 除了初始化对象之外，每个构造函数(拷贝构造函数除外)还要创建一个引用计数，用来记录有多少对象与正在创建的对象共享状态。当我们创建一个对象的时候，只有一个对象共享状态
 *   因此将计数器初始化为1
 * - 拷贝构造函数不分配新的计数器，而是拷贝给定对象给定对象的数据成员，包括计数器。拷贝构造函数递增共享的计数器，指出给定对象的状态又被一个新用户所共享。
 * - 析构函数递减计数器，指出共享状态的用户少一个。如果计数器变为0，则析构函数释放状态。
 * - 拷贝赋值运算符递增右侧运算对象的计数器，递减左侧运算对象的计数器。如果左侧运算对象的计数器变为0，意味着它的共享状态没有用户了，考呗赋值运算符就必须销毁状态
 */
HasPtr::~HasPtr()
{
    /**
     * @brief 类指针的拷贝成员"篡改"引用计数
     * 析构函数不能无条件地delete ps——可能还有其他对象指向这块内存。析构函数应该递减引用计数，指出共享string的对象少了一个。
     * 如果计数器变为0，则析构函数释放ps和use指向的内存
     * 
     */
    if (--*use == 0) //如果引用计数变为0
    {
        delete ps;  //释放string内存
        delete use; //释放计数器内存
        
    }
}
using namespace std;
int main()
{
    HasPtr p1("Hiya!");
    HasPtr p2(p1); // p1和p2指向相同的string
    HasPtr p3(p1); // p1,p2和p3都指向相同的string

    return 0;
}