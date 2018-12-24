#ifndef SORTER_H_
#define SORTER_H_
#include <unistd.h>

size_t getthis_line(char** lineptr, size_t *n, FILE *stream);
char* str_token(char* string, char const* delimiter);
int * mergeSort(char *arr[], int x);
void sort(char *arr[], int x, int y);
void merge(char *arr[], int left, int middle, int right);

struct Row * parseRowtoint(struct Row **rows, char **row_values, int n);
char* Rowtypes(struct Row *rows, int columnIndex);
char* Columntypes(struct Row **rows, int i, int j);
void printCSV(struct Row *thisRow, FILE *output);
void Sorter(FILE* input, FILE* output, char * which_column);
int Status(char *path, char *which_column);
int direct (const char * start_directory, char* which_column, const char * output_directory);






const char* movie[] = {
    "color",
    "director_name",
    "num_critic_for_reviews",
    "duration",
    "director_facebook_likes",
    "actor_3_facebook_likes",
    "actor_2_name",
    "actor_1_facebook_likes",
    "gross",
    "genres",
    "actor_1_name",
    "movie_title",
    "num_voted_users",
    "cast_total_facebook_likes",
    "actor_3_name",
    "facenumber_in_poster",
    "plot_keywords",
    "movie_imdb_link",
    "num_user_for_reviews",
    "language",
    "country",
    "content_rating",
    "budget",
    "title_year",
    "actor_2_facebook_likes",
    "imdb_score",
    "aspect_ratio",
    "movie_facebook_likes"
};

typedef struct Row {
    char* color;
    char* director_name;
    char* num_critic_for_reviews;
    char* duration;
    char* director_facebook_likes;
    char* actor_3_facebook_likes;
    char* actor_2_name;
    char* actor_1_facebook_likes;
    char* gross;
    char* genres;
    char* actor_1_name;
    char* movie_title;
    char* num_voted_users;
    char* cast_total_facebook_likes;
    char* actor_3_name;
    char* facenumber_in_poster;
    char* plot_keywords;
    char* movie_imdb_link;
    char* num_user_for_reviews;
    char* language;
    char* country;
    char* content_rating;
    char* budget;
    char* title_year;
    char* actor_2_facebook_likes;
    char* imdb_score;
    char* aspect_ratio;
    char* movie_facebook_likes;
} Row;

typedef struct typeRow {
	char* color;
	char* director_name;
	int num_critic_for_reviews;
	char* duration;
	int director_facebook_likes;
	int actor_3_facebook_likes;
	char* actor_2_name;
	int actor_1_facebook_likes;
	int gross;
	char* genres;
	char* actor_1_name;
	char* movie_title;
	int num_voted_users;
	int cast_total_facebook_likes;
	char* actor_3_name;
	int facenumber_in_poster;
	char* plot_keywords;
	char* movie_imdb_link;
	int num_user_for_reviews;
	char* language;
	char* country;
	char* content_rating;
	int budget;
	int title_year;
	int actor_2_facebook_likes;
	double imdb_score;
	double aspect_ratio;
	int movie_facebook_likes;
};
#endif
