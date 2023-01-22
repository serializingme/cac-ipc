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

typedef PVOID(__thiscall* CConnectIfcDataTLV_Constructor)(PVOID, PLONG32, PVOID, PVOID);
typedef VOID(__thiscall* CConnectIfcDataTLV_Destructor)(PVOID);
typedef LONG(__thiscall* CConnectIfcDataTLV_AddCredentialsName)(PVOID, PSTRING16);
typedef LONG(__thiscall* CConnectIfcDataTLV_AddCredentialsValue)(PVOID, PSTRING16);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetAggAuthFlag)(PVOID, PSTRING16);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetAggAuthRequest)(PVOID, PSTRING16);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetAuthCookie)(PVOID, PSTRING16);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetCertMatchPattern)(PVOID, PSTRING16);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetClientAuthCertNeeded)(PVOID, BOOL);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetClientCertStoreType)(PVOID, UINT32);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetClientCertThumbprint)(PVOID, PSTRING16);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetConfigCookie)(PVOID, PSTRING16);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetConnectMessageResult)(PVOID, LONG32);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetConnectMessageType)(PVOID, UINT16);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetContentType)(PVOID, UINT16);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetCredentialsCount)(PVOID, UINT16);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetCSDEventFired)(PVOID, INT32);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetCSDStartUrl)(PVOID, PSTRING16);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetCSDStubUrl)(PVOID, PSTRING16);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetCSDTicket)(PVOID, PSTRING16);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetCSDToken)(PVOID, PSTRING16);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetCSDTokenVerified)(PVOID, INT32);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetDataBlobBuffer)(PVOID, UINT16, PUINT8);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetDestFilePath)(PVOID, PSTRING16);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetEnrollmentCAHref)(PVOID, PSTRING16);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetGroupURLCookie)(PVOID, PSTRING16);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetIKEAuthMethod)(PVOID, USER_AUTH_METHOD);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetIKEIdentity)(PVOID, PSTRING16);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetIsSBL)(PVOID, BOOL);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetLastConnectError)(PVOID, PSTRING16);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetOpCode)(PVOID, UINT16);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetOrigPeerUrl)(PVOID, PSTRING16);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetPeerPrimaryIPAddress)(PVOID, PSTRING16);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetPeerSecondaryIPAddress)(PVOID, PSTRING16);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetPeerUrl)(PVOID, PSTRING16);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetPID)(PVOID, ULONG32);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetProcessedCSDData)(PVOID, INT32);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetProtocolType)(PVOID, CONNECT_PROTOCOL_TYPE);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetProtocolVersion)(PVOID, CONNECT_PROTOCOL_VERSION);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetProxyEnAuthority)(PVOID, UINT16, PUINT8);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetProxyEnPassword)(PVOID, UINT16, PUINT8);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetProxyEnPrincipal)(PVOID, UINT16, PUINT8);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetProxyHost)(PVOID, PSTRING16);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetProxyMessage)(PVOID, PSTRING16);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetProxyPort)(PVOID, PSTRING16);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetProxyRealm)(PVOID, PSTRING16);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetProxyString)(PVOID, PSTRING16);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetProxyType)(PVOID, UINT16);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetResponseString)(PVOID, PSTRING8);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetResponseType)(PVOID, UINT16);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetServerCertThumbprint)(PVOID, PSTRING16);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetSGFriendlyHostName)(PVOID, PSTRING16);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetStrapPubKey)(PVOID, PSTRING16, PSTRING16);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetUsePeerPrimaryIPAddress)(PVOID, BOOL);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetVerifyCSDTokenOnly)(PVOID, INT32);
typedef LONG(__thiscall* CConnectIfcDataTLV_SetVpnTunnelScope)(PVOID, VPN_TUNNEL_SCOPE);

