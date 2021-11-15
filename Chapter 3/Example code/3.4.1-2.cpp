#include <iostream>
#include <vector>
#include <string>

using std::vector;

//迭代器类型
vector<int>::iterator it;        //it能读写vector<int>的元素
std::string::iterator it2;       //it2能读写string对象中的字符
vector<int>::const_iterator it3; //it3只能读元素，不能写元素

