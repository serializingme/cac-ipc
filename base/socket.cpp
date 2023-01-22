/*
 * Copyright (C) 2022 Duarte Silva
 *
 * This file is part of CAC IPC.
 *
 * CAC IPC is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CAC IPC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with CAC IPC. If not, see <http://www.gnu.org/licenses/>.
 */
#include "common.h"
#include "socket.h"

CWinSockWrapper::CWinSockWrapper(PDWORD errorCode)
	: initialized(FALSE), wsaData({})
{
	if (((*errorCode) = WSAStartup(MAKEWORD(2, 2), &this->wsaData)) == 0) {
		initialized = TRUE;
	}
}

CWinSockWrapper::~CWinSockWrapper() {
	if (initialized == TRUE) {
		WSACleanup();
	}
}

BOOL CWinSockWrapper::IsInitialized() {
	return this->initialized;
}

CWinSockServer::CWinSockServer(PDWORD errorCode, LPCTSTR address, INT port)
	: serverSocket(INVALID_SOCKET), serverThread(NULL)
{
	SOCKADDR_IN serverAddress = {
		.sin_family = AF_INET,
		.sin_port = htons(port)
	};
	DWORD threadId = 0;

	if ((this->serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
		goto failedWinSock;
	}
	
	if (InetPton(AF_INET, address, &serverAddress.sin_addr) != 1) {
		goto failedWinSock;
	}
	
	if (bind(this->serverSocket, (SOCKADDR*)&serverAddress, sizeof(SOCKADDR_IN)) == SOCKET_ERROR) {
		goto failedWinSock;
	}
	
	if (listen(this->serverSocket, 1) == SOCKET_ERROR) {
		goto failedWinSock;
	}

	this->serverThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)CWinSockServer::Thread,
		(LPVOID)this->serverSocket, 0, &threadId);

	if (this->serverThread == NULL) {
		goto failedThread;
	}

	goto success;

failedWinSock:
	*errorCode = WSAGetLastError();
	goto cleanup;

failedThread:
	*errorCode = GetLastError();

cleanup:
	if (this->serverSocket != INVALID_SOCKET) {
		closesocket(this->serverSocket);
		this->serverSocket = INVALID_SOCKET;
	}
success:
	return;
}

CWinSockServer::~CWinSockServer() {
	if (this->serverThread != NULL) {
		WaitForSingleObject(this->serverThread, INFINITE);
	}

	if (this->serverSocket != INVALID_SOCKET) {
		closesocket(this->serverSocket);
		this->serverSocket = INVALID_SOCKET;
	}
}

/**
 * The server thread will be running on the code bellow.
 */
DWORD WINAPI CWinSockServer::Thread(LPVOID lpParam) {
	SOCKET	serverSocket = (SOCKET)lpParam;
	SOCKET	clientSocket = INVALID_SOCKET;
	CHAR	receivedData[1024];
	INT	receivedCount;

	do
	{
		if (clientSocket != INVALID_SOCKET)
		{
			receivedCount = recv(clientSocket, receivedData, ARRAYSIZE(receivedData), 0);

			if (receivedCount == SOCKET_ERROR)
			{
				goto cleanup;
			}
			else if (receivedCount == 0)
			{
				shutdown(clientSocket, SD_SEND);
				closesocket(clientSocket);
				clientSocket = INVALID_SOCKET;

				goto cleanup;
			}
		}
		else
		{
			clientSocket = accept(serverSocket, NULL, NULL);

			if (clientSocket == INVALID_SOCKET)
			{
				goto cleanup;
			}
		}
	}
	while (TRUE);

cleanup:
	if (clientSocket != INVALID_SOCKET)
	{
		closesocket(clientSocket);
		clientSocket = INVALID_SOCKET;
	}

	return 0;
}

CWinSockClient::CWinSockClient(PDWORD errorCode, LPCTSTR address, INT port)
	: clientSocket(INVALID_SOCKET)
{
	SOCKADDR_IN serverAddress = {
		.sin_family = AF_INET,
		.sin_port = htons(port)
	};

	if ((this->clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
		goto failed;
	}

	if (InetPton(AF_INET, address, &serverAddress.sin_addr) != 1) {
		goto failed;
	}

	if (connect(this->clientSocket, (SOCKADDR*)&serverAddress, sizeof(SOCKADDR_IN)) == SOCKET_ERROR) {
		goto failed;
	}

	goto success;

failed:
	*errorCode = WSAGetLastError();

	if (this->clientSocket != INVALID_SOCKET) {
		closesocket(this->clientSocket);
		this->clientSocket = INVALID_SOCKET;
	}
success:
	return;
}

CWinSockClient::~CWinSockClient() {
	if (this->clientSocket != INVALID_SOCKET) {
		shutdown(this->clientSocket, SD_SEND);
		closesocket(this->clientSocket);
		this->clientSocket = INVALID_SOCKET;
	}
}

BOOL CWinSockClient::DumpMessage(PIPCMESSAGE ipcMessage) {
	if (this->clientSocket == INVALID_SOCKET) {
		return FALSE;
	}
	
	if (send(this->clientSocket, (CHAR*)ipcMessage, ipcMessage->headerLength + ipcMessage->dataLength, 0) == SOCKET_ERROR) {
		return FALSE;
	}

	return TRUE;
}