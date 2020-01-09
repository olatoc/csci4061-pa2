// Add Guard to header file (google what are guards)
// Function prototypes to 
//			Traverse the Folder
//			Partition the text file paths to 'm' files 
#ifndef PHASE1_H

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
#define PHASE1_H

int file_count;
int file_array_i;
char **all_file_paths;
int *files_per_m;

void phase_1(char *folder, int m);
int *partition();
int count_files();
void create_mapper_files(int m);
int fill_file_array(char *dir);
void fill_mapper_files(int *files_per_m, char **all_file_paths, int file_count, int m);


#endif