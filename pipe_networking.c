#include "pipe_networking.h"

int server_handshake(int * client) {
  // create WKP
  mkfifo("frodo", 0644);
  int fd = open("frodo", O_RDONLY);
  printf("Server connected\n");

  char temp[MESSAGE_BUFFER_SIZE];
  read(fd, temp, MESSAGE_BUFFER_SIZE);
  remove("frodo");
  printf("private name: %s", temp);
  
  int fd2 = open(temp, O_WRONLY);
  write(fd2, "received", MESSAGE_BUFFER_SIZE);

  return fd2;
}

int client_handshake(int * server) {
  // create private FIFO
  mkfifo("samwise", 0644);

  // connect to WKP
  int fd = open("frodo", O_WRONLY);
  // send name to WKP
  write(fd, "samwise", strlen("samwise") + 1);

  int fd2 = open("samwise", O_RDONLY);
  
  remove("samwise");
  write(fd, "okay", MESSAGE_BUFFER_SIZE);

  return fd;
}
