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

/**
 *
 */
enum DNLDR_OPERATING_MODE {
	DNLDR_OPERATING_MODE_TODO
};

typedef PVOID(__thiscall* CDnldrArgsTlv_Constructor)(PVOID, PLONG32);
typedef VOID(__thiscall* CDnldrArgsTlv_Destructor)(PVOID);
typedef LONG(__thiscall* CDnldrArgsTlv_SetUsingSmartCard)(PVOID, BOOL);
typedef LONG(__thiscall* CDnldrArgsTlv_SetTunnelState)(PVOID, VPN_TUNNEL_STATE);
typedef LONG(__thiscall* CDnldrArgsTlv_SetSGFriendlyHostName)(PVOID, PSTRING16);
typedef LONG(__thiscall* CDnldrArgsTlv_SetSessionToken)(PVOID, PSTRING16);
typedef LONG(__thiscall* CDnldrArgsTlv_SetSessionID)(PVOID, PSTRING16);
typedef LONG(__thiscall* CDnldrArgsTlv_SetServerCertHash)(PVOID, PSTRING16);
typedef LONG(__thiscall* CDnldrArgsTlv_SetProxyUser)(PVOID, PSTRING16);
typedef LONG(__thiscall* CDnldrArgsTlv_SetPoxyType)(PVOID, PUINT16);
typedef LONG(__thiscall* CDnldrArgsTlv_SetProxyString)(PVOID, PSTRING16);
typedef LONG(__thiscall* CDnldrArgsTlv_SetProxyReam)(PVOID, PSTRING16);
typedef LONG(__thiscall* CDnldrArgsTlv_SetProxyPort)(PVOID, PSTRING16);
typedef LONG(__thiscall* CDnldrArgsTlv_SetProxyPassword)(PVOID, PSTRING16);
typedef LONG(__thiscall* CDnldrArgsTlv_SetProxyMessage)(PVOID, PSTRING16);
typedef LONG(__thiscall* CDnldrArgsTlv_SetProxyHost)(PVOID, PSTRING16);
typedef LONG(__thiscall* CDnldrArgsTlv_SetProxyAuthority)(PVOID, PSTRING16);
typedef LONG(__thiscall* CDnldrArgsTlv_SetProfileURI)(PVOID, PSTRING16);
typedef LONG(__thiscall* CDnldrArgsTlv_SetProfileHash)(PVOID, PSTRING16);
typedef LONG(__thiscall* CDnldrArgsTlv_SetOptionalModules)(PVOID, PSTRING16);
typedef LONG(__thiscall* CDnldrArgsTlv_SetOperationMode)(PVOID, DNLDR_OPERATING_MODE);
typedef LONG(__thiscall* CDnldrArgsTlv_SetL10NURI)(PVOID, PSTRING16);
typedef LONG(__thiscall* CDnldrArgsTlv_SetGatewayURL)(PVOID, PSTRING16);
typedef LONG(__thiscall* CDnldrArgsTlv_SetGatewaySecodaryIPAddress)(PVOID, PSTRING16);
typedef LONG(__thiscall* CDnldrArgsTlv_SetGatewayPrimaryIPAddress)(PVOID, PSTRING16);
typedef LONG(__thiscall* CDnldrArgsTlv_SetDetermneProxy)(PVOID, PBOOL);
typedef LONG(__thiscall* CDnldrArgsTlv_SetConnectionType)(PVOID, CONNECT_PROTOCOL_TYPE);
typedef LONG(__thiscall* CDnldrArgsTlv_SetConfigXml)(PVOID, PSTRING16);
typedef LONG(__thiscall* CDnldrArgsTlv_SetClientCertHash)(PVOID, PSTRING16);
typedef LONG(__thiscall* CDnldrArgsTlv_SetCfgCookie)(PVOID, PSTRING16);
typedef LONG(__thiscall* CDnldrArgsTlv_SetCertificateInfo)(PVOID, PCERTIFICATEINFOTLV);
typedef LONG(__thiscall* CDnldrArgsTlv_SetBaseURI)(PVOID, PSTRING16);
typedef LONG(__thiscall* CDnldrArgsTlv_SetAggAuthCertficateInfo)(PVOID, PCERTIFICATEINFOTLV);

class CDnldrArgsTlv : public CIPCClassWrapper {
protected:
	CDnldrArgsTlv_Constructor constructor;
	CDnldrArgsTlv_Destructor destructor;
	CDnldrArgsTlv_SetUsingSmartCard setUsingSmartCard;
	CDnldrArgsTlv_SetTunnelState setTunnelState;
	CDnldrArgsTlv_SetSGFriendlyHostName setSGFriendlyHostName;
	CDnldrArgsTlv_SetSessionToken setSessionToken;
	CDnldrArgsTlv_SetSessionID setSessionID;
	CDnldrArgsTlv_SetServerCertHash setServerCertHash;
	CDnldrArgsTlv_SetProxyUser setProxyUser;
	CDnldrArgsTlv_SetPoxyType setPoxyType;
	CDnldrArgsTlv_SetProxyString setProxyString;
	CDnldrArgsTlv_SetProxyReam setProxyRealm;
	CDnldrArgsTlv_SetProxyPort setProxyPort;
	CDnldrArgsTlv_SetProxyPassword setProxyPassword;
	CDnldrArgsTlv_SetProxyMessage setProxyMessage;
	CDnldrArgsTlv_SetProxyHost setProxyHost;
	CDnldrArgsTlv_SetProxyAuthority setProxyAuthority;
	CDnldrArgsTlv_SetProfileURI setProfileURI;
	CDnldrArgsTlv_SetProfileHash setProfileHash;
	CDnldrArgsTlv_SetOptionalModules setOptionalModules;
	CDnldrArgsTlv_SetOperationMode setOperationMode;
	CDnldrArgsTlv_SetL10NURI setL10NURI;
	CDnldrArgsTlv_SetGatewayURL setGatewayURL;
	CDnldrArgsTlv_SetGatewaySecodaryIPAddress setGatewaySecondaryIPAddress;
	CDnldrArgsTlv_SetGatewayPrimaryIPAddress setGatewayPrimaryIPAddress;
	CDnldrArgsTlv_SetDetermneProxy setDetermineProxy;
	CDnldrArgsTlv_SetConnectionType setConnectionType;
	CDnldrArgsTlv_SetConfigXml setConfigXml;
	CDnldrArgsTlv_SetClientCertHash setClientCertHash;
	CDnldrArgsTlv_SetCfgCookie setCfgCookie;
	CDnldrArgsTlv_SetCertificateInfo setCertificateInfo;
	CDnldrArgsTlv_SetBaseURI setBaseURI;
	CDnldrArgsTlv_SetAggAuthCertficateInfo setAggAuthCertficateInfo;

public:
	CDnldrArgsTlv(CModuleWrapper* moduleWrapper);
	virtual ~CDnldrArgsTlv();

	BOOL ConstructInstance();
	virtual BOOL PrepareInstance();
	VOID DestructInstance();
};

class CDnldrArgsTlvDumper : public CDumper {
public:
	CDnldrArgsTlvDumper(CSkip* destination, CModuleWrapper* moduleWrapper)
		: CDumper(destination, new CDnldrArgsTlv(moduleWrapper))
	{
	}

	~CDnldrArgsTlvDumper() {
		delete this->wrappedClass;
	}
};
