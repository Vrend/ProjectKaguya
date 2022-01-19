#include "main.h"

volatile int locked;

volatile char sensor_data[50];

int PORT1, PORT2;

char* labels[4] = {"Altitude", "Pressure", "Temperature", "Speed"};
float actual[4] = {35994.39f, 11.211f, 68.322f, 482.17f};
float target[4] = {36000.0f, 11.3f, 68.0f, 480.0f};

int main(int argc, char* argv[]) {
  locked = 1;

  if(argc != 3) {
    printf("Usage: main [port1] [port2]\n");
    return 1;
  }

  PORT1 = atoi(argv[1]);
  PORT2 = atoi(argv[2]);

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
  s_addr.sin_port = htons(PORT2);

  if(fd < 0) {
    printf("Error creating internal socket\n");
    exit(1);
  }

  if(bind(fd, (struct sockaddr*) &s_addr, slen) < 0) {
    printf("Error binding socket\n");
    exit(1);
  }

  //printf("Listening for messages on 127.0.0.1:5001 ...\n");

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
	addr.sin_port = htons(PORT1);

  int addr_len = sizeof(addr);

  if(bind(fd, (struct sockaddr*) &addr, addr_len) < 0) {
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
    int client_fd = accept(fd, (struct sockaddr*) &addr, (socklen_t*) &addr_len);

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

	char read_buffer[50];

  printf("Request from %s on port %d\n", ip, port);

  int e;

  int show_help = 0;

  int crash_imminent = 0;

  while(1) {
    bzero(read_buffer, 50);
    char* clear = "\033[H\033[J";
    char* refresh = "Press enter to refresh\n";
    char* prompt;

    if(crash_imminent == 1) { // crashed
      char* final_moments1 = "\n\n Connection to the plane has failed...\n\n";
      char* final_moments2 = " ...last moments indicate catastrophic failure... ";
      char* final_moments3 = "...survival is unlikely.\n";
      char* writetolog = "\n  More information can be found in /var/log/plane.log\n";
      send(fd, clear, strlen(clear), MSG_NOSIGNAL);
      send(fd, final_moments1, strlen(final_moments1), MSG_NOSIGNAL);
      sleep(2.5);
      send(fd, final_moments2, strlen(final_moments2), MSG_NOSIGNAL);
      sleep(2.5);
      send(fd, final_moments3, strlen(final_moments3), MSG_NOSIGNAL);
      sleep(2);
      send(fd, writetolog, strlen(writetolog), MSG_NOSIGNAL);
      close(fd);
      write_flag();
      exit(0);
    }

    if(update_table(target, actual) < 0) { // plane crash imminent
      crash_imminent = 1;
      char* garbled = "snaoa8QpcYqitNqXwzxOqeLKlaNVa1LZ1TFliT5mItVAIRO0KORBM38XvXuqOa7BwFU4zfYS4eH3GpRnBPIHep22LuL89Hw8zlJHcjs0NlSZpiurnAR6AzOUmjK08ITSuJLIOJ9KFavhH4TOEXbtPBmB1eTdwLMfTFiBvO9lWKmkRghS6uclmfcKfewL87kRCaQWbdB0aafGMfvC0lyRVl2iXVNxSj9hXsWqKyDKoHM6Xzz91X5uFI6G0lFfeAJEPzuuAz7mY5ciiFAuySzx7hOEavQzQEt9Cleoh6gTuXT2QpSDHBoafNroT7lnZ8iOh59cG4QjVmZoWB0X520sojsRLcjvcfgnbHwYD7n3sF5l0zaBcganPV5QZQEEAex9sDDKUYpoN4klOY3P0INbZ1Sb1Or7VERFV4iR4Tp89u33rnwnhRrhmBLDRj4SygB5jqq9E6YWiVlrKhzizcF93DSqTOTAaF3GUxcCyjXItU4Gk8gRawbDgL3GesquyDqNYRxRmIclVQy4z8kxfWPMPMA1lvrgW90Puv3eGfzNZrN7MpWsDE3HZesQmwuiWOxHwBxnWFR8wvjPvZp5D8lDhHSwaafGMfvC0lyRVl2iXVNxSj9hXsWqKyDKoHM6Xzz91X5uFI6G0lFfeAJEPzuuAz7mY5ciiFAuySzx7hOEavQzQEt9Cleoh6gTuXT2QpSDHBoafNroT7lnZ8iOh59cG4QjVmZoWB0X520sojsRLcjvcfgnbHwYD7n3sF5l0zaBcganPV5QZQEEAex9sDDKUYpoN4klOY3P0INbZ1Sb1Or7VERFV4iR4Tp89u33rnwnhRrhmBLDRj4SygB5jqq9E6YWiVlrKhzizcF93DSqTOTAaF3GUxcCyjXItU4Gk8gRawbDgL3GesquyDqNYRxRmIclVQy4z8kxfWPMPMA1lvrgW90Puv3eGfzNZrN7MpWsDE3HZesQmwuiWOxHwBxnWFR8wvjPvZp5D8lDhHSwaafGMfvC0lyRVl2iXVNxSj9hXsWqKyDKoHM6Xzz91X5uFI6G0lFfeAJEPzuuAz7mY5ciiFAuySzx7hOEavQzQEt9Cleoh6gTuXT2QpSDHBoafNroT7lnZ8iOh59cG4QjVmZoWB0X520sojsRLcjvcfgnbHwYD7n3sF5l0zaBcganPV5QZQEEAex9sDDKUYpoN4klOY3P0INbZ1Sb1Or7VERFV4iR4Tp89u33rnwnhRrhmBLDRj4SygB5jqq9E6YWiVlrKhzizcF93DSqTOTAaF3GUxcCyjXItU4Gk8gRawbDgL3GesquyDqNYRxRmIclVQy4z8kxfWPMPMA1lvrgW90Puv3eGfzNZrN7MpWsDE3HZesQmwuiWOxHwBxnWFR8wvjPvZp5D8lDhHSw";
      send(fd, garbled, strlen(garbled), MSG_NOSIGNAL);
      sleep(2.5);
      continue;
    }

    if(locked == 1) {
      prompt = "\n Session is locked. Modification disabled.";
    }
    else {
      prompt = "\n >> ";
    }

    e = send(fd, clear, strlen(clear), MSG_NOSIGNAL);
    if(e < 0) {
      break;
    }

    char* output = gen_table(labels, target, actual);
    send(fd, output, strlen(output), MSG_NOSIGNAL);
    free(output);

    if(show_help == 1) {
      char* help = "OPTIONS:\n[H]elp/[?]: Show this dialog\n[S]et <key> <val>: set target value of <key> to <val>\n[Q]uit: Close connection\n";
      send(fd, help, strlen(help), MSG_NOSIGNAL);
      show_help = 0;
    }

    send(fd, refresh, strlen(refresh), MSG_NOSIGNAL);
    send(fd, prompt, strlen(prompt), MSG_NOSIGNAL);

    e = read(fd, read_buffer, 50);
    if(e <= 0) {
      break;
    }

    int code = handle_input(read_buffer, fd);
    if(code == 0) {
      break;
    }
    else if(code == 1) {
      show_help = 1;
    }
  }

	close(fd);
	pthread_exit(0);
}


int handle_input(char* input, int fd) {
  if(locked == 1) {
    return -1;
  }

  if(strlen(input) == 0) {
    printf("No input\n");
    return -1;
  }
  //printf("%s\n", input);
  for(int i = 0; input[i]; i++){
    input[i] = tolower(input[i]);
  }

  if(input[0] == 'q') { // quit connection
    char* done = "Closing connection...\n";
    send(fd, done, strlen(done), MSG_NOSIGNAL);
    return 0; // close connection
  }
  else if(input[0] == 'h' || input[0] == '?') { // show help
    return 1;
  }
  else if(input[0] == 's') { // change target value
    char* tokens[3];
    int c = 0;
    char* token = strtok(input, " ");
    while(token != NULL) {
      if(c == 3) { // too many args
        return -1;
      }
      tokens[c] = token;
      token = strtok(NULL, " ");
      c++;
    }
    if(c != 3) {
      return -1;
    }
    float val = (float) strtod(tokens[2], NULL);
    if(val == 0.0f) { // bad val
      return -1;
    }
    set_target(target, labels, tokens[1], val);
  }
  return -1; // no action required
}

int update_table(float* targets, float* actuals) {
  float lbounds[4] = {50.0f, 6.0f, 1.0f, 120.0f};
  float ubounds[4] = {50000.0f, 20.0f, 130.0f, 600.0f};
  float diffs[4] = {1000.0f, 0.6f, 5.0f, 30.0f};
  for(int i = 0; i < 4; i++) {
    float target = targets[i];
    float actual = actuals[i];
    float lbound = lbounds[i];
    float ubound = ubounds[i];
    float diff = diffs[i];
    float x = (float)rand()/(float)(RAND_MAX/diff);
    if(actual <= target) {
      actual += x;
      if(actual > ubound) {
        return -1;
      }
    }
    else {
      actual -= x;
      if(actual < lbound) {
        return -1;
      }
    }
    actuals[i] = actual;
  }
  return 0;
}

void set_target(float* targets, char** labels, char* property, float value) {
  for(int i = 0; i < 4; i++) {
    char label[25];
    strcpy(label, labels[i]);
    for(int j = 0; label[j]; j++) {
      label[j] = tolower(label[j]);
    }
    if(strcmp(label, property) == 0) {
      targets[i] = value;
      break;
    }
  }
}

void gen_space(char* spaces, int n) {
  strcpy(spaces, " ");
  for(int i = 1; i < n; i++) {
    strcat(spaces, " ");
  }
}

char* gen_table(char** labels, float* targets, float* actuals) {
  char* title = "\n Boeing Flight Manager PLID74\n";
  char* bound = " +-------------+------------+------------+\n";
  char* header = " |    NAME     |   ACTUAL   |   TARGET   |\n";
  // available space per column
  int col1 = 13;
  int col2 = 12;
  int col3 = 12;

  char* output = malloc(1000);
  strcpy(output, title);
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

void write_flag() {
  if(locked == 1) {
    return;
  }
  printf("Opening flag file\n");
  FILE* flagfile = fopen("/program/flag.txt", "r");
  char flag[25];
  bzero(flag, 25);
  printf("Reading flag...\n");
  fgets(flag, 25, flagfile);
  printf("The value of flag is: %s\n", flag);
  fclose(flagfile);

  printf("Opening log file\n");
  FILE* logfile = fopen("/var/log/plane.log", "w");
  printf("Putting flag in log file\n");
  fputs(flag, logfile);
  printf("Putting garbage in log file\n");
  fputs("\n\nDEBUG INFO:\nfdsjlkafds;lkkjo54o4tjrjf94rjfjidffjsasfjdaljsjlkfdkjafdglkjfjadskfjkdjasdfdjkdsjkafdfldlskaflkkdsjalj;kfdjkal;fdjlks;dfjklalkjdjkldsfjkladsjklfdjlkadkjlfdajlkadfjlkfdlkjafdsljk;fsjlksfdjklfdslkjfsljk;fsljkfsjlkfljk;dsafsjlkfdsajfdijorjoiewjgjkdosfjoiasojafojifdasoijfdsojifdojidsfoijafijodjoifdsojfdsjoifdsojfds;fdsjk;lafj;kfadj", logfile);
  printf("Closing log file\n");
  fclose(logfile);
}
