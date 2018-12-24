#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "scannerCSVsorter.h"
#include "mergesort.c"

#define MAX_NUM_ROWS 10000
#define MAX_NUM_COLS 10000
#define PATH 256

int rowss = 0;
pid_t initial;
int columnss = 0;

int main(int argc, char* argv[]) {
    int x,y,n;
    Row *rows[MAX_NUM_ROWS];
    char* which_column;
    char *data[MAX_NUM_ROWS];
    int sort;
    int *order;
    char* start_directory="";
    char* output_directory="";
    initial = getpid();


    //To check flags here

    char* Error = "Error, need -c, -d, and -o flags.";

    if (strcmp(argv[1],"-c") == 0){
        which_column = argv[2];
    }
    else{
        printf("%s",Error);
        exit(1);
    }

    printf("INITIAL PID: %i\n", initial);
    printf("PIDS of all child processes: ");
    fflush(stdout);

    //Check number of arguments after initial process

    if (argc==3){
        direct("./", which_column, NULL);
    } else if (argc == 5){
        if (strcmp(argv[3],"-d") !=0){
            printf("%s", Error);
            exit(1);
        } else {
            direct(argv[4], which_column, NULL);
        }
    } else if (argc == 7){
        if (strcmp(argv[3], "-d") != 0 && strcmp(argv[5],"-o") != 0){
            printf("%s", Error);
            exit(1);
        } else {
            direct(argv[4], which_column, argv[6]);
        }
    } else {
        printf("%s", Error);
        exit(1);
    }
    return 0;
}


void Sorter(FILE* input, FILE* output, char * which_column){
    int x,y,n;
    Row *rows[MAX_NUM_ROWS];
    //char* which_column;
    char *data[MAX_NUM_ROWS];
    int sort;
    int *order;

    for(n = 0; n < (sizeof(movie) / sizeof(movie[n])); n++){
        if(strcmp(movie[n], which_column) == 0) {
            sort = n;
            break;
        }
    }
    while(!feof(input)) {
        char* line = NULL;
        char* value;
        char* token;
        char* current_row_values[MAX_NUM_COLS];
        int value_index = 0;
        size_t size;

        if(columnss > 0 && rows[columnss - 1] == 0x0) {
            break;
        }

        getthis_line(&line, &size, input);

        if(rowss == 0) {
            line = NULL;
            getthis_line(&line, &size, input);
        }
        rowss++;
        token = str_token(line, ",");

        while(token) {

            value = *token ? token : "NULL";

            current_row_values[value_index] = value;

            token = str_token(NULL, ",\n");
            value_index++;
        }
        rows[columnss] = parseRowtoint(rows, current_row_values, columnss);

        columnss++;

    }

    for(y = 0; y < rowss - 1; y++){
        data[y] = Columntypes(rows,y,sort);
    }
//here we print the sorted data into the csv file
    order = mergeSort(data, rowss - 1);
    fprintf(output, "color,director_name,num_critic_for_reviews,duration,director_facebook_likes,actor_3_facebook_likes,actor_2_name,actor_1_facebook_likes,gross,genres,actor_1_name,movie_title,num_voted_users,cast_total_facebook_likes,actor_3_name,facenumber_in_poster,plot_keywords,movie_imdb_link,num_user_for_reviews,language,country,content_rating,budget,title_year,actor_2_facebook_likes,imdb_score,aspect_ratio,movie_facebook_likes\n");
//need to check if this part works
    for(x = 0; x < rowss - 1; x++){
        struct Row *thisRow = rows[order[x]];
        printCSV(thisRow, output);
    }

    fclose(output);
    fclose(input);
}

struct Row * parseRowtoint(struct Row *rows[], char* row_values[], int n) {

    if(n != 0 && strcmp(row_values[11], rows[n-1] -> movie_title) == 0) {
        return 0x0;
    }
    rows[n] = malloc(sizeof (struct Row));

    rows[n] -> color = row_values[0];
    rows[n] -> director_name = row_values[1];
    rows[n] -> num_critic_for_reviews = row_values[2];
    rows[n] -> duration = row_values[3];
    rows[n] -> director_facebook_likes = row_values[4];
    rows[n] -> actor_3_facebook_likes= row_values[5];
    rows[n] -> actor_2_name = row_values[6];
    rows[n] -> actor_1_facebook_likes = row_values[7];
    rows[n] -> gross = row_values[8];
    rows[n] -> genres = row_values[9];
    rows[n] -> actor_1_name = row_values[10];
    rows[n] -> movie_title = row_values[11];
    rows[n] -> num_voted_users = row_values[12];
    rows[n] -> cast_total_facebook_likes = row_values[13];
    rows[n] -> actor_3_name = row_values[14];
    rows[n] -> facenumber_in_poster = row_values[15];
    rows[n] -> plot_keywords = row_values[16];
    rows[n] -> movie_imdb_link = row_values[17];
    rows[n] -> num_user_for_reviews = row_values[18];
    rows[n] -> language = row_values[19];
    rows[n] -> country = row_values[20];
    rows[n] -> content_rating = row_values[21];
    rows[n] -> budget = row_values[22];
    rows[n] -> title_year = row_values[23];
    rows[n] -> actor_2_facebook_likes = row_values[24];
    rows[n] -> imdb_score = row_values[25];
    rows[n] -> aspect_ratio = row_values[26];
    rows[n] -> movie_facebook_likes = row_values[27];

