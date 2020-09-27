# This was a project for the class CSCI 4061: Introduction to Operating Systems   
# csci4061-pa2

                /*
                * test machine: csel-kh1250-01.cselabs.umn.edu
                * date due: October 25th, 2019
                * name: Oliver Latocki, Jonathan Sulisz
                * x500: latoc004, sulis005  
                */

• **The purpose of our program**

The purpose of the program is to demonstrate the Map/Reduce programming model, wherein a problem is broken up into several parallel computations, the "mapper" phase, which return intermediate data to be then coalesced into a final solution via the "reducer" phase.  
The program demonstrates this with a simple program to count the number of times a word within some files starts with any given letter. These files exist in a sample directory, which also contains subdirectories. The program returns the final result as a file of the format:

`A 123`  
`B 123`  
...  


# • How to compile the program

Using the Makefile provided in the src folder, run:  

`make`  


***ASSUMPTIONS***

-Those specified in the writeup  
-The program is passed arguments in the way they are passed in the Makefile:  

`./mapreduce ../Testcases/TestCase3 32`  

Where the entire relative path of the Sample direcory is given, not just the Sample directory name.

# • What exactly your program does

This program is split into four phases, each of which produces intermediate data necessary for the subsequent phase.  
**Phase Overviews**  
***Phase 1***  
This phase traverses the directory specified in the first command line argument. It counts the textfiles and partitions them evenly among the m processes, also specified in the command line arguments. Specifically, it creates m files, "Mapper_i.txt" inside the directory "MapperInput" and fills them with the filepaths of the respective partitioned textfiles. 

&nbsp;&nbsp;&nbsp; Count_files(char *dir){...}

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Loops through the given directory(s) to figure out how many text files are present. If another directory is present within the directory it will open that directory to search again. Returns integer of total number of files counted.

&nbsp;&nbsp;&nbsp; ***int fill_file_array(char *dir){...}***

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; This function loops through the entire directory, and adds file directory path to the array (all_file_paths[]). The function returns an integer that is based on how the tests ran.

&nbsp;&nbsp;&nbsp; ***int *partition(int m, int files){...}***

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Simple function that runs two for-loops to determine the number of files to store in each mapper_x.txt file. Uses known amount of files and total number of files to calculate. Returns array of each file size.

&nbsp;&nbsp;&nbsp; ***void fill_mapper_files(...){...}***

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; For loop that offloads it's content to appropiate Mapper_X.txt file.

&nbsp;&nbsp;&nbsp; ***void create_mapper_files(int m){...}***

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; For loops that creates Mapper_x.txt files based off of given argv value.

***Phase 2***  
This is the "mapper" phase of the Map/Reduce process. This phase is called m times, each by a separate process which is forked in main. Since there are m processes running, each call to phase_2 is only responsible for its own parition, or its own "Mapper_i.txt" file.  
Before calling phase_2, main creates m pipes, which phase_2 will write to once it is called.
Phase 2 opens each of the textfiles inside its mapper file, counts the occurances of words starting with each letter of the alphabet, and stores the total as an array of ints.  
Phase 2 then writes the array to the pipe made in main. Once the process has written to the pipe, it terminates, returning to main.  

&nbsp;&nbsp;&nbsp; ***void read_mapper_files(...){...}***

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Opens Mapper_X.txt files and splits the lines through a new char, the line is passed off to parse_file(...)

&nbsp;&nbsp;&nbsp; ***void parse_file(...){...}***

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Following read_mapper_files(), this function utilizes getline to traverse the entire char and only reads characters. To distinguish capital from lower case an if-statement if used with subtracting the according ASCII value from the value fetched to add count (letter_count).

&nbsp;&nbsp;&nbsp; ***void write_to_pipe(...){...}***

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Write() to the pipe with the letter_count incremented throughout phase_2().

***Phase 3***  
This is the "reduce" phase of the Map/Reduce process, which is forked by main as a new process. This phase reads the pipes written to by the mapper processes and combines the arrays stored in them. It does this by creating an array that represents the total sum of each array.  
This phase then writes the total sum of all the letter counts to a file called "ReducerResult.txt" and exits.  

&nbsp;&nbsp;&nbsp; ***void write_to_reducer_file(...){...}***

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Creates ReducerResult.txt file in main directory and loops through letter_counts_total[]. Sets Reducer Result as "character number_counts_total".

***Phase 4***  
This is the final phase of the program. Once all the mapper processes and the reducer process have exited, phase_4 outputs the final result. To demonstrate file redirection, this phase reads the data in "ReducerResult.txt" into an array and prints it to stdout. However, it redirects stdout to a file named "FinalResult.txt", causing the output to be printed there.

&nbsp;&nbsp;&nbsp; ***void read_reducer_result(...){...}***

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Loops through ReducerResult.txt from phase 3 and places results in letter_counts_final.

&nbsp;&nbsp;&nbsp; ***void write_final_result(...){...}***

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Creates FinalResult.txt along with writing the values from letter_counts_final, from read_reducer_result, but is written through STOUT.

# • If you have attempted extra credit  

We have.
