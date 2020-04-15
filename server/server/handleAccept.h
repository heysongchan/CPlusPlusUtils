
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

std::string CreateChildProcess(char* cmd);//根据命令行运行子进程程序

void doCreatePipe(HANDLE* IN_RD, HANDLE* IN_WR, HANDLE *OUT_RD, HANDLE* OUT_WR);//创建两个Pipe，一个Pipe两端各一个read和write

std::string ReadFromPipe(HANDLE g_hChildStd_OUT_Rd);//从pipe的out端读出data

void ErrorExit(PTSTR lpszFunction);