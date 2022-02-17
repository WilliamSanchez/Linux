#include <iostream>
#include <stdlib.h>

using namespace std;

class Persona{
   
   protected: //private:
   	string nombre;
   	int edad;
   public:
   	Persona(string,int);
   	void mostrarPersona();
};

class Alumno : public Persona{
   
    private:
       string codigoAlumno;
       float notaFinal;
    
    public:
       Alumno(string, int, string, float);
       void mostrarAlumno();
};

Alumno::Alumno(string _nombre, int _edad, string _codigoAlumno, float _notaFinal) : Persona(_nombre, _edad){
 
  codigoAlumno = _codigoAlumno;
  notaFinal = _notaFinal;
}
 
Persona::Persona(string _nombre, int _edad){
  nombre = _nombre;
  edad = _edad;
}

void Alumno::mostrarAlumno(){
    mostrarPersona();
    cout<<"Codigo Alumno "<<codigoAlumno<<endl;
    cout<<"Nota final: "<<notaFinal<<endl;

}

void Persona::mostrarPersona(){
   cout<<"Nombre: "<<nombre<<endl;
   cout<<"Edad: "<<edad<<endl;
}

int main(){

   Alumno Alumno1("William",30,"12345567",12.8);
   Alumno1.mostrarAlumno();
   return 0;
}
