#include pipe_networking.h

int server_handshake(int * client) {

  mkfifo("frodo", 0644);
  int fd = open("frodo", O_RDONLY);
  printf("Server connected\n");

  char temp[MESSAGE_BUFFER_SIZE];
  read(fd, temp, 
}

int client_handshake(int * server) {
  mkfifo("samwise", 0644);

  int fd = open("frodo", O_WRONLY);
  write(fd, "samwise", MESSAGE_BUFFER_SIZE);

  int fd2 = open("samwise", O_RDONLY);
}
