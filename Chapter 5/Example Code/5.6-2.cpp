#include <iostream>
#include <errno.h>
using namespace std;
int main()
{
    int item1, item2;
    while (cin >> item1 >> item2)
        try
        {
            //执行添加两个Sales_item对象的代码
            //如果添加失败，代码会抛出一个runtime_error异常错误
        }
        catch (runtime_error &err)
        {
            //提醒用户两个ISBN必须一致，询问是否重新输入
            cout << err.what()
                 << "\n Try Again? Enter y or n" << endl;
            char c;
            cin >> c;
            if (!cin || c == 'n')
                break;
            
        }
}
