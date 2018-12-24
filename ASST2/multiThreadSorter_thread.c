#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pthread.h>
#include "multiThreadSorter_thread.h"
#include "mergesort.c"

int arrcapacity = 60000;
int threadNumber = 1;
int moviecapacity = 0;
char *heading;

struct list *first = NULL;
struct list *p1;
struct list *p2;

Imdbinfo **imdb = NULL;

pthread_mutex_t a = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t b = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t c = PTHREAD_MUTEX_INITIALIZER;

pid_t initial; 

int main(int argc, char *argv[])
{
	
	initial = getpid();
	struct stat sb;

	imdb = (Imdbinfo**) malloc(sizeof(Imdbinfo*) * arrcapacity);

	first = (struct list*) malloc(sizeof(struct list));
	p1 = first;
	p2 = first;

	char *outputdirectory;
	char *inputdirectory;

	if(argc == 3)
	{
		printf("Initial PID: %i\n", initial);
		printf("TIDS of all spawned threads: ");
		heading = argv[2];
		fflush(stdout);
		inputdirectory = ".";
		outputdirectory = ".";
	}
	
	else if(argc == 5)
	{
		if(strcmp(argv[1], "-c") == 0)
		{
			heading = argv[2];
			
			if(strcmp(argv[3], "-d") == 0)
			{
				inputdirectory = argv[4];
				outputdirectory = ".";
			}
			else
			{
				inputdirectory = ".";
				outputdirectory = argv[4];
			}
		}
		else
		{
			heading = argv[4];
			if(strcmp(argv[1], "-d") == 0)
			{
				inputdirectory = argv[2];
				outputdirectory = ".";
			} 
			else
			{
				inputdirectory = ".";
				outputdirectory = argv[2];
			}
		}

		printf("Initial PID: %i\n", initial);
		printf("TIDS of all spawned threads: ");
		fflush(stdout);
	}

	else if(argc == 7)
	{
		if(strcmp(argv[1], "-c") == 0)
		{
			heading = argv[2];
			if(strcmp(argv[3], "-d") == 0)
			{
				inputdirectory = argv[4];
				outputdirectory = argv[6];
			}
			else
			{
				inputdirectory = argv[6];
				outputdirectory = argv[4];
			}
		}
		
		else if(strcmp(argv[1], "-o") == 0)
		{
			outputdirectory = argv[2];
			if(strcmp(argv[3], "-c") == 0)
			{
				heading = argv[4];
				inputdirectory = argv[6];
			}
			else
			{
				heading = argv[6];
				inputdirectory = argv[4];
			}

		}
		else
		{
			inputdirectory = argv[2];
			if(strcmp(argv[3], "-c") == 0)
			{
				heading = argv[4];
				outputdirectory = argv[6];
			}
			else
			{
				outputdirectory = argv[4];
				heading = argv[6];
			}
		}
		printf("Initial PID: %i\n", initial);
		printf("TIDS of all spawned threads: ");
		fflush(stdout);
	}

	else
	{
		printf("%s\n", "Invalid Argument/Input" );
		exit(0);
	}


	if(stat(inputdirectory, &sb) != 0 || !S_ISDIR(sb.st_mode))
	{
		printf("%s\n","Invalid Search - Directory does not exist" );
		exit(0);
	}

	if(stat(outputdirectory, &sb) != 0 || !S_ISDIR(sb.st_mode))
	{
		printf("%s\n","Directory does not exist" );
		exit(0);
	}

	pthread_mutex_lock(&c);
	directory(inputdirectory);
	pthread_mutex_unlock(&c);

	while(p2 ->next != NULL)
	{
		pthread_join(p2 -> id, NULL);
		p2 = p2 -> next;
	}

	printf("\n");
	printf(" Total number of threads: %d\n", threadNumber);
	imdb = merge(imdb, moviecapacity, heading);
	Output(moviecapacity, outputdirectory);
	return(0);

}


void directory (char *dir)
{
	DIR *direct;

	struct dirent *sd;
	struct stat statbuf;

	direct = opendir(dir);

	if(direct == NULL){
		return;
	}

	while((sd = readdir(direct)) != NULL)
	{
		char *catenate = (char*)malloc(sizeof(char)*1000);
		memcpy(catenate, dir, sizeof(char)*strlen(dir));
		catenate[strlen(dir)] = '\0';
		
		if(dir[strlen(dir)-1] != '/')
		{
			catenate = strcat(catenate, "/");
		}

		catenate = strcat(catenate, sd->d_name);

		if(strlen(sd->d_name) > 4 && strstr(sd->d_name, ".csv") != NULL)
		{
			if(strlen(sd->d_name) > 10 && strstr(sd->d_name, "sorted") != NULL)
			{
				continue;
			}

			pthread_mutex_lock(&b);
			char *tmp = strdup(catenate);

			pthread_create(&p1->id, NULL, csv, (void *) tmp);

			threadNumber++; 
			p1 -> next = (struct list*) malloc(sizeof(struct list));
			p1 = p1->next;

			pthread_mutex_unlock(&b);
		}
		else
		{
			if(stat(catenate, &statbuf) == 0)
			{
				if(S_ISDIR(statbuf.st_mode) && strcmp(sd->d_name, ".") != 0 && strcmp(sd->d_name, "..") != 0)
				{
					pthread_mutex_lock(&b);
					char *in = strdup(catenate);
					pthread_create(&p1 -> id, NULL, thrd, (void *)in);
					threadNumber++;
					p1->next = (struct list*) malloc(sizeof(struct list));
					p1 = p1 -> next;

					pthread_mutex_unlock(&b);
				}
			}
		}
		free(catenate);
	}
	closedir(direct);
	return;
}

