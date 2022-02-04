#include <stdio.h>
#include <string.h>

#define TAM_MAX 50

typedef struct client_t client_t, *pno;
struct client_t
{
    int pid;
    char password[TAM_MAX]; // -> 50 chars
    pno next;

    pno (*AddClient)(client_t *); 
};

pno client_t_AddClient(client_t *self) { 
/* code */ 
   printf("pid %d\n",self->pid);
   printf("password %s\n",self->password);
}

int main()
{

    client_t client, client_next;
    client.pid = 78;
    strcpy(client.password,"William Sanchez");
    client.next = &client_next;
    client.AddClient = client_t_AddClient; // probably really done in some init fn

    //code ..

    client.AddClient(&client);

}
