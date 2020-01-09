#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/main.h"

int main(int argc, char *argv[]){

	// argument count check
	if (argc != 3){
		fprintf(stderr, "incorrect argument number");
	}
	//sample_dir is the directory to traverse and parse
	char *sample_dir;
	sample_dir = (char*)malloc(sizeof(char)*128);
	strcpy(sample_dir, argv[1]);

	int m = atoi(argv[2]);
	int files_per_m[m];
	//phase1 - Data Partition Phase
	phase_1(sample_dir, m);
	free(sample_dir);

	//create array of file descriptors; m of them
	//one array for each pipe
	//allocate memory for dynamic arrays to pass around in phase2 and phase3
	int **fds = (int **)malloc(sizeof(int*)*m);
	for (int i = 0; i < m; i++){
		fds[i] = (int*)malloc(sizeof(int));
	}
	//create pipes
	for (int i = 0; i < m; i++){
		if ((pipe(fds[i])) == -1){
			fprintf(stderr, "pipe failed\n");
		}
	}
	
	//just make a function call to code in phase2.c
	//phase2 - Map Function
	//create m processes and call phase2 on each of them
	int pid;
	for (int i = 0; i < m; i++){
		pid = fork();
		if (pid < 0){
			fprintf(stderr, "error creating process");
		} else if (pid == 0){
			phase_2(i, fds);
		} else if (pid > 0){
			//wait for each process to finish
			wait(NULL);
		}
	}
	//wait for children to terminate

	//just make a function call to code in phase3.c
	//phase3 - Reduce Function
	//fork a process for reduce and call reduce on child process
	int reduce_pid = fork();
	if (reduce_pid < 0){
		fprintf(stderr, "error creating process");
	} else if (reduce_pid == 0){
		/* child process */
		phase_3(fds, m);
	} else if (reduce_pid > 0){
		//wait for process to finish
		wait(NULL);
	}

	//free allocated memory for file descriptor array
	for (int i = 0; i < m; i++){
		free(fds[i]);
	}
	free(fds);
		
	//just make a function call to code in phase4.c
	//master process reports the final output
	//master process calls phase4, which creates and writes to FinalResult.txt
	phase_4();
	
	return 0;
}