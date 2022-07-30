#include <iostream>
#include <fstream>
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
    ofstream out1, out2;

    /**
     * @brief 使用文件流对象
     *
     */
    // ifstream in(ifile); //构造一个ifstream并打开给定文件
    // ofstream out;//输出流未关联到任何文件
    //用fstream代替iostream&

    /**
     * @brief 文件模式——用于指出如何使用文件
     * in       以只读的方式打开
     * out      以写的方式打开
     * app      每次打开写操作前均ing为到文件末尾
     * ate      打开文件后立即定位到文件末尾
     * trunc    截断文件
     * binary   以二进制方式进行io
     *
     * 但是指定文件模式有如下限制：
     * - 只可以对ofstream或fstream对象设定out模式
     * - 只可以对ifstream或fstream对象设定in模式
     * - 只有当out也被设定时才可以设定trunc模式
     *
     */

    /**
     * @brief 自动构造和析构
     *
     *
     */
    int process(bool test)
    {
        return 0;
    }
    for (auto p = argv + 1; p != argv + argc; p++)
    {
        ifstream input(*p); //创建输出流并打开文件
        if (input)          //如果文件打开成功，"处理"此文件
        {
            process(input);
        }
        else
            cerr << "counldn't open:" + string(*p);
    } //每个循环步input都会离开作用域，因此会被销毁
    /**
     * @brief 以out模式打开文件会丢弃已有的数据
     * 在默认情况下，当我们打开一个ofstream时，文件的内容会被丢弃，阻止一个ofstream清空给定文件内容的方法时同时指定app模式
     *
     */
    // 在这几条语句中，file1都会被截断
    ofstream out("file1"); //隐含以输出模式打开文件并截断文件
    ofstream out2("file1", ofstream::out);
    ofstream out3("file1", ofstream::out | ofstream::trunc);
    //为了保留文件内容，必须显式地指定app模式
    ofstream app("file2", ofstream::app); //隐含为输出模式
    ofstream app2("file2", ofstream::out | ofstream::app);
    // 调用open时都会确定文件模式
    //对于一个给定流，每次打开文件时，都可以改变其模式
    ofstream out;                        //未指定打开模式
    out.open("scratchpad");              //模式隐含设置为输出和截断
    out.close();                         //关闭out，以便我们将其用于其他文件
    out.open("precious", ofstream::app); //模式为输出和追加
    out.close();
    return 0;
}