int decipher(char *file, Imdbinfo **marr, int moviecap)
{
	FILE *data = fopen(file, "r");

	if(!data)
	{
		perror("Error: ");
		return(-1);
	}

	char *tmp = (char *)malloc(sizeof(char)*500);
	char *tmp2;
	char *l = NULL; 
	char *tk;
	size_t lcap;

	int x;
	int test = 0;
	int ptr = 0;
	int counter = 0;

	for(x =0; x<moviecap; x++)
	{
		marr[x] = (Imdbinfo*)malloc(sizeof(Imdbinfo));
	}

	x=0;

	getline(&l, &lcap, data);
	while ( (tk = strsep(&l, ",")) != NULL)
	{
		if(strcmp(tk, heading) == 0)
		{
			test =1;
		}
		ptr++;
		x++;
	}

	if(ptr != 28 || test ==0)
	{
		printf("%s\n", "Category Not Found - Invalid Category" );
		exit(1);
	}

	test=0;
	ptr =0;

	while(getline(&l, &lcap, data) != -1)
	{
		if(ptr > (arrcapacity-1))
		{
			moviecap = moviecap * 2;
			marr = realloc(imdb, (sizeof(Imdbinfo*) * moviecap));

			for(x=ptr; x<moviecap; x++)
			{
				marr[x] = (Imdbinfo*)malloc(sizeof(Imdbinfo));
			}
		}

		counter=0;
		while ( (tk = strsep(&l, ",")) != NULL)
		{
			if(tk != NULL && strlen(tk) > 0 && test==1)
			{
				tmp2 = (char*)malloc(sizeof(char) * (strlen(tmp) + strlen(tk) +2));
				tmp2 = strcat(tmp2, tmp);
				tmp2 = strcat(tmp2,tk);

				tmp = (char*)malloc(sizeof(char) * strlen(tmp2));

				tmp = tmp2;

				if(tk[strlen(tk)-1] == '\"')
				{
					test = 0;
				} 

				tmp2 = strtok(tmp2, "\"");
				counter--;
				mytok(tmp2);
				parseData(tmp2, counter, ptr, marr);
				counter++;
				continue;
			}

			tmp = (char*)malloc(sizeof(char)*strlen(tk));
			tmp = tk;
			mytok(tk);

			if(tk[0] == '\"')
			{
				test =1;
			}

			parseData(tk, counter, ptr, marr);
			counter++;
		}
		tmp = "\0";
		ptr++;
	}
	fclose(data);
	return ptr; 
}

void parseData(char *tk, int x, int ptr, Imdbinfo **marr)
{
        switch(x){
                case 0:
                        marr[ptr]->color = tk;
                        break;
                case 1:
                        marr[ptr]->director_name = tk;
                        break;
                case 2:
                        marr[ptr]->num_critic_for_reviews = atoi(tk);
                        break;
                case 3:
                        marr[ptr]->duration = atoi(tk);
                        break;
                case 4:
                        marr[ptr]->director_facebook_likes = atoi(tk);
                        break;
                case 5:
                        marr[ptr]->actor_3_facebook_likes = atoi(tk);
                        break;
                case 6:
                        marr[ptr]->actor_2_name = tk;
                        break;
                case 7:
                        marr[ptr]->actor_1_facebook_likes = atoi(tk);
                        break;
	        	case 8:
                        marr[ptr]->gross = atoi(tk);
                        break;
                case 9:
                        marr[ptr]->genres = tk;
                        break;
                case 10:
                        marr[ptr]->actor_1_name = tk;
                        break;
                case 11:
                        marr[ptr]->movie_title = tk;
                        break;
                case 12:
                        marr[ptr]->num_voted_users = atoi(tk);
                        break;
                case 13:
                        marr[ptr]->cast_total_facebook_likes = atoi(tk);
                        break;
                case 14:
                        marr[ptr]->actor_3_name = tk;
                        break;
                case 15:
                        marr[ptr]->facenumber_in_poster = atoi(tk);
                        break;
                case 16:
                        marr[ptr]->plot_keywords = tk;
                        break;
                case 17:
                        marr[ptr]->movie_imdb_link = tk;
                        break;
                case 18:
                        marr[ptr]->num_user_for_reviews = atoi(tk);
                        break;
                case 19:
                        marr[ptr]->language = tk;
                        break;
                case 20:
                        marr[ptr]->country = tk;
                        break;
                case 21:
                        marr[ptr]->content_rating = tk;
                        break;
                case 22:
                        marr[ptr]->budget = atoi(tk);
                        break;
                case 23:
                        marr[ptr]->title_year = atoi(tk);
                        break;
                case 24:
                        marr[ptr]->actor_2_facebook_likes = atoi(tk);
                        break;
                case 25:
                        marr[ptr]->imdb_score = atof(tk);
                        break;
                case 26:
                        marr[ptr]->aspect_ratio = atof(tk);
                        break;
                case 27:
                        marr[ptr]->movie_facebook_likes = atoi(tk);
                default:
                        break;
        }
        return;
}

