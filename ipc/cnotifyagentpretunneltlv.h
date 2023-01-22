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

typedef PVOID(__thiscall* CNotifyAgentPreTunnelTlv_Constructor)(PVOID, PLONG32, UINT32);
typedef VOID(__thiscall* CNotifyAgentPreTunnelTlv_Destructor)(PVOID);
typedef LONG(__thiscall* CNotifyAgentPreTunnelTlv_SetConnectContinue)(PVOID, BOOL);
typedef LONG(__thiscall* CNotifyAgentPreTunnelTlv_SetConnectStopReason)(PVOID, CONNECT_STOP_REASON);
typedef LONG(__thiscall* CNotifyAgentPreTunnelTlv_SetDecodedSSOToken)(PVOID, PSTRING16);
typedef LONG(__thiscall* CNotifyAgentPreTunnelTlv_SetDetermineProxy)(PVOID, BOOL);
typedef LONG(__thiscall* CNotifyAgentPreTunnelTlv_SetDeviceGlobalUniqueID)(PVOID, PSTRING16);
typedef LONG(__thiscall* CNotifyAgentPreTunnelTlv_SetDeviceName)(PVOID, PSTRING16);
typedef LONG(__thiscall* CNotifyAgentPreTunnelTlv_SetDeviceType)(PVOID, PSTRING16);
typedef LONG(__thiscall* CNotifyAgentPreTunnelTlv_SetDeviceUniqueID)(PVOID, PSTRING16);
typedef LONG(__thiscall* CNotifyAgentPreTunnelTlv_SetEncodedSSOToken)(PVOID, PSTRING16);
typedef LONG(__thiscall* CNotifyAgentPreTunnelTlv_SetHostAddress)(PVOID, PSTRING16);
typedef LONG(__thiscall* CNotifyAgentPreTunnelTlv_SetHostMightRequireProxyWithAlwaysOn)(PVOID, BOOL);
typedef LONG(__thiscall* CNotifyAgentPreTunnelTlv_SetHostProtocol)(PVOID, PSTRING16);
typedef LONG(__thiscall* CNotifyAgentPreTunnelTlv_SetHostRequiresProxyWithAlwaysOn)(PVOID, BOOL);
typedef LONG(__thiscall* CNotifyAgentPreTunnelTlv_SetMacAddresses)(PVOID, PMAP);
typedef LONG(__thiscall* CNotifyAgentPreTunnelTlv_SetPlatformVersion)(PVOID, PSTRING16);
typedef LONG(__thiscall* CNotifyAgentPreTunnelTlv_SetPrimaryHostIPAddress)(PVOID, PSTRING16);
typedef LONG(__thiscall* CNotifyAgentPreTunnelTlv_SetProfileName)(PVOID, PSTRING16);
typedef LONG(__thiscall* CNotifyAgentPreTunnelTlv_SetProxyString)(PVOID, PSTRING16);
typedef LONG(__thiscall* CNotifyAgentPreTunnelTlv_SetSecondaryHostIPAddress)(PVOID, PSTRING16);
typedef LONG(__thiscall* CNotifyAgentPreTunnelTlv_SetStrapDHPublicKey)(PVOID, PSTRING16);
typedef LONG(__thiscall* CNotifyAgentPreTunnelTlv_SetStrapPublicKey)(PVOID, PSTRING16);
typedef LONG(__thiscall* CNotifyAgentPreTunnelTlv_SetUIProcessPID)(PVOID, ULONG32);
typedef LONG(__thiscall* CNotifyAgentPreTunnelTlv_SetVpnTunnelScope)(PVOID, VPN_TUNNEL_SCOPE);

class CNotifyAgentPreTunnelTlv : public CIPCClassWrapper {
protected:
	CNotifyAgentPreTunnelTlv_Constructor constructor;
	CNotifyAgentPreTunnelTlv_Destructor destructor;
	CNotifyAgentPreTunnelTlv_SetConnectContinue setConnectContinue;
	CNotifyAgentPreTunnelTlv_SetConnectStopReason setConnectStopReason;
	CNotifyAgentPreTunnelTlv_SetDecodedSSOToken setDecodedSSOToken;
	CNotifyAgentPreTunnelTlv_SetDetermineProxy setDetermineProxy;
	CNotifyAgentPreTunnelTlv_SetDeviceGlobalUniqueID setDeviceGlobalUniqueID;
	CNotifyAgentPreTunnelTlv_SetDeviceName setDeviceName;
	CNotifyAgentPreTunnelTlv_SetDeviceType setDeviceType;
	CNotifyAgentPreTunnelTlv_SetDeviceUniqueID setDeviceUniqueID;
	CNotifyAgentPreTunnelTlv_SetEncodedSSOToken setEncodedSSOToken;
	CNotifyAgentPreTunnelTlv_SetHostAddress setHostAddress;
	CNotifyAgentPreTunnelTlv_SetHostMightRequireProxyWithAlwaysOn setHostMightRequireProxyWithAlwaysOn;
	CNotifyAgentPreTunnelTlv_SetHostProtocol setHostProtocol;
	CNotifyAgentPreTunnelTlv_SetHostRequiresProxyWithAlwaysOn setHostRequiresProxyWithAlwaysOn;
	CNotifyAgentPreTunnelTlv_SetMacAddresses setMacAddresses;
	CNotifyAgentPreTunnelTlv_SetPlatformVersion setPlatformVersion;
	CNotifyAgentPreTunnelTlv_SetPrimaryHostIPAddress setPrimaryHostIPAddress;
	CNotifyAgentPreTunnelTlv_SetProfileName setProfileName;
	CNotifyAgentPreTunnelTlv_SetProxyString setProxyString;
	CNotifyAgentPreTunnelTlv_SetSecondaryHostIPAddress setSecondaryHostIPAddress;
	CNotifyAgentPreTunnelTlv_SetStrapDHPublicKey setStrapDHPublicKey;
	CNotifyAgentPreTunnelTlv_SetStrapPublicKey setStrapPublicKey;
	CNotifyAgentPreTunnelTlv_SetUIProcessPID setUIProcessPID;
	CNotifyAgentPreTunnelTlv_SetVpnTunnelScope setVpnTunnelScope;

public:
	CNotifyAgentPreTunnelTlv(CModuleWrapper* moduleWrapper);
	virtual ~CNotifyAgentPreTunnelTlv();

	BOOL ConstructInstance();
	virtual BOOL PrepareInstance();
	VOID DestructInstance();
};

class CNotifyAgentPreTunnelTlvDumper : public CDumper {
public:
	CNotifyAgentPreTunnelTlvDumper(CSkip* destination, CModuleWrapper* moduleWrapper)
		: CDumper(destination, new CNotifyAgentPreTunnelTlv(moduleWrapper))
	{
	}

	~CNotifyAgentPreTunnelTlvDumper() {
		delete this->wrappedClass;
	}
};
