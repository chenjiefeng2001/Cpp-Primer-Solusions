//含有可变形参的函数
#include <iostream>
#include <initializer_list>
using namespace std;
using std::initializer_list;
int main()
{
    /**
     * @brief 使用initializer_list形参
     * 如果函数的实参数量未知但是全部实参的类型都一致，那么可以使用initializer_list类型的实参。
     * initalizer_list提供的操作
     * initilizer_list<T> list;          默认类型初始化：T元素的空列表
     * initilizer _list<T> list{a,b,c,...};         list的元素数量和初始值一样多：list元素是对应初始值的版本，列表中的元素是const
     * list2(list)或者list=list                           拷贝或者赋值一个initlizer_list元素对象不会拷贝到列表中的元素，拷贝之后原始列表和副本共享这个元素（也就是说两边都可以动这个元素，真好）
     * list.size()                      列表中的元素数量
     * list.begin()                     返回指向list中首元素的指针
     * list.end()                       返回指向list中尾元素下一位置的指针
     */
    initializer_list<string> ls;//initializer 的元素类型是string
    initializer_list<
}
