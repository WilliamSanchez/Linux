#include <iostream>
#include <thread>
#include <stdexcept>

#include "parallel_accumulate.h"


int main(){
 
  const int size = 10000;
  int *my_array = new int[size];
  int ref = 0;

  srand(0);

  for(size_t i = 0; i<size; i++)
  {
    my_array[i] = rand()%10;
  }

  int rer_val = parallel_accumulate<int*, int>(my_array, my_array + size, ref);
  std::cout << "final result "<< rer_val << std::endl;

  return 0;
}




































