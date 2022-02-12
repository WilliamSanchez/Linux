#include <iostream>

using namespace std;

void do_something(int& i)
{
    ++i;
    cout<<"inside of function "<<i<<"\n";
    
}

struct func
{
   int& y;
   func(int& h):y(h){ // y toma el valor de h, donde h es el valor pasado desde el main
   	cout<<"inside of operator "<<y<<"\n";
   }
   void operator()(){
     cout<<"inside of void operator \n";
     for(unsigned j=0;j<1000000;++j){
        do_something(y);    
     }
   }
};

struct w_struct
{
   int i;
};

struct p_struct
{
   int i;
};

struct foo {
  int bar;
  foo() : bar(3) {}   //look, a constructor
  int getBar() 
  { 
    return bar; 
  }
};


/*
struct func
{
    int& i;

    func(int& i_):i(i_){}

    void operator()()
    {
        for(unsigned j=0;j<20;++j)
        {
            cout<<"inside of operator "<<j<<"\n";
            do_something(i);
        }
    }
};
*/
int main()
{
    int r = 9;
    int p = 19;
    struct w_struct *o_struct;
    struct w_struct *my_struct;
    struct w_struct other={12};
    my_struct = &other;
    my_struct->i=25;
    o_struct->i=50;

    func my_func(r);
    func w_func(p);
    
    foo f;
    int y = f.getBar(); // y is 3
//    my_func->i=9;
    //func my_func(r);
    cout<<"my_struct "<<my_struct->i<<"\n";
    cout<<"o_struct "<<o_struct->i<<"\n";
    cout<<"foo "<<y<<"\n";
}
