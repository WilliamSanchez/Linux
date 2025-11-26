#include <iostream>
#include <thread>

void foo()
{
  printf("Hello from foo\n");
}


int main(){
 
  std::thread thread1(foo);

  if(thread1.joinable())
  {
    printf("Thread 1 is joinable before join\n");
  }else{
    printf("Thread 1 is not joinable before join\n");
  }

  thread1.join();

  if(thread1.joinable())
  {
    printf("Thread 1 is joinable after join\n");
  }else{
    printf("Thread 1 is not joinable after join\n");
  }
  
  std::thread thread2;

  if(thread2.joinable())
  {
    printf("Thread 2 is joinable before join\n");
  }else{
    printf("Thread 2 is not joinable before join\n");
  }

  printf("hello from main\n");
  return 0;
}




