class CConnectIfcDataTLV : public CIPCClassWrapper {
protected:
	CConnectIfcDataTLV_Constructor constructor;
	CConnectIfcDataTLV_Destructor destructor;
	CConnectIfcDataTLV_AddCredentialsName addCredentialsName;
	CConnectIfcDataTLV_AddCredentialsValue addCredentialsValue;
	CConnectIfcDataTLV_SetAggAuthFlag setAggAuthFlag;
	CConnectIfcDataTLV_SetAggAuthRequest setAggAuthRequest;
	CConnectIfcDataTLV_SetAuthCookie setAuthCookie;
	CConnectIfcDataTLV_SetCertMatchPattern setCertMatchPattern;
	CConnectIfcDataTLV_SetClientAuthCertNeeded setClientAuthCertNeeded;
	CConnectIfcDataTLV_SetClientCertStoreType setClientCertStoreType;
	CConnectIfcDataTLV_SetClientCertThumbprint setClientCertThumbprint;
	CConnectIfcDataTLV_SetConfigCookie setConfigCookie;
	CConnectIfcDataTLV_SetConnectMessageResult setConnectMessageResult;
	CConnectIfcDataTLV_SetConnectMessageType setConnectMessageType;
	CConnectIfcDataTLV_SetContentType setContentType;
	CConnectIfcDataTLV_SetCredentialsCount setCredentialsCount;
	CConnectIfcDataTLV_SetCSDEventFired setCSDEventFired;
	CConnectIfcDataTLV_SetCSDStartUrl setCSDStartUrl;
	CConnectIfcDataTLV_SetCSDStubUrl setCSDStubUrl;
	CConnectIfcDataTLV_SetCSDTicket setCSDTicket;
	CConnectIfcDataTLV_SetCSDToken setCSDToken;
	CConnectIfcDataTLV_SetCSDTokenVerified setCSDTokenVerified;
	CConnectIfcDataTLV_SetDataBlobBuffer setDataBlobBuffer;
	CConnectIfcDataTLV_SetDestFilePath setDestFilePath;
	CConnectIfcDataTLV_SetEnrollmentCAHref setEnrollmentCAHref;
	CConnectIfcDataTLV_SetGroupURLCookie setGroupURLCookie;
	CConnectIfcDataTLV_SetIKEAuthMethod setIKEAuthMethod;
	CConnectIfcDataTLV_SetIKEIdentity setIKEIdentity;
	CConnectIfcDataTLV_SetIsSBL setIsSBL;
	CConnectIfcDataTLV_SetLastConnectError setLastConnectError;
	CConnectIfcDataTLV_SetOpCode setOpCode;
	CConnectIfcDataTLV_SetOrigPeerUrl setOrigPeerUrl;
	CConnectIfcDataTLV_SetPeerPrimaryIPAddress setPeerPrimaryIPAddress;
	CConnectIfcDataTLV_SetPeerSecondaryIPAddress setPeerSecondaryIPAddress;
	CConnectIfcDataTLV_SetPeerUrl setPeerUrl;
	CConnectIfcDataTLV_SetPID setPID;
	CConnectIfcDataTLV_SetProcessedCSDData setProcessedCSDData;
	CConnectIfcDataTLV_SetProtocolType setProtocolType;
	CConnectIfcDataTLV_SetProtocolVersion setProtocolVersion;
	CConnectIfcDataTLV_SetProxyEnAuthority setProxyEnAuthority;
	CConnectIfcDataTLV_SetProxyEnPassword setProxyEnPassword;
	CConnectIfcDataTLV_SetProxyEnPrincipal setProxyEnPrincipal;
	CConnectIfcDataTLV_SetProxyHost setProxyHost;
	CConnectIfcDataTLV_SetProxyMessage setProxyMessage;
	CConnectIfcDataTLV_SetProxyPort setProxyPort;
	CConnectIfcDataTLV_SetProxyRealm setProxyRealm;
	CConnectIfcDataTLV_SetProxyString setProxyString;
	CConnectIfcDataTLV_SetProxyType setProxyType;
	CConnectIfcDataTLV_SetResponseString setResponseString;
	CConnectIfcDataTLV_SetResponseType setResponseType;
	CConnectIfcDataTLV_SetServerCertThumbprint setServerCertThumbprint;
	CConnectIfcDataTLV_SetSGFriendlyHostName setSGFriendlyHostName;
	CConnectIfcDataTLV_SetStrapPubKey setStrapPubKey;
	CConnectIfcDataTLV_SetUsePeerPrimaryIPAddress setUsePeerPrimaryIPAddress;
	CConnectIfcDataTLV_SetVerifyCSDTokenOnly setVerifyCSDTokenOnly;
	CConnectIfcDataTLV_SetVpnTunnelScope setVpnTunnelScope;

public:
	CConnectIfcDataTLV(CModuleWrapper* moduleWrapper);
	virtual ~CConnectIfcDataTLV();

	BOOL ConstructInstance();
	virtual BOOL PrepareInstance();
	VOID DestructInstance();
};

class CConnectIfcDataTLVDumper : public CDumper {
public:
	CConnectIfcDataTLVDumper(CSkip* destination, CModuleWrapper* moduleWrapper)
		: CDumper(destination, new CConnectIfcDataTLV(moduleWrapper))
	{
	}

	~CConnectIfcDataTLVDumper() {
		delete this->wrappedClass;
	}
};
