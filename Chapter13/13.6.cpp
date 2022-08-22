#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
class StrVec
{
public:
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {} //显式初始化构造函数
    StrVec(StrVec &&);                                                 //移动构造函数
    StrVec(const StrVec &);                                            //拷贝构造函数
    StrVec &operator=(const StrVec &);                                 //拷贝赋值运算符
    StrVec &operator=(StrVec &&);                                      //移动赋值运算符
    void push_back(const std::string &);                               //拷贝元素
    size_t size() const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }
    std::string *begin() const { return elements; }
    std::string *end() const { return first_free; }
    ~StrVec();

private:
    static std::allocator<std::string> allocate;
    void chk_n_alloc()
    {
        if (size() == capacity())
            reallocate();
    }
    std::pair<std::string *, std::string *> alloc_n_copty(const std::string *, const std::string *); //工具函数，被拷贝构造函数，赋值运算符和析构函数所使用
    void free();                                                                                     //销毁元素以释放内存
    void reallocate();                                                                               //获得更多内存拷贝已有元素
    std::string *elements;
    std::string *first_free;
    std::string *cap;
};

pair<std::string *, std::string *>
StrVec::alloc_n_copty(const string *b, const string *e)
{
    //分配空间保存给定范围中的元素
    auto data = allocate.allocate(e - b);
    //初始化并返回一个pair，该pair由data和uninitialized_copy的返回值构成
    return {data, uninitialized_copy(b, e, data)};
}

