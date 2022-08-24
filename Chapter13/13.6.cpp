#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <set>
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
    void push_back(const std::string &); //拷贝元素
    void push_back(std::string &&);      //移动元素

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
//拷贝并交换赋值运算符和移动操作
class HasPtr
{
public:
    HasPtr(HasPtr &&p) noexcept : ps(p.ps), i(p.i) { p.ps = 0; }
    // 既是拷贝构造函数，也是移动构造函数
    HasPtr &operator=(HasPtr rhs)
    {
        std::swap(*this, rhs);
        return *this;
        /**
         * @brief 建议:更新三/五法则
         * 所有五个拷贝控制成员应该看作一个整体:一般来说，如果一个类定义了任何一个拷贝操作，它就应该定义所有五个操作。
         * 如前所述，某些类必须定义拷贝构造函数、拷贝赋值运算符和析构函数才能正常工作。这些类通常拥有一个资源，而拷贝成员必须拥有此成员。
         * 一般来说，拷贝一个资源会导致一些额外的开销。在这种拷贝非必要的情况下，定义了移动构造函数和移动赋值运算符的累就可以避免此问题
         */
    }

private:
    int ps;
    int i;
};
/**
 * @brief Message 类的移动操作
 * 定义了自己的拷贝构造函数和拷贝赋值运算符的类通常也会从移动操作中受益。
 *
 */
class Message
{
public:
    // folder被隐式初始化为空集合
    explicit Message(const std::string &str = " ") : contents(str) {}
    //拷贝控制成员，用来管理指向本message的指针
    Message(const Message &);
    Message(Message &&);
    Message &
    operator=(const Message &);
    Message &
    operator=(Message &&);
    ~Message();
    //从给定的Folder中添加，删除本Message
    void save(Folder &);
    void remove(Folder &);
    void move_Folders(Message *);

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
void Message::move_Folders(Message *m)
{
    folders = std::move(m->folders);
    for (auto f : folders)
    {                //对每个folder
        f->remMsg(); //从Folder中删除
        f->addMsg(); //将本Message添加到Folder中
    }
    m->folders.clear(); //确保销毁m是无害的
}
void StrVec::push_back(const std::string &s)
{
    chk_n_alloc(); //确保有空间容纳新的元素
    //在first_free指向的元素中构造s的一个副本
    allocate.construct(first_free++, s);
}
void StrVec::push_back(std::string &&s)
{
    chk_n_alloc(); //确保有足够的空间
    allocate.construct(first_free, std::move(s));
}
//这两个成员几乎都是相同的，差别在于右值引用版本使用了move函数来将其参数传递给construct
/**
 * @brief 移动迭代器
 * 新标准库中定义了一种移动迭代器适配器
 * 一个移动迭代器通过改变给定迭代器的解引用运算符的行为来适配次迭代器。一般来说，一个迭代器的解引用运算符返回一个元素的左值
 * 与其他迭代器不同，移动迭代器的解引用运算生成一个右值引用
 *
 */
Message::Message(Message &&m) : contents(std::move(m.contents))
{
    move_Folders(&m); //移动Folders并更新Folder是指针
}
Message &Message::operator=(Message &&rhs)
{
    if (this != &rhs)
    {
        remove_from_Folders();
        contents = std::move(rhs.contents); //移动赋值运算符
        move_Folders(&rhs);                 //重置Folders指向本Message
    }
    return *this;
}
/**
 * @warning 不要随意使用移动操作
 * 由于一个移后源对象具有不确定的状态，对其调用std::move是相当危险的。当我们调用move时，必须绝对确认移后源对象没有其他用户
 * 通过在类代码中小心地使用move，可以大幅提升性能。而如果随意在普通用户代码(与类实现代码相对)中使用移动操作，很可能导致莫名
 * 奇妙的、难以查找的错误，而难以提升应用程序的性能
 */
/**
 * 除了构造函数和赋值运算符之外，如果一个成员函数同时提供拷贝和移动版本，它也能从中受益。这种允许移动的成员函数通常使用与
 * 拷贝/移动构造函数和赋值运算符相同的参数模式——一个版本接受一个指向const的左值引用，第二个版本接受一个指向非const的右值引用
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
    //如果一个类既有移动构造函数，也有拷贝构造函数，那么编译器将会按照普通函数的匹配规则来确定使用的是哪个构造函数。赋值操作也是类似
    StrVec v1, v2;
    v1 = v2;                    // v2是左值;使用拷贝赋值
    StrVec getVec(istream &);   // getVec返回一个右值
    v2 = getVec(cin);           // getVec(cin)是一个右值；使用移动赋值
    int &&rr3 = std::move(rr1); //正确
    //若一个类有拷贝构造函数而未定义移动构造函数，在此情况下，编译器不会合成移动构造函数，而是直接使用拷贝构造函数来
    //代替掉移动构造函数(即使使用move来试图移动也是一样的)
    //这种用拷贝构造函数来代替移动构造函数几乎肯定是安全的。因为在一般情况下，拷贝构造函数满足对应的移动过构造函数的要求:
    //它会拷贝给定的对象，并将原对象置于有效的状态。实际上，拷贝构造函数甚至都不会改变原对象的值
    //如果一个类有一个可用的拷贝构造函数而没有移动构造函数，则其对象是通过拷贝构造函数来"移动"的。拷贝赋值运算符和移动赋值运算符的情况类似
}