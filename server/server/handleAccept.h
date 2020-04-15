
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <strsafe.h>
#include "util.h"

#define DEFAULT_BUFLEN 1024
#define DEFAULT_PORT "27015"

int handleAccept(SOCKET* PListenSocket);

std::string CreateChildProcess(char* cmd);//���������������ӽ��̳���

void doCreatePipe(HANDLE* IN_RD, HANDLE* IN_WR, HANDLE *OUT_RD, HANDLE* OUT_WR);//��������Pipe��һ��Pipe���˸�һ��read��write

std::string ReadFromPipe(HANDLE g_hChildStd_OUT_Rd);//��pipe��out�˶���data

void ErrorExit(PTSTR lpszFunction);