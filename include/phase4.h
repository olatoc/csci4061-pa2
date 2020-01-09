// Add Guard to header file
// Function prototypes for
//			Master process's reporting procedure

#ifndef PHASE4_H

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
#define PHASE4_H

int *letter_counts_final;

void phase_4();
void read_reducer_result();
void write_final_result(int *letter_counts_final);

#endif