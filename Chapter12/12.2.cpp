#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory>
using namespace std;
/**
 * @brief 动态数组
 * new和delete运算符一次分配/释放一个对象，但某些应用需要一次为很多对象分配内存的功能。
 * 为了支持这种需求，C++语言和标准库提供了两种一次分配一个对象数组的方法。C++定义了另
 * 一个名为allocator的类，允许我们将分配和初始化分离。使用allocator通常会提供更好的性能
 * 和更灵活的内存管理能力。
 *
 */
// new和数组
size_t get_size()
{
}
int main()
{
    int *pa = new int[get_size()];
    typedef int arrT[42]; //分配一个42个int的数组;p指向第一个int
    //由于分配的内存并不是一个数组类型，因此不能对动态数组调用begin或者end。并且也不能使用for来直接调用动态数组中的元素
    //动态数组并不是一种数组类型。它只是一种内存的分配方式
    int *pia = new int[10];          // 10个未初始化的int
    int *pia2 = new int[10]();       // 10个值未初始化为0的int
    string *psa = new string[10];    // 10个空string
    string *psa2 = new string[10](); // 10个空string
    // 在新标准中，我们还可以提供一个元素初始化器的花括号列表
    int *pia3 = new int[10]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    // 10个string,前四个用给定的初始化器初始化，剩余的进行值初始化
    string *psa3 = new string[10]{"a", "an", "the", string(3, 'x')};
    /**
     * @brief
     * 与内置数组对象的列表初始化一样，初始化器会用来初始化动态数组，如果初始化数目小于元素数目，剩余元素将进行值初始化。
     * 如果初始化器数目大于元素数目，则new表达式失败，不会分配任何的内存。
     */
    //动态分配一个空数组是合法的
    size_t n = get_size();
    int *p = new int[n]; //分配数组保存元素
    for (int *q = p; q != p + n; ++q)
        //处理数组
        /**
         * @brief get_size()返回0
         * 代码仍能正常工作，但是我们不能创建一个大小为0的静态数组对象
         */
        //释放动态数组
        //为了释放动态数组，我们使用一种特殊形式的delete——在指针前面加上一个空方括号对
        delete p; // p必须指向一个动态分配的对象或为空
    delete[] pa;  // pa必须指向一个动态分配爹数组或为空
    //当我们释放一个指向数组的指针时，空方括号对时必须的:它指示编译器此指针指向一个对象数组的第一个元素。
    //即不管外表如何，p必须指向一个对象数组的首元素，而不是一个类型为arrT的单一对象
    /**
     * @warning
     * 如果我们在delete一个数组指针时忘记了方括号，或者在delete一个单一对象的指针时使用了方括号，编译器很可能不会给出
     * 警告。但是我们的程序会在执行过程中突然出现异常
     */
    //智能指针和动态数组
    //标准库提供了一个可以管理new分配的数组的unique_ptr版本。为了用一个unique_ptr管理动态数组，我们必须在对象类型后面跟一对空方括号
    unique_ptr<int[]> up(new int[10]); // up包含指向int的10个未初始化数组
    up.release();                      //自动用delete[]销毁其指针
    /**
     * @brief 指向数组的unique_ptr
     * 指向数组的unique_ptr不支持成员访问运算符(点和箭头运算符)
     * 其他unique_ptr操作不变
     * unique_ptr<T[]> u            u可以指向一个动态分配的数组，数组元素类型为T
     * unique_ptr<T[]> u(p)         u指向内置指针p所指向的动态数组分配的数组。p必须能转换为类型T*
     * u[i]                         返回u拥有的数组中位置i处的对象，但是前提是u必须指向一个数组
     */
    /**
     * @brief allocator类
     * new分配内存有一定的灵活性上的局限性，其中一方面表现在它将内存分配和对象组合在了一起。类似的，delete
     * 将对象析构和内存释放组合在一起。我们分配单个对象时，通常希望将内存分配和对象初始化组合在一起。因为在
     * 这种情况下，我们几乎肯定知道对象应该有什么值
     *
     * 当分配一大块内存时，我们通常计划在这块内存上按需构造对象。在此情况下，我们希望将内存分配和对象构造分离
     * 这意味着我们可以分配大块内存，但只在真正需要时才真正执行对象创建操作(伴随一定开销)
     */
    string *const test = new string[n]; //构造一个空string
    string s;
    string *test2 = test; // test2指向test
    while (cin >> s && test2 != test + n)
    {
        /* code */
        *test2++ = s;
    }
    const size_t size = test2 - test; //记住我们读取了多少个string
    delete[] test;
    // allocator类
    allocator<string> alloc; //可以分配string的allocator对象
    // auto const p = alloc.deallocate(n); //分配n个未初始化的string
    /**
     * @brief 标准库allocator类及其算法
     * allocator<T> a           定义了一个名为a的allocator对象，它可以为类型为T的对象分配内存
     * a.allocate(n)            分配一段原始的、未构造的内存，保存n个类型为T的对象
     * a.deallocate(p,n)        释放从T*指针p中地址开始的内存，这块内存保存了n个类型为T的对象;p必须是一个先前由allocate返回的指针，
     *                          且n必须是p创建时所要求的大小。在调用deallocate之前，用户必须对每个在这块内存中创建的对象调用destroy
     * a.conststruct(p,args)    p必须是一个类型为T*的指针，指向一块原始内存;arg被传递给类型为T的构造函数，用来在p指向的内存中构造一个对象
     * a.destroy(p)             p为T*类型的指针，此算法对p指向的对象执行析构函数
     */
    // allocator分配未构造的内存
    auto p = test;  //q指向最后构造的元素之后的位置
    alloc.construct(q++);
    alloc.construct(q++,10,'c');

    return 0;
}