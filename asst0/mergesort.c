#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int final[5044];
char *temp[5044];


void merge(char *arr[],int left, int middle, int right) {
	int first, second, i;
	
   for(first = left, second = middle + 1, i = left; first <= middle && second <= right; i++) {

    if(strcmp(tolower(arr[first]),tolower(arr[second])) <= 0) {
		temp[i] = arr[first++]; 			
	} else {
		temp[i] = arr[second++]; 						
		}
	}

	while(first <= middle) {
		temp[i++] = arr[first++];
	}

	while(second <= right) {
		temp[i++] = arr[second++];
	}

	for(i = left; i <= right; i++){
		arr[i]= temp[i];
	}

}

void sort(char *arr[],int x, int y){
	int z= (x + y) / 2;

	if(x < y) {
		sort(arr,x,z);
		sort(arr,z+1, y);
		merge(arr,x,z,y);
	} else {
		return;
	}
}

int * mergeSort(char *arr[], int x) {
	int i,left,right,k,l;
	char **unsorted = malloc(sizeof(char *) * x);
	for (i = 0; i < x; i++) {
		unsorted[i] = malloc(strlen(arr[i]));
		strcpy(unsorted[i],arr[i]);
	}

	left = 0;
	right = x - 1;

	sort(arr, left, right);

	k = 0;
	for(i = 0; i < x; i++){
		int j = 0;
		for(j = 0; j < x; j++){
			if(strcmp(tolower(arr[i]),tolower(unsorted[j])) == 0) {
				char str[12];
				sprintf(str, "%d", j);
				unsorted[j] = strcat(unsorted[j], str);
				final[k] = j;
				k++;
				break;
			}
		}
	}

	return final;
}



