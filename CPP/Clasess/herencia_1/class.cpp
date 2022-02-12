#include <iostream>
#include <cstring>

#include "vivos.h"

using namespace std;

class servivo {

 public:
	virtual void myServivo(){
		cout << "animal ser vivo " << endl;		
	}	
};

class Animal : public servivo {

 private:
	int a;
	char nome[20];

 public:
	Animal();
	Animal(int b, char *aNome);

	void myServivo(){
		cout << "animal" << endl;		
	}

	int getAnimalAge();
	void setAnimalNome(char *aNome);


	~Animal();
};

Animal::Animal(){

	a = 0;
	nome[0] = '\0';
}

Animal::Animal(int b, char *aNome){
	a = b;
	strcpy(nome,aNome);
}

Animal::~Animal(){

	cout << "destructor " << endl;
}

int Animal::getAnimalAge(){
	return a;
}

void Animal::setAnimalNome(char *aNome){

	strcpy(nome,aNome);

}

int main(int arg, char *argc[]){

	servivo *p;
	Animal lobo, perro;
	vivos hombre;

	p = &perro;
//	Animal Oveja = new Animal(4,"roro");
//	lobo.setAnimalNome("lala");

	
	cout <<"Age " << lobo.getAnimalAge() << endl;
	cout << "double " << hombre.getVivosAge() << endl;
	p->myServivo();


}

