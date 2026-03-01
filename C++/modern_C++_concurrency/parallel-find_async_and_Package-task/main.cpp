#pragma once

#include <iostream>
#include <execution>
#include <chrono>

#include "parallel_find.h"
#include "utils.h"

const size_t testeSize = 1000;

using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::milli;

int main()
{
  std::vector<int> ints(testeSize);

  for(size_t i=0; i < testeSize; i++)
  {
    ints[i]=i;
  }

  int looking_for = 50000000;

auto startTime = high_resolution_clock::now();
auto value = parallel_find_pt(ints.begin(),ints.end(), looking_for);
auto endTime = high_resolution_clock::now();
print_results("Parallel-package_task_imp:       ",startTime,endTime);

startTime = high_resolution_clock::now();
std::find(ints.begin(),ints.end(), looking_for);
endTime = high_resolution_clock::now();
print_results("STL-Sequential:       ",startTime,endTime);

startTime = high_resolution_clock::now();
std::find(std::execution::par, ints.begin(),ints.end(), looking_for);
endTime = high_resolution_clock::now();
print_results("STL-Parallel-par:       ",startTime,endTime);

startTime = high_resolution_clock::now();
std::find(std::execution::seq, ints.begin(),ints.end(), looking_for);
endTime = high_resolution_clock::now();
print_results("STL-Parallel-seq:       ",startTime,endTime);


return 0;
}

