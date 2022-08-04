#include <iostream>
#include <algorithm>
#include <numeric>
#include <functional>
#include <vector>
#include <list>
#include <iterator>
using namespace std::placeholders;
using namespace std;
/**
 * @brief 再探迭代器
 * 除了为每个容器定义的迭代器之外，标准库在头文件iterator中还定义了额外几种迭代器
 * - 插入迭代器:这些迭代器被绑定到一个容器上，可用来向容器插入元素
 * - 流迭代器:这些迭代器被绑定到输入或者输出流上，可用来遍历所关联的IO流
 * - 反向迭代器: 这些迭代器向后而不是向前移动。除了forward_list之外的标准库容器都有反向迭代器
 */
//插入迭代器
/**
 * @brief 插入迭代器操作
 * it=t                 在it指定的当前位置插入t。假定c是it绑定的容器，依赖于插入迭代器的不同种类，此赋值会分别调用
 *                      c.push+back(t)、c.push_front(t)、c.insert(t,p)，其中p为传递给inserter的迭代器位置
 * *it,++it,it++        这些操作虽然存在，但不会对it做任何事情。每个操作都返回it
 */

/**
 * @brief 插入器类型
 * - back_inserter      创建一个使用push_back的迭代器
 * - front_inserter     创建一个push_front的迭代器
 * - inserter           创建一个使用insert的迭代器。此函数接受第二个参数，这个参数必须是指向给定容器的迭代器
 *                      元素将被插入到给定迭代器所表示的元素之前
 */

/**
 * @brief front_inserter生成的迭代器
 * front_inserter生成的迭代器行为与inserter生成的迭代器不一样。当我们使用front_inserter时，元素总是插入到容器的第一个元素之前。
 * 即使我们传递给inserter的位置原来指向第一个元素，只要我们在此元素之前插入一个新元素，那么此元素就不再是容器的首元素了
 */
int main()
{
    // list<int> a1st = {1, 2, 3, 4};
    // list<int> a1st2, a1st3; //空list
    // //拷贝完成之后，a1st2包含4 3 2 1
    // copy(a1st.cbegin(), a1st.cend(), front_inserter(a1st2));
    // //拷贝完成之后，a1st3包含1 2 3 4
    // copy(a1st.cbegin(), a1st.cend(), inserter(a1st3, a1st3.begin()));
    // for (const auto &value : a1st)
    // {
    //     cout << value << endl;
    // }
    // for (const auto &value : a1st2)
    // {
    //     cout << value << endl;
    // }
    // for (const auto &value : a1st3)
    // {
    //     cout << value << endl;
    // }
    /**
     * @brief iostream迭代器
     * 虽然iostream类型不是容器，但是标准库定义了可以用于这些IO类型对象的迭代器。istream_iterator读取输入流
     * ostream_iterator向一个输出流写数据。
     * 这些迭代器将他们对应的流当作一个特定类型的元素序列来处理。通过使用流迭代器，我们可以用泛型算法从流对象读取数据
     * 以及向其写入数据
     */
    // istream_iterator操作
    // vector<int> vec;    //空vector
    // istream_iterator<int> int_iter(cin); //从cin读取int
    // istream_iterator<int> eof;           // istream尾后迭代器
    // while (int_iter != eof)
    // {
    //     //后置递增运算读取流，返回迭代器的旧值
    //     //解引用迭代器，获得从流读取的前一个值
    //     vec.push_back(*int_iter++);
    // }
    //此循环从cin读取int值，保存在vec中。在每个循环步中，循环体代码检查int_iter是否等于eof。（这里的eof被定义为空的istream_iterator）
    // 当然，也可以重写成以下形式:
    // istream_iterator<int> in_iter(cin), eof; //从cin读取int
    // vector<int> vec(in_iter, eof);
    // /**
    //  * @brief ostream_iterator操作
    //  * ostream_iterator<T> out(os);     out将类型为T的值写到输出流os中
    //  * ostream_iterator<T> out(os,d);   out将类型为T的值写道输出流os中，每个值后面都输出一个d。d指向一个空字符结尾的字符数组
    //  * out=val                          用<<运算符将val写入out绑定的ostream中。val的类型必须于out可写的类型兼容
    //  * *out,++out,out++;                这些运算符都是存在的，但不对out做任何事情，每个操作都返回out
    //  */
    // ostream_iterator<int> out_iter(cout, " ");
    // for (auto e : vec)
    //     *out_iter++ = e; //赋值语句实际上将元素写入cout
    // cout << endl;
    /**
     * @brief 反向迭代器
     * 反向迭代器就是在容器中从尾元素向首元素反向移动的迭代器。对于反向迭代器，递增（以及递减）
     * 的操作含义均会颠倒。并且除了forward_list之外的其他容器均支持此迭代器操作
     * 当然，此迭代器也分为const和非const版本
     *
     */
    vector<int> vec2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (auto r_iter = vec2.crbegin(); r_iter != vec2.crend(); ++r_iter)
    {
        cout << *r_iter << endl;
    }
    return 0;
}