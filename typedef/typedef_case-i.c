#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#define typeof(var) _Generic( (var),\
char: "Char",\
int: "Integer",\
float: "Float",\
char *: "String",\
void *: "Pointer",\
default: "Undefined")


/*
-------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------






-------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------

#define CC_ATTRIBTE(attr) __attribute__((attr))

CC_PRINTFLIKE(fmt,var) CC_ATTRIBUTE(format(gnu_printf, fmt, var))

typedef int (asn_constr_check_f)(void *application_specific_key, 
				const struct asn_TYPE_descriptor_s *type_descriptor_which_failed, 
				const void *structure_wich_failedd_ptr,
				const char *error_message_format, ...) CC_PRINTFLIKE(4,5);


*/

#define CC_ATTRIBTE(attr) __attribute__((attr))
#define CC_PRINTFLIKE(fmt,var) CC_ATTRIBUTE(format(gnu_printf, fmt, var))

typedef int(condition)(double *a, void *func);
typedef int (*Operation)(int,int);
typedef int(newString)(const void *key, void *dado, const char *dados_char, ...); // CC_PRINTFLIKE(4,5);
void __attribute__((constructor)) before_main_log();
void __attribute__((destructor)) end_main_log();
int global_data __attribute__((section(".my_data_section"))); //: Places a variable in a specific ELF section, useful for memory mapping or linking.
//void print_log(...) __attribute__((noreturn)); //__attribute__((noreturn)): This attribute indicates that a function will never return to its caller. This is useful for functions like exit() or functions that always throw an exception, allowing the compiler to perform optimizations based on this knowledge and suppress warnings about missing return statements.

void myformat1(const char *, ...);
void myformat2(const char *, ...) __attribute__((format(printf,1,2)));

int add(int a, int b)
{
	return a+b;
};

int main(){
  
    double x1=90;
    int x2=9;
    float x3=9.9;
    condition new_condition;
    Operation op_func = add;
    int result = op_func(5,7);
    int unused_var __attribute__((unused)); //Suppresses warnings about unused variables.
    
   int resul = new_condition(&x1,"HOLA");
   printf("line [%d] function [%s] Result : %d\n\r",__LINE__,__FUNCTION__,resul);
   printf("Result of operation: %d --%d\n\r",result,unused_var);
   myformat1("Here some integer %d, %d\n",x3,x2);
   //myformat2("Here some integer %d, %d, %x\n",x1,x2,x3);
   //print_log();

  
  return 0;
}
/*
void print_log(...)
{
	printf("%s attribute noreturn\n\r",__FUNCTION__);
}
*/

void myformat1(const char *, ...)
{
	printf("Myformat1\n\t");
}
void myformat2(const char *, ...)
{
	printf("Myformat2\n\t");
}

void before_main_log() {printf("BEFORE MAIN FUNCTION\n\r");}
void end_main_log() {printf("END MAIN FUNCTION\n\r");}

int new_condition(double *x, void *y)
{
   (void)x;
   (void)y;
   printf("typeof %s\n\r",typeof(x));
   printf("typeof %s\n\r",typeof(y));
   return 0;
}
