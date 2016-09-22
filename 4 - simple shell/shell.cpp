#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

#include <fcntl.h> //for O_ constant definitions

using namespace std;

//Evan Heaton
//Program 4
//shell.cpp

#define MAX_LINE 1024

int main(int argc, char* argv[]) {
	
	//comment in README about MAX_LINE size
	string buffer;

	//TO DO: gotta check for command line arguments and handle them as scripts
	
	//getline_status set to getline's return value. If it's -1,
	//indicating EOF or another error, exit the loop
	
	ifstream in;
	if (argc > 1) {
		in.open(argv[1]);
		//cout << "Loaded script file";
	}

	while (1) {
		
		if (argc == 1) {
			cerr << "shell> ";
			fflush(stderr);
		
			getline(cin, buffer);
		
			if (cin.fail()) {
			}
			if (cin.eof()) {
			}
		}
		else {
			getline(in, buffer);
			if (in.fail()) {
				//perror("Failed to read script");
			}
			if (in.eof()) {
				//break;
				
			}
			//cout << buffer;
		}

		struct command* current_command;
		current_command = parse_command(buffer.c_str());
		
		//TO DO: step 3: Based on argument 0 (the command name), either execute one of the built-in commands, or fork and execute an external program.
		
		if (current_command->args[0] == NULL) { //(nothing) entered
			free_command(current_command);
			continue;
		}
		else if (strcmp(current_command->args[0], "exit") == 0) {
			free_command(current_command);
			break;
		}
		else if (strcmp(current_command->args[0], "cd") == 0) {
			if (current_command->args[1] == NULL) {
				//change to home directory
				if (chdir(getenv("HOME")) == -1) {
					perror("Failed to go to Home Directory");
				}
			}
			else {
				//change to args[1]
				if (chdir(current_command->args[1]) == -1 ) {
					perror("Error changing directory");
				}
			}
			
		}
		else if (strcmp(current_command->args[0], "setenv") == 0 ) {
			//check for no arguments
			if (current_command->args[1] == NULL) {
				perror("No Environment variable specified");
			} else if (current_command->args[2] == NULL) {
				if (unsetenv(current_command->args[1]) == -1)
					perror("Error unsetting environment variable");
			} else {
				if (setenv(current_command->args[1], current_command->args[2], 420) == -1)
					perror("Error setting environment variable");
			}
		}
		
		else {
			pid_t child_pid = fork();
			if (child_pid < 0) {
				perror("Can't fork!");
			}
			else if (child_pid == 0) {
				//child process
				//I/O redirection
				if (current_command->in_redir != NULL) {
					int oldfd = open(current_command->in_redir, O_RDONLY);
					if (dup2(oldfd, 0) == -1)
						perror("Error with in-redirection");
					else
						close(oldfd);
				}
				if (current_command->out_redir != NULL) {
					int oldfd = open(current_command->out_redir, O_WRONLY | O_TRUNC | O_CREAT , S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH );
					if (dup2(oldfd, 1) == -1 ) {
						perror("Error with out-redirection");
						_exit(69);
					}
					else
						close(oldfd);
				}

				int exec_result = execvp(current_command->args[0],current_command->args);
				//ideally these lines won't execute??
				//Zack Arnett
				if (exec_result == -1) {
					perror("Could not execute process");
				}
				
				return -1;
			}
			else {
				//parent process
				pid_t w;
				int status;
				signal(SIGINT,SIG_IGN); //IGNORE!!
				if ((w = waitpid(child_pid, &status, 0)) < 0) {
					perror("Couldn't wait for child!");
					exit(EXIT_FAILURE);
					//return -1;
				}
				signal(SIGINT,SIG_DFL); //Back to normal
				if (WIFSIGNALED(status) != 0) {
					perror("Command Killed");
				}
				/* My attempt to get test case 5..... But when I put this code in it messes up plenty of other test cases. UGH
				if (w > 0 && WIFEXITED(status)) {
					fprintf(stderr,"exited with status=%d", WEXITSTATUS(status));
				}
				*/
				
			}
			
			
			//fork??
			//echo(current_command);
		}
		
		free_command(current_command);
		
	}	
	
	//getline() == -1 !!! EOF?
	
	in.close();

	return 0;
}

//Wait this is inherited, nevermind. I'll still leave it in because why not
void echo(struct command *c) {
	
	int i=0;
	while (c->args[i++] != NULL)
		cout << c->args[i] << " ";
	cout << endl;
	return;
}
