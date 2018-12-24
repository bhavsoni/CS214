#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <signal.h>

#include "bankingServer.h"
#include "bankingAccount.h"

acc** bank;
int manyacc;

pthread_mutex_t accmutex[20];
pthread_mutex_t openaccmut;

node* head = NULL;

int portNum;

int main(int argc, char **argv){	

	if(argc!= 2){
		printf("%s\n", "Please enter valid port number");
		exit(1);
	}

	portNum = atoi(argv[1]);
	bank = openBank();
	manyacc = 0;
	
	pthread_t claccept;
	
	pthread_t output;
	
	signal(SIGINT, handler);
	
	if(pthread_create(&claccept, 0, clientAccept, 0) != 0)
	{
		printf("!---> Could not start server.\n");
		exit(EXIT_FAILURE);
	}

	pthread_create(&output, 0, outputThread, 0);
	pthread_join(claccept, NULL);
	
	printf("Server--> Server end.\n");
	return 0;
}


void* clientAccept(void* sup)
{
	int connex = 0;
	int listener = 0;
	char sender[1025];
	
	struct sockaddr_in serv_addr;
	
	listener = socket(AF_INET, SOCK_STREAM, 0);

	memset(&serv_addr, '0', sizeof(serv_addr));
	memset(sender, '\0', sizeof(sender));



	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(portNum);

	bind(listener, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

	if(listen(listener, 10) ==-1)
	{
		printf("!---> Listen error.\n");
		return NULL;
	}
	
	while(1)
	{
		
		if(listen(listener, 10) ==-1)
		{
			printf("!---> Listen error.\n");
		}
		
		connex = accept(listener, (struct sockaddr*)NULL, NULL);
		strcpy(sender, "Server--> Connection to server successful.\n");
		printf("Server--> Connection to client successful.\n");
		write(connex, sender, strlen(sender));
		
		pthread_t clserv;
		
		if(pthread_create(&clserv, 0, clientServ, &connex) != 0)
		{
			printf("!---> Failure launching client-service thread.\n");
			sleep(1);
		}		
	}
	return NULL;
}


void* clientServ(void* sup)
{
	int x = *(int *)sup;	

	adding(x);
	
	char client[1024] = {'\0'};
	
	while(1)
	{
		int yyy;
		
		char buf[1024] = {'\0'};
		
		//Wait for a message in the buffer
		if ((yyy = recv(x, buf, 1024,0)) == -1)
		{
			printf("!---> Could not receive data from client.\n");
			break;
		} 
		else if (yyy == 0)
		{
			printf("Server--> Connection closed with client.\n");
			break;
		}
		
		buf[yyy] = '\0';
		printf("Server--> Received from client: %s.\n", buf);
		
		
		char ox[100];
		char argue[100] = {'\0'};
		sscanf(buf, "%s %s", ox, argue);		
		

		memset(buf, '\0', 1024);
		
		action(ox, argue, client, buf);
		
		if ((send(x, buf, 100,0))== -1)
		{
			printf("!---> Could not send message.\n");
			close(x);
            break;
		}
	}
	printf("Server--> Closing client service thread.\n");	
	deleting(x);
	close(x);	
	return NULL;
}

void* outputThread(void* x)
{
	
	while(1)
	{
		printf("Server:  \n--- CURRENT BALANCES: ---\n");
		pthread_mutex_lock(&openaccmut);
		outputBank(bank);
		pthread_mutex_unlock(&openaccmut);
		sleep(20);
	}
}


void handler(int s)
{
	
	printf("\nServer--> Server shutting down. Closing all clients.\n");
	
	node* tmp = head;
	
	while(tmp != NULL)
	{
		int bhav = tmp->bhav;
		if ((send(bhav, "quit", 3, 0))== -1)
		{
			printf("!---> Could not shut down one of the clients.\n");
			close(bhav);
            break;
		}
		tmp = tmp->next;
	}
	exit(0);
}


int check(const char *x)
{
  while (*x != '\0')
  {
    if (!isspace(*x))
      return 0;
    x++;
  }
  return 1;
}


void action(char* one, char* two, char* client, char buf[])
{
	printf("Server--> Begin interaction: %s %s\n", one, two);
	
	memset(buf, '\0', strlen(buf));
	
	if(strcmp(one, "create") == 0)
	{
		if(check(two) != 0)
		{
			sprintf(buf, "!---> Please provide an account name.");
			return;
		}
		
		if(client[0] != '\0')
		{
			sprintf(buf, "!---> Cannot create while in account session.");
			return;	
		}
		
		if(manyacc == 20)
		{
			sprintf(buf, "!---> Bank is full.");
			return;	
		}
		
		if(posit(bank, manyacc, two) != -1)
		{
			sprintf(buf, "!---> That account already exists.");
			return;			
		}
		
		pthread_mutex_lock(&openaccmut);
		acc* new = newAcc(bank, manyacc, two);
		manyacc++;
		sprintf(buf, "Server--> Created account: %s", new->id);
		pthread_mutex_unlock(&openaccmut);
		
	} 

	else if(strcmp(one, "serve") == 0)
	{		
		if(client[0] != '\0')
		{
			sprintf(buf, "!---> Please end current account session.");
			return;			
		}
		if(check(two) != 0)
		{
			sprintf(buf, "!---> Please provide an account name.");
			return;
		}
		
		int pos = posit(bank, manyacc, two);
		
		if(pos == -1)
		{
			sprintf(buf, "!---> Please provide a valid account.");
			return;			
		}
		
		if(pthread_mutex_trylock(&accmutex[pos]) != 0)
		{
			sprintf(buf, "!---> This account is already in session elsewhere.");
			return;	
		}
		
		bank[pos]->seshflag = 1;
		
		strcpy(client, two);
		sprintf(buf, "Server--> Started account: %s", client);
		
	}
	
	else if(strcmp(one, "deposit") == 0)
	{
		if(client[0] == '\0')
		{
			sprintf(buf, "!---> Deposit command only valid in account session.");
			return;			
		}
		
		if(check(two) != 0)
		{
			sprintf(buf, "!---> Please provide an amount.");
			return;
		}
		
		if(deposit(bank, manyacc, atof(two), client) == -1)
		{
			sprintf(buf, "!---> Invalid deposit amount.");
			return;
		}
		sprintf(buf, "Server--> Deposit successful.");
	}

	else if(strcmp(one, "withdraw") == 0)
	{
		if(client[0] == '\0')
		{
			sprintf(buf, "!---> Withdraw command only valid in account session.");
			return;
		}
		
		if(check(two) != 0)
		{
			sprintf(buf, "!---> Please provide an amount.");
		}
		
		if(withdraw(bank, manyacc, atof(two), client) == -1)
		{
			sprintf(buf, "!---> Invalid withdrawal amount.");
			return;
		}
		sprintf(buf, "Server--> Withdrawal successful.");
	} 

	else if(strcmp(one, "query") == 0)
	{
		if(client[0] == '\0')
		{
			sprintf(buf, "!---> Query command only valid in account session.");
			return;
		}
		float bal;
		bal = query(bank, manyacc, client);
		sprintf(buf, "$%0.2f", bal);
		
	} 

	else if(strcmp(one, "end") == 0)
	{
		if(client[0] == '\0')
		{
			sprintf(buf, "!---> Not in account session.");
			return;
		}
		
		int pos = posit(bank, manyacc, client);
		pthread_mutex_unlock(&accmutex[pos]);
		bank[pos]->seshflag = 0;		
		
		sprintf(buf, "Server--> Ended account session.");
		client[0] = '\0';			
		
	} 
	
	else if(strcmp(one, "quit") == 0)
	{	
		if(client[0] != '\0')
		{
			int pos = posit(bank, manyacc, client);
			pthread_mutex_unlock(&accmutex[pos]);	
			bank[pos]->seshflag = 0;
		}

		sprintf(buf, "quit");		
	} 
	else
	{
		sprintf(buf, "!---> Command not recognized.");
		return;
	}
}


node* newNode(int bhav)
{
	node* result = (node *)malloc(sizeof(node));
	result->bhav = bhav;
	result->next = NULL;
	return result;
}

node* adding(int bhav)
{
	node* new = newNode(bhav);
	if(head == NULL)
	{
		head = new;
		return head;
	}
	node* tmp = head->next;
	head->next = new;
	new->next = tmp;
	return new;
}

int deleting(int bhav){
	node* tmp = head;
	node* next;
	if(tmp != NULL)
	{
		if(tmp->bhav == bhav)
		{
			head = tmp->next;
			free(tmp);
			return 0;
		}
		next = tmp->next;
	}
	else
	{
		return 0;
	}
	
	while(next != NULL)
	{
		if(next->bhav == bhav)
		{
			tmp->next = next->next;
			node* tmp1 = next->next;
			free(next);
			next = tmp1;
		}
	}
	return 0;
}