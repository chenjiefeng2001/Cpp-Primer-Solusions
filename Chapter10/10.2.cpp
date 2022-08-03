#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;
void elimDups(vector<string> &words)
{
    //按字典序排序words，以便查找重复单词
    sort(words.begin(),words.end());
    //unique重排输入范围，使得每个单词只出现一遍
    //排列再范围的前部，返回指向不重复区域之后一个位置的迭代器
    auto end_unique=unique(words.begin(),words.end());
    words.erase(end_unique,words.end());
    //标准库算法对迭代器而不是容器进行操作。因此算法不能直接添加或者删除元素
    /**
     * @brief 
     * 即使words没有重复单词，这样直接调用erase也是安全的。在此情况下，unique会返回words.end()。因此，传递给erase的两个参数具有相同的值：words.end()
     * 迭代器相等意味着传递给erase的元素范围为空。删除一个空范围没有什么不良后果
     */
}
int main()
{
    vector<int> vec = {10, 11, 12, 20, 30};
    int sum = accumulate(vec.begin(), vec.end(), 0);
    // accumulate 的三个参数的类型决定了函数中使用哪个加法运算符以及返回值的类型
    /**
     * @brief 只读算法
     * 一些算法只会读取其输入范围内的元素，而从不改变元素。find就是这样一种算法，count也是
     */

    /**
     * @brief 操纵两个序列的算法
     *
     *
     */
    vector<int> roster1 = {10, 20, 12, 203, 0};
    vector<int> roster2 = {2, 103, 203, 506, 0};
    equal(roster1.begin(), roster1.end(), roster2.begin());
    fill(vec.begin(), vec.end(), 0);
    fill(vec.begin(), vec.begin() + vec.size() / 2, 10);
    /**
     * @brief back_inserter
     * 一种保证算法有足够元素空间来容纳输出数据的方法是使用插入迭代器。插入迭代器是一种向容器中添加元素的迭代器。
     * 通常情况，当我们通过一个迭代器向容器元素赋值时，值呗赋予迭代器指向的元素。而当我们通过一个插入迭代器赋值时，一个赋值号右侧值相等的元素被添加进入容器中
     */
    // vector<int> vect;                     //空向量
    // auto it = back_insert_iterator(vect); //通过它赋值会将元素添加到vec中 //vec中现在有一个元素，值为42
    // fill_n(back_insert_iterator(vect), 10, 0);
    int a1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int a2[sizeof(a1) / sizeof(*a1)]; // a2与a1的大小一样
    auto ret = copy(begin(a1), end(a1), a2);
    /**
     * @brief copy返回的是其目的位置迭代器（递增后）的值。即，ret恰好指向拷贝a2尾元素之后的位置
     * 多个算法都提供所谓的拷贝版本。这些算法计算新元素的值，但不会将它们放置在输入序列的末尾，而是创建一个新的序列保存这个结果
     */
    //此调用将会将所有的0元素改为42
    vector<int> ilst = {12, 0, 0, 1, 102, 0, 1};
    // replace_copy(ilst.begin(),ilst.end(),0,42);
    /**
     * @brief 重拍容器元素的算法
     * 某些算法会重排容器中元素的顺序，一个明显例子是sort。调用sort会重排输入序列中的元素，使之有序，它是利用元素类型的<运算符来实现排序的
     *
     *
     */
    return 0;
}