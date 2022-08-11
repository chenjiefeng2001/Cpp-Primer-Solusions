#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
//使用头文件memory
#include <memory>
#include <string>
using namespace std;
/**
 * @brief 动态内存
 * 除了自动和static对象外，C++还支持动态分配对象。动态分配的对象的生存期与它们在哪里创建
 * 是无关的，只有当显式地被释放时，这些对象才会被销毁
 */
/**
 * 除了静态内存和栈内存，每个程序还拥有一个内存池。这部分内存被称作自由空间或堆。程序用堆来存储动态分配的对象
 */

/**
 * @brief 智能指针
 * 为了更容易地使用动态内存，新标准提供了两种智能指针类型来管理动态对象。
 * 智能指针的行为类似常规指针，区别在于它负责自动释放所指向的对象。新标准库提供的这两种
 * 智能指针的区别在于管理底层指针的方式：
 * - shared_ptr允许多个指针指向同一个对象
 * - unique_ptr则"独占"所指向的对象
 * 除了这两种之外，还定义了一个weak_ptr对象，它是一种弱引用，指向shared_ptr所管理的对象
 */

shared_ptr<string> p1;    // shared_ptr，可以指向string
shared_ptr<list<int>> p2; // shared_ptr，可以指向int的list
//在默认初始化中每个智能指针中都会保存有一个空指针
//智能指针与普通指针使用方式类似。解引用一个智能指针返回它所指向的对象。如果在一个条件判断中使用
//智能指针，则可以检测是否为空指针

class StrBlob
{
public:
    typedef std::vector<std::string>::size_type size_type;
    StrBlob(/* args */);
    StrBlob(std::initializer_list<std::string> il);
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    void push_back(const std::string &t) { data->push_back(t); }
    void pop_back();
    std::string &front();
    std::string &back();
    ~StrBlob();

private:
    std::shared_ptr<std::vector<std::string>> data;
    //如果data[i]不合法，则抛出一个异常
    void check(size_type i, const std::string &msg) const;
};

StrBlob::StrBlob(/* args */) : data(make_shared<vector<string>>())
{
}
StrBlob::StrBlob(initializer_list<string>(il)) : data(make_shared<vector<string>>(il))
{
}
StrBlob::~StrBlob()
{
}

void StrBlob::check(size_type i, const string &msg) const
{
    if (i >= data->size())
        throw out_of_range(msg);
}
string &StrBlob::front()
{
    //如果vector为空，check会抛出一个异常·1
    check(0, "front on empty StrBlob");
    return data->front();
}
string &StrBlob::back()
{
    check(0, "back on the empty StrBlob");
    return data->back();
}
void StrBlob::pop_back()
{
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}
// data(make_shared<vector<string>>(il));
// {
//     /* data */
// };
// vector<string> v1;
// {
//     vector<string> v2 = {"a", "an", "the"};
// }

struct Foo
{
public:
    Foo() = default;
};

void contest(int *args)
{
    /**
     * @brief 指针值和delete
     * 传递给delete的指针必须指向动态分配的内存，或者是一个空指针
     * delete会释放一块而非new分配的内存，或者将相同的指针值释放多次，其行为是未定义的
     */

    int i, *pi1 = &i, *pi2 = nullptr;
    double *pd = new double(33), *pd2 = pd;
    // delete i; //错误，并非为完整的指针
    delete pi1; //未定义:pi1指向一个局部变量
    delete pd;  //正确
    delete pd2; //未定义:pd2指向的内存已经被释放了
    delete pi2; //正确，pi2指向一个空指针，并且释放空指针总是没有错误的
    //释放一个const对象
    const int *pci = new const int(1024);
    delete pci;
    //动态对象的生存周期直到被释放为止
    /**
     * 由shared_ptr管理的内存在最后一个shared_ptr销毁时会自动被释放掉，但是对于内置指针类型来管理的内存并不是这样。
     * 对于一个由内置指针管理的动态对象，直到被显式释放之前都是存在的
     */
    /**
     * 小心：动态内存的管理非常容易出错
     * 使用new和delete管理动态内存存在三个常见问题：
     * - 忘记delete内存。忘记释放动态内存常常会导致人们常说的"内存泄漏"问题，因为这种内存永远不可能被归还给自由空间了。查找内存泄漏是十分困难的
     *   因为通常程序运行很长时间之后，真正耗尽内存时，才能检测得到这种错误
     * - 使用已经释放掉的对象。通过在释放内存后将指针置为空，有时可以检测出这种错误
     * - 同一块内存释放两次。当有有两个指针指向相同的动态分配对象时，可能发生这种错误。如果对其中一个指针进行了delete操作，对象的内存就被归怀给自由
     *   空间了。如果我们随后又delete了第二个指针，自由空间就可能被破坏
     */
}
/**
 * delete之后重置指针值
 * 当我们delete一个指针之后，指针值就会变为无效值了，虽然变成了无效值，但是很多机器时尚指针仍然保存着动态内存的地址，只不过delete之后
 * 指针就变成了人们所说的空悬指针，即指向一块曾经保存数据对象但是现在已经无效的内存指针
 */

