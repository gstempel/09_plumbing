#include "pipe_networking.h"

int server_handshake(int * client) {
  // #1: create WKP
  mkfifo("frodo", 0644);
  printf("WKP 'frodo' created\n");
  // #2: connect to WKP
  int fd = open("frodo", O_RDONLY); // This blocks, waiting for client connection
  printf("Server connected to frodo\n");
  // #5: read from WKP
  char temp[MESSAGE_BUFFER_SIZE];
  printf("Server reading from frodo...\n");
  read(fd, temp, MESSAGE_BUFFER_SIZE);
  printf("Private name: %s\n", temp);
  // #7: remove WKP
  remove("frodo");
  printf("Removed WKP\n");
  // #8: connect to private FIFO
  int fd2 = open(temp, O_WRONLY);
  printf("Server connected to samwise\n");
  printf("Sending recieved signal to client...\n");
  write(fd2, "received", MESSAGE_BUFFER_SIZE);
  read(fd, temp, MESSAGE_BUFFER_SIZE);
  printf("Connection confirmed from client: %s\n", temp);
  return fd2;
}

int client_handshake(int * server) {
  // #3: create private FIFO
  mkfifo("samwise", 0644);
  printf("Private FIFO created\n");
  // #4: connect to WKP
  int fd = open("frodo", O_WRONLY); // unblocks #2
  printf("Client connected to frodo\n");
  // #6 write to WKP (send name of private FIFO)
  printf("Sending name of private FIFO to server...\n");
  write(fd, "samwise", MESSAGE_BUFFER_SIZE);
  // #8: connect to private FIFO
  int fd2 = open("samwise", O_RDONLY); // This blocks, waiting for server connection
  printf("Client connected to samwise\n");
  // #5: connect to private FIFO
  char temp[MESSAGE_BUFFER_SIZE];
  read(fd2, temp, MESSAGE_BUFFER_SIZE);
  printf("Connection confirmed from server: %s\n", temp);
  // #8: remove private FIFO
  remove("samwise");
  printf("Removed private FIFO\n");
  // #9: send message back to server
  write(fd, "okay", MESSAGE_BUFFER_SIZE);
  return fd;
}
