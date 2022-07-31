#include <iostream>
#include <vector>
#include <list>
using namespace std;
/**
 * @brief 迭代器测试
 * 迭代器和容器一样有着公共的接口——一个迭代器提供某个操作，那么所有提供相同操作的迭代器对这个操作的实现方式都是相同的
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char const *argv[])
{
    /** 迭代器范围，由一对迭代器表示，两个迭代器分别指向同一个容器中的于是怒或者是尾元素之后的位置。这两个迭代器通常被成为
     * begin和end
     * 或者是first和last，这两个标记了容器中元素的一个范围
     */
    //注：第二个迭代器并不会指向的是尾部元素，而是指向尾部元素之后的位置，迭代器范围中的元素包含first所表示元素以及从first到last之间的所有元素
    //这种元素的范围被称为左闭合区间
    /**
     * @brief 对构成范围的迭代器的要求
     * 如果满足如下条件，两个迭代器begin和end构成一个迭代器范：
     * - 它们指向同一个容器中的元素，或者是容器最后一个元素之后的位置
     * - 我们可以通过反复递增begin来达到end。
     * 使用左闭合范围蕴含的编程假定
     * 标准库使用左闭合范围是因为这种范围有三种方便的性质。假定begin和end构成一个合法的迭代器范围，则
     * - 如果begin和end相等，则范围为空
     * - 如果begin和end不相等，则至少包含一个元素，且begin指向该范围中的第一个元素
     * - 我们可以对begin递增若干次，使得begin==end
     */
    // vector<int> v;
    // while (v.begin() != v.end())
    // {
    //     *begin = val;
    //     ++begin;
    // }
    // iter是通过list<string>定义的一个迭代器类型
    list<string>::iterator iter;
    //count是通过vector<int>定义的一个difference_type类型
    vector<int>::difference_type count;
    
    return 0;
}
