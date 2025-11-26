#pragma once

#include <iostream>
#include <thread>
#include <chrono>
#include "common.h"

void foo()
{
  printf("Hello from foo\n");
}

void other_operations()
{
  std::cout<<"This is other operation\n";
  throw std::runtime_error("This is a runtime error");
}

int main(){

  std::thread foo_thread(foo);

  thread_guard tg(foo_thread);
  try
  {
    other_operations();
  }catch(...){}

  return 0;
}