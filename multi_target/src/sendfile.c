#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>

#include "../include/udt.h"

#define BACKLOG     5
#define HOST        "127.0.0.1"
#define PORT        "8000"
#define BUFFER_SIZE 10240

int main(int argc, char *argv[])
{
    socket_t        sock, conn;
    int             err;
    struct addrinfo hints, *result;

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

    /* bind to address */
    if (udt_bind(sock, result -> ai_addr, result -> ai_addrlen) == -1) {
        fprintf(stderr, "Could not bind socket\n");
        exit(errno);
    }

    freeaddrinfo(result);

    if (hints.ai_socktype == SOCK_STREAM) {

        /* listen for connections */
        if (udt_listen(sock, BACKLOG) == -1) {
            fprintf(stderr, "Could not listen on socket\n");
            exit(errno);
        } else {
            fprintf(stdout, "Listening on %s\n", PORT);
        }

        /* get a connection */
        if ((conn = udt_accept(sock, NULL, NULL)) == -1) {
            fprintf(stderr, "Connection failed\n");
            exit(errno);
        } else {
            fprintf(stdout, "New connection\n");
        }

    } else {
        conn = sock;
        fprintf(stdout, "Active on %s\n", PORT);
    }

    /* send, recv filename */
    char filename[BUFFER_SIZE];
    memset(filename, 0, sizeof(filename));
    udt_recv(conn, filename, BUFFER_SIZE, 0);
    printf("\tFilename: %s\n\n", filename);

    /* send file */
    int filefd = open(filename, O_RDONLY);
    int64_t offset = 0;
    if (filefd < 0) return 2;
    if (udt_sendfile(conn, filefd, offset, 10, 0) < 0) return 1;
    close(filefd);

    printf("\nClient disconnected\n");

    /* close connection */
    if (udt_close(sock) == -1) {
        fprintf(stderr, "Could not close socket\n");
        exit(errno);
    }

    return 0;
}
