#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <omp.h>

#define COUNT 7
#define WORD_SIZE 20
char *FILE_NAME;
char words[COUNT][WORD_SIZE] = {"Hi","the","Originium","here","mount","inference","Ursus"};
int word_count[COUNT]; //array of integers initialized to 0

void read_word(char *temp, FILE *fp){
	int i=0;
	char ch=' ';
	
	while( (ch=fgetc(fp))!=EOF && isalpha(ch)==0 ); //ignore all non-alphabets till we reach next letter
	
	while( ch!=EOF && isalpha(ch) )
		{
		//printf("%c",ch);
		temp[i++] = ch;
		ch = fgetc(fp); //move to next character
		}
	temp[i] = '\0';
	//printf("%s",temp);	
}

int get_word_count(int num){ //tells which word in array words[] to search for in text file
	
	FILE *fp = fopen(FILE_NAME,"r");
	char temp[WORD_SIZE]; //temporary buffer to store a word
	int ret_val=0;
	
	while( feof(fp)==0 )
		{
		read_word(temp, fp);
		//printf("%s",temp);
		if(strcasecmp(words[num], temp) == 0 )
			ret_val++;		
		}
	return ret_val;
}

int main(int argc, char *argv[]){
	
	FILE_NAME = argv[1];
	int n_threads = atoi(argv[2]);
	//FILE *input = fopen(i);
	
	double t = omp_get_wtime();
	#pragma omp parallel for num_threads(n_threads) //schedule(dynamic,1)
	for(int i=0; i<COUNT; i++)
		{
		word_count[i] = get_word_count(i);
		}
	t = omp_get_wtime() - t; 
	/*
	for(int i=0; i<COUNT; i++)
		printf("%s: %d\n",words[i], word_count[i]);
	*/
	printf("%.4f\t", t);
	return 0;
}
