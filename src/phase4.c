#include "phase4.h"
// You are free to use your own logic. The following points are just for getting started
/* Final Result
	1)	The master process reads the "ReducerResult.txt"
	2) 	Print the contents to standard output which is redirected to "FinalResult.txt"
			i.e., on using printf, the statement should be written to "FinalResult.txt"
*/

void phase_4(){
	letter_counts_final = (int*)malloc(sizeof(int)*26);
	read_reducer_result();
	write_final_result(letter_counts_final);
}

/* this function reads the file ReducerResult.txt in to an array letter_counts_final */
void read_reducer_result(){
	char filename[128];
	sprintf(filename, "ReducerResult.txt");
	FILE *fp;
    char *line;
    size_t len = 0;
    fp = fopen(filename, "r");
    if (fp == NULL){
        exit(1);
	}
	int i = 0;
    while ((getline(&line, &len, fp)) != -1) {
		letter_counts_final[i] = atoi(&line[2]);
		i++;
    }
	if (line){
		free(line);
	}
	fclose(fp);
}


/* this function writes the final output, the textfile "FinalResult.txt"
	by redirecting the stdout file to said textfile */
void write_final_result(int *letter_counts_final){
	// store temp lines to send to stdout
	char line[128];
	//open file
	int fd = open("FinalResult.txt", O_RDWR | O_CREAT | O_TRUNC, 0600);
	//dup stdout to undo redirection later
    int out = dup(1);
	//move stdout to fd
    if (dup2(fd, 1) == -1) {
		fprintf(stderr,"redirection error");
	}
	//print ot stdout (FinalResult.txt)
	for (int i = 0; i < 26; i++){
		sprintf(line, "%c %d", 65 + i, letter_counts_final[i]);
		puts(line);
	}
	//send output buffer to stdout
    fflush(stdout);
	close(fd);
	//undo redirection
    dup2(out, fileno(stdout));
    close(out);
}
