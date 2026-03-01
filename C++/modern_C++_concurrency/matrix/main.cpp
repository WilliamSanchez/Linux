#pragma once

#include <iostream>
#include <functional>
#include <iterator>
#include <numeric>
#include <vector>
#include <execution>
#include <chrono>

#include "matrix.h"
#include "utils.h"

const size_t testeSize = 1000;

using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::milli;

void perfomance_test_multiplicy()
{
  const int matrix_size = 1000;
  Matrix A(matrix_size,matrix_size);  
  Matrix B(matrix_size,matrix_size);
  Matrix C(matrix_size,matrix_size);
  Matrix D(matrix_size,matrix_size);

  A.set_all(1);
  B.set_all(1);

  auto startTime = high_resolution_clock::now();
  Matrix::multiplicy(&A,&B,&C);
  auto endTime = high_resolution_clock::now();
  print_results("Sequential matrix multiplication ", startTime, endTime);

  startTime = high_resolution_clock::now();
  Matrix::parallel_multiplicy(&A,&B,&C);
  endTime = high_resolution_clock::now();
  print_results("Parallel matrix multiplication ", startTime, endTime);

}

void perfomance_test_transpose()
{
  const int matrix_size = 1000;
  Matrix A(matrix_size,matrix_size);  
  Matrix B(matrix_size,matrix_size);

  A.set_all(1);

  auto startTime = high_resolution_clock::now();
  Matrix::transpose(&A,&B);
  auto endTime = high_resolution_clock::now();
  print_results("Sequential matrix transpose ", startTime, endTime);

  startTime = high_resolution_clock::now();
  Matrix::parallel_traspose(&A,&B);
  endTime = high_resolution_clock::now();
  print_results("Parallel matrix transpose ", startTime, endTime);

}

int main()
{
  
  //perfomance_test_multiplicy();
  perfomance_test_transpose();
  return 0;
}

