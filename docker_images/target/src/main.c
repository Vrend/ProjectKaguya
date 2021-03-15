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
  while(1);
}

void totally_secure_copy(char* input) {
  char sensor_data_raw[50];
  strcpy(sensor_data_raw, input);
  /* DEBUG: Need to make data modifications... */
  strncpy(sensor_data, sensor_data_raw, 50);
}

void* internal_server() {
  printf("Hey, I'm the internal server!\n");
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
  printf("Hey, I'm the external server!\n");
  return NULL;
}
