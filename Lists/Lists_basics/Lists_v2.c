#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node{  
    int x;
    struct Node *next;
}Node;

void insert_end(Node **root, int value){
   Node *new_node = malloc(sizeof(Node));
   new_node->x = value;
   new_node->next=NULL;

   if(*root == NULL){
      *root = new_node;
      return;
   }

   Node *curr = *root;
   while(curr->next != NULL){
     curr=curr->next; 
   }
  
   curr->next = new_node;

}

int main(int argc, char *argv[]){

    Node *root = NULL;
    insert_end(&root, 33);
    insert_end(&root, -5);
    insert_end(&root, 25);
    insert_end(&root, 55);
   
    for(Node* curr= root; curr != NULL; curr = curr->next){
      printf("Element: %d\n",curr->x);

    }
   
    free(root->next->next);
    free(root->next);
    free(root);
    
    return 0;
}
