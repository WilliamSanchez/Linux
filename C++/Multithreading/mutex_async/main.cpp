#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>
#include <future>

using namespace std;
using namespace std::chrono;

typedef long int ull;

ull findOdd(ull start, ull end)
{
   ull OddSum = 0;
   cout<<"ThreadID of findOdd: "<<std::this_thread::get_id()<<endl;
   for(ull i=start; i<=end; ++i)
   {
      if(i & 1)
         OddSum += i;
   }
   
   return OddSum;
}

int main()
{
  ull start = 0, end = 1900000000;
  
  cout<<"ThreadID: "<<std::this_thread::get_id()<<endl;
  cout<<"Thread create if the policy is std::launch::async!!"<<endl;

  std::future<ull> OddSum = std::async(std::launch::deferred, findOdd, start, end);
//  std::future<ull> OddSum = std::async(std::launch::async, findOdd, start, end);

  cout<< "Waiting for result !!!" << endl;
  cout<<"OddSum: " << OddSum.get() << endl;
  cout << "complted!!" << endl;

  return 0;
}