    return rows[n];
}

//This method is used to read in the lines from the CSV
size_t getthis_line(char **lineptr, size_t *n, FILE *stream) {
    char *buffer = NULL;
    char *p = buffer;
    size_t size;
    int x;

    if (lineptr == NULL) {
        return -1;
    }
    if (stream == NULL) {
        return -1;
    }
    if (n == NULL) {
        return -1;
    }
    buffer = *lineptr;
    size = *n;

    x = fgetc(stream);
    if (x == EOF) {
        return -1;
    }
    if (buffer == NULL) {
        buffer = malloc(4096);
        if (buffer == NULL) {
            return -1;
        }
        size = 4096;
    }
    p = buffer;
    while(x != EOF) {
        if ((p - buffer) > (size - 1)) {
            size = size + 128;
            buffer = realloc(buffer, size);
            if (buffer == NULL) {
                return -1;
            }
        }
        *p++ = x;
        if (x == '\n') {
            break;
        }
        x = fgetc(stream);
    }

    *p++ = '\0';
    *lineptr = buffer;
    *n = size;

    return p - buffer - 1;
}

char* str_token (char * string, char const * delimiter) {
    static char *pntr = NULL;
    char *p, *result = 0;
    if(string != NULL){
        pntr = string;
    }
    if(pntr == NULL){
        return NULL;
    }
    if((p = strpbrk (pntr, delimiter)) != NULL) {
       *p  = 0;
       result = pntr;
       pntr = ++p;
    }
 return result;
}

void printCSV(struct Row *thisRow, FILE *output) {
    int c = 0;
    for (c = 0; c < 27; c++) {
        fprintf(output, "%s,", Rowtypes(thisRow, c));
    }
    fprintf(output, "%s\n", Rowtypes(thisRow, c));
}


char* Columntypes(struct Row *rows[], int i, int j) {
    switch (j) {
        case 0:
            return (*rows[i]).color;
        case 1:
            return (*rows[i]).director_name;
        case 2:
            return (*rows[i]).num_critic_for_reviews;
        case 3:
            return (*rows[i]).duration;
        case 4:
            return (*rows[i]).director_facebook_likes;
        case 5:
            return (*rows[i]).actor_3_facebook_likes;
        case 6:
            return (*rows[i]).actor_2_name;
        case 7:
            return (*rows[i]).actor_1_facebook_likes;
        case 8:
            return (*rows[i]).gross;
        case 9:
            return (*rows[i]).genres;
        case 10:
            return (*rows[i]).actor_1_name;
        case 11:
            return (*rows[i]).movie_title;
        case 12:
            return (*rows[i]).num_voted_users;
        case 13:
            return (*rows[i]).cast_total_facebook_likes;
        case 14:
            return (*rows[i]).actor_3_name;
        case 15:
            return (*rows[i]).facenumber_in_poster;
        case 16:
            return (*rows[i]).plot_keywords;
        case 17:
            return (*rows[i]).movie_imdb_link;
        case 18:
            return (*rows[i]).num_user_for_reviews;
        case 19:
            return (*rows[i]).language;
        case 20:
            return (*rows[i]).country;
        case 21:
            return (*rows[i]).content_rating;
        case 22:
            return (*rows[i]).budget;
        case 23:
            return (*rows[i]).title_year;
        case 24:
            return (*rows[i]).actor_2_facebook_likes;
        case 25:
            return (*rows[i]).imdb_score;
        case 26:
            return (*rows[i]).aspect_ratio;
        case 27:
            return (*rows[i]).movie_facebook_likes;
        default:
            return (*rows[i]).movie_title;
        }
}

char* Rowtypes(struct Row *row, int columnIndex) {
    switch (columnIndex) {
        case 0:
            return row -> color;
        case 1:
            return row -> director_name;
        case 2:
            return row -> num_critic_for_reviews;
        case 3:
            return row -> duration;
        case 4:
            return row -> director_facebook_likes;
        case 5:
            return row -> actor_3_facebook_likes;
        case 6:
            return row -> actor_2_name;
        case 7:
            return row -> actor_1_facebook_likes;
        case 8:
            return row -> gross;
        case 9:
            return row -> genres;
        case 10:
            return row -> actor_1_name;
        case 11:
            return row -> movie_title;
        case 12:
            return row -> num_voted_users;
        case 13:
            return row -> cast_total_facebook_likes;
        case 14:
            return row -> actor_3_name;
        case 15:
            return row -> facenumber_in_poster;
        case 16:
            return row -> plot_keywords;
        case 17:
            return row -> movie_imdb_link;
        case 18:
            return row -> num_user_for_reviews;
        case 19:
            return row -> language;
        case 20:
            return row -> country;
        case 21:
            return row -> content_rating;
        case 22:
            return row -> budget;
        case 23:
            return row -> title_year;
        case 24:
            return row -> actor_2_facebook_likes;
        case 25:
            return row -> imdb_score;
        case 26:
            return row -> aspect_ratio;
        case 27:
            return row -> movie_facebook_likes;
        default:
            return row -> movie_title;
    }
}

