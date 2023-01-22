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

typedef PVOID(__thiscall* CStartParameters_Constructor)(PVOID, PLONG32, PVOID);
typedef VOID(__thiscall* CStartParameters_Destructor)(PVOID);
typedef LONG(__thiscall* CStartParameters_SetAggAuthCertificateInfo)(PVOID, PCERTIFICATEINFOTLV);
typedef LONG(__thiscall* CStartParameters_SetAuthMethod)(PVOID, USER_AUTH_METHOD);
typedef LONG(__thiscall* CStartParameters_SetCertificateInfo)(PVOID, PCERTIFICATEINFOTLV);
typedef LONG(__thiscall* CStartParameters_SetCfgClientCertTp)(PVOID, LPCSTR);
typedef LONG(__thiscall* CStartParameters_SetCfgModules)(PVOID, LPCSTR);
typedef LONG(__thiscall* CStartParameters_SetCfgProtocol)(PVOID, LPCSTR);
typedef LONG(__thiscall* CStartParameters_SetCfgServerCertTp)(PVOID, LPCSTR);
typedef LONG(__thiscall* CStartParameters_SetDetermineProxy)(PVOID, BOOL);
typedef LONG(__thiscall* CStartParameters_SetGUICmdLine)(PVOID, LPCWSTR);
typedef LONG(__thiscall* CStartParameters_SetGUIDesktop)(PVOID, LPCSTR);
typedef LONG(__thiscall* CStartParameters_SetGUIEnv)(PVOID, LPCWSTR);
typedef LONG(__thiscall* CStartParameters_SetGUIFilePath)(PVOID, LPCWSTR);
typedef LONG(__thiscall* CStartParameters_SetIkeIdentity)(PVOID, PSTRING8);
typedef LONG(__thiscall* CStartParameters_SetInitiatorPID)(PVOID, PULONG32);
typedef LONG(__thiscall* CStartParameters_SetInvokedByCode)(PVOID, PSTRING16);
typedef LONG(__thiscall* CStartParameters_SetPrimarySGIPAddr)(PVOID, LPCSTR);
typedef LONG(__thiscall* CStartParameters_SetProfileName)(PVOID, PSTRING16);
typedef LONG(__thiscall* CStartParameters_SetProxyAuthority)(PVOID, PSTRING16);
typedef LONG(__thiscall* CStartParameters_SetProxyEnAuthority)(PVOID, UINT16, PUINT8);
typedef LONG(__thiscall* CStartParameters_SetProxyEnPswd)(PVOID, UINT16, PUINT8);
typedef LONG(__thiscall* CStartParameters_SetProxyEnUser)(PVOID, UINT16, PUINT8);
typedef LONG(__thiscall* CStartParameters_SetProxyHost)(PVOID, PSTRING16);
typedef LONG(__thiscall* CStartParameters_SetProxyMessage)(PVOID, PSTRING16);
typedef LONG(__thiscall* CStartParameters_SetProxyPort)(PVOID, PSTRING16);
typedef LONG(__thiscall* CStartParameters_SetProxyPswd)(PVOID, PSTRING16);
typedef LONG(__thiscall* CStartParameters_SetProxyRealm)(PVOID, PSTRING16);
typedef LONG(__thiscall* CStartParameters_SetProxyString)(PVOID, PSTRING16);
typedef LONG(__thiscall* CStartParameters_SetProxyType)(PVOID, PUINT16);
typedef LONG(__thiscall* CStartParameters_SetProxyUser)(PVOID, PSTRING16);
typedef LONG(__thiscall* CStartParameters_SetSecondarySGIPAddr)(PVOID, LPCSTR);
typedef LONG(__thiscall* CStartParameters_SetSGCookie)(PVOID, LPCSTR);
typedef LONG(__thiscall* CStartParameters_SetSGFriendlyHostName)(PVOID, PSTRING16);
typedef LONG(__thiscall* CStartParameters_SetSGURL)(PVOID, LPCSTR);
typedef LONG(__thiscall* CStartParameters_SetUsingSmartcard)(PVOID, BOOL);
typedef LONG(__thiscall* CStartParameters_SetVpnType)(PVOID, CONNECT_PROTOCOL_TYPE);
typedef LONG(__thiscall* CStartParameters_SetWaitForGUI)(PVOID, BOOL);


class CStartParameters : public CIPCClassWrapper {
protected:
	CStartParameters_Constructor constructor;
	CStartParameters_Destructor destructor;
	CStartParameters_SetAggAuthCertificateInfo setAggAuthCertificateInfo;
	CStartParameters_SetAuthMethod setAuthMethod;
	CStartParameters_SetCertificateInfo setCertificateInfo;
	CStartParameters_SetCfgClientCertTp setCfgClientCertTp;
	CStartParameters_SetCfgModules setCfgModules;
	CStartParameters_SetCfgProtocol setCfgProtocol;
	CStartParameters_SetCfgServerCertTp setCfgServerCertTp;
	CStartParameters_SetDetermineProxy setDetermineProxy;
	CStartParameters_SetGUICmdLine setGUICmdLine;
	CStartParameters_SetGUIDesktop setGUIDesktop;
	CStartParameters_SetGUIEnv setGUIEnv;
	CStartParameters_SetGUIFilePath setGUIFilePath;
	CStartParameters_SetIkeIdentity setIkeIdentity;
	CStartParameters_SetInitiatorPID setInitiatorPID;
	CStartParameters_SetInvokedByCode setInvokedByCode;
	CStartParameters_SetPrimarySGIPAddr setPrimarySGIPAddr;
	CStartParameters_SetProfileName setProfileName;
	CStartParameters_SetProxyAuthority setProxyAuthority;
	CStartParameters_SetProxyEnAuthority setProxyEnAuthority;
	CStartParameters_SetProxyEnPswd setProxyEnPswd;
	CStartParameters_SetProxyEnUser setProxyEnUser;
	CStartParameters_SetProxyHost setProxyHost;
	CStartParameters_SetProxyMessage setProxyMessage;
	CStartParameters_SetProxyPort setProxyPort;
	CStartParameters_SetProxyPswd setProxyPswd;
	CStartParameters_SetProxyRealm setProxyRealm;
	CStartParameters_SetProxyString setProxyString;
	CStartParameters_SetProxyType setProxyType;
	CStartParameters_SetProxyUser setProxyUser;
	CStartParameters_SetSecondarySGIPAddr setSecondarySGIPAddr;
	CStartParameters_SetSGCookie setSGCookie;
	CStartParameters_SetSGFriendlyHostName setSGFriendlyHostName;
	CStartParameters_SetSGURL setSGURL;
	CStartParameters_SetUsingSmartcard setUsingSmartcard;
	CStartParameters_SetVpnType setVpnType;
	CStartParameters_SetWaitForGUI setWaitForGUI;

public:
	CStartParameters(CModuleWrapper* moduleWrapper);
	virtual ~CStartParameters();

	BOOL ConstructInstance();
	virtual BOOL PrepareInstance();
	VOID DestructInstance();
};

class CStartParametersDumper : public CDumper {
public:
	CStartParametersDumper(CSkip* destination, CModuleWrapper* moduleWrapper)
		: CDumper(destination, new CStartParameters(moduleWrapper))
	{
	}

	~CStartParametersDumper() {
		delete this->wrappedClass;
	}
};
