#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <list>
#include <iterator>
using namespace std;
/**
 * @brief 泛型算法结构
 * 任何算法的最基本特性时它要求其迭代器提供哪些操作。
 */
/**
 * 迭代器类别
 * 输入迭代器           只读，不写；单遍扫描，只能递增
 * 输出迭代器           只写，不读；单遍扫描，只能递增
 * 前向迭代器           可读写；多遍扫描，只能递增
 * 双向迭代器           可读写；多变扫描，可递增递减
 * 随机访问迭代器       可读写；多遍扫描，支持全部迭代器运算
 */

/**
 * @brief 迭代器类别
 * - 输入迭代器:可以读取序列中的元素。一个输入迭代器必须支持
 *      - 用于比较两个迭代器的相等和不相等的运算符(==,!=)
 *      - 用于推进迭代器的前置和后置递增运算符(++)
 *      - 用于读取元素的解引用运算符(*):解引用只会出现在赋值运算符的右侧
 *      - 箭头运算符(->),等价于（*it).member，即解引用迭代器，并提取兑现的个成员
 * 输入迭代器只用于顺序访问。对于一个输入迭代器，*it++保证是有效的，但递增它可能导致所有其他指向流的迭代器失效
 * 其结果就是，不能保证输入迭代器的状态可以保存下来并用来访问元素。
 * 因此输入迭代器只能使用单遍扫描算法
 * - 输出迭代器:可以看作输入迭代器功能上的补集——只写而不读元素。输出迭代器必须支持
 *      - 用于推进迭代器的前置和后置递增运算
 *      - 解引用运算符(*),只出现在赋值运算符的左侧(向一个已经解引用的输出迭代器赋值，就是将值写入它所指向的元素)
 * 我们只能向一个输出迭代器赋值一次。类似输入迭代器，输出迭代器只能用于单遍扫描算法。用作目的位置的迭代器通常都是输出迭代器。
 * - 前向迭代器: 可以读写元素。这类迭代器只能在序列中沿一个方向移动。前向迭代器支持所有输入和输出迭代器的操作，而且可以多次读写同一个元素。因此，我们可以保存前向迭代器的状态，
 *               使用前向迭代器的算法可以对序列进行多遍扫描。
 * - 双向迭代器: 可以正向\反向读写序列中的元素。除了支持所有前向迭代器的操作之外，双向迭代器还支持前置和后置递减运算符(--)
 * - 随机访问迭代器: 提供在常量时间内访问序列中任意元素的能力
 *      - 用于比较两个迭代器相对位置的关系运算符(<,<=,>,>=)
 *      - 迭代器和一个整数数值的加减运算(+,+=,-和-=)，计算结果是迭代器在序列中前进(或后退)给定证书个元素后的位置
 *      - 用于两个迭代器上的减法运算符(-)，得到两个迭代器的距离
 *      - 下标运算符iter[n],与*(iter[n])等价
 */

/**
 * @brief  算法形参模式
 * 在任何其他算法分类之上，还有一组参数规范。
 * - alg(beg,end,other args);
 * - alg(beg,end,dest,other args);
 * - alg(beg,end,beg2,other args);
 * - alg(beg,end,beg2,end2,other args);
 */
int main()
{
    return 0;
}