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

    json_object *obj = json_object_new_object();
    json_object *msg = json_object_new_string(buffer);
    json_object_object_add(obj, "Message", msg);
    json_object_object_add(obj, "Counter", json_object_new_int(0));

    // printf("Printf: %s\n", json_object_to_json_string(obj));

    mx_printstr("\n");
    send(
      client_sock, json_object_to_json_string(obj), 
      mx_strlen(json_object_to_json_string(obj)), 0
    );

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
        mx_printstr(
          json_object_to_json_string(
            json_object_object_get(
              json_tokener_parse(buffer), "Message"
        )));
        mx_printstr("\n");
        printf("Counter: %d\n", json_object_get_int(json_object_object_get(obj, "Counter")));
    }
    json_object_put(obj);
    /* Free parsed json */
  }
  
  
  

  
  mx_printstr("Disconnected from the server.\n");

  return 0;
}
