/**
 * @file 5.2.cpp
 * @author chenjiefeng2001(1497735430@qq.com)
 * @brief 语句作用域
 * @version 0.1
 * @date 2021-11-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <vector>
#include <iostream>
#include <string>
using namespace std;
using std::vector;
//if,switch,while 和for语句中的控制结构只有在控制结构的变量中，只有在这些语句的作用域中变量才是有效的科，一旦语句结束那么这个范围也就停止了
int main()
{
    /**
     * @brief if 语句和if else语句的形式
     * if (cobdition)
     *      statement
     * if (condition)
     *      statement1
     * else
     *      statement2
     */
    int grade;
    const vector<string> scores = {"F", "D", "C", "B", "A", "A++"};
    string lettergrade;
    if (grade < 60)
        lettergrade = scores[0];
    else
    {
        lettergrade = scores[(grade - 50) / 10];
        if (grade % 10 > 7)
            lettergrade += "+"; //末尾是把或者就的成绩添加一个加号
        else if (grade % 10 < 3)
            lettergrade += "-"; //末尾是0，1，，1的乘积添加以恶搞减号
    }
}