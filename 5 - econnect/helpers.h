
#ifndef HELPERS_H
#define HELPERS_H

#include "csapp.h"

void echo(int connfd);
int login(int connfd, rio_t rio, char *client_hostname, char *client_port, char *username);
int commands(int connfd, rio_t rio, char *username);



#endif //HELPERS_H
