#include <iostream>
int main()
{

    //currval是正在统计的数，读入的新值存入val
    int currval = 0, val = 0; //initial
    if (std::cin >> currval)
    {
        int cnt = 1; //保存我们正在处理的当前值的个数
        while (std::cin >> val)
        {
            if (val == currval)
            {
                ++cnt;
            }
            else
            {
                std::cout << currval << " occurs " << cnt << " times " << std::endl;
                currval = val;
                cnt = 1; //重新计数
            }
            std::cout << currval << " occurs" << cnt << " times " << std::endl;
        }
        return 0;
    }
