#include <iostream>
#include <algorithm>
#include <list>
//使用头文件memory
#include <memory>
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
     *
     */
}