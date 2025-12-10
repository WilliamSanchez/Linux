#include <iostream>
#include <thread>
#include <future>
#include <string>
#include <stdexcept>
#include <chrono>
#include <mutex>

void print_result1(std::future<int>& fut)
{
  if(fut.valid())
  {
    std::cout << "This is valid future\n";
    std::cout << fut.get() << "\n";
  }else{
    std::cout << "This is invalid future\n";
  }  
}

void run_code1()
{
  std::promise<int> prom;
  std::future<int> fut(prom.get_future());

  std::thread th1(print_result1, std::ref(fut));
  std::thread th2(print_result1, std::ref(fut));

  prom.set_value(5);

  th1.join();
  th2.join();
}

void print_result2(std::shared_future<int>& fut)
{
    std::cout << fut.get() << " valid future\n";
}

void run_code2()
{
  std::promise<int> prom;
  std::shared_future<int> fut(prom.get_future());

  std::thread th1(print_result2, std::ref(fut));
  std::thread th2(print_result2, std::ref(fut));

  prom.set_value(5);

  th1.join();
  th2.join();
}


int main(){
  
  //run_code1();
  run_code2();

  printf("hello from main\n");
  return 0;
}




































