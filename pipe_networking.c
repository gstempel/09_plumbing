#include "pipe_networking.h"

int server_handshake(int * from_client) {
  // #1: create WKP
  mkfifo("frodo", 0644);
  printf("WKP 'frodo' created\n");

  // #2: connect to WKP
  int fd = open("frodo", O_RDONLY); // This blocks, waiting for client connection
  printf("Server connected to frodo\n");

  // #7: read from WKP
  char temp[MESSAGE_BUFFER_SIZE+1];
  printf("Server reading from frodo...\n");
  read(fd, temp, MESSAGE_BUFFER_SIZE);
  temp[MESSAGE_BUFFER_SIZE] = 0;
  printf("Private name: %s\n", temp);

  // #8: remove WKP
  remove("frodo");
  printf("Removed WKP\n");

  // #9: connect to private FIFO
  int fd2 = open(temp, O_WRONLY);
  printf("Server connected to samwise\n");

  // #10: send message to client
  printf("Sending recieved signal to client...\n");
  write(fd2, "received", strlen("received") + 1);

  // #15: recieve message from client
  read(fd, temp, MESSAGE_BUFFER_SIZE);
  temp[MESSAGE_BUFFER_SIZE] = 0;
  printf("Connection confirmed from client: %s\n", temp);

  // #16: return fds of pipes
  *from_client = fd;  
  return fd2;
}

int client_handshake(int * to_server) {
  // #3: create private FIFO
  mkfifo("samwise", 0644);
  printf("Private FIFO created\n");

  // #4: connect to WKP
  int fd = open("frodo", O_WRONLY); // unblocks #2
  printf("Client connected to frodo\n");

  // #5 write to WKP (send name of private FIFO)
  printf("Sending name of private FIFO to server...\n");
  write(fd, "samwise", strlen("samwise") + 1);

  // #6: connect to private FIFO
  int fd2 = open("samwise", O_RDONLY); // This blocks, waiting for server connection
  printf("Client connected to samwise\n");

  // #11: recieve message from server
  char temp[MESSAGE_BUFFER_SIZE+1];
  read(fd2, temp, MESSAGE_BUFFER_SIZE);
  temp[MESSAGE_BUFFER_SIZE] = 0;
  printf("Connection confirmed from server: %s\n", temp);

  // #12: remove private FIFO
  remove("samwise");
  printf("Removed private FIFO\n");

  // #13: send message back to server
  write(fd, "okay", strlen("okay") + 1);

  // #14: return fds of pipes
  *to_server = fd;
  return fd2;
}
