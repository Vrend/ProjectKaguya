#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


void* internal_server();
void* external_server();

void unlock_system();
void totally_secure_copy(char* input);
