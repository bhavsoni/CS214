#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bankingServer.h"
#include "bankingAccount.h"


acc* openAcc(char* id)
{

	acc* new = (acc *)malloc(sizeof(acc));
	new->id = (char *)malloc(255);
	strcpy(new->id, id);
	new->bal = 0.0;
	new->seshflag = 0;
	return new;	
}

void releaseAcc(acc* acc)
{
	free(acc->id);
	free(acc);
}

acc** openBank()
{
	acc** bnk = (acc **)malloc(20*sizeof(acc *));
	acc** tmp = bnk;
	int x;
	for(x=0; x<20; x++)
	{
		*tmp = NULL;
	}
	return bnk;
}


char* outputAcc(acc* acc)
{
	if(acc == NULL)
	{
		return NULL;
	}
	
	char* result = NULL;
	printf("%s - $%.2f", acc->id, acc->bal);
	
	if(acc->seshflag == 1)
	{
		printf(" - Service active\n");
	} 
	else
	{ 
		printf("\n");
	}
	return result;	
}

char* outputBank(acc* bnk[])
{
	acc** bank0 = bnk;
	char* result = NULL;
	int x;
	printf("****************************************\n");

	for(x=0; x<20; x++)
	{
		outputAcc(bnk[x]);
		bank0++;
	}

	printf("****************************************\n");
	return result;
}


acc* newAcc(acc* bnk[], int bankcap, char* id)
{
	if(bankcap == 20)
	{
		return NULL;
	}

	acc* acct = openAcc(id);

	acc** bank0 = bnk;
	int x;
	for(x=0; x<20; x++)
	{
		if(bnk[x]==NULL)
		{
			bnk[x] = acct;
			bankcap++;
			return acct;
		}
		bank0++;
	}
	return NULL;

}


int posit(acc* bnk[], int bankcap, char* client){
	int x;
	for(x = 0; x < 20; x++)
	{
		if(bnk[x] != NULL && strcmp(bnk[x]->id, client) == 0)
		{
			return x;
		}
	}
	return -1;
}


int withdraw(acc* bnk[], int bankcap, float amt, char* client)
{
	if(!client || amt <= 0){
		return -1;
	}
	
	int pos = posit(bnk, bankcap, client);

	if(bnk[pos]->bal < amt)
	{
		return -1;
	}
	
	bnk[pos]->bal -= amt;	
	return 1;
}

int deposit(acc* bnk[], int bankcap, float amt, char* client)
{
	if(client == NULL || amt <= 0)
	{
		return -1;
	}	
	int pos = posit(bnk, bankcap, client);
	bnk[pos]->bal = bnk[pos]->bal + amt;
	return 1;
}


float query(acc* bnk[], int bankcap, char* client)
{
	if(client == NULL){
		return -1;
	}
	int pos = posit(bnk, bankcap, client);
	
	return bnk[pos]->bal;	

}