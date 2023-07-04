#include <iostream>
#include <thread>
#include <mutex>

std::mutex m1,m2;

void task_a()
{
  while(1)
  {
     std::lock(m1,m2);
//     m1.lock();
//     m2.lock();
     std::cout << "task a\n";
     m1.unlock();
     m2.unlock();
  }

  
}

void task_b()
  {
    while(1)
    {
      std::lock(m2,m1);
//     m2.lock();
//     m1.lock();
      std::cout << "task b\n";
      m2.unlock();
      m1.unlock();
    }
  }


int main()
{
  std::thread th1(task_a);
  std::thread th2(task_b);
  th1.join();
  th2.join();
}





































