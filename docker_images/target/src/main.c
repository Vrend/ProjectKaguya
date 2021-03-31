#include "main.h"

volatile int locked;

volatile char sensor_data[50];

int main() {
  locked = 1;

  pthread_t ep;
  pthread_t ip;

  pthread_create(&ep, NULL, external_server, NULL);
  pthread_create(&ip, NULL, internal_server, NULL);

  pthread_join(ep, NULL);
  pthread_join(ip, NULL);
  return 0;
}

/* DEBUG: This should never be run */
void unlock_system() {
  printf("Unlocking system...\n");
  locked = 0;
  while(1); // Block further sensor data input
}

void totally_secure_copy(char* input) {
  char sensor_data_raw[50];
  strcpy(sensor_data_raw, input);
  /* DEBUG: Need to make data modifications... */
  strncpy(sensor_data, sensor_data_raw, 50);
}

void* internal_server() {
  int fd = socket(AF_INET, SOCK_DGRAM, 0);

  struct sockaddr_in s_addr, c_addr;

  unsigned int slen = sizeof(s_addr);
  unsigned int clen = sizeof(c_addr);

  s_addr.sin_family = AF_INET;
  s_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  s_addr.sin_port = htons(5001);

  if(fd < 0) {
    printf("Error creating internal socket\n");
    exit(1);
  }

  if(bind(fd, (struct sockaddr*) &s_addr, slen) < 0) {
    printf("Error binding socket\n");
    exit(1);
  }

  printf("Listening for messages on 127.0.0.1:5001 ...\n");

  int recv_len;

  while(1) {
    char tbuff[100];
    bzero(tbuff, 100);
    if((recv_len = recvfrom(fd, tbuff, 100, 0, (struct sockaddr*) &c_addr, &clen)) == -1) {
      sleep(1);
      continue;
    }
    tbuff[99] = '\0';

    char* output = "Data received!\n";
    int soutput = strlen(output);

    sendto(fd, output, soutput, 0, (struct sockaddr*) &c_addr, clen);

    totally_secure_copy(tbuff);

    printf("Size of input: %d, locked: %d\n", recv_len, locked);
    printf("Sensor Data: %s\n", sensor_data);

  }

  close(fd);

  return NULL;
}

void* external_server() {

  int fd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(5000);

  int addr_len = sizeof(addr);

  if(bind(fd, (struct sockaddr_in*) &addr, addr_len) < 0) {
    printf("Failed to bind\n");
    return NULL;
  }

  if(listen(fd, 99) < 0) {
    printf("Failed to listen\n");
    return NULL;
  }

  if(fd < 0) {
    printf("Failed to make socket\n");
    return NULL;
  }

  while(1) {
    int client_fd = accept(fd, (struct sockaddr_in*) &addr, (socklen_t*) &addr_len);

    pthread_t client;
    response_args* args = (response_args*) malloc(sizeof(response_args));
		args->fd = client_fd;
		strcpy(args->ip, inet_ntoa(addr.sin_addr));
		args->port = (int) ntohs(addr.sin_port);
		pthread_create(&client, NULL, handle_connection, (void*) args);
  }

  return NULL;
}

void* handle_connection(void* args) {
	pthread_detach(pthread_self());
	int fd = ((response_args*) args)->fd;
	char ip[30];
	strcpy(ip, ((response_args*) args)->ip);
	int port = ((response_args*) args)->port;
	free(args);

  char* labels[4] = {"Altitude", "Pressure", "Temperature", "Speed", };
  float actual[4] = {35994.39f, 11.211f, 68.322f, 482.17f};
  float target[4] = {36000.0f, 11.3f, 68.0f, 480.0f};

	char read_buffer[50];

  printf("Request from %s on port %d\n", ip, port);

  int e;

  while(1) {
    bzero(read_buffer, 50);
    char* clear = "\033[H\033[J";
    char* prompt = "\n >> ";

    e = send(fd, clear, strlen(clear), MSG_NOSIGNAL);
    if(e < 0) {
      break;
    }

    char* output = gen_table(labels, target, actual);
    send(fd, output, strlen(output), MSG_NOSIGNAL);
    free(output);

    send(fd, prompt, strlen(prompt), MSG_NOSIGNAL);

    e = read(fd, read_buffer, 50);
    if(e <= 0) {
      break;
    }

    if(strlen(read_buffer) > 0 && read_buffer[0] == 'q') {
      char* done = "Closing connection...\n";
      send(fd, done, strlen(done), MSG_NOSIGNAL);
      break;
    }

    printf("%s\n", read_buffer);
  }

	close(fd);
	pthread_exit(0);
}

void gen_space(char* spaces, int n) {
  strcpy(spaces, " ");
  for(int i = 1; i < n; i++) {
    strcat(spaces, " ");
  }
}

char* gen_table(char** labels, float* targets, float* actuals) {
  char* bound = " +-------------+------------+------------+\n";
  char* header = " |    NAME     |   ACTUAL   |   TARGET   |\n";
  // available space per column
  int col1 = 13;
  int col2 = 12;
  int col3 = 12;

  char* output = malloc(1000);
  strcpy(output, "\n");
  strcat(output, bound);
  strcat(output, header);
  strcat(output, bound);

  for(int i = 0; i < 4; i++) {
    char* label = labels[i];
    float target = targets[i];
    float actual = actuals[i];
    char target_s[10];
    char actual_s[10];
    gcvt(target, 8, target_s);
    gcvt(actual, 8, actual_s);

    int spacing1 = (col1 - strlen(label)) / 2;
    int spacing2 = col1 - strlen(label) - spacing1;
    int spacing3 = (col2 - strlen(actual_s)) / 2;
    int spacing4 = col2 - strlen(actual_s) - spacing3;
    int spacing5 = (col3 - strlen(target_s)) / 2;
    int spacing6 = col3 - strlen(target_s) - spacing5;
    char space1[spacing1+1];
    char space2[spacing2+1];
    char space3[spacing3+1];
    char space4[spacing4+1];
    char space5[spacing5+1];
    char space6[spacing6+1];
    gen_space(space1, spacing1);
    gen_space(space2, spacing2);
    gen_space(space3, spacing3);
    gen_space(space4, spacing4);
    gen_space(space5, spacing5);
    gen_space(space6, spacing6);

    char line[100];
    sprintf(line, " |%s%s%s|%s%s%s|%s%s%s|\n", space1, label, space2, space3, actual_s, space4, space5, target_s, space6);
    strcat(output, line);
  }

  strcat(output, bound);

  return output;
}