int direct (const char * start_directory, char* which_column, const char * output_directory)
{
    char *directory = (char *) malloc(PATH);
    pid_t process;
    int childs = 1;
    pid_t child_process;
    strcpy(directory, start_directory);

    DIR * this_directory = opendir(directory);

    if (this_directory == NULL)
    {
        printf ("Bad Directory '%s'\n", directory);
        return 1;
    }

    while(this_directory != NULL)
    {
        struct dirent * current_file;
        char * file_name;
        current_file = readdir(this_directory);


        if (childs == 256)
        {
            break;
        }

        if (!current_file)
        {
            break;
        }


        file_name = current_file->d_name;

        if (current_file->d_type == DT_DIR)
        {
            if (strcmp(file_name, ".") != 0 && strcmp(file_name, "..") !=0)
            {
                childs++;

                int length = 0;
                char path[PATH];
                length = snprintf(path, PATH, "%s/%s", current_file, file_name);
                if (length > PATH - 1)
                {
                    printf("Path length exceeds MAX");
                    return -1;
                }


                pid_t pid;
                pid = fork();

                if (pid < 0)
                {
                    printf("Failed fork\n");
                    break;
                }

                else if (pid == 0)
                {
                    strcat(directory, "/");
                    strcat(directory,file_name);
                    this_directory = opendir(directory);
                }
                else if (pid > 0)
                {
                    printf("%i, ", pid);
                    fflush(stdout);
                }
            }
        }

        else if (current_file->d_type == DT_REG)
        {
            char pathname[256];
            FILE* csv;
            sprintf(pathname, "%s/%s", directory, file_name);
            csv = fopen(pathname, "r");

            char *period = strrchr(file_name, '.');

            if (period == NULL || strcmp(period, ".csv") != 0)
            {
                printf("File is not a .csv: %s\n", file_name);
            }

            else if (csv != NULL && !Status(pathname, which_column))
            {
                childs++;

                pid_t pidd, pid;
                pid = fork();

                if (pid < 0) 
                {
                    printf("Failed to process\n");
                    break;
                }

                else if(pid == 0)
                {

                    char * outputpath = malloc(sizeof(char)*512);
                    char *file_namee = (char *) malloc(strlen(file_name) + 1);
                    strcpy(file_namee, file_name);
                    char *period = strrchr(file_namee, '.');
                    if (period != NULL)
                    {
                        *period = '\0';
                    }

                    if (output_directory == NULL)
                    {
                        strcpy(outputpath,directory);
                    } else 
                    {
                        strcpy(outputpath,output_directory);
                    }

                    strcat(outputpath,"/");
                    strcat(outputpath,file_namee);
                    strcat(outputpath,"-sorted-");
                    strcat(outputpath,which_column);
                    strcat(outputpath,".csv");


                    FILE *outputCSV = fopen(outputpath,"w");


                    Sorter(csv, outputCSV, which_column);
                    //USE OUR SORT HERE (csvfile, csvfileout, which_column);
                    free(outputpath);
                    free(file_namee);
                }
                else if (pid > 0)
                {
                    printf("%i, ", pid);
                    fflush(stdout);
                }
            } 
            else 
            {
                fprintf(stderr, "%s\n",  "ERROR: Invalid Input");
                exit(1);
            }
        }
    }

    int x, y; 
    x, y = 0;
    int child_stat;
    int total = childs;




    while (total > 0)
    {
        while ((y = wait(&child_stat)) != -1)
        {
            if (WIFEXITED(child_stat))
            {
                x = x+WEXITSTATUS(child_stat);
            }
        }

        --total;
    }

    free(directory);
    if (closedir(this_directory))
    {
        printf("Error closing Directory");
        return -1;
    }

    if (getpid() == initial)
    {
        printf("\nTOTAL Processes: %d\n\r", (x + childs));
    }
}



int Status(char *path, char *which_column){
    char *strings = (char *) malloc(strlen("-sorted-") + strlen(which_column) + strlen(".csv") + 1);
    strcpy(strings, "-sorted-");
    strcat(strings, which_column);
    strcat(strings, ".csv");
    if (strstr(path, strings) == NULL){
        free(strings);
        return 0;

    }

    else {
        free(strings);
        return 1;
    }
}

