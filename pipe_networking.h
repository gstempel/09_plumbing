#include <sys/types.h>
#include <sys/stat.h>

#define MESSAGE_BUFFER_SIZE = 50

int server_handshake(int * client);

int client_handshake(int * server);