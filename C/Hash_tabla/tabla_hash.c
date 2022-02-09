#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define L_NOMBRE	100
#define N		5

struct registro{
	char nombre[L_NOMBRE];
	char info[1000];
};
typedef struct registro reg;

typedef struct nodo{
   reg registro;
   struct nodo *a, *s;
}nodo;

nodo *tabla[]={NULL,NULL,NULL,NULL,NULL};

char leer_char();
void agregar_registro();
void buscar_registro();
void eliminar_registro();


int main(int argc, char **argv){
  
  char opcion;
  do{
     printf("\t\tMENU\n\r");
     printf("a-> Agregar dato\n\r");
     printf("b-> Buscar dato\n\r");
     printf("e-> Eliminar dato\n\r");
     printf("s-> Salir\n\r");
     printf("Opcion: ");
     opcion = leer_char();    
     opcion = tolower(opcion);
    switch(opcion){
	case 'a':
		agregar_registro();
		break;
	case 'b':
		buscar_registro();
		break;
	case 'e':
		eliminar_registro();
		break;
 	default: 
		break; 

    }
  }while(opcion != 's');
  return 0;
}

int hash(char *key);
void acomodar(reg registro, int llave);
void buscar_registro();
nodo *buscar(char *nombre,int llave);
void mostrar_registro(reg r);
void eliminar(nodo *q, int llave);

void agregar_registro(){
    reg r;
    char nombre[L_NOMBRE];
    printf("Escriba el nombre ...");
    fgets(r.nombre,L_NOMBRE,stdin);
    printf("Escriba la info ...");
    fgets(r.info,1000,stdin);
    int llave = hash(r.nombre);
    printf("Llave %d: %s",llave,r.nombre);
    acomodar(r,llave);
}

void buscar_registro(){
    char nombre[L_NOMBRE];
    printf("Escriba el nombre para eliminar...");
    fgets(nombre,L_NOMBRE,stdin);
    int llave = hash(nombre);
    printf("Llave %d: %s",llave,nombre);
    nodo *resultado = buscar(nombre,llave);
    if(resultado){
       mostrar_registro(resultado->registro);
    }else{
	printf("No esta el nombre para eliminar...");
    }
}


void eliminar_registro(){
    char nombre[L_NOMBRE];
    printf("Escriba el nombre para eliminar...");
    fgets(nombre,L_NOMBRE,stdin);
    int llave = hash(nombre);
    printf("Llave %d: %s",llave,nombre);
    nodo *resultado = buscar(nombre,llave);
    if(resultado){
       mostrar_registro(resultado->registro);
       eliminar(resultado,llave);
    }else{
	printf("No esta el nombre para eliminar...");
    }
}


void eliminar(nodo *q, int llave){

  if(q->s){
     q->s->a = q->a; 
  }

  if(q->a){
      q->a->s = q->s;
  }else{
      tabla[llave] = q->s; 
  }

  free(q);

}

nodo *buscar(char *nombre,int llave){
  nodo *p = tabla[llave];
  while(p){   
     if(strcmp(p->registro.nombre,nombre) == 0)
	return p;
     p = p->s;
  }	
  return NULL;
}

void mostrar_registro(reg r){
  printf("Nombre: %s",r.nombre);
  printf("Info:	%s",r.info);
}

void acomodar(reg r, int llave){
    nodo *nuevo = malloc(sizeof(nodo));
    nuevo->registro = r;
    nuevo->a = NULL;
    nuevo->s = tabla[llave];
    if(tabla[llave])
    	tabla[llave]->a = nuevo;
    tabla[llave]=nuevo;
}

int hash(char *key){
  int longitud = strlen(key)-1;
  int suma = 0;
  for(int i=0;i<longitud;i++)
	suma += key[i];
  return suma%N;
}

char leer_char(){
   char c = getchar();
   getchar();
   return c;
}


