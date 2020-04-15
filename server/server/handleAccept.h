#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "util.h"

#define DEFAULT_BUFLEN 1024
#define DEFAULT_PORT "27015"

int handleAccept(SOCKET* PListenSocket);

int startProcess(const std::string cmd);