#include <iostream>
#include <thread>
#include <list>
#include <mutex>

class bank_account
{
    double balance;
    std::string name;
    std::mutex m;

  public:
    bank_account(){};
    bank_account(double _balance, std::string _name) :balance(_balance), name (_name){}
    bank_account(bank_account& ) = delete;
    bank_account& operator = (bank_account& ) = delete;

    void withdraw(double amount)
    {
      std::lock_guard<std::mutex> lg(m);
      balance -= amount;
    }

    void deposite(double amount)
    {
      std::lock_guard<std::mutex> lg(m);
      balance += amount;
    }

    void tarnsfer(bank_account& from , bank_account& to , double amount)
    {
      
      std::cout<< std::this_thread::get_id() <<  " Hold the lock for both mutex " <<std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));

      std::unique_lock<std::mutex> Ul_1(from.m, std::defer_lock);
      std::unique_lock<std::mutex> Ul_2(to.m, std::defer_lock);
      std::lock(Ul_1, Ul_2);

      from.balance -=amount;
      to.balance += amount;

      std::cout << "transfer to - " << to.name << " from - " << from.name << std::endl;
     }
};

void x_operations()
{
  std::cout << "this some opertions" << std::endl;
}

void y_operations()
{
  std::cout << "this some other opertions" << std::endl;
}

std::unique_lock<std::mutex> get_lock()
{
  std::mutex m;
  std::unique_lock<std::mutex> lk(m);
  x_operations();
  return lk;
}

void run_code1()
{
  bank_account account;
  bank_account account_1(1000, "James");
  bank_account account_2(2000, "Mathew");

  std::thread thread_1(&bank_account::tarnsfer, &account, std::ref(account_1), std::ref(account_2),500);
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  std::thread thread_2(&bank_account::tarnsfer, &account, std::ref(account_2), std::ref(account_1),200);

  thread_1.join();
  thread_2.join();
}


void run_code2()
{
   std::unique_lock<std::mutex> lk(get_lock());
   y_operations();
}

int main(){
 
  run_code1();
  run_code2();
  
  printf("hello from main\n");
  return 0;
}




































