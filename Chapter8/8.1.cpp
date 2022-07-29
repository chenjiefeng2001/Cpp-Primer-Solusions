// IO标准库
#include <iostream>
using namespace std;
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

/** @brief 管理条件状态
 * 流对象的rdstate成员返回一个iostate值，对应流的当前状态，setstate操作将给定条件位置位，表示发生了对应的错误。
 * clear成员是一个重载的成员：它有一个不接受参数的版本，而另一个版本接受一个iostate类型的参数
 */
int main(int argc, char const *argv[])
{
    printf("hello world");
    cout << "hi!" << endl;  //输出hi和一个换行，然后刷新缓冲区
    cout << "hi!" << flush; //输出hi，然后刷新缓冲区，不附加任何额外字符
    cout << "hi!" << ends;  //输出hi和一个空字符，然后刷新缓冲区
    /**
     * @brief unitbuf 操纵符
     * 如果想在每次输出操作后都刷新缓冲区，可以使用unitbuf操纵符
     *
     */
    cout << unitbuf; //所有输出操作后都会立刻刷新缓冲区
    cout << nounitbuf;//回到正常的缓冲方式
    /**
     * @brief 关联输入和输出流
     * 当一个输入流被关联到一个输出流时，任何试图从输入流读取数据的操作都会先刷新关联的输出流。
     * 交互式系统通常应该关联输入流和输出流。这意味着所有的输出，包括用户提示的信息，都会在读操作之前被打印出来
     */
    /** @brief tie
     * tie有两个版本，一个是不带参数，返回指向输出流的指针。如果本对象当前关联到一个输出流，则返回的就是指向这个流的指针，如果对象未关联到流，则返回空指针。
     * 第二个版本接受一个指向ostream的指针，将自己关联到此ostream
     */
    return 0;
}
