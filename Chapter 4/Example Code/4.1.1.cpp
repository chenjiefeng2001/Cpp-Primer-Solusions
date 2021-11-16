#include <iostream>
using namespace std;
int main()
{
    /**
     * 左值和右值在C++中比C中稍微复杂那么一点点，一个左值表达式的结果是一个对象或者是一个函数，然而常量对象为代表的某些左值实际上并不能作为赋值语句的左侧运算对象。并且某些的求值结果虽然是对象，但是却是右值，所以按以下的方法进行粗滤的区分
     * - 赋值运算符需要一个（非常量）左值作为器左侧的运算对象，得到的结果也仍然是一个左值
     * - 取地址符作用于一个左值运算对象，返回一个指向该运算对象的指针，这个指针是一个右值
     * - 内置解引用运算符、下标运算符、迭代器解引用运算符、string和vector的下标运算符的求值结果都是左值
     * - 内置类型和迭代器的递增递减运算符作用于左值运算对象，其迁至版本所得的的结果也是左值
     */
    cout << (6 + 3) * (4 / 2 + 2) << endl;
    cout << ((6 + 3) * 4) / 2 + 2 << endl;
    cout << 6 + 3 * 4 / (2 + 2) << endl;
    
    return 0;
}