#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define LINESIZE 128


struct word{
	char *word;
	unsigned count;
};


void add_word(struct word *words_arr, int *w_count, char *s){
	for(int i = 0; i<*w_count; i++){
		if(strcmp(s, words_arr[i].word) == 0){
			words_arr[i].count++;
			return;
		}
	}
    words_arr[*w_count].word = malloc(strlen(s));
	strcpy(words_arr[*w_count].word, s);
	words_arr[*w_count].count = 1;
	(*w_count)++;
};

void upper(char *s){
	for (int i=0; s[i]; i++){
		s[i] = toupper (s[i]);
	} 
};

int compare_word(struct word *a, struct word *b){
	if (a->count < b->count){
		return 1;
	} 
	if (a->count > b->count){
		return -1;
	} 
	return 0;
}


int main(int argc, char *argv[]) {
	FILE *FILEIN; 
	FILEIN = fopen(argv[1], "r");
	char line[LINESIZE];
	char w[1000], *token;
	int w_count = 0;
	int WORDS_ARR_SIZE = 5000;

	//Allocate arrays for words
	struct word *words_arr = malloc(sizeof(struct word) * WORDS_ARR_SIZE);
	size_t len;

	if(FILEIN == NULL){
		perror("File cannot me opened \n");
		exit(0);
	}
	//Read line by line
	while ((fgets(line, LINESIZE, FILEIN)) != NULL) {
		//Delete new line character from each line
		len = strlen(line);
		if (len > 0 && line[len-1] == '\n') {
		  line[--len] = '\0';
		}
		///Tokenize each line, uppercase each token
		token = strtok(line, " ");
		while(token != NULL) {
			upper(token);
			//Add each uppered token to the words array structure
			add_word(words_arr, &w_count, token);
			//Check if the word array exceed allocated space, if it is increase the size of the array by 2
			if (w_count >= WORDS_ARR_SIZE){
				WORDS_ARR_SIZE = WORDS_ARR_SIZE * 2;
				words_arr = realloc(words_arr, sizeof(struct word) * WORDS_ARR_SIZE);
			}
			//Skip space token
		  	token = strtok(NULL, " ");
		}
	}

	//Sort array
	qsort((void *) words_arr, w_count, sizeof (struct word), (int (*) (const void *, const void *)) compare_word);
	//Print elements
	if(w_count>50){
		for (int i = 0; i < 50; ++i){
			printf("%s %d\n", words_arr[i].word, words_arr[i].count);
		}
	}
	else{
		for (int i = 0; i < w_count; i++)
		{
			printf("%s %d\n", words_arr[i].word, words_arr[i].count);
		}
	}
	//Free allocated memory
	for (int i = 0; i < w_count; i++){
		free(words_arr[i].word);
	}
	free(words_arr);

	fclose(FILEIN);



	return 0;
}