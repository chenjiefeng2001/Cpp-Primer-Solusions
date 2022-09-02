#include <iostream>
#include <vector>
// 构造函数与拷贝控制
//和其他类一样，位于继承体系中的类也需要控制当其对象执行一系列操作时会发生什么样的行为
/**
 * @brief 虚析构函数
 * 继承关系对基类拷贝控制最直接的影响是基类通常该定义一个虚析构函数，这样我们就能动态分配内存了
 *
 *
 *
 */
class Quote {
public:
  //如果我们删除的是一个指向派生类对象的基类指针，则需要虚析构函数
  virtual ~Quote() = default; //动态绑定析构函数
};
class Bulk_quote : public Quote {
public:
  Bulk_quote() = default;
};
int main(int argc, char *argv[]) { /*code here*/
  Quote *itemP = new Quote;        //静态类型与动态类型一致
  delete itemP;                    //调用Quote的析构函数
  itemP = new Bulk_quote;          //静态类型与动态类型不一致
  delete itemP;                    //调用Bulk_quote的析构函数
  //虚析构函数对于之前有关析构函数的经验准则并不适用
  //如果基类的析构函数不是虚函数，则delete一个指向派生类对象的基类指针将产生未定义的行为
  return 0;
}