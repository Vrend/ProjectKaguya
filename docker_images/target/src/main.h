#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>

void* internal_server();
void* external_server();

void unlock_system();
void totally_secure_copy(char* input);

void* handle_connection(void* args);
char* gen_table(char** labels, float* target, float* actual);
void gen_space(char* spaces, int n);
int handle_input(char* input, int fd);
void set_target(float* targets, char** labels, char* property, float value);
int update_table(float* targets, float* actuals);

void write_flag();

typedef struct response_args {
	int fd;
	char ip[30];
	int port;
} response_args;
