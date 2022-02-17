#include <iostream>
#include <stdlib.h>
using namespace std;

class punto{

   private:
   	int x,y;
   
   public:
   	punto(int,int);
   	~punto();
   	void setPunto(int,int);
   	int getPuntoX();
   	int getPuntoY();
};

punto::punto(int _x, int _y){
    x = _x;
    y = _y;

}

//Destructor
punto::~punto(){

}

void punto::setPunto(int _x, int _y){
    x = _x;
    y = _y;
}

int punto::getPuntoX(){
   return x;
}

int punto::getPuntoY(){
   return y;
}

int main(){
   
    punto punto1(1,2);
    //punto1.setPunto(10,45);  
    punto1.~punto();
    
    punto punto2(10,20);
    cout<<"X = "<<punto2.getPuntoX()<<" Y = "<<punto2.getPuntoY()<<endl;
  
    return 0;

}


