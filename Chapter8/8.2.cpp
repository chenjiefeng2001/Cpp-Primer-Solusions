#include <iostream>
using namespace std;
/**
 * @brief 文件输入和输出
 * 头文件fstream定义了三个类型来支持
 * - ifstream从一个给定文件读取数据
 * - ofstream向一个给定文件写入数据
 * - fstream可以读写给定文件
 */
/**fsteam特有的操作
 * fstream fstrm            创建一个未绑定的文件流，fstream是头文件fstream中定义的一个类型
 * fstream fstrm(s)         创建一个fstream，打开名为s的文件。s可以是string类型，或者是一个指向C风格字符串的指针。
 *                          这些构造函数都是explicit的。默认的文件模式mode依赖于fstream类型
 * fstream fstrm(s,mode)    与前一个构造函数类似，但按指定mode打开文件
 * fstrm.open(s)            打开一个名为s的文件，并将文件与fstrm绑定。s可以是一个string或者一个指向C风格字符串的指针。
 *                          默认的文件mode依赖于fstream的类型。返回void
 * fstrm.close()            关闭与fstrm绑定的文件。返回void
 * fstrm.isopen()           返回一个bool值，指出与fstrm关联的文件是否成功打开并且尚未关闭
 */

int main(int argc, char const *argv[])
{
    /**
     * @brief 使用文件流对象
     *
     */
    // ifstream in(ifile); //构造一个ifstream并打开给定文件
    // ofstream out;//输出流未关联到任何文件
    //用fstream代替iostream&
    
    return 0;
}
