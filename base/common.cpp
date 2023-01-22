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

CModuleWrapper::CModuleWrapper(LPCTSTR modulesDirectory, LPCTSTR moduleName, PDWORD errorCode)
	: moduleHandle(NULL)
{
	// Make sure the application finds the DLLs that may be necessary.
	if (SetDllDirectory(modulesDirectory) == FALSE || (this->moduleHandle = LoadLibrary(moduleName)) == NULL) {
		*errorCode = GetLastError();
	}
}

CModuleWrapper::~CModuleWrapper() {
	if (this->moduleHandle != NULL) {
		FreeLibrary(this->moduleHandle);
	}
}

CIPCClassWrapper::CIPCClassWrapper(CModuleWrapper* moduleWrapper)
	: CClassWrapper(moduleWrapper)
{
	this->getIpcMessage = this->moduleWrapper->GetExport<CIPCTLV_getIpcMessage>(
		"?getIpcMessage@CIPCTLV@@IAEJAAPAVCIpcMessage@@@Z");
	this->destroyIpcMessage = this->moduleWrapper->GetExport<CIpcMessage_destroyIpcMessage>(
		"?destroyIpcMessage@CIpcMessage@@QAEXXZ");

	this->realInstance = AllocateMemory<CIPCTLV>();
}

CIPCClassWrapper::~CIPCClassWrapper() {
	if (realInstance != NULL) {
		FreeMemory<CIPCTLV>(this->realInstance);
	}

	this->realInstance = NULL;
}

LONG CIPCClassWrapper::CreateIpcMessage(PPIPCMESSAGE resultingIpcMsg) {
	return this->getIpcMessage(this->realInstance, resultingIpcMsg);
}

VOID CIPCClassWrapper::DestroyIpcMessage(PIPCMESSAGE ipcMessage) {
	this->destroyIpcMessage(ipcMessage);
}

CDumper::CDumper(CSkip* destination, CIPCClassWrapper* wrappedClass)
	: destination(destination), wrappedClass(wrappedClass)
{
}

CDumper::~CDumper() {
}

BOOL CDumper::DumpMessage() {
	if (this->wrappedClass == NULL) {
		return FALSE;
	}

	PIPCMESSAGE ipcMessage = NULL;
	BOOL bResult = FALSE;


	if (this->wrappedClass->ConstructInstance() == FALSE || this->wrappedClass->PrepareInstance() == FALSE) {
		goto failed;
	}

	if (this->wrappedClass->CreateIpcMessage(&ipcMessage) != 0) {
		goto failed;
	}

	if (this->destination->DumpMessage(ipcMessage) == FALSE) {
		goto failed;
	}

	bResult = TRUE;
failed:
	if (ipcMessage != NULL) {
		this->wrappedClass->DestroyIpcMessage(ipcMessage);
	}

	if (this->wrappedClass->GetInstance() != NULL) {
		this->wrappedClass->DestructInstance();
	}

	return bResult;
}

/**
 * 
 */
LPCSTR paramLPCSTR = "UTF8STRING";

LPCWSTR paramLPCWSTR = L"UTF16STRING";

STRING8 paramSTRING8 = {
	.value = {
		.pointer = paramLPCSTR,
	},
	.length = 10
};

STRING16 paramSTRING16 = {
	.value = {
		.pointer = paramLPCWSTR,
	},
	.length = 11
};

BOOL paramBOOL = TRUE;

UINT8 paramUINT8 = 0x41;

UINT16 paramUINT16 = 0x4243;

UINT32 paramUINT32 = 0x44454647;

UINT64 paramUINT64 = 0x48494a4b4c4d4e4f;

ULONG32 paramULONG32 = 0x50515253;

INT32 paramINT32 = 0x54555657;

INT64 paramINT64 = 0x6162636465676869;

LONG32 paramLONG32 = 0x6a6b6c6d;

UINT8 paramUINT8Array[8] = {
	0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75
};

VECTOR paramUINT8Vector = {
	.first = paramUINT8Array,
	.last = MAKEPTR(PUINT8, paramUINT8Array, ARRAYSIZE(paramUINT8Array)),
	.end = MAKEPTR(PUINT8, paramUINT8Array, ARRAYSIZE(paramUINT8Array))
};

// Very uncertain this is the actual way a two elements std::map would be allocated, the thing is that as it is, the
// call to CNotifyAgentPreTunnelTlv::SetMacAddresses works and the two MAC addresses are present in the PCAP.
NODE paramMAPRight = {
	.left = &paramMAPHead,
	.parent = &paramMAPLeft,
	.right = &paramMAPHead,
	.nil = 0,
	.key = {
		.value = L"00-11-22-33",
		.length = 11
	},
	.value = 0
};
NODE paramMAPLeft = {
	.left = &paramMAPHead,
	.parent = &paramMAPHead,
	.right = &paramMAPRight,
	.nil = 0,
	.key = {
		.value = L"aa-bb-cc-dd",
		.length = 11
	},
	.value = 1
};

NODE paramMAPHead = {
	.left = &paramMAPLeft,
	.parent = &paramMAPHead,
	.right = &paramMAPRight,
	.nil = 1
};

MAP paramMAP = {
	.head = &paramMAPHead
};
