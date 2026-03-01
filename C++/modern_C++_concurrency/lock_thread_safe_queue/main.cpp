#include "thread_safe_queue.h"

int main()
{
  sequential_queue5<int> queueInteger;
  queueInteger.push(5645);
  queueInteger.push(87456);
  queueInteger.push(94565);
  queueInteger.push(3457);
  queueInteger.push(5);
  queueInteger.push(639);

  queueInteger.printData();
  std::cout << "Removing: " << *(queueInteger.pop().get()) << std::endl;
  std::cout << "Removing: " << *(queueInteger.pop().get()) << std::endl;
  std::cout << "Removing: by wait pop(): " << *(queueInteger.wait_pop().get()) << std::endl;
  queueInteger.printData();
  
  std::cout << "Removing: by wait pop(): " << *(queueInteger.wait_pop().get()) << std::endl;
  queueInteger.printData();
  
  std::cout << "Removing: " << *(queueInteger.pop().get()) << std::endl;
  queueInteger.printData();

  return 0;
}