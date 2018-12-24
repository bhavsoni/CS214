#include <stdio.h>

typedef struct node{
	int bhav;
	struct node *next;	
} node;

void* clientAccept(void* sup);
void* clientServ(void* sup);
void* outputThread(void* x);
void handler(int s);
void action(char* one, char* two, char* client, char buf[]);
node* newNode(int bhav);
node* adding(int bhav);
int deleting(int bhav);