void Output(int cap, char *outputdirectory)
{
	char *tmp1 = (char*)malloc(sizeof(char)*100);
	char *tmp2 = (char*)malloc(sizeof(char)*100);
	char *tmp3 = (char*)malloc(sizeof(char)*100);
	char *tmp4 = (char*)malloc(sizeof(char)*100);
	
	int x;
	
	strcpy(tmp1, outputdirectory);

	tmp2 = strcat(tmp1, "/AllFiles-sorted-");
	tmp3 = strcat(tmp2, heading);
	tmp4 = strcat(tmp3, ".csv");
	
	FILE *data = fopen(tmp4, "w");
	
	fprintf(data, "color,director_name,num_critic_for_reviews,duration,director_facebook_likes,actor_3_facebook_likes,actor_2_name,actor_1_facebook_likes,gross,genres,actor_1_name,movie_title,num_voted_users,cast_total_facebook_likes,actor_3_name,facenumber_in_poster,plot_keywords,movie_imdb_link,num_user_for_reviews,language,country,content_rating,budget,title_year,actor_2_facebook_likes,imdb_score,aspect_ratio,movie_facebook_likes\n");
    	
  	for(x = 0; x < cap; x++){
	        fprintf(data,"%s,%s,%d,%d,%d,%d,%s,%d,%d,%s,%s,%s,%d,%d,%s,%d,%s,%s,%d,%s,%s,%s,%d,%d,%d,%f,%f,%d\n",
	 		imdb[x]->color,
	 		imdb[x]->director_name,
	 		imdb[x]->num_critic_for_reviews,
	 		imdb[x]->duration,
	 		imdb[x]->director_facebook_likes,
	 		imdb[x]->actor_3_facebook_likes,
	 		imdb[x]->actor_2_name,
	 		imdb[x]->actor_1_facebook_likes,
	 		imdb[x]->gross,
	 		imdb[x]->genres,
	 		imdb[x]->actor_1_name,
	 		imdb[x]->movie_title,
	 		imdb[x]->num_voted_users,
	 		imdb[x]->cast_total_facebook_likes,
	 		imdb[x]->actor_3_name,
	 		imdb[x]->facenumber_in_poster,
	 		imdb[x]->plot_keywords,
	 		imdb[x]->movie_imdb_link,
	 		imdb[x]->num_user_for_reviews,
	 		imdb[x]->language,
	 		imdb[x]->country,
	 		imdb[x]->content_rating,
	 		imdb[x]->budget,
	 		imdb[x]->title_year,
	 		imdb[x]->actor_2_facebook_likes,
	 		imdb[x]->imdb_score,
	 		imdb[x]->aspect_ratio,
	 		imdb[x]->movie_facebook_likes);
  	}
	free(tmp1);
	free(imdb);
	fclose(data);
	return;
}

void mytok(char *tk)
{
	int ptr = 0;
	int x = 0;

    while(tk[ptr] == ' ' || tk[ptr] == '\t')
    {
    	ptr++;
    }

    while(tk[x + ptr] != '\0')
    {
   		tk[x] = tk[ptr + x];
   		x++;
   	}

   	tk[x] = '\0';
    x = 0;
    ptr = -1;

    while(tk[x] != '\0')
    {
    	if(tk[x] != ' ' && tk[x] != '\t')
    	{
    		ptr = x;
    	}
    	x++;
    }

    tk[ptr + 1] = '\0';
    return; 
}


void bind (Imdbinfo **marr, int ptr)
{
	int x=0;
	while(x<ptr)
	{
		if(moviecapacity > (arrcapacity-1))
		{
			arrcapacity = arrcapacity * 2;
			imdb = realloc(imdb, sizeof(Imdbinfo*) * arrcapacity);
		}
		imdb[moviecapacity] = marr[x];
		moviecapacity++;
		x++;
	}
}

void *csv (void *p)
{
	int ptr;
	int moviecap= 6000;
	char *catenate = (char *)p;

	Imdbinfo **marr = (Imdbinfo **) malloc(sizeof(Imdbinfo*) * moviecap);
	ptr = decipher(catenate, marr, moviecap);
	pthread_mutex_lock(&a);
	printf("%zu,", pthread_self());
	bind(marr, ptr);
	free(catenate);
	free(marr);
	pthread_mutex_unlock(&a);
	return NULL;

}

void *thrd(void *p)
{
	printf("%zu,", pthread_self());
	pthread_mutex_lock(&c);
	directory((char*)p);
	pthread_mutex_unlock(&c);
	return NULL;
}


