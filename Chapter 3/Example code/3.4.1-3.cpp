#include <iostream>
#include <string>
#include <vector>

using std::vector;
using namespace std;

vector<int> v;
const vector<int> cv;
auto it1 = v.begin();//it1 类型为vector<int>::iteror
auto it2 = cv.begin();//it2 类型为vector<int>::const_iterator 