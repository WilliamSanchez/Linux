#include <iostream>
#include <thread>
#include <chrono>

void foo()
{
  printf("Hello from foo\n");
}

void bar()
{
  printf("Hello from bar\n");
}

int main(){
 
  std::thread thread1(foo);
  std::thread thread2 = std::move(thread1);

  thread1 = std::thread(bar);

  thread1.join();
  thread2.join();
  
  printf("hello from main\n");

  return 0;
}




































