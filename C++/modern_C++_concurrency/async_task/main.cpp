#include <iostream>
#include <thread>
#include <future>
#include <string>

void printing()
{
  std::cout<<"printing runs on." << std::this_thread::get_id() << std::endl;
}

int addition(int x, int y)
{
  std::cout<<"additions run on."<< std::this_thread::get_id()<<std::endl;
  return x+y;
}

int substraction(int x, int y)
{
  std::cout<<"subsractions run on."<< std::this_thread::get_id()<<std::endl;
  return x-y;
}

int main(){
  
  std::cout<<"main thread id -"<<std::this_thread::get_id() << std::endl;

  int x = 100;
  int y = 50;

  std::future<void> f1 = async(std::launch::async,printing);
  std::future<int> f2 = async(std::launch::deferred,addition,x,y);
  std::future<int> f3 = async(std::launch::deferred | std::launch::async, substraction,x,y);

  f1.get();
std::cout<<"value received using f2 future - " << f2.get()<<std::endl;
std::cout<<"value received using f2 future - " << f3.get()<<std::endl;  

  printf("hello from main\n");
  return 0;
}




































