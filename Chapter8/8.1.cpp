// IO标准库
#include <iostream>
/**
 * @brief
 * - istream (输入流)类型，提供输入操作
 * - ostream (输出流)类型，提供输出操作
 */
/**
 *IO 类
 * - iostream :
 *      - istream, wistream 从流读取数据
 *      - ostream,wostream  从流写入数据
 * - fstream :
 *      - ifstream,wifstream 从文件读取数据
 *      - ofstream，wofstream 从文件写入数据
 * - sstream :
 *      - istringstream,wistringstream 从string读取数据
 *      - ostringstream,wostringstream 从string写入数据
 *      - stringstream,wstringstream 读写string
 * 为了支持使用宽字符的语言，标准库定义了一组类型和对象来操纵wchat_t类型的数据。宽字符版本的类型和函数以一个w开始。‘
 */
/**
 * IO类型间的关系
 *  概念上，设备类型和字符大小都不会影响我们要执行的IO操作。
 * 标准库可以让我们忽略那些不同类型的流之间的差异，这是通过继承机制实现的。
 *
 */
// io对象不能做拷贝或赋值
//因为不能拷贝IO对象，所以我们不能将形参设置成流类型
//进行IO操作的函数通常以引用方式传递和返回流，。读写一个IO对象回改变其状态，因此传递和返回是不能是const的

/**
 * @brief 条件状态
 * IO库条件状态
 * strm::iostate    strm是一种io类型，iostate是一种机器相关的类型，提供了表达状态条件的完整功能
 * strm::badbit     strm::badbit用来指出流已经崩溃
 * strm::failbit    strm::failbit用来指出一个IO操作失败了
 * strm::eofbit     strm::eofbit用来指出到达了文件结束
 * strm::goodbit    strm::goodbit用来指出流位处于错误状态，此值保证为0
 * s.eof()          若s的eofbit的置位，则返回true
 * s.fail()         若流s的failbit或badbit置位，则返回true
 * s.bad()          若流s的badbit置位，则返回true
 * s.good()         若流s处于有效状态，则返回true
 * s.clear()        将流s中所有的条件状态复位，将流的状态设置为有效
 * s.clear(flags)   根据给定的flags标志位，将流的状态设置为有效。返回void根据给定的flags标志位，将流s中对应条件状态位复位。flags
 *                  的类型欸strm::iostate。返回void
 * s.setstate(flags)根据给定的flags标志位，将流s中对应条件状态位置位。flags的类型为strm::iostate。返回void
 * s.rdstate()      返回流s的当前状态，返回值类型为strm::iostate
 */

int main(int argc, char const *argv[])
{
    printf("hello world");
    return 0;
}
