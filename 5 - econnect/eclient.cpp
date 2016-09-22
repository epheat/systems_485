/*
 * Evan Heaton
 * Program 5
 * eclient.cpp
 *
 */
/* $begin eclientmain */
#include "csapp.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv) 
{
	int clientfd;
	char username[MAXLINE], password[MAXLINE], *host, *port, buf[MAXLINE];
	rio_t rio;
	
	
	if (argc != 3) {
		fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
		exit(0);
	}
	host = argv[1];
	port = argv[2];

	clientfd = Open_clientfd(host, port);
	Rio_readinitb(&rio, clientfd);
	
	std::cout << "Welcome to eclient! Please login.\nUsername: ";
	//std::cin.ignore(256, '\n');
	Fgets(username, MAXLINE, stdin);
	//std::cin >> username;
	Rio_writen(clientfd, username, strlen(username));
	std::cout << "Password: ";
	
	//Rio_readlineb(&rio, buf, MAXLINE);
	
	Fgets(password, MAXLINE, stdin);
	//std::cout << "PASSWORD READ: " << password;
	//std::cin >> password;
	Rio_writen(clientfd, password, strlen(password));
	Rio_readlineb(&rio, buf, MAXLINE);
	if (strcmp(buf, "Login Approved\n") != 0) { /* Login Fail */
		std::cout << "Login Failed\n";
		Close(clientfd);
		exit(0);
	}
	
	/* Begin Command Portion */
	while (1) {
		printf("esh> ");
		Fgets(buf, MAXLINE, stdin);
		if (strcmp(buf, "quit\n") ==0) {
			break;
		} //QUIT!
		else if (strcmp(buf, "\n") ==0)
			continue;
		Rio_writen(clientfd, buf, strlen(buf)); //send unlimited commands
		
		Rio_readlineb(&rio, buf, MAXLINE);
		while (strcmp(buf,"RRSH COMMAND COMPLETED\n") != 0) {
			cout << buf;
			Rio_readlineb(&rio, buf, MAXLINE);
		}
	}
	
	Close(clientfd); //line:netp:echoclient:close
	exit(0);
}
/* $end eclientmain */
