#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include <functional>
//引用_1
/**
 * @brief _n
 * _n类型都定义在一个名为placeholders的命名空间中，而这个命名空间本身定义在std命名空间。为了使用这些民资，两个命名空间都要写上
 * using namespace namespace_name
 * _n表示占位符，即回调函数的第n个参数
 * 这种形式说明希望所特有来自namespace_name的名字都可以在我们的程序中直接使用
 */
using std::placeholders::_1;
using namespace std;
/**
 * @brief 定制操作
 * 很多算法都会比较输入序列中的元素。默认情况下，这类算法使用元素类型的<或==运算符完成比较。标准库还为这些算法定义了额外的版本，允许我们提供自己定义的操作来代替默认的运算符
 */
//向算法传递函数
/**
 * @brief 谓词
 * 为此是一个可调用的表达式，其返回结果是一个能用做条件的值。
 * 标准库算法所使用的谓词分为两类：
 * - 一元谓词
 * - 二元谓词
 *
 */
bool isShorter(const string &s1, const string &s2)
{
    return s1.size() < s2.size();
}
void elimDups(vector<string> &words)
{
    //按字典序排序words，以便查找重复单词
    sort(words.begin(), words.end());
    // unique重排输入范围，使得每个单词只出现一遍
    //排列再范围的前部，返回指向不重复区域之后一个位置的迭代器
    auto end_unique = unique(words.begin(), words.end());
    words.erase(end_unique, words.end());
    //标准库算法对迭代器而不是容器进行操作。因此算法不能直接添加或者删除元素
    /**
     * @brief
     * 即使words没有重复单词，这样直接调用erase也是安全的。在此情况下，unique会返回words.end()。因此，传递给erase的两个参数具有相同的值：words.end()
     * 迭代器相等意味着传递给erase的元素范围为空。删除一个空范围没有什么不良后果
     */
}
string make_plural(size_t ctr, const string &word, const string &ending)
{
    return (ctr > 1) ? word + ending : word;
} //简单的三目运算符，这个是书里没提及的部分
ostream &print(ostream &os, const string &s, char c)
{
    return os << s << c;
}
void biggies(vector<string> &words, vector<string>::size_type sz)
{
    elimDups(words);
    stable_sort(words.begin(), words.end(), isShorter);
    //获取一个迭代器，指向第一个满足size()>=sz的元素
    //计算满足size>=sz的元素的数目
    //打印长度大于等于给定值的单词，每个单词后面接一个空格
    //使用捕获列表

    /**
     * lambda表达式以一对[]开始，我们可以在其中提供一个以逗号分隔的名字列表，这些名字都是它所在函数中定义的
     *一个lambda只有在其捕获列表中捕获一个它所在函数中的局部变量，才能在函数体中使用该变量
     */
    // auto check6 = bind(check_size, _1, 6);
    // string s = "hello";
    // bool b1 = check6(s);
    auto wc = find_if(words.begin(), words.end(), bind(check_size, _1, sz));
    /**
     * @brief bind参数
     * 我们可以用bind修正参数的值。更一般的，可以用bind绑定给定可调用对象中的参数或重新安排其顺序
     *
     */
    /**
     * 绑定引用参数
     * 默认情况下，bind的那些不是占位符的参数被拷贝到bind返回的可调用对象中。但是，与lambda类似，有时对有些绑定的参数我们希望以引用的方式传递，或是要绑定参数的类型无法拷贝
     * 例如向其中输入一个os，但是os总所周知是不能拷贝的，因此我们必须用标准库ref函数来进行传递
     */
    for_each(words.begin(), words.end(),
             bind(print, ref(os), _1, " "));
             
    /**
     * @brief 向后兼容：参数绑定
     * 旧版本C++提供的绑定函数参数的语言特性限制更多，也更复杂。标准库定义了两个分别名为bind1st和bind2nd的函数。
     * 类似bind，这两个函数接受一个函数作为参数，生成一个新的可调用的对象，改对象调用给定函数，并将绑定的参数传递给它。
     * 但是这两个函数只能绑定第一或者第二个参数。因此新版本对此弃用了，应该改为使用bind
     */
    
    // auto wc = find_if(words.begin(), words.end(),
    //                   [sz](const string &a)
    //                   { return a.size() >= sz; });
    //计算满足size>=sz的元素数目
    auto count = words.end() - wc;

    cout << count << " " << make_plural(count, "word", "s") << "of length" << sz << " or longer " << endl;
    //调用make_plural来决定是输出word还是words

    /**
     * @brief for_each算法
     * 此算法接受一个可调用对象，并对输入序列中每个元素调用此对象
     */
    for_each(wc, words.end(),
             [](const string &s)
             { cout << s << " "; });
    cout << endl;
    wc = find_if(words.begin(), words.end(),
                 [=](const string &s)
                 {
                     return s.size() >= sz;
                 });
}

