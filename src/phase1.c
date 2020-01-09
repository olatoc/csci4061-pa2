#define _BSD_SOURCE

#include "../include/phase1.h"
// You are free to use your own logic. The following points are just for getting started
/* 	Data Partitioning Phase - Only Master process involved
	1) 	Create 'MapperInput' folder
	2) 	Traverse the 'Sample' folder hierarchy and insert the text file paths
		to Mapper_i.txt in a load balanced manner
	3) 	Ensure to keep track of the number of text files for empty folder condition 
*/

void phase_1(char *folder, int m){
	//Create MapperInput folder
	int pid = fork();
	char path[128];
	char *args_mkdir[3] = {"mkdir", "MapperInput", NULL};
	if (pid < 0){
		fprintf(stderr, "error creating process");
	} else if (pid > 0){
		/* parent process */
		wait(NULL);
	} else if (pid == 0){
		/* child process */
		execvp(args_mkdir[0], args_mkdir);
	}

	//append ../Testcases/ to beginning of directory name, in case it is not specified
	sprintf(path, "%s", folder);
	/* create mapper files */
	create_mapper_files(m); //O(m)

	//count the total files within the directory to be used for partitioning
	int total_files = count_files(path); //O(n)
	if (total_files == 0){
		fprintf(stdout,"The Sample folder is empty\n");
		return;
	}
	//allocate memory for array of filepaths
	all_file_paths = (char**)malloc(sizeof(char*)*total_files);
	for (int i = 0; i < total_files; i++){
		all_file_paths[i] = (char*)malloc(sizeof(char)*128);
	}
	//global counter to fill array of all filepaths
	file_array_i = 0;
	fill_file_array(path); //O(n)

	files_per_m = partition(m, total_files); //O(m)

	//fill Mapper_i.txt files with filepaths of xxx.txt files to parse
	fill_mapper_files(files_per_m, all_file_paths, total_files, m); //O(n)

	//free all dynamic memory
	for (int i = 0; i < total_files; i++){
		free(all_file_paths[i]);
	}
	free(all_file_paths);
}

//this function uses depth first search to count the total files in the directory pointed to by dir
int count_files(char *dir){
	DIR *dr = NULL;
	struct dirent *ent;
	char *path;
	int file_count;
	if((dr = opendir(dir)) == NULL){
		return 0;
	}
	if (dr == NULL) {
		printf("ERROR: directory doesn't exist\n");
		return 0;
	}
	file_count = 0;
	while ((ent = readdir(dr)) != NULL){
		if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0){
			continue;
		}
		if (ent->d_type == DT_REG){
			file_count += 1;
		} else if (ent->d_type == DT_DIR){
			path = (char*)malloc(256);
			sprintf(path,"%s/%s", dir, ent->d_name);
			file_count += count_files(path);
			free(path);
		}
	}
	closedir(dr);
	return file_count;
}

//this function uses depth first search to fill the array
//all_file_paths with all the files in the directory pointed to by dir
int fill_file_array(char *dir){
	DIR *dr = NULL;
	struct dirent *ent;
	char *path;
	int file_count;
	if((dr = opendir(dir)) == NULL){
		return 0;
	}
	if (dr == NULL) {
		printf("ERROR: directory doesn't exist\n");
		return -1;
	}
	file_count = 0;
	while ((ent = readdir(dr)) != NULL){
		if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0){
			continue;
		}
		if (ent->d_type == DT_REG){
			path = (char*)malloc(256);
			sprintf(path,"%s/%s", dir, ent->d_name);
			strcpy(all_file_paths[file_array_i], path);
			free(path);
			file_array_i += 1;
		} else if (ent->d_type == DT_DIR){
			path = (char*)malloc(256);
			sprintf(path,"%s/%s", dir, ent->d_name);
			fill_file_array(path);
			free(path);
		}
	}
	closedir(dr);
}

//this function determines number of files to store in each Mapper_i.txt file
int *partition(int m, int files){
	int *files_per_m = (int *)malloc(sizeof(int)*m);
	int remainder = files % m;
	for (int i = 0; i < m; i++){
		files_per_m[i] = files/m;
	}
	int i = 0;
	while (i < remainder){
		files_per_m[i % m] += 1;
		i += 1;
	}
	return files_per_m;
}

//this function fills the Mapper_i.txt files with the list of .txt files to parse by each mapper
void fill_mapper_files(int *files_per_m, char **all_file_paths, int file_count, int m){
	FILE *fp;
	char filename[128];
	int k = 0;
	for (int i = 0; i < m; i++){
		sprintf(filename, "MapperInput/Mapper_%d.txt", i);
		fp = fopen(filename, "w+");
		for (int j = 0; j < files_per_m[i]; j++){
			fprintf(fp, "%s\n", all_file_paths[k]);
			k++;
		}
		fclose(fp);
	}
}

/* this function creates the Mapper_i.txt files inside MapperInput */
void create_mapper_files(int m){
	/* create files */
	FILE *fp;
	char filename[128];
	for (int i = 0; i < m; i++){
		sprintf(filename, "MapperInput/Mapper_%d.txt", i);
		fp = fopen(filename, "w+");
		fclose(fp);
	}
}