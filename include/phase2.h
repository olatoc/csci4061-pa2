// Add Guard to header file
// Function prototypes for
//			map function that will go through text files in the Mapper_i.txt to get the (letter, wordcount)
#ifndef PHASE2_H

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
#include "phase1.h"
#define PHASE2_H

int *letter_counts;
int phase_2(int i, int **fds);
void read_mapper_file(int i);
void parse_file(char * filename);
void write_to_pipe(int i, int **fds);

#endif