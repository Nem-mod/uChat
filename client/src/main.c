#include "../inc/client.h"

int main(){

  char *ip = "127.0.0.1";
  int port = 5555;
  int client_sock;
  struct sockaddr_in addr;
  //socklen_t addr_size;
  char buffer[1024];
  int ret;

  client_sock =  Socket(AF_INET, SOCK_STREAM, 0);

  mx_printstr("[+]TCP server socket created.\n");

  mx_memset(&addr, '\0', sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = inet_addr(ip);

  ret = connect(client_sock, (struct sockaddr*)&addr, sizeof(addr));
  if(ret < 0) 
  {
    mx_printerr("[-] Error in connection\n");
    close(client_sock);
    exit(-1);
  }
  mx_printstr("Connected to the server.\n");

  while (1)
  {
    mx_memset(&buffer, 0, sizeof(buffer));
    mx_printstr("Client: ");
    scanf("%s", &buffer[0]);
    mx_printstr("\n");
    send(client_sock, buffer, strlen(buffer), 0);

    if(strcmp(buffer, ":exit") == 0)
    {
        close(client_sock);
        mx_printerr("[-]Disconnected from server.\n");
        close(client_sock);
        break;
	}

    mx_memset(&buffer, 0, sizeof(buffer));
    if(recv(client_sock, buffer, sizeof(buffer), 0) < 0)
    {
        mx_printerr("[-]Error in receiving data.\n");
        exit(-1);

    } else {
        mx_printstr("Server:");
        mx_printstr(buffer);
        mx_printstr("\n");
    }
  }
  
  
  

  
  mx_printstr("Disconnected from the server.\n");

  return 0;
}