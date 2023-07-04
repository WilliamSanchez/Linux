#include <iostream>
using namespace std;

extern "C"
{
   #include <stdio.h>
   int gol(int g)
   {
     printf("Hola aqui desde C\n");
     return 5*g;
   }
}


class foo
{
   public: 
   
   	foo(int x): y(x), z(y)
   	{  
   	}	

        int showY()
        {
           return y;
        }

        int showZ()
        {
           return z*gol(2);
        }
        
   private:
        
        int y;
        int z;        
};


class foo2: public foo
{

    public:
          foo2(int x, int y): foo(x), z2(y){}
          
          int show2Z2()
          {
            return z2;
          }
  
    private:
    	int z2;

};


int main()
{

   foo unomas(5);
   foo2 dosmas(15,35);
   
   cout<<unomas.showY()<<"> Hello world! <"<<unomas.showZ()<<"\n";
   cout<<dosmas.showZ()<<" class que hereda "<<dosmas.show2Z2()<<"\n";
   cout<<"probando C "<<gol(5)<<"\n";
    


   return 0;
}







































