#include "../inc/client.h"

int main(){

  char *ip = "127.0.0.1";
  int port = 23134;

  int sock;
  struct sockaddr_in addr;
  //socklen_t addr_size;
  char buffer[1024];
  //int n;

  sock =  Socket(AF_INET, SOCK_STREAM, 0);

  mx_printstr("[+]TCP server socket created.\n");

  mx_memset(&addr, '\0', sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = port;
  addr.sin_addr.s_addr = inet_addr(ip);

  connect(sock, (struct sockaddr*)&addr, sizeof(addr));
  mx_printstr("Connected to the server.\n");

  mx_memset(&buffer, 0, sizeof(buffer));
  mx_strcpy(buffer, "HELLO, THIS IS CLIENT.");
  mx_printstr("Client: ");
  mx_printstr(buffer);
  mx_printstr("\n");

  send(sock, buffer, strlen(buffer), 0);

  mx_memset(&buffer, 0, sizeof(buffer));
  recv(sock, buffer, sizeof(buffer), 0);
  mx_printstr("Server: ");
  mx_printstr(buffer);
  mx_printstr("\n");

  close(sock);
  mx_printstr("Disconnected from the server.\n");

  return 0;
}
