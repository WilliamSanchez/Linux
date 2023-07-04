/*

1. Condition variables allow us to synchronise threads via notifications.
   a. notify_one();
   b. notify_all();
2. You need mutex to use condition variable
3. Condition variable is used to synchronise two or more threads.
4. Best use case of condition variable is Producer/Consumer problem.
5. Condition variables can be used for two purposes:
    a. Notify other threads
    b. Wait for some condition

*/


#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

std::condition_variable cv;
std::mutex m;
long balance;

void addMoney(int money)
{
   std::lock_guard<mutex> lg(m);
   balance += money;
   cout << "Amount Added Current Balance: "<< balance<< endl;
   cv.notify_one();
}

void withdrowMoney(int money)
{
   std::unique_lock<mutex> ul(m);
   cv.wait(ul,[]{return (balance !=0 ) ? true:false;});
   if(balance >= money)
   {
      balance -= money;
      cout<< "Amount Deducted: " << money << endl;
   }
   else
   {
     cout << "Amount Can't be deducted, current balance is less than " << money << endl;
   }
   cout << "Current Balance Is : "<< balance << endl;
}

int main()
{
  std::thread t1(withdrowMoney, 600);
  std::this_thread::sleep_for(std::chrono::seconds(2));
  std::thread t2(addMoney,500);
  t1.join();
  t2.join();
  return 0;

}



































