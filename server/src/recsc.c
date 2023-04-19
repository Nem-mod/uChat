#include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <sys/socket.h>

// #define BUFSIZE 1024

// int main(int argc, char const *argv[])
// {
//     int sockfd, bytes;
//     struct sockaddr_in servaddr;
//     char buffer[BUFSIZE];
//     char message[BUFSIZE * 10];  // Allocate a buffer that is 10 times larger than the receive buffer
//     int message_length = 0;

//     // Create socket
//     if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
//     {
//         perror("socket");
//         exit(EXIT_FAILURE);
//     }

//     // Set server address and port
//     memset(&servaddr, 0, sizeof(servaddr));
//     servaddr.sin_family = AF_INET;
//     servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
//     servaddr.sin_port = htons(8080);

//     // Connect to server
//     if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
//     {
//         perror("connect");
//         exit(EXIT_FAILURE);
//     }

//     printf("Connected to server: %s:%d\n", inet_ntoa(servaddr.sin_addr), ntohs(servaddr.sin_port));

//     // Receive message from server
//     while ((bytes = recv(sockfd, buffer, BUFSIZE, 0)) > 0)
//     {
//         memcpy(message + message_length, buffer, bytes);
//         message_length += bytes;

//         // Check if we have received the entire message
//         if (message_length >= BUFSIZE * 10)
//         {
//             printf("Error: Message too large\n");
//             break;
//         }

//         // If we have received the entire message, break out of the loop
//         if (strstr(message, "\r\n\r\n") != NULL)
//         {
//             break;
//         }
//     }

//     // Print the received message
//     printf("Received message: %s\n", message);

//     // Close socket
//     close(sockfd);

//     return 0;
// }
