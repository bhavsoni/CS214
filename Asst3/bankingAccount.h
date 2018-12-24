#include <stdio.h>

typedef struct acc{

	char* id;
	float bal;
	int seshflag;

} acc;

acc* openAcc(char* id);
void releaseAcc(acc* acc);
acc** openBank();
char* outputAcc(acc* acc);
char* outputBank(acc* bnk[]);
acc* newAcc(acc* bnk[], int bankcap, char* id);
int posit(acc* bnk[], int bankcap, char* client);
int withdraw(acc* bnk[], int bankcap, float amt, char* client);
int deposit(acc* bnk[], int bankcap, float amt, char* client);
float query(acc* bnk[], int bankcap, char* client);