#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node{
  
    int x;
    struct Node *next;

}Node;

int main(int argc, char *argv[]){

    Node root;
    root.x = 1;
    root.next = malloc(sizeof(Node));
    root.next->x=-2;
    root.next->next =  malloc(sizeof(Node));
    root.next->next->x = -3;
    root.next->next->next = NULL;
/*
    Node *curr = &root;

    while(curr != NULL){     
       printf("Element: %d\n",curr->x);
       curr = curr->next;
    } 

*/    
    for(Node* curr=&root; curr != NULL; curr = curr->next){
      printf("Element: %d\n",curr->x);

    }
   
    free(root.next->next);
    free(root.next);
    
    return 0;
}
