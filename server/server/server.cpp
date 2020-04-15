// server.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#undef UNICODE

#define WIN32_LEAN_AND_MEAN

//#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include "handleAccept.h"

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")


int _tmain(int argc, char* argv[])//argv[1] :  port
{
	WSADATA wsaData; 
	int iResult;
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);//The WSAStartup function is called to initiate use of WS2_32.dll.
	//The WSADATA structure contains information about the Windows Sockets 
	//implementation.The MAKEWORD(2, 2) parameter of WSAStartup makes a 
	//request for version 2.2 of Winsock on the system, and sets the passed 
	//version as the highest version of Windows Sockets support that the caller can use.
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	struct addrinfo *result = NULL;
	struct addrinfo hints;
	PCSTR port = DEFAULT_PORT;
	if (argc > 1){
		port = argv[1];
	}
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;
	// Resolve the server address and port
	iResult = getaddrinfo(NULL, port, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}	
	SOCKET ListenSocket = INVALID_SOCKET;
	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	//once bind,no longer needed addrinfo,then free
	freeaddrinfo(result);

	int i = 1;
	while (i){
		iResult = listen(ListenSocket, SOMAXCONN); //maximum length of the queue of pending connections to accept
		if (iResult == SOCKET_ERROR) {
			printf("listen failed with error: %d\n", WSAGetLastError());
			closesocket(ListenSocket);
			WSACleanup();
			return 1;
		}
		printf("listen on port:%s\n", port);
		//
		int status = handleAccept(&ListenSocket);
		
		if (status == 2){//exit
			i = 0;
		}
	}
	// No longer need server socket
	//closesocket(ListenSocket);
	WSACleanup();
	return 0;
}

