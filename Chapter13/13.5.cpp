#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <utility>
using namespace std;
/**
 * @brief StrVec——vector的简化版本
 * 先使用一个allocator来分配足够的大段内存，然后再使用三个指针成员来指向其元素所使用的内存
 * - elements       指向分配的内存中的首元素
 * - first_free     指向最后一个实际元素之后的位置
 * - cap            指向分配的内存末尾之后的位置
 */

class StrVec
{
public:
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {} //显式初始化构造函数
    StrVec(const StrVec &);                                            //拷贝构造函数
    StrVec &operator=(const StrVec &);                                 //拷贝赋值运算符
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
StrVec::StrVec(const StrVec &s)
{
    //调用alloc_n_copy分配空间以容纳与s一样多的元素
    auto newdata = alloc_n_copty(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}
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
int main()
{
    return 0;
}