/**
 * @brief 智能指针和普通指针不要混合使用
 * shared_ptr 可以协调对象的析构，但这仅限于其自身的拷贝之间
 * 这也是为啥不推荐使用new生成智能指针而是推荐使用make_shared
 *
 */

void process(shared_ptr<int> ptr)
{
    /**
     * process的参数是传值的方式传递的，因此会被拷贝到ptr中。拷贝一个shared_ptr会递增其引用计数，因此，在process运行过程中，引用计数至少为2
     * 当process结束时，ptr的引用计数会递减，但不会变为0。因此，当局部变量ptr被摧毁时，ptr指向的内存不会释放
     *
     */
    //使用ptr
    //因此正确的做法是传递给process函数一个shared_ptr而不是内置指针
} // ptr离开作用域，被销毁

int main()
{
    if (p1 && p1->empty())
        *p1 = "Hi"; //如果p1指向一个空string，解引用p1,将一个新值赋予string
    /**
     * shared_ptr和unique_ptr都支持的操作
     * shared_ptr<T> sp;        智能空指针，可以指向类型为T的对象
     * unique_ptr<T> up;
     * p                        将p用作一个条件判断，若p指向一个对象，则为true
     * *p                       解引用p，获得它指向的对象
     * p-> mem                  等价于(*p).mem
     * p.get()                  返回p中保存的指针。（要小心使用，因为如果智能指针已经释放了对象，则返回的指针所指向的对象是没有的）
     * swap(p,q)                交换p和q中的指针
     * p.swap()
     *
     * shared_ptr独有的操作
     * make_shared<T>(args)     返回一个shared_ptr,指向一个动态分配的对象。使用args初始化对象
     * shared_ptr<T>p(q)        p是一个shared_ptr q的拷贝；此操作会递增q中的计数器。q中的指针必须能转换为T*
     * p=q                      p和q都是shared_ptr，所保存的指针必须能够互相转换。此操作会递减p的引用计数，递增q的引用计数；若p的引用计数变为0，则会将其管理的原内存释放
     * p.unique()               若p.use_count()为1，返回true，否则返回false
     * p.use_count()            返回与p共享对象的智能指针的数量；(主要用于调试，不建议用在release上，因为实在是太慢了)
     */
    //指向一个值为42的int的shared_ptr
    shared_ptr<int> p3 = make_shared<int>(42);
    // p4指向一个值为"9999999"的string
    shared_ptr<string> p4 = make_shared<string>(10, '9');
    // p5指向一个值初始化的int
    shared_ptr<int> p5 = make_shared<int>();
    // p6指向一个动态分配的空vector<string>
    auto p6 = make_shared<vector<string>>();
    // shared_ptr 的拷贝和赋值
    /**
     * 当进行拷贝或者赋值操作时，每个shared_ptr都会记录有多少个其他shared_ptr
     * 指向相同的对象
     */
    auto p = make_shared<int>(42);
    auto q(p); // p和q都指向相同的对象，此对象有两个引用者
    //递增引用计数器的方法:
    /**
     * - 用一个shared_ptr去初始化另一个shared_ptr
     * - 将它作为参数传递给一个函数
     * 作为参数的返回值
     */
    //当一个shared_ptr的引用计数器变为0，则自动释放指向的对象
    auto r = make_shared<int>(42); // r指向的int只有一个引用者
    r = q;                         //给r赋值，令它指向另一个地址
                                   //递增q指向的对象的引用计数
                                   //递减r原来指向的对象的引用计数
                                   // r原来指向的对象已经没有引用者，所以会自动释放
                                   //到底是一个计数器还是其他数据结构来记录有多少指针共享对象，完全由标准库的具体实现来决定，这并不是重点，关键是
                                   //是智能指针类能记录有多少个shared_ptr指向相同的对象，并能够在恰当的时候自动释放对象
    // shared_ptr自动销毁所管理的对象
    // factory返回一个shared_ptr，指向一个动态分配的对象
    // shared_ptr<Foo> factory(T arg)
    // {
    //     //恰当地处理arg
    //     // shared_ptr 负责释放内存
    //     return make_shared<Foo>(arg)
    // }
    /**
     * @brief shared_ptr自动摧毁所管理的对象
     * 当指向一个对象的最后一个shared_ptr被摧毁时，shared_ptr类会自动销毁此对象。(这是通过析构函数来完成的)
     * 析构函数通常用来释放对象所分配的资源
     * shared_ptr的析构函数会递减它所指向的对象的引用计数。当变为0时就会释放
     *
     * 当然，他也会自动释放相关联的内存，当该对象不再使用时，shared_ptr会自动释放所占的对象
     * 由于在最后一个shared_ptr销毁内存之前都不会释放，所以应该保证shared_ptr在无用之后不再保留就非常重要了。
     * 如果你忘记销毁程序不再需要的shared_ptr，程序仍会正确执行，但是内存会被浪费掉
     *
     * shared_ptr在无用之后仍然保留的一种情况:
     * 你将shared_ptr存放在一个容器中，随后重排了容器，从而不再需要某些元素。在这种情况下，你应该确保用erase删除那些不再需要的shared_ptr元素
     */

    /**
     * @brief 使用了动态生存期的资源的类
     * 使用原因：
     * - 程序不知道自己需要使用多少对象
     * - 程序不知道所需对象的准确类型
     * - 程序需要在多个对象之间共享数据
     */
    /**
     * 直接管理内存
     * C++语言定义了两个运算符来分配和释放动态内存。
     * - new用来分配内存
     * - delete 释放new分配的内存
     */
    // int *pi = new int;
    //此new表达式在自由空间构造一个int型对象，并返回指向该对象的指针
    /**
     * 默认情况下动态分配的对象是默认初始化的，这意味着内置类型或组合类型的对象的值将是未定义的·1，
     * 而类类型对象用默认构造函数进行初始化
     */
    string *ps = new string;          //初始化为空string
    int *pi = new int;                // pi指向一个·1未初始化的int
    int *pi = new int(1024);          // pi指向的对象的值为1024
    string *ps = new string(10, '9'); //*ps为"9999999999"s
    // vector有十个元素，值依次从0到9
    vector<int> *pv = new vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    //也可以选择动态分配
    string *ps1 = new string;   // 默认初始化为空string
    string *ps2 = new string(); //值初始化为空string
    int *pi1 = new int;         //默认初始化；pi1的值未定义
    int *pi2 = new int();       //值初始化为0，pi2为0;
    /**
     * 对于定义了自己的构造函数的类类型来说，要求值初始化是没有意义的。因为不管采用什么形式的初始化，对象都会通过默认构造函数来初始化
     * 但是对于内置类型，两种形式的差别非常大，值初始化的内置类型对象有着良好的定义的值，而默认初始化的对象的值则是未定义的。类似的，
     * 对于类中那些依赖于编译器合成的默认构造函数的内置类型成员，如果它们未在类内被初始化，那么它们的值也是未定义的
     */
    auto p4 = new auto(*p1); // p指向一个与p1相同的对象
    //动态分配的const对象
    //分配并初始化一个const int
    const int *pci = new const int(1024);
    //分配并默认初始化一个const的空string
    const string *pcs = new const string;
    /**
     * @brief 内存耗尽
     * 虽然现代计算机通常配备有很大的内存，但是也是有可能在某些特定情况下被耗尽的，一旦耗尽内存，new表达式初始化就会失败
     * 这时new就会抛出一个类型位bad_alloc的异常，我们可以改变使用new的方式来阻止抛出异常
     */
    //如果分配失败，new返回一个空指针
    int *p1 = new int;           //如果分配失败，则会抛出std::bad_alloc
    int *p2 = new (nothrow) int; //如果分配失败，则会返回一个空指针
    //这种形式的new称为定位new
    //定位new表达式允许我们向new传递额外参数。

    /**
     * @brief Shared_ptr 和new结合使用
     *  如果我们不初始化一个智能指针，它就会初始化为一个空指针。
     */
    shared_ptr<double> ptest;            // shared_ptr 可以指向一个double
    shared_ptr<int> ptest2(new int(42)); // ptest2指向一个值为42的int
    //接受指针参数的智能指针构造函数是explicitr的。因此，我们不能将一个内置指针隐式的转换为一个智能指针，必须使用直接初始化形式
    shared_ptr<int> ptest3(new int(1024)); //正确，使用了直接初始化的形式
                                           /**
                                            * @brief get函数的使用
                                            * 智能指针定义了一个名为get的函数，它返回一个内置指针，指向智能指针管理的对象。此函数是为了这样一种情况而设计的:
                                            * 我们需要向不能使用智能指针的代码传递一个内置指针。使用get返回的指针的代码不能delete此指针
                                            */
    shared_ptr<int> p(new int(1024));      //引用计数为1
    int *q = p.get();                      //正确，但是使用q的时候要注意不能让它管理的指针被释放
    {
        //新程序块
        //未定义:两个独立的shared_ptr指向相同的内存
        shared_ptr<int>(q);
    } //程序块结束，q被销毁，它指向的内存被释放
    /**
     * get用来将指针的访问权限传递给代码，你只有在确定代码不会delete指针的情况下，才能使用get。特别是，永远不要使用get初始化另一个智能指针或者为另一个智能指针赋值
     */
    //其他shared_ptr操作
    p.reset(new int(1024));
    // reset会更新引用计数，如果需要的话，会释放p所指向的对象。reset成员常与unique一起使用，来控制多个shared_ptr对象
    //在进行改变底层对象之前，我们需要检查自己是否是当前对象的仅有的用户，如果不是，在改变之前需要制作一份新的拷贝
    //  if(!p.unique())
    //      p.reset(new string(*p));
    /**
     * @brief 智能指针异常
     * 如果使用智能指针，即使程序块过早结束，智能指针类也能确保在内存不再需要时将其释放
     * 函数的推出有两种可能:正常处理结束或者发生了异常，无论发生那种情况，局部对象都会被销毁。
     * 如果在被销毁前就抛出异常并且没被捕获到，那么这块内存就永远没法被销毁了
     */

    return 0;
}
/**
 * @brief 定义和改变shared_ptr的其他方法
 * shared_ptr<T> p(q)       p管理内置指针q所指向的对象;q必须指向new分配的内存，且能够转换为T*的类型
 * shared_ptr<T> p(u)       p从unique_ptr u那里接管了对象的所有权;将u置为空
 * shared_ptr<T> p(q,d)     p接管了内置指针q所指向的对象的所有权。q必须能够转换为T*的类型。p将使用可调用对象d来代替delete
 * shared_ptr<T> p(p2,d)    p是shared_ptr p2的拷贝，唯一的区别是p将用而代替对象d来代替delete
 * p.reset()                若p是唯一指向其所选对象的shared_ptr，reset会释放此对象，若传递了可选参数内置指针q，会令p指向q，否则会将q置为空。若还传递了参数d，将会调用d而不是
 *                          用delete来释放q
 */

/**
 * @brief 智能指针陷阱
 * 智能指针可以提供对动态分配的内存安全而又方便的管理，但这建立在正确使用的前提下。为了正确使用智能指针，我们必须坚持一些规范：
 * - 不使用相同的内置指针值初始化(或reset)多个智能指针，
 * - 不delete get() 返回的指针
 * - 不使用get()初始化或reset另一个智能指针
 * - 如果你用get()返回的指针，记住当最后一个对对应的智能指针销毁后，你的指针就变为无效了
 * - 如果你使用智能指针管理的资源不是new分配的内存，记住传递给它一个删除器
 */
