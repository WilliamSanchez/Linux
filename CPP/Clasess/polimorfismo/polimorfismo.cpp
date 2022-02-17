#include <iostream>
#include <stdlib.h>

using namespace std;

class Persona {
    private:
       string nombre;
       int edad;
       
   public:
       Persona(string,int);
       virtual void mostrar();
};

class Alumno:public Persona{
   private:
      float notaFinal;
   public:
      Alumno(string,int,float);
      void mostrar();

};

class Professor : public Persona{

    private:
       string materia;
    public:
       Professor(string,int,string);
       void mostrar();

};

Persona::Persona(string _nombre, int _edad){
   nombre = _nombre;
   edad = _edad;
}

void Persona::mostrar(){  
    cout<<"Nombre: "<<nombre<<endl;
    cout<<"Edad: "<<edad<<endl;
}

Alumno::Alumno(string _nombre, int _edad, float _notaFinal) : Persona(_nombre,_edad){
    notaFinal = _notaFinal;
}

void Alumno::mostrar(){
    Persona::mostrar();
    cout<<"Nota Final: "<<notaFinal<<endl;
}

Professor::Professor(string _nombre, int _edad, string _materia) : Persona(_nombre,_edad){
    materia = _materia;
}

void Professor::mostrar(){
   Persona::mostrar();
   cout<<"Materia: "<<materia<<endl;
}


int main(){

  Persona *vector[3];
  
  vector[0] = new Alumno("Alejandro",20,3.5);
  vector[1] = new Alumno("Maria",27,5.0);
  vector[2] = new Professor("William",37,"Matematicas");
  vector[0]->mostrar();
  cout<<"\n";
  vector[1]->mostrar();
  cout<<"\n";
  vector[2]->mostrar();
  cout<<"\n";
  return 0;
}

