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

/**
 * Helper macros for dealing with pointers.
 */
#define MAKEPTR(type, address, offset) \
	(type)((UINT32)(address) + (UINT32)(offset))

#define MAKEDLT(type, address, offset) \
	(type)((UINT32)(address) - (UINT32)(offset))

/**
 * Helper function to allocate memory on the process heap.
 */
template <typename T> T* AllocateMemory(SIZE_T size = sizeof(T)) {
	return (T*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
}

/**
 * Helper function to free memory allocated on the process heap.
 */
template <typename T> BOOL FreeMemory(T* pointer) {
	return HeapFree(GetProcessHeap(), HEAP_ZERO_MEMORY, pointer);
}

enum USER_AUTH_METHOD {
	USER_AUTH_METHOD_TODO = 0xc0c1c2c3
};

enum CONNECT_FAILURE_REASON {
	CONNECT_FAILURE_REASON_TODO = 0xc0c1c2c3
};

enum CONNECT_PROTOCOL_TYPE {
	CONNECT_PROTOCOL_TYPE_TODO_1 = 0x0001,
	CONNECT_PROTOCOL_TYPE_TODO = 0xc0c1c2c3
};

enum CONNECT_PROTOCOL_VERSION {
	CONNECT_PROTOCOL_VERSION_TODO = 0xc2c3
};

enum CONNECT_STOP_REASON {
	CONNECT_STOP_REASON_TODO = 0xc0c1c2c3
};

/**
 * The function CKeyExchangeTLV::SetVpnTunnelScope points to the existing of at least two enumeration values even if
 * the meaning or name of each are end. Deeper analysis required to understand that. In the generator code the
 * enumeration value VPN_TUNNEL_SCOPE_1 is the one used as it helps identify the endieness in the network
 * serialized version of the IPC message.
 */
enum VPN_TUNNEL_SCOPE {
	VPN_TUNNEL_SCOPE_0 = 0x00000000,
	VPN_TUNNEL_SCOPE_1 = 0x00000001
};

enum VPN_TUNNEL_STATE {
	VPN_TUNNEL_STATE_TODO = 0xc0c1c2c3
};

enum VPNCON_SUBSTATE {
	VPNCON_SUBSTATE_TODO = 0xc0c1c2c3
};

enum SESSION_INFO_SCOPE {
	SESSION_INFO_SCOPE_TODO = 0xc0c1c2c3
};

/**
 * One can see in vpnagent.exe at the 0x0045c87b address, that if the ADDR_FAMILY is different than one, then the IP
 * address format is "0:0:0:0:0:0:0:0", otherwise it is "0.0.0.0". This means that when the enumeration value is 1 the
 * address family is IPv4.
 */
enum ADDR_FAMILY {
	ADDR_FAMILY_IPV4 = 0x00000001,
	ADDR_FAMILY_IPV6 = 0x00000002
};

enum QUARANTINE_STATE {
	QUARANTINE_STATE_TODO = 0xc0c1c2c3
};

enum TUNNELING_MODE {
	TUNNELING_MODE_TODO = 0xc0c1c2c3
};

enum REASON_CODE {
	REASON_CODE_TODO = 0xc0c1c2c3
};

enum ALWAYS_ON_VPN {
	ALWAYS_ON_VPN_TODO = 0xc0c1c2c3
};

enum COMPR_ALGORITHM {
	COMPR_ALGORITHM_TODO = 0xc0c1c2c3
};

enum PROTOCOL_CIPHER {
	PROTOCOL_CIPHER_TODO = 0xc0c1c2c3
};

enum PROTOCOL_VERSION {
	PROTOCOL_VERSION_TODO = 0xc0c1c2c3
};

enum MUS_STATUS {
	MUS_STATUS_TODO = 0xc0c1c2c3
};

enum NETCTRL_STATE {
	NETCTRL_STATE_TODO = 0xc0c1c2c3
};

enum NETENV_STATE {
	NETENV_STATE_TODO = 0xc0c1c2c3
};

enum NETWORK_TYPE {
	NETWORK_TYPE_TODO = 0xc0c1c2c3
};

/**
 * For the great majority of things CAC uses the C++ std::base_string. However, apparently there are differences
 * between the C runtime CAC was compiled with (MSVC 2015) and the one this utility is (which is newer than the one
 * used to compile CAC). At least, I didn't manage to make it work when using std::base_string instances directly.
 * 
 * For example, the following code:
 * 
 *	 std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t>> paramMAP(L"TEST");
 *	 userAuthenticationTlv->setSecondarySGIPAddress(&paramMAP)
 * 
 * Produces the following TLV:
 * 
 *	 Type	Length	Value
 *	 0014	0002	e0a2
 * 
 * It seems the problem here is that, when the string is small enough (16 characters for UTF-8, and 8 characters for
 * UTF-16) the runtime does not allocate memory for the string, but it rather copies the string to the paramHead 16 bytes
 * of the std::base_string class. Basically it either uses the paramHead bytes as a pointer to a larger buffer or as the
 * storage for a smaller one.
 *
 * This behaviour doesn't seem ccompatible with the new versions of the C runtime, and it either breaks the utility or
 * it memory leaks into the generated/dumped TLV messages when supplying an instance of the newer version of a
 * std::base_string.
 * 
 * There might be a better way than this to solve this issue, in the last I decided to recreate the UTF-8 and UTF-16
 * versions of the std::base_string. This was the quickest way to sort this issue that I thought of, and that didn't 
 * involve faffing about with C runtime versions, or finding the std::base_string constructor in CAC's binaries (after
 * a quick search, I couldn't find these as exported symbols of the C runtime DLL bundled with CAC most likely because
 * std::base_string is a template class).
 * 
 * To be noted as well that I didn't search the Internet for a solution to this issue, so there might be some define
 * or other "turn this flag onto change behaviour" that is easier than the solution as described above.
 * 
 * For some more details of how the strings are used in CAC, in vpncommon.dll, check the CIPCTLV::addStringValue
 * function and the function at 0x1000af70.
 */
typedef struct _STRING16 {
	union _VALUE {
		LPCWSTR	pointer;	// 0x00 to 0x04
		WCHAR	buffer[8];	// 0x00 to 0x10
	} value;
	UINT32	length;			// 0x10 - Length of the string.
	UINT32	reserved = 8;	// 0x14 - Forces CAC to use the paramHead 4 bytes as a pointer to the string, instead of the
} STRING16, *PSTRING16;		// paramHead 16 bytes (or more depending on the indicated string length) of the structure as
							// the string. It indicates the current storage reserved for string.

typedef struct _STRING8 {
	union _VALUE {
		LPCSTR	pointer;	// 0x00 to 0x04
		CHAR	buffer[16];	// 0x00 to 0x10
	} value;
	UINT32	length;			// 0x10
	UINT32	reserved = 16;	// 0x14
} STRING8, *PSTRING8;

/**
 * Also didn't manage to make std::vector work with CAC. Easier to just recreate the structure CAC is expecting. In
 * the case of std::vector the structure is two pointers, one for the beginning of array, one for the end of the
 * sequence, and another for the end of the array.
 */
typedef struct _VECTOR {
	PVOID	first;		// 0x00
	PVOID	last;		// 0x04
	PVOID	end;		// 0x08
} VECTOR, *PVECTOR;

/**
 * Since std::veccctor and std>>basic_string didn't work, didn't even try with std::map. Also it was becoming quite
 * interesting to see how the STL implementation that CAC uses, handles the storage of the std::map and other types
 * (which is quite different from the MSVC implementation that is used 
 * 
 * Note that the NODE structure, the one that contains the key/value pairs, is implemented to support a key that is
 * a UTF16 string, and a value that is a boolean. This is so because the only function that uses a map as a parameter is
 * CNotifyAgentPreTunnelTlv::SetMacAddresses, so therre isn't a need to generalize. Also, of all the C STL mimicking
 * structures, this is the one that there is more uncertainty, it is mostly cobled together from single stepping CAC's
 * code and looking at MSVC STL implementation.
 */
typedef struct _NODE NODE, *PNODE;

typedef struct _NODE {
	PNODE		left;			// 0x00
	PNODE		parent;			// 0x04
	PNODE		right;			// 0x08
	UINT8		unknown1;		// 0x0c
	UINT8		nil;			// 0x0d
	USHORT		unknown2;		// 0x0e
	STRING16	key;			// 0x10
	UINT8		value;			// 0x28
} NODE, *PNODE;

typedef struct _MAP {
	PNODE		head;
} MAP, *PMAP;

/**
 * Represents a IPC message as serialized by CAC (the equivalent to the CIpcMessage structure). This only includes the
 * header portion, to get to the data area one just needs to add the headerLength to the address at which the IPC
 * message was allocated, where the size of the data is given by the dataLength field of the header.
 * 
 * This structure and its use has the objective of making it easier while debugging the code of the utility itself.
 * Solely from a TLV generating perspective, one could use a PVOID for referencing CIpcMessage instances.
 */
typedef struct _CIPCMESSAGE {
	UINT32	idTag;			// 0x00
	UINT16	headerLength;	// 0x04
	UINT16	dataLength;		// 0x06
	UINT32	ipcResponseCB;	// 0x08
	UINT32	msgUserContext;	// 0x0c
	UINT32	requestMsgId;	// 0x10
	UINT32	returnIpcIndex;	// 0x14
	UINT8	messageType;	// 0x18
	UINT8	messageId;		// 0x19
} IPCMESSAGE, *PIPCMESSAGE, **PPIPCMESSAGE;

/**
 * Prototype for the function used to destroy and free the memory used by an IPC message that was obtained by using the
 * function CIPCCTLV::getIpcMessage.
 */
typedef VOID(__thiscall* CIpcMessage_destroyIpcMessage)(PIPCMESSAGE);

/**
 * Represents a CIPCTLV class instance. Same objective as for the IPCMESSAGE structure above, to make debugging the
 * utility own code easier.
 */
typedef struct _CIPCTLV {
	PVOID	vftableCTLV;				// 0x00
	UINT32	unknown1;					// 0x04
	PVOID	vftableCIpcResponseInfo;	// 0x08
	UINT32	ipcResponseCB;				// 0x0c
	UINT32	requestMsgId;				// 0x10
	UINT32	returnIpcIndex;				// 0x14
	UINT32	messageId;					// 0x18
	UINT32	messageType;				// 0x1c
	UINT8	unknown2;					// 0x20
	UINT32	dataCrypt;					// 0x24
} CIPCTLV, *PCIPCTLV;

/**
 * Method used to create a new IPC message from an existing CIPCTLV instance. IPC messages obtained using this method
 * need to be cleaned/freed up using the CIpcMessage::destroIpcMessage method.
 */
typedef LONG(__thiscall* CIPCTLV_getIpcMessage)(PCIPCTLV, PPIPCMESSAGE);

class CModuleWrapper {
private:
	HMODULE moduleHandle;

public:
	CModuleWrapper(LPCTSTR modulesDirectory, LPCTSTR moduleName, PDWORD errorCode);
	~CModuleWrapper();

	template <typename T> T GetExport(LPCSTR exportName) {
		return (T)GetProcAddress(this->moduleHandle, exportName);
	}
};

template <typename T> class CClassWrapper {
protected:
	CModuleWrapper* moduleWrapper;
	T*				realInstance;

public:
	inline T* GetInstance() {
		return this->realInstance;
	}

	CClassWrapper(CModuleWrapper* moduleWrapper)
		: moduleWrapper(moduleWrapper)
	{
	}

	virtual ~CClassWrapper() {
	}

	virtual BOOL ConstructInstance() = 0;
	virtual BOOL PrepareInstance() = 0;
	virtual VOID DestructInstance() = 0;
};

class CIPCClassWrapper : public CClassWrapper<CIPCTLV> {
private:
	CIPCTLV_getIpcMessage getIpcMessage;
	CIpcMessage_destroyIpcMessage destroyIpcMessage;

public:
	LONG CreateIpcMessage(PPIPCMESSAGE resultingIpcMsg);

	VOID DestroyIpcMessage(PIPCMESSAGE ipcMessage);

	CIPCClassWrapper(CModuleWrapper* moduleWrapper);
	virtual ~CIPCClassWrapper();
};

class CSkip {
public:
	virtual BOOL DumpMessage(PIPCMESSAGE ipcMessage) = 0;
};

class CDumper {
protected:
	CSkip*				destination;
	CIPCClassWrapper*	wrappedClass;

public:
	CDumper(CSkip* destination, CIPCClassWrapper* wrappedClass);
	virtual ~CDumper();

	BOOL DumpMessage();
};

/**
 * Global variables used when preparing/setting the TLVs of each message.
 */
extern LPCSTR paramLPCSTR;
extern LPCWSTR paramLPCWSTR;

extern BOOL paramBOOL;

extern UINT8 paramUINT8;
extern UINT16 paramUINT16;
extern UINT32 paramUINT32;
extern UINT64 paramUINT64;
extern ULONG32 paramULONG32;

extern UINT8 paramUINT8Array[8];

extern INT32 paramINT32;
extern INT64 paramINT64;
extern LONG32 paramLONG32;

extern STRING8 paramSTRING8;
extern STRING16 paramSTRING16;

extern VECTOR paramUINT8Vector;

extern NODE paramMAPLeft;
extern NODE paramMAPRight;
extern NODE paramMAPHead;
extern MAP paramMAP;
