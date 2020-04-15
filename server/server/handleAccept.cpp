
#include "handleAccept.h"
int handleAccept(SOCKET* PListenSocket){
	SOCKET ListenSocket = *PListenSocket;
	SOCKET ClientSocket = INVALID_SOCKET;
	int iSendResult, iResult;
	char* recvbuf = new char[DEFAULT_BUFLEN];
	memset(recvbuf, 0, DEFAULT_BUFLEN);
	int recvbuflen = DEFAULT_BUFLEN;
	// Accept a client socket
	ClientSocket = accept(ListenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET) {
		printf("accept failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	// Receive until the peer shuts down the connection
	std::string* pstr = new std::string();
	std::string& str = *pstr;
	do {
		iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			str.append(recvbuf);
			printf("Bytes received: %d\n", iResult);			
		}
		else if (iResult == 0)
			printf("end read\n");
		else  {
			printf("recv failed with error: %d\n", WSAGetLastError());
			closesocket(ClientSocket);
			WSACleanup();
			return 1;
		}

	} while (iResult > 0);	
	delete recvbuf; recvbuf = NULL;
	
	const std::wstring wstr = utf8_2_ws(str);
	std::string str_utf8 = ws2s(wstr); 
	printf("cmd:"); printf(str_utf8.c_str()); printf("\n");
	if (str_utf8 == "exit"){
		return 2;//exit
	}
	startProcess(str_utf8);//start process
	delete pstr; pstr = NULL;

	// Echo the buffer back to the sender
	iSendResult = send(ClientSocket, str_utf8.c_str(),str_utf8.size(), 0);
	if (iSendResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
		return 1;
	}
	printf("Bytes sent: %d\n", iSendResult);

	// shutdown the connection since we're done
	iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
		return 1;
	}
	// cleanup
	closesocket(ClientSocket);
	printf("Connection closed\n");
	printf("-------------------------------------------------------------------------\n\n\n");
	return 0;
};

int startProcess(const std::string cmd){
	STARTUPINFO si; //参数设置  
	memset(&si, 0, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_SHOW;

	PROCESS_INFORMATION pi; //参数结束  

	/*printf("Please enter the name of process to start:");
	std::string name;
	cin >> name;*/

	using namespace std;
	printf("-------------------------------------------------------------------------\n");
	if (!CreateProcess(NULL, (LPSTR)cmd.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
		cout << "Create Error!" << endl;
		printf("-------------------------------------------------------------------------\n");
		return false;
	}
	else {
		//WaitForSingleObject(pi.hProcess,0);		
		WaitForSingleObject(pi.hProcess, INFINITE);
		cout << cmd << "  finished!" << endl;
		printf("-------------------------------------------------------------------------\n");
	}
	return 0;
}