void func1()
{
    size_t v1 = 42; //局部变量
    //将v1拷贝到名为f的可调用对象上
    auto f = [v1]
    { return v1; };
    v1 = 0;
    auto j = f(); // j为42;f保存了我们创建它时v1的拷贝
}
//引用捕获
void func2()
{
    size_t v1 = 42; //局部变量
    //对象f2包含v1的引用
    auto f2 = [&v1]
    { return v1; };
    v1 = 0;
    auto j = f2(); // j为0；f2保存v1的引用，而非拷贝，因此这里j=f2=v1=0
    /**
     * v1之前的&指出了以引用方式捕获。一个以引用方式捕获的变量与其它类型的引用行为类似。当我们在lambda函数体内使用此变量时
     * 实际上使用的是引用所绑定的对象。
     */
    //引用捕获与返回引用有着相同的问题和限制。如果我们采用引用方式捕获一个变量，就必须确保被引用的对象在lambda执行的时候一直存在。
}
/**
 * @brief 隐式捕获
 * 除了显式列出我们希望使用的来自所在函数的变量之外，还可以让编译器根据lambda表达式中的代码来进行推断我们要使用哪些变量
 */
/**
 * lambda捕获列表
 * []                           空捕获列表。lambda不能使用所在函数中的变量。一个lambda只有捕获变量之后才能使用他们
 * [names]                      names是一个逗号分隔的名字列表，这些名字都是lambda所在函数的局部变量。默认情况下，
 *                              捕获列表中的变量都被拷贝。名字前如果使用了&，则采用引用捕获方式
 * [&]                          隐式捕获列表，采用引用捕获的方式。lambda体中所使用的来自所在函数实体都采用使用
 * [=]                          隐式捕获列表，采用值捕获的方式。lambda体将拷贝所使用的来自所在函数的实体的值
 * [&,identifier_list]          identifier_list是一个逗号分隔额达列表，包含0个或多个来自所在函数的变量。这些变量
 *                              采用值捕获的方式，而任何隐式捕获的变量都采用引用的方式捕获。identifier_list中的名字前面不能使用&
 * [=,identifier_list]          identifier_list中的变量都采用引用方式捕获，而任何隐式捕获的变量都采用值方式捕获。identifier_list中的名字不能包括this，且这些名字之前都必须使用&
 */
/**
 * 可变lambda
 * 默认情况下，对于一个值被拷贝的变量，lambda不会改变其值。如果我们希望能改变一个被捕获的变量的值，就必须在参数列表首加上关键字mutable
 *
 */
void fucn3()
{
    size_t v1 = 42; //局部变量
    // f可以改变它所捕获的变量的值
    auto f = [v1]() mutable
    { return ++v1; };
    v1 = 0;
    auto j = f(); // j为43
}
//一个引用捕获的变量是否可以修改依赖于此引用指向的是一个const类型还是非const类型
void func4()
{
    size_t v1 = 42; //局部变量
    // v1是一个非const变量的引用
    //可以通过f2中引用来改变它
    auto f2 = [&v1]
    { return ++v1; };
    v1 = 0;
    auto j = f2(); // j为1
}
bool check_size(const string &s, string::size_type sz)
{
    return s.size() >= sz;
}
int main()
{
    vector<string> words = {"10", "102", "2034", "204", "68", "2034", "204"};
    sort(words.begin(), words.end(), isShorter);
    elimDups(words); //将words按字典序重排，并消除重复单词
    for (const auto &s : words)
    {
        cout << s << " "; //打印每个元素，以空格分隔
    }
    cout << endl;
    /**
     * @brief lambda表达式
     * 根据算法接受一元谓词还是二元谓词，我们传递给算法的谓词必须严格接受一个或者两个参数。
     * 但是有时候我们希望进行的操作需要更多的参数，超出了算法对谓词的限制。因此可以使用lambda表达式来进行传递
     */
    /**
     * lambda的捕获和返回
     * 当定义一个lambda时，编译器生成一个与lambda对应的新的类类型
     * 值捕获
     * 类似参数传递，变量的捕获方式也可以是值或引用。到目前为止，我们的lambda采用值捕获的方式。与传值参数类似，采用值捕获的i按提示变量可以拷贝。
     */
    vector<int> vi = {10, -10, 25, 30, -20, -103};
    transform(vi.begin(), vi.end(), vi.begin(), [](int i)
              { return i < 0 ? -i : i; });
    for (const auto &value : vi)
    {
        cout << value << endl;
    }
    /**
     * @brief 参数绑定
     * 对于那种只在一两个地方使用的简单操作，lambda表达式时最有用的。如果我们需要在很多地方使用相同的操作
     * 通常定义一个函数，而不是多次编写相同的lambda表达式。
     * 但是，如果我们在使用例如find_if之类的函数时，新建的函数并不能作为参数传入，所以我们必须解决如何向sz形参传递一个参数的问题
     */

    /**
     * @brief 标准库bind函数
     * 我们可以使用bind的标准库函数来解决向check_size传递一个长度参数问题
     * 调用形式：
     * auto newCallable=bind(callable,arg_list);
     */
    //绑定check_size的sz参数

    return 0;
}