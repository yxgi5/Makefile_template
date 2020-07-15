#include <sys/socket.h>
#include <unistd.h>

#include "udt.h"
#include "core.h"
#include "receiver.h"
#include "sender.h"
#include "util.h"
#include "buffer.h"

extern conn_t connection;

int udt_startup() {
    send_buffer_init();
    recv_buffer_init();
    return 0;
}

socket_t udt_socket(af_type af, sock_type type, int protocol)
{
    if (type != SOCK_STREAM && type != SOCK_DGRAM) {
        errno = 5003;  /* bad params */
        return -1;
    }
    connection.type = type;

    return socket(af, type, 0);
}

int udt_bind (socket_t sock, sockaddr_t *addr, int len)
{
    int result = 0;

    result = bind(sock, (struct sockaddr *)addr, len);
    if (result == -1) return result;

    connection.sock = sock;
    connection.is_open = 1;
    connection.addrlen = len;
    connection.is_connected = 0;
    connection.is_client = 0;

    thread_start((thread_worker_t) receiver_start, (&connection));
    thread_start((thread_worker_t) sender_start, (&connection));

    return result;
}

int udt_connect(socket_t sock, const sockaddr_t *addr, int len)
{
    int result = 0;

    result = connect(sock, (struct sockaddr *)addr, len);
    if (result == -1) return result;

    connection.sock = sock;
    connection.addr = *addr;
    connection.addrlen = len;
    connection.is_open = 1;
    connection.is_connected = 0;
    connection.is_client = 1;

    thread_start((thread_worker_t) receiver_start, (&connection));
    thread_start((thread_worker_t) sender_start, (&connection));

    handshake_init();

    while (!connection.is_connected);
    return result;
}

int udt_accept(socket_t sock, sockaddr_t *addr, int *addr_len)
{
    return accept(sock, addr, (unsigned int *) addr_len);
}

int udt_listen(socket_t sock, int backlog)
{
    return listen(sock, backlog);
}

int udt_recv(socket_t sock, char *buffer, int len, int flags)
{
    int num_read;

    do {
        if (connection.is_open == 0 && connection.is_connected == 0)
            return 0;

        num_read = recv_buffer_read(buffer, len);
    } while (num_read == 0);

    return num_read;
}

int udt_send(socket_t sock, char *buffer, int len, int flags)
{
    if (!connection.is_connected) return -1;
    return send_buffer_write(buffer, len);
}

int udt_close(socket_t sock)
{
    connection_close();
    while (connection.is_open);
    return close(sock);
}

int64_t udt_recvfile(socket_t sock, int file, int64_t *offset, int64_t filesize,
                     int blocksize)
{
    int num_read = 0;

    do {
        if (connection.is_open == 0 && connection.is_connected == 0)
            return 0;

        num_read = recv_file_buffer_read(file, offset, filesize, blocksize);
    } while (num_read == 0);

    return num_read;
}

int64_t udt_sendfile(socket_t sock, int file, int64_t offset, int64_t filesize,
                     int blocksize)
{
    if (!connection.is_connected) return -1;
    return send_file_buffer_write(file, offset, filesize, blocksize);
}
