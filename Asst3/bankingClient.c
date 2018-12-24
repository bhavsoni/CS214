#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <signal.h>
#include <ctype.h>

#include "bankingClient.h"

#define MAX_COMMAND_SIZE 106

char reciever[1024];
char sender[1024];
int kyle = 0;

int main(int argc, char** argv)
{
	
	if(argc<2)
	{
		printf("!---> Invalid number of arguments.\n");
		exit(1);
	}
	
	char* hostID = argv[1];
	int portNum = atoi(argv[2]);
	char* IP = NULL;
	struct hostent *hostEntry = NULL; 
	hostEntry = gethostbyname(hostID);
	IP = inet_ntoa(*((struct in_addr*)hostEntry->h_addr_list[0]));
 	
 	int x = 0;	
	
	struct sockaddr_in serv_addr;
	
	memset(reciever, '0', sizeof(reciever));

	if((kyle = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("!---> Could not create socket.\n");
		return 1;
	}
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portNum);
	serv_addr.sin_addr.s_addr = inet_addr(IP);
	

	while(connect(kyle, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
	{
		printf("Establishing connection with server...\n");	
		sleep(5);	
	}	
	
	if((x = read(kyle, reciever, sizeof(reciever)-1)) > 0)
	{		
		reciever[x] = 0;
		
		if(fputs(reciever, stdout) == EOF)
		{
			printf("!---> Fputs error.\n");
		}		
	}
	
	if(x < 0){
		printf("!---> Read error.\n");
	}
	
	pthread_t outresp;

	pthread_t incom;
	
	
	signal(SIGINT, inthandler);
	
	if(pthread_create(&incom, 0, inthread, &kyle) != 0)
	{
		printf("!---> Failure launching command input thread.\n");
		exit(1);
	}
	
	if(pthread_create(&outresp, 0, outthread, &kyle) != 0)
	{
		printf("!---> Failure launching response output thread.\n");
		exit(1);
	}
	
	pthread_join(incom, NULL);
	printf("Client end.\n");
	return 0;
		
}

void inthandler(int s)
{
	memset(sender, '\0', strlen(sender));
	strcpy(sender, "end");
	if ((send(kyle,sender, strlen(sender),0))== -1)
	{
		printf("!---> Could not close client account session on exit.\n");
		close(kyle);
		exit(1);
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


void* outthread(void* x)
{
	int sock = *(int *)x;
	while(1)
	{
		memset(reciever, '\0', strlen(reciever));
		
		int yyy = recv(sock, reciever, sizeof(reciever), 0);
		
		if(yyy <= 0)
		{
			printf("!---> Connection closed.\n");
			break;
		}
		
		if(strcmp(reciever, "quit") == 0)
		{
			printf("Client closing.\n");
			exit(0);
		}
		
		if(check(reciever) == 0){
			printf("%s\n", reciever);
		}
	}
	return NULL;
}


void* inthread(void* x)
{
	int sock = *(int *)x;
	while(1)
	{
		printf("Input instruction:\n");
		
		char com[MAX_COMMAND_SIZE];
		memset(com, '\0', MAX_COMMAND_SIZE);
		
		memset(sender, '\0', strlen(sender));
		
		char ox[100];
		char argue[100];
		char error[100];
		fgets(com, MAX_COMMAND_SIZE, stdin);
		
		if ((strlen(com)>0) && (com[strlen (com) - 1] == '\n'))
		{
			com[strlen (com) - 1] = '\0';
		}
		
		int par = sscanf(com, "%s %s %s", ox, argue, error);
		
		if(par == 2)
		{
			strcat(ox, " ");
			strcat(ox, argue);
		} 
		else if(par > 2)
		{
			printf("!---> Command not recognized.\n");
			continue;
		}

		strcpy(sender, ox);
		
		if ((send(sock,sender, strlen(sender),0))== -1)
		{
                printf("!---> Could not send message.\n");
                close(sock);
                exit(1);
        }
        sleep(2);
	}
	return NULL;
}