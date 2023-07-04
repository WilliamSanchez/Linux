#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

void run(int count){
   while(count-- > 0)
   	cout<<count<<" CppNUTS" << endl;
//   std::this_thread::sleep_for(chrono::seconds(5));
   cout << "thread finished " << endl;
}

int main(){
 
  std::thread t1(run,10);
  cout<< "main()"<<endl;
   t1.detach();
/*
  t1.join();
  if(t1.joinable())
    t1.join();
 */
  cout<<"main() after" << endl;
  std::this_thread::sleep_for(chrono::seconds(5));
  return 0;
}




































