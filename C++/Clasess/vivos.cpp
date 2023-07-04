#include <iostream>

#include "vivos.h"

using namespace std;

vivos::vivos(){
	r = 34;
	dob = 9283;
}
vivos::vivos(int ing, double sal){
	r = ing;
	dob = sal;
}

vivos::~vivos(){
	cout << "Destructor" <<endl;
};

void vivos::setVivosAge(int ing){

	r = ing;
}

double vivos::getVivosAge(){
	return dob;
}	



