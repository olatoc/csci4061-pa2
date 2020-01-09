// Add Guard to header file
// Function prototype for 
//			reduce function that will receive list from all the Mappers to create a single list
//			the single list is then written to ReducerResult.txt

#ifndef PHASE3_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#define PHASE3_H

void phase_3(int **fds, int m);
void write_to_reducer_file(int *letter_counts_total);

#endif