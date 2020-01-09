#include "phase3.h"
// You are free to use your own logic. The following points are just for getting started
/* Reduce Function
	1)	The reducer receives the list from 'm' mappers via pipes
	2)	Ensure proper closing of pipe ends
	3) 	Combine the lists to create a single list
	4) 	Write the list to "ReducerResult.txt" in the current folder
*/

void phase_3(int **fds, int m){
	//arrays to store letter counts per mapper process and the total
	int letter_counts_m[m][26];
	int letter_counts_total[26];
	/* read from pipe output of each mapper into individual arrays */
	for (int i = 0; i < m; i++){
		close(fds[i][1]);
		read(fds[i][0], letter_counts_m[i], sizeof(int)*26);
	}
	//zero array of junk from stack
	for (int i = 0; i < 26; i++){
		letter_counts_total[i] = 0;
	}
	/* combine all arrays into one array */
	for (int i = 0; i < m; i++){
		for (int j = 0; j < 26; j++){
			letter_counts_total[j] += letter_counts_m[i][j];
		}
	}
	//write to ReducerResult.txt
	write_to_reducer_file(letter_counts_total);
	//kill process
	exit(0);
}
//this function creates and writes to the temp file "ReducerResult.txt"
void write_to_reducer_file(int *letter_counts_total){
	FILE *fp;
	char filename[128];
	int k = 0;
	sprintf(filename, "ReducerResult.txt");
	fp = fopen(filename, "w+");
	for (int i = 0; i < 26; i++){
		fprintf(fp, "%c %d\n", 65 + i, letter_counts_total[i]);
	}
	fclose(fp);
}
