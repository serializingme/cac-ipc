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
#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

/**
 * Wrapper class around WinSock functionality.
 */
class CWinSockWrapper {
private:
	BOOL initialized;
	WSADATA wsaData;

public:
	BOOL IsInitialized();

	CWinSockWrapper(PDWORD errorCode);
	~CWinSockWrapper();
};


class CWinSockServer {
private:
	SOCKET serverSocket;
	HANDLE serverThread;

private:
	static DWORD WINAPI Thread(LPVOID lpParam);

public:
	CWinSockServer(PDWORD errorCode, LPCTSTR address, INT PORT);
	~CWinSockServer();
};


class CWinSockClient: public CSkip {
private:
	SOCKET clientSocket;

public:
	CWinSockClient(PDWORD errorCode, LPCTSTR address, INT PORT);
	~CWinSockClient();

	BOOL DumpMessage(PIPCMESSAGE ipcMessage);
};
