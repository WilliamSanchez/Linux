#include <iostream>
#include <thread>
#include <atomic>

//std::atomic<int> i = 0;  [123]
thread_local std::atomic<int> i = 0; //[111]

void foo()
{
  ++i;
  std::cout << i;
}



int main(){
 
  std::thread thread1(foo);
  std::thread thread2(foo);
  std::thread thread3(foo);


  thread1.join();
  thread2.join();
  thread3.join();
  
  printf("\nhello from main\n");
  return 0;
}




































