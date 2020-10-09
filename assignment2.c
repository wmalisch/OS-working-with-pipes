#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

// Reading and writing end of the pipe
#define READ_END 0
#define WRITE_END 1

int main(int argc, char **argv)
{

	/*************************************** command line arguments ***************************************
		To compile assignment2.c: gcc assignment2.c -o assignment2
		To run your program: ./assignment2 "CS" "3305" " is fun!"
		argv[0] = "./assignment2"
		argv[1] = "CS"
		argv[2] = "3305"
		argv[3] = " is fun!"

		Number of arguments (argc) = 4

		In this assignment, the parent process reads argv[1] and the child process reads argv[2] and argv[3]
		e.g. In the parent process: char *x = argv[1];
	*******************************************************************************************************/

	// If the user does not pass X, Y and Z, the program will terminate
	if (argc != 4)
	{
		printf("Invalid arguments\n");
		exit(0);
	}

	// You must insert the following into your code (Replace zeros with the appropriate values/variables)
	// 
	// Note: You do not need to implement a function to concatenate two strings. "string.h" header file has been included



	/***************************************************************************************************
	 * 										   YOUR CODE GOES HERE										
	 ***************************************************************************************************/

	int port[2];
	pid_t pid, x, y;

	// Create pipe and make sure theres no error
	if(pipe(port) < 0){
		perror("Pipe error");
		exit(0);
	}

	// Call fork to create child process
	pid = fork();

	// Error in fork
	if (pid < 0) 
	{
    	perror("fork error");
    	exit(0);
  	}
	
	// Parent process
	if(pid > 0) 
	{
		x = getpid();
		char store[(strlen(argv[1])+strlen(argv[2])+strlen(argv[3]))];  // Set a char [] to hold the entire concatenation of string arguments
		printf("A pipe is created for communication between parent (PID %d) and child\n", x);
		printf("parent (PID %d) created a child (PID %d)\n", x, pid);
		char *str = argv[1];  // Get CS string
		printf("parent (PID %d) receives X = \"%s\" from the user\n", x, str);
		wait(NULL);
		read(port[0],&store,(strlen(argv[2])+strlen(argv[3])));
		printf("parent (PID %d) reads Y' from the pipe (Y' = \"%s\")\n", x, store);
		printf("parent (PID %d) concatenates X and Y' to generate the string: %s\n", x, strcat(str,store));
	}

	// Child process
	if(pid == 0) 
	{
		y = getpid();
		char *three = argv[2];  // Get 3305 string
		char *fun = argv[3];  // Get is fun string
		printf("child (PID %d) receives Y = \"%s\" and Z = \"%s\" from the user\n", y, three, fun);
		printf("child (PID %d) concatenates Y and Z to generate Y'= %s\n", y, strcat(three, fun));
		write(port[1],three,strlen(three));
		printf("child (PID %d) writes Y' into the pipe\n", y);			
	}
	return 0;
}
