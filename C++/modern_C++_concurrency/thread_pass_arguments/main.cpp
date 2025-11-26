#include <iostream>
#include <thread>

void sum(int x, int y)
{
  printf("x + y = %d\n", x + y);
}

void func(int &x)
{
  while(true)
  {
    printf("Thread 1 valye of X - %d\n",x);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
}

int main(){
 
 int p = 9;
 int q = 25;
 int x = 5;
 //std::thread thread1(sum, p, q);
 //sthread1.join();

  printf("Main thread value of x - %d\n",x);
  std::thread thread2(func, std::ref(x)); 
  std::this_thread::sleep_for(std::chrono::milliseconds(5000));

  x = 15;
  printf("Main thread value ox x - %d\n",x);
  thread2.join();

  printf("hello from main\n");
  return 0;
}




































