#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "simpleCSVSorter.h"
#include "mergesort.c"

#define MAX_NUM_ROWS 10000
#define MAX_NUM_COLS 10000

int rowss = 0;
int columnss = 0;

int main(int argc, char* argv[]) {
    int x,y,n;
    Row *rows[MAX_NUM_ROWS];
    char* which_column;
    char *data[MAX_NUM_ROWS];
    int sort;
    int *order;

    which_column = argv[2];
    for(n = 0; n < (sizeof(movie) / sizeof(movie[n])); n++){
        if(strcmp(movie[n], which_column) == 0) {
            sort = n;
            break;
        }
    }
    while(!feof(stdin)) {
        char* line = NULL;
        char* value;
        char* token;
        char* current_row_values[MAX_NUM_COLS];
        int value_index = 0;
        size_t size;

        if(columnss > 0 && rows[columnss - 1] == 0x0) {
            break;
        }

        getthis_line(&line, &size, stdin);

        if(rowss == 0) {
            line = NULL;
            getthis_line(&line, &size, stdin);
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

    order = mergeSort(data, rowss - 1);
    printf("color,director_name,num_critic_for_reviews,duration,director_facebook_likes,actor_3_facebook_likes,actor_2_name,actor_1_facebook_likes,gross,genres,actor_1_name,movie_title,num_voted_users,cast_total_facebook_likes,actor_3_name,facenumber_in_poster,plot_keywords,movie_imdb_link,num_user_for_reviews,language,country,content_rating,budget,title_year,actor_2_facebook_likes,imdb_score,aspect_ratio,movie_facebook_likes\n");

    for(x = 0; x < rowss - 1; x++){
        struct Row *thisRow = rows[order[x]];
        printCSV(thisRow);
    }
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

void printCSV(struct Row *thisRow) {
    int c = 0;
    for (c = 0; c < 27; c++) {
        printf("%s", Rowtypes(thisRow, c));
        printf(",");
    }
    printf("%s", Rowtypes(thisRow, c));
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
