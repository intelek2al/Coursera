#include <string>
#include <vector>
#include <iostream>
using namespace std;

#define UNIC_LINE_2(line) local_variable_##line
#define UNIC_LINE(line) UNIC_LINE_2(line)
#define UNIQ_ID UNIC_LINE(__LINE__)

// int main()
// {
//   int UNIQ_ID(__LINE) = 0;
//   string UNIQ_ID = "hello";
//   vector<string> UNIQ_ID = {"hello", "world"};
//   vector<int> UNIQ_ID = {1, 2, 3, 4};
// }
