#include <iostream>
#include <thread>

void foo()
{
  printf("Hello from foo - %d\n", std::this_thread::get_id());
}

class callback_class
{
  public:
    void operator()()
    {
      printf("Hello from class with function call operator - %d\n", std::this_thread::get_id());
    }
};

int main(){
 
  std::thread thread1(foo);

  callback_class obj;
  std::thread thread2(obj);

  std::thread thread3([] 
  {
    printf("Hello from lambda - %d\n", std::this_thread::get_id());
  }); 

  thread1.join();
  thread2.join();
  thread3.join();
  
  printf("hello from main\n");
  return 0;
}




































