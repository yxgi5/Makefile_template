#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include "../include/udt.h"

#define HOST "127.0.0.1"
#define PORT "9000"
#define BUFFER_SIZE 10240
#define MAXLINE 100

int main(int argc, char *argv[])
{
    socket_t        sock;
    int             err;
    struct addrinfo hints,
                    *result;

    char buf[MAXLINE];

    udt_startup();

    /* get address info */
    memset(&hints, 0, sizeof(hints));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    /*hints.ai_socktype = SOCK_STREAM;*/

    if ((err = getaddrinfo(NULL, PORT, &hints, &result)) != 0) {
        fprintf(stderr, "Error: %s\n", gai_strerror(err));
        exit(err);
    }

    /* create a socket */
    sock = udt_socket(result -> ai_family,
                      result -> ai_socktype,
                      result -> ai_protocol);
    if (sock == -1) {
        fprintf(stderr, "Could not create socket\n");
        exit(errno);
    }

    /* connect to server */
    if (udt_connect(sock, result -> ai_addr, result -> ai_addrlen) == -1) {
        fprintf(stderr, "Could not connect to socket\n");
        exit(errno);
    } else {
        fprintf(stderr, "Connected\n");
    }

    freeaddrinfo(result);

    /* send file */
    int filefd = open("assets/sendfile", O_RDONLY);
    if (filefd < -1) return 2;
    if (udt_sendfile(sock, filefd, 0, 10, 0) < 0) return 1;
    close(filefd);

    /* send, recv */
//    size_t size;
//    char *line;
    udt_send(sock, "\tClient wants to talk", 22, 0);
    //while (1) 
    while(fgets(buf, MAXLINE, stdin)!= NULL)
    {
        //printf("\t\n>> ");
        //size = 0;
        //size = getline(&line, &size, stdin);
	//printf("size = %d",size);
        //if (size == 1) break;
        //*(line + size - 1) = '\0';
        
        //udt_send(sock, line, size, 0);
//	    printf("%s, %d",buf,strlen(buf));
        udt_send(sock, buf, strlen(buf), 0);
        //free(line);
    }

    printf("Disconnected\n");

    /* close the connection */
    udt_close(sock);
    return 0;
}
