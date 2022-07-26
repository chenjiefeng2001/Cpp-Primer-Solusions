#include <iostream>
using namespace std;
//类成员声明的名字查找

int main(int argc, char const *argv[])
{
    printf("heloo world");

    return 0;
}
/**
 * @brief 名字查找步骤
 * - 首先，再名字所在的块中部寻找其声明语句，只考虑在名字的使用之前出现的声明
 * - 如果没找到，那么继续查找外层的作用域
 * - 如果最终没有找到匹配的声明，则程序报错
 */
//在外围作用域寻找时，尽管外层的对象被隐藏了，但是仍然可以使用作用域运算符访问它

/**
 * @brief 成员初始化的顺序
 * 构造函数的初始值列表只说明用于初始化成员的值，并不限定初始化的具体执行顺序
 * 但是如果一个成员的初始化是用另一个成员来初始化实现的，那么就必须考虑初始化顺序了
 * 所以最好令构造函数初始值的顺序与成员生命的顺序一致。并且如果可能的话，尽量避免使用某些成员初始化其他成员
 */

/**
 * @brief 默认实参和构造函数
 *
 *
 */

/**
 * @brief 聚合类
 * - 所有成员都是public的
 * - 没有定义任何构造函数
 * - 没有类内初始值
 * - 没有基类，也没有virtual函数
 */

/**
 * @brief 显式初始化类的对象的成员的缺点：
 * - 要求类的所有成员都是public的
 * - 将正确初始化每个对象的成员的重任交给了类的用户。
 * - 添加或者删除一个成员之后，所有的类的初始化语句都需要更新
 *
 */

/**
 * @brief constexpr构造函数
 * 虽然构造函数不能是const，但是字面值常量的构造函数可以是constexpr函数。
 */
class debug
{
public:
    constexpr debug(bool b = true) : hw(b), io(b), other(b) {}
    constexpr debug(bool h, bool i, bool o) : hw(h), io(i), other(o) {}
    constexpr bool any() { return hw || io || other; }
    void set_io(bool b) { io = b; }
    void set_hw(bool b) { hw = b; }
    void set_other(bool b) { other = b; }

private:
    bool hw;            //硬件错误
    bool io;            //io错误
    bool other;         //其他错误
};