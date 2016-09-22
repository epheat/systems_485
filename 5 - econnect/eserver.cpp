/* 
 * Evan Heaton
 * Program 5
 * eserver.cpp 
 */ 
/* $begin eservermain */
#include "csapp.h"
#include "helpers.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) 
{
	int listenfd, connfd;
	socklen_t clientlen;
	struct sockaddr_storage clientaddr;  /* Enough space for any address */  //line:netp:echoserveri:sockaddrstorage
	char client_hostname[MAXLINE], client_port[MAXLINE];

	if (argc != 2) {
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(0);
	}

	listenfd = Open_listenfd(argv[1]);
	while (1) {
		clientlen = sizeof(struct sockaddr_storage); 
		connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        	Getnameinfo((SA *) &clientaddr, clientlen, client_hostname, MAXLINE, 
                		client_port, MAXLINE, 0);
        	printf("Connected to (%s, %s)\n", client_hostname, client_port);
		//printf("prelogin");
		rio_t rio;
        	Rio_readinitb(&rio, connfd);
		char username[MAXLINE];
		int login_status = login(connfd, rio, client_hostname, client_port, username);
		if (login_status == -3) {
			printf("Error: Disconnected.\n");
			continue;
		} else if (login_status == -2) {
			printf("User %s denied access: incorrect password.\n", username);
			continue;
		} else if (login_status == -1) {
			printf("User %s denied access: unauthorized user.\n", username);
			continue;
		} else if (login_status == 0) {
			printf("User %s successfully logged in.\n", username);
			//YAY!
		}
		//printf("postlogin");
		//echo(connfd);
		
		/* Begin Command Protocol */
		int command_status = commands(connfd, rio, username);
		if (command_status == -3) {
			printf("User %s disconnected.\n",username);
			continue;
		}
		
		Close(connfd);
	}
	exit(0);
}
/* $end eservermain */