void StrVec::push_back(const string &s)
{
    chk_n_alloc();
    //在first_free 指向的元素中构造s的副本
    allocate.construct(first_free++, s);
    /**
     *  当我们使用allocator分配内存时，必须记住内存是为构造的，为了使用此原始内存，我们必须调用construct，在此构造一个对象。
     *  值得注意的是，调用construct也会增加first_free的引用计数，这不是废话吗)
     *
     */
}
void StrVec::free()
{
    //不能传递给deallocate一个空指针，不然就throw_exception
    if (elements)
    {
        for (auto p = first_free; p != elements;)
        {
            allocate.destroy(--p);
        }
        allocate.deallocate(elements, cap - elements);
    }
}
// StrVec::StrVec(const StrVec &s)
// {
//     //调用alloc_n_copy分配空间以容纳与s一样多的元素
//     auto newdata = alloc_n_copty(s.begin(), s.end());
//     elements = newdata.first;
//     first_free = cap = newdata.second;
//  }
StrVec::~StrVec()
{
    free();
}
StrVec &StrVec::operator=(const StrVec &rhs)
{
    //调用alloc_n_copy分配内存，大小与rhs中元素占用空间一样多
    auto data = alloc_n_copty(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}
StrVec &StrVec::operator=(StrVec &&rhs) noexcept
{
    //直接检测自赋值
    if (this != &rhs)
    {
        free();                  //释放已有的元素
        elements = rhs.elements; //    从rhs接管资源
        first_free = rhs.first_free;
        cap = rhs.cap;
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    //在这里直接去检查了this指针与rhs的地址是否相同。如果相同，右侧和左侧运算对象指向相同的对象，我们无需做其他的任何事情。
    //否则，我们释放左侧运算对象所使用的内存，并接管给定对象的内存
    return *this;
}
/**
 * @brief 移后源对象必须可析构
 * 从一个对象移动数据并不会销毁此对象，但有时在移动操作完成之后，源对象会被销毁，因此，我们编写一个移动操作时，
 * 必须确保移后源对象进入一个可析构的状态。
 * 除了将移后源对象设置为析构安全的状态之外，移动操作还必须保证对象仍然是有效的。
 *
 *
 */
//在移动操作之后，移后源对象必须保持有效的、可析构的状态，但是用户不能对其值做任何的假设
void StrVec::reallocate()
{
    //我们将分配当前大小两倍的空间
    auto newcapacity = size() ? 2 * size() : 1;
    //分配新内存
    auto newdata = allocate.allocate(newcapacity);
    //将数据从旧内存中移动到新内存
    auto dest = newdata;  //指向新数组中下一个空闲位置
    auto elem = elements; //指向旧数组中的下一个位置
    for (size_t i = 0; i != size(); ++i)
    {
        allocate.construct(dest++, std::move(*elem++));
    }
    free(); //一旦我们完成移动，那么立即释放旧内存空间
    //更新我们的数据结构，执行新元素
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}
/**
 * @brief 右值引用
 * 为了支持移动操作，新标准定义了一种新的引用类型——右值引用
 * 所谓的右值引用就是必须绑定到右值的引用。我们通过&&而不是&来获得右值引用
 * 右值引用的重要性质——只能绑定到一个将要销毁的对象。
 * 右值引用的代码可以自由地接管所引用的对象的资源
 * 右值引用指向将要被销毁的对象。因此，我们可以从绑定到右值引用的对象"窃取"状态
 */
//标准库move函数
StrVec::StrVec(StrVec &&s) noexcept : elements(s.elements), first_free(s.first_free), cap(s.cap)
{
    s.elements = s.first_free = s.cap = nullptr;
    //不抛出异常的移动构造函数和移动赋值运算符必须标记为noexcept
    /**
     * @brief 移动构造函数和移动拷贝赋值运算符
     * 类似string类，如果我们自己的类也同时支持移动和拷贝，那么也能从中受益，为了让我们自己的类也支持移动操作，
     * 需要为其定义移动过构造函数和移动赋值运算符。这两个成员类似对应的拷贝操作，但它们从给定对象"窃取"资源而不是拷贝资源
     * 最终，移后源对象将被销毁，这意味着我们得在其上边运行析构函数。
     */
} //移动操作
/**
 * @brief 标准库与自定义的类型交互
 * 两个相互关联的事实:
 * - 首先，虽然移动操作通常不抛出异常，但抛出异常也是允许的
 * - 其次，标准库容器能对异常发生时其自身的行为提供保障
 * 潜在问题:移动一个对象通常会改变它的值，如果重新分配过程使用了移动构造函数，且在移动了部分而不是全部元素后抛出了一个异常
 * 就会产生问题。旧空间中的元素已经被改变了，而新空间中未构造的函数可能尚不存在。在此情况下，vector可能不能满足自身保持不变的要求
 */
//合成的移动操作
struct X
{
    int i;         //内置类型可以移动
    std::string s; // string定义了自己的移动操作
};
struct hasX
{
    X mem;
};
X x, x2 = std::move(x);       //使用合成的移动构造函数
hasX hx, hx2 = std::move(hx); //使用合成的移动构造函数
/**
 * 只有当一个类没有定义任何自己版本的拷贝控制成员，且它的所有数据成员都能移动构造或者移动赋值时，
 * 编译器才会为它合成移动构造函数或移动赋值运算符
 */
/**
 * 与拷贝构造函数不同，移动操作永远不会隐式地定义为删除的函数。但是，如果我们显式地要求编译器生成=default的移动操作，且编译器
 * 不能移动所有成员，则编译器会将移动操作定义为删除的函数。除了第一个重要的例外，什么时候将合成的移动操作定义为删除的函数遵循与
 * 定义删除合成拷贝操作类似的原则:
 * - 与拷贝构造函数不同，移动构造函数被定义为删除的函数的条件时:有类成员定义了自己的拷贝狗战术且未定义移动构造函数，或者是有类成员未定义自己的
 *   拷贝构造函数且编译器无法为其合成移动构造函数。移动赋值运算符的情况与移动构造函数类似
 * - 如果有类成员的移动构造函数或者移动赋值运算符被定义为删除或者是不可访问的，则类的移动构造函数或移动赋值运算符将被定义为删除的
 * - 类似拷贝构造函数，如果类的析构函数被定义为删除的或不可访问的，则eider移动构造函数被定义为删除的
 * - 类似考呗赋值运算符，如果有类成员时const的或是引用，则类的移动赋值运算符被定义为删除的
 *
 * 移动操作和合成的拷贝控制成员还有最后一个相互作用的关系: 一个类是否定义了自己的移动操作对拷贝操作如何合成有影响。
 * 定义了一个移动构造函数或移动赋值运算符的累必须定义了自己的拷贝操作。否则，这些成员默认地被定义为删除的
 */

using namespace std;
int main()
{
    int &&rr1 = 42; //正确，字面值常量是定值
    /**
     * 虽然我们不能将一个右值引用直接绑定到一个左值上，但是我们可以显式地将一个左值转换为对应的
     * 右值引用类型
     * 调用move函数以为之恶，除了对rr1赋值或销毁它之外，我们将不再使用它。
     * 在调用move函数之后，我们不能对移后源对象做任何假设
     * 我们可以销毁一个移后源对象，也可以赋予它新值，但不能使用一个移后源对象的值
     */
    int &&rr3 = std::move(rr1); //正确
}