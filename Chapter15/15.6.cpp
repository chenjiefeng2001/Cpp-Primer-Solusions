#include <iostream>
#include <string>
#include <vector>

class Base {
public:
  Base();
  ~Base();
  void isbn();
  virtual int fcn();

protected:
};
class D1 : public Base {
public:
  //隐藏基类的fcn，这个fcn不是虚函数
  // D1继承了Base::fcn()的定义
  int fcn(int);      //形参列表与Base中的fcn不一致
  virtual void f2(); //是一个新的虚函数，在Base中不存在
};
class D2 : public D1 {
public:
  int fcn(int); //是一个非虚函数，隐藏了D1::fcn(int)
  int fcn();    //覆盖了Base的虚函数fcn
  void f2();    //覆盖了D1的虚函数f2
  // D1的fcn虚函数并没有覆盖Base的虚函数fcn，原因是其形参列表不同，实际上，
  // D1的fcn将隐藏Base的fcn。此时拥有了两个名为fcn的函数：一个是D1从Base继承而来的虚函数fcn；另一个是D1自己定义的接受一个int参数的非虚函数fcn
};
class Quote {};
class Disc_quote : public Quote {};
class Bulk_quote : Base {};
/**
 * @brief 在编译时进行名字查找
 * 一个对象、引用或者指针的静态类型决定了该对象的哪些成员是可见的。即使静态类型与动态类型可能不一致
 * 但是我们能使用哪些成员仍然是由静态类型决定的。
 */
//名字冲突与继承
//和其他作用域一样，派生类也能重用定义在其直接基类或间接基类种的名字，此时定义在内层作用域的名字将隐藏定义在外层作用域的名字
struct Base2 {
  Base2() : mem(0) {}

protected:
  int mem;
};
struct Derived2 : Base2 {
  Derived2(int i) : mem(i) {} //用i初始化Derived2::mem
  // Base2::mem进行默认初始化
  int get_mem() { return mem; }                   //返回的是Derived2::mem
  int get_base2_mem(int i) { return Base2::mem; } //用域作用符来控制返回的成员

protected:
  int mem; //隐藏基类中的mem
           //派生类的成员将隐藏同名的基类成员
};
/**
 * @warning 关键概念 名字查找和继承
 * 理解函数调用的解析过程对于理解C++的继承至关重要，假定我们调用p->mem()，则依次执行以下四个步骤
 * - 首先确定p的静态类型。因为我们调用的是一个成员，所以该类型必然是类类型
 * -
 * 在p的静态类型对应的类中查找mem。如果找不到，则一次在直接基类中不断查找直至达到继承链的顶端。如果找遍了该类及其基类仍然找不到，
 *   则编译器将报错
 * -
 * 一旦找到了mem，就进行常规的类型检查亿确认对于当前找到的mem，本次调用是否合法
 * - 假设调用合法，则编译器将根据调用的是否是虚函数而产生不同的代码
 *   -
 * 如果mem是虚函数且我们是通过引用或指针进行的调用，则编译器产生的代码将在运行时确定到底运行该函数的哪个版本，依据是对象的动态类型
 *   -
 * 反之，如果mem不是虚函数或者我们是通过对象进行的调用，则编译器将产生一个常规函数调用
 */
struct Base3 {
  int memfcn();
};
struct Derived3 : Base3 {
  int mmemfcn(int); //隐藏基类memfcn
};
Derived3 d;
Base3 b;
/**
 * @brief 虚函数与作用域
 * 假如基类与派生类的虚函数接受的实参不同，则我们就无法通过基类的引用或指针调用派生类的虚函数了
 */

using namespace std;
int main() {
  Bulk_quote bulk;
  // cout << bulk.isbn();
  /**
   * @brief 名字isbn的解析过程
   * -
   * 因为我们是通过Bulk_quote的对象调用isbn的，所以首先在Bulk_quote种查找，这一步没有找到isbn
   * -
   * 因为Bulk_quote是Disc_quote的派生类，所以接下来在Disc_quote中查找，仍然找不到
   * - 因为Disc_quote是Quote的派生类，所以接着查找Quote种的isbn
   */
  //通过基类调用隐藏的虚函数
  Base bobj;
  D1 d1obj;
  D2 d2obj;
  Base *bp1 = &bobj, *bp2 = &d1obj, *bp3 = &d2obj;
  bp1->fcn(); //虚调用，将在运行时调用Base::fcn
  bp2->fcn(); //虚调用，将在运行时调用Base::fcn
  bp3->fcn(); //虚调用，将在运行时调用D2::fcn
  D1 *d1p = &d1obj;
  D2 *d2p = &d2obj;
  // bp2->f2();  //错误:Base没有名为f2的成员
  d1p->f2(); //虚调用，将在运行时调用D1::f2()
  d2p->f2(); //虚调用，将在运行时调用D2::f2()
  //前三条调用语句是通过基类的指针进行的，因为fcn是虚函数，所以编译器产生的代码将在运行时确定使用虚函数的哪个版本。判断的依据是该指针所绑定的对象的
  //真实类型。
  //覆盖重载函数
  /*
   * 和其他函数一样，成员函数无论是否是虚函数都能被重载。派生类可以覆盖重载函数的0个或多个实例。如果派生类希望所有的重载版本对于它来说是可见的，那么它就需要覆盖所有的版本，或者一个版本也不覆盖
   * 有时一个类仅需覆盖重载集合中的一些而非全部函数，此时，如果我们不得不覆盖基类中的每一个版本的话，显然操作将极其繁琐
   * 一种好的解决方案是为重载的成员提供一条using声明语句，这样我们就无须覆盖基类中的每一个重载版本了。
   * using 声明语句指定一个名字而不指定形参列表，
   */
}
