#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
//使用头文件memory
#include <memory>
#include <string>

using namespace std;
/**
 * @brief unique_ptr
 * 一个unique_ptr“拥有”它所指向的对象，与shared_ptr不同，某个时刻只能有一个unique_ptr指向一个给定的对象
 * 当unique_ptr被销毁时，它所指向的对象也会被销毁(也就是说，这个是一个映射指针，即一对一绑定的)
 * 与shared_ptr不同，没有类似make_shared的标准库函数返回一个unique_ptr。当我们定义了一个unique_ptr时，需要将其绑定到一个new返回的
 * 的指针上
 *
 */
unique_ptr<int> p1;                  //可以指向一个int的unique_ptr
unique_ptr<int> ptest2(new int(42)); // p2指向一个值为42
unique_ptr<string> ptest(new string("Stegosaurus"));
/**
 * @brief 删除器
 * 默认情况下，shared_ptr假定它们指向的是动态内存。因此当一个shared_ptr
 */
//由于一个unique_ptr拥有它所指向的对象，因此unique_ptr不支持普通的拷贝或者赋值操作
/**
 * @brief unique_ptr支持的操作
 * unique_ptr<T> u1;        空unique_ptr，可以指向类型为T的对象，会使用delete来释放它的指针;
 * unique_ptr<T,D>  u2;     u2会使用一个类型为D的可调用对象来释放它的指针
 * unique_ptr<T,D> u(d);    空unique_ptr，指向类型为T的对象，用类型为D的对象来代替delete
 * u=nullptr;               释放u指向的对象，将u置为空
 * u.release();             u放弃对指针的控制权，返回指针，并将u置为空
 * u.reset();               释放u所指向的对象
 * u.reset(q);              如果提供了内置指针q，令u指向这个对象;否则置为空
 * u.reset(nullptr);
 */
//传递unique_ptr和返回unique_ptr
//不能拷贝unique_ptr的规则有个例外:我们可以拷贝或者赋值给一个将要被销毁的unique_ptr
unique_ptr<int> clone(int p)
{
    //正确:从int*创建一个unique_ptr<int>
    return unique_ptr<int>(new int(p));
}
int main()
{
    unique_ptr<string> p2(ptest.release()); //将控制权转移给p2
    unique_ptr<string> p3(new string("Trex"));
    // reset释放了
    p2.reset(p3.release());
    // release成员返回unique_ptr当前保存的指针并将其置为空。因此，p2被初始化为p1原来保存的指针，而p1被置为空
}