#include <iostream>
#include <stdlib.h>

using namespace std;

/*

Persona   --> Estudiante --> Universitario
   |
   V
Empleado

*/

class Persona{
   
   private:
        string nombre;
        int edad;
   public:
        Persona(string,int);
        void mostrarPersona();
};

class Empleado : public Persona{
     private:
         float sueldo;
     public:
         Empleado(string,int,float);
         void mostrarEmpleado();
};

class Estudiante : public Persona{
   private:
      float notaFinal;
   public:
      Estudiante(string,int,float);
      void mostrarEstudiante();
};

class Universitario : public Estudiante{   
    private:
       string carrera;
    public:
       Universitario(string,int,float,string);
       void mostrarUniversitario();
};

Persona::Persona(string _nombre, int _edad){    
    nombre = _nombre;
    edad = _edad;
}

void Persona::mostrarPersona(){
    cout<<"Nombre: "<<nombre<<endl;
    cout<<"Edad: "<<edad<<endl;
}

Empleado::Empleado(string _nombre,int _edad,float _sueldo) : Persona(_nombre,_edad){
      sueldo = _sueldo;
}

void Empleado::mostrarEmpleado(){
   mostrarPersona();
   cout<<"Sueldo: "<<sueldo<<endl;
}


Estudiante::Estudiante(string _nombre, int _edad, float _notaFinal) : Persona(_nombre,_edad){
    notaFinal = _notaFinal;
}

void Estudiante::mostrarEstudiante(){
    mostrarPersona();
    cout<<"Nota Final: "<<notaFinal<<endl;
}

Universitario::Universitario(string _nombre, int _edad, float _notaFinal, string _carrera) : Estudiante(_nombre,_edad,_notaFinal){
    carrera = _carrera;
}

void Universitario::mostrarUniversitario(){
     mostrarEstudiante();
     cout<<"Carrera: "<<carrera<<endl;   
}

int main(){

   Empleado empleado1("Carlos",35,1300);
   cout<<"-Empleado-"<<endl;
   empleado1.mostrarEmpleado();
   cout<<"\n";
 
   Estudiante estudiante1("William",37,5.0);
   cout<<"-Estudiante"<<endl;
   estudiante1.mostrarEstudiante();
   cout<<"\n";
   
   Universitario universitario1("Ines",19,3.5,"Ingeniria de Control");
   cout<<"-Universitario-"<<endl;
   universitario1.mostrarUniversitario();
   cout<<"\n";
   
   
  return 0;
}
