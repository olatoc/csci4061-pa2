#include "phase2.h"
// You are free to use your own logic. The following points are just for getting started
/* 	Map Function
	1)	Each mapper selects a Mapper_i.txt to work with
	2)	Creates a list of letter, wordcount from the text files found in the Mapper_i.txt
	3)	Send the list to Reducer via pipes with proper closing of ends
*/

int phase_2(int i, int**fds){
	//allocate array to store letter counts of mapper i
	letter_counts = (int*)malloc(sizeof(int)*26);
	//zero array of junk from stack
	for (int j = 0; j < 26; j++){
		letter_counts[j] = 0;
	}
	//read files stored in Mapper_i.txt
	read_mapper_file(i);
	//write resulting array to pipe
	write_to_pipe(i, fds);
	free(letter_counts);
	//kill process
	exit(0);
}

//this function reads and parses all the files stored in Mapper_i.txt
void read_mapper_file(int i){
	//open file
	char mapper_filename[128];
	char *filename = malloc(sizeof(char)*128);
	sprintf(mapper_filename, "MapperInput/Mapper_%d.txt", i);
	FILE *fp = fopen(mapper_filename, "r");
	//parse each file inside Mapper_i.txt
	while ((fgets(filename, sizeof(char)*128, fp)) != NULL) {
		parse_file(filename);
	}
	free(filename);
	fclose(fp);
}

//this function opens a file filename and sums the count of each occurance of every letter
//in every file within Mapper_i.txt
void parse_file(char *filename){
	//remove \n from end of filename; necessary to open properly
	filename[strcspn(filename, "\n")] = 0;
	FILE *fp;
    char *line;
	char c;
    size_t len = 0;
    fp = fopen(filename, "r");
    if (fp == NULL){
        exit(1);
	}
	//count how many occurances of a word's starting with each letter within the file
    while ((getline(&line, &len, fp)) != -1) {
		c = line[0];
		if (c >= 65 && c <= 90){
			/* handle capital letters */
			letter_counts[c - 65] += 1;
		} else if(c >= 97 && c <= 122){
			/* handle lowercase letters */
			letter_counts[c - 97] += 1;
		}
    }
	if (line){
		free(line);
	}
	fclose(fp);
}

void write_to_pipe(int i, int **fds){
	close(fds[i][0]);
	write(fds[i][1], letter_counts, sizeof(int)*26);
}
