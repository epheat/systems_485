/*
 * Evan Heaton
 * Program 5
 * helpers
 */
/* $begin helpers */
#include "csapp.h"
#include "helpers.h"
#include "parser.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

using namespace std;

void echo(int connfd) 
{
    int n; 
    char buf[MAXLINE]; 
    rio_t rio;

    Rio_readinitb(&rio, connfd);
    while((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) {
	printf("server received %d bytes\n", n);
	Rio_writen(connfd, buf, n);
    }
}

int login(int connfd, rio_t rio, char* client_hostname, char* client_port, char* username) {
	
	//char username[MAXLINE];
	char password[MAXLINE];
	char login_approve[] = "Login Approved\n";
	char login_fail[] = "Login Failed\n";
	//char dummy[] = "Kappa = Grey Face (no space)\n";
	int n; //Number of bytes read

	//rio_t rio;
	//Rio_readinitb(&rio, connfd);
		
	n = Rio_readlineb(&rio, username, MAXLINE);
	if (!n)
		return -3;
	//printf("username: %s\n", username);

	//Rio_writen(connfd, dummy, strlen(dummy));

	n = Rio_readlineb(&rio, password, MAXLINE);
	if (!n)
                return -3;
	//printf("\npassword: %s\n", password);
	
	/* User [username] logging in from [IPaddr] at TCP port [PortNumber] */
	printf("User %s logging in from %s at TCP port %s.\n", 
			strtok(username, "\n"), client_hostname, client_port);
	
	/* VALIDATION */
	ifstream in;
	in.open("rrshusers.txt");
	string user, pass;
	bool user_was_found = false;
	bool correct_pass = false;
	
	while (in >> user >> pass) {
		//cout << "user:" << user << "pass:"  << pass;
		if (strcmp(user.c_str(), strtok(username, "\n")) == 0) {
		//if (user == username) {
			user_was_found = true;
			if (strcmp(pass.c_str(), strtok(password, "\n")) == 0)
			//if (pass == password) 
				correct_pass = true;
			break;
		}
	}	
	
	in.close();

	if (!user_was_found/*username is not in file*/) {
		Rio_writen(connfd, login_fail, strlen(login_fail));
		return -1;
	} else {
		if (!correct_pass/*password does not match*/) {
			Rio_writen(connfd, login_fail, strlen(login_fail));
			return -2;
		} else {
			Rio_writen(connfd, login_approve, strlen(login_approve));
			return 0;
			//Logged in!
		}
	}
}

int commands(int connfd, rio_t rio, char *username) {
	
	char command[MAXLINE];
        char dum1[] = "BabyRage\n";
        char dum2[] = "Keepo\n";
        char dum3[] = "PogChamp\n";
        char end[] = "\nRRSH COMMAND COMPLETED\n";
	char execute_fail[MAXLINE];
	
	int n; //Number of bytes read
	
	ifstream in;
	string extracted_cmd;
	
	while (1) {
		
		/* Read a command */
		n = Rio_readlineb(&rio, command, MAXLINE);
		if (!n)
			return -3;	
	
		/* parse the command */
		struct command *parsed;
		parsed = parse_command(command);
		
		printf("User %s sent the command %s to be executed.\n", 
				username, parsed->args[0]);
		
		/* does the command exist in rrshcommands.txt? */
		bool command_found = false;
		
		in.open("rrshcommands.txt");
		while (in >> extracted_cmd) {/*will it reset on the next loop/command?*/
			if (strcmp(extracted_cmd.c_str(), parsed->args[0]) == 0) {
				command_found = true;
				break;
			}
		}
		in.close();
		
		if (command_found) {
			printf("Executing command %s on behalf of user %s.\n",
					parsed->args[0], username);
			//for the sake of testing, just send back 4 lines
                	if (strcmp(parsed->args[0], "Kappa") == 0) {
				Rio_writen(connfd, dum1, strlen(dum1));
                		Rio_writen(connfd, dum2, strlen(dum2));
                		Rio_writen(connfd, dum3, strlen(dum3));
	                	Rio_writen(connfd, end, strlen(end));
			} else {
			
			
				/* Execute external command */	
			
				/* FORK */
				pid_t child_pid = fork();
				if (child_pid < 0) {
					//Can't fork!!
				} else if (child_pid == 0) {
					/* Child Process */
				
					/* Call necessary dup2() functions */
					int dev_null = open("/dev/null", O_RDWR);
					Dup2(dev_null, 0);
					Dup2(connfd, 1);
					Dup2(connfd, 2);
					/* Call Execve() */
					Execve(parsed->args[0], parsed->args, environ);
				
					/* End Child Process */
				} else {
					/* Parent Process */
					pid_t w;
					int status;
					if ((w = waitpid(child_pid, &status, 0)) < 0) {
						//exit failure!
					} 
					Rio_writen(connfd, end, strlen(end));
				
					/* End Parent Process */
				}
			}
			
			
			
			
			
			
			
			
		} else {
			sprintf(execute_fail, "Cannot execute %s on this server.\n", 
					parsed->args[0]);
			Rio_writen(connfd, execute_fail, strlen(execute_fail));
			Rio_writen(connfd, end, strlen(end));
			printf("Command %s denied from user %s.\n",
					parsed->args[0], username);	
		}	
	}	
	
	return 0;
}



/* $end helpers */

