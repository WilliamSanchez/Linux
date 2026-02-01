#include <stdio.h>
#include "rcwrapper.h"

int main(){
    printf("INIT TESTE ASN\n");
    char n[]={0,3,4};
    encode_rc_action_Definition(n,2);
    //encode_rc_eventrigger(n,2);
    //encode_rc_eventrigger(n,5);
    return 0;
}