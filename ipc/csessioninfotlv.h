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
 * In CSessionInfoTlv::SetDynamicSplitTunDomains it is possible to identify that there is at least one enumeration
 * value. Further in vpnagent.exe at 0x0045c5d5 and at 0x0045c64b one can identify that 0 and 1 are values.
 */
enum DYN_SPLIT_TUN_TYPE {
	DYN_SPLIT_TUN_TYPE_TODO_0 = 0x00000000,
	DYN_SPLIT_TUN_TYPE_TODO_1 = 0x00000001,
};

/**
 *
 */
typedef struct _DYN_ROUTE {
	UINT8	unknown[0x76];
} DYN_ROUTE, *PDYN_ROUTE;

/**
 *
 */
typedef struct _ROUTE {
	UINT8	unknown[0x12];
} ROUTE, *PROUTE;

/**
 *
 */
typedef struct _FW_RULE {
	UINT8	unknown[0x58];
} FW_RULE, *PFW_RULE;

typedef PVOID(__thiscall* CSessionInfoTlv_Constructor)(PVOID, PLONG32);
typedef VOID(__thiscall* CSessionInfoTlv_Destructor)(PVOID);
typedef LONG(__thiscall* CSessionInfoTlv_AddDynamicNonsecureRoute)(PVOID, ADDR_FAMILY, PDYN_ROUTE, BOOL);
typedef LONG(__thiscall* CSessionInfoTlv_AddDynamicSecureRoute)(PVOID, ADDR_FAMILY, PDYN_ROUTE, BOOL);
typedef LONG(__thiscall* CSessionInfoTlv_AddFwRule)(PVOID, PFW_RULE);
typedef LONG(__thiscall* CSessionInfoTlv_AddNonsecureRoute)(PVOID, ADDR_FAMILY, PROUTE, BOOL);
typedef LONG(__thiscall* CSessionInfoTlv_AddSecureRoute)(PVOID, ADDR_FAMILY, PROUTE, BOOL);
typedef LONG(__thiscall* CSessionInfoTlv_SetAdministrativeDomain)(PVOID, PSTRING16);
typedef LONG(__thiscall* CSessionInfoTlv_SetAlwaysOnVPN)(PVOID, ALWAYS_ON_VPN);
typedef LONG(__thiscall* CSessionInfoTlv_SetAppliedNonsecureRouteCount)(PVOID, ADDR_FAMILY, UINT16);
typedef LONG(__thiscall* CSessionInfoTlv_SetAppliedSecureRouteCount)(PVOID, ADDR_FAMILY, UINT16);
typedef LONG(__thiscall* CSessionInfoTlv_setClientIPv4Addr)(PVOID, PSTRING8);
typedef LONG(__thiscall* CSessionInfoTlv_setClientIPv6Addr)(PVOID, PSTRING8);
typedef LONG(__thiscall* CSessionInfoTlv_SetClientOperatingMode)(PVOID, UINT32);
typedef LONG(__thiscall* CSessionInfoTlv_SetDAPUserMessage)(PVOID, PSTRING16);
typedef LONG(__thiscall* CSessionInfoTlv_SetDynamicSplitTunDomains)(PVOID, DYN_SPLIT_TUN_TYPE, PSTRING8);
typedef LONG(__thiscall* CSessionInfoTlv_SetInvokedByCode)(PVOID, PSTRING16);
typedef LONG(__thiscall* CSessionInfoTlv_SetOnConnectScriptName)(PVOID, PSTRING16);
typedef LONG(__thiscall* CSessionInfoTlv_SetOnDisconnectScriptName)(PVOID, PSTRING16);
typedef LONG(__thiscall* CSessionInfoTlv_SetProfileName)(PVOID, PSTRING16);
typedef LONG(__thiscall* CSessionInfoTlv_setProxyHostName)(PVOID, PSTRING8);
typedef LONG(__thiscall* CSessionInfoTlv_setProxyIPAddr)(PVOID, PSTRING8);
typedef LONG(__thiscall* CSessionInfoTlv_setProxyPort)(PVOID, UINT16);
typedef LONG(__thiscall* CSessionInfoTlv_SetQuarantineState)(PVOID, QUARANTINE_STATE);
typedef LONG(__thiscall* CSessionInfoTlv_SetSessionInfoScope)(PVOID, SESSION_INFO_SCOPE);
typedef LONG(__thiscall* CSessionInfoTlv_setSGAddr)(PVOID, PSTRING8);
typedef LONG(__thiscall* CSessionInfoTlv_SetSGFriendlyHostName)(PVOID, PSTRING16);
typedef LONG(__thiscall* CSessionInfoTlv_setSGHostName)(PVOID, PSTRING8);
typedef LONG(__thiscall* CSessionInfoTlv_SetTunnelingMode)(PVOID, ADDR_FAMILY, TUNNELING_MODE);
typedef LONG(__thiscall* CSessionInfoTlv_SetVpnProtocol)(PVOID, CONNECT_PROTOCOL_TYPE);

class CSessionInfoTlv : public CIPCClassWrapper {
protected:
	CSessionInfoTlv_Constructor constructor;
	CSessionInfoTlv_Destructor destructor;
	CSessionInfoTlv_AddDynamicNonsecureRoute addDynamicNonsecureRoute;
	CSessionInfoTlv_AddDynamicSecureRoute addDynamicSecureRoute;
	CSessionInfoTlv_AddFwRule addFwRule;
	CSessionInfoTlv_AddNonsecureRoute addNonsecureRoute;
	CSessionInfoTlv_AddSecureRoute addSecureRoute;
	CSessionInfoTlv_SetAdministrativeDomain setAdministrativeDomain;
	CSessionInfoTlv_SetAlwaysOnVPN setAlwaysOnVPN;
	CSessionInfoTlv_SetAppliedNonsecureRouteCount setAppliedNonsecureRouteCount;
	CSessionInfoTlv_SetAppliedSecureRouteCount setAppliedSecureRouteCount;
	CSessionInfoTlv_setClientIPv4Addr setClientIPv4Addr;
	CSessionInfoTlv_setClientIPv6Addr setClientIPv6Addr;
	CSessionInfoTlv_SetClientOperatingMode setClientOperatingMode;
	CSessionInfoTlv_SetDAPUserMessage setDAPUserMessage;
	CSessionInfoTlv_SetDynamicSplitTunDomains setDynamicSplitTunDomains;
	CSessionInfoTlv_SetInvokedByCode setInvokedByCode;
	CSessionInfoTlv_SetOnConnectScriptName setOnConnectScriptName;
	CSessionInfoTlv_SetOnDisconnectScriptName setOnDisconnectScriptName;
	CSessionInfoTlv_SetProfileName setProfileName;
	CSessionInfoTlv_setProxyHostName setProxyHostName;
	CSessionInfoTlv_setProxyIPAddr setProxyIPAddr;
	CSessionInfoTlv_setProxyPort setProxyPort;
	CSessionInfoTlv_SetQuarantineState setQuarantineState;
	CSessionInfoTlv_SetSessionInfoScope setSessionInfoScope;
	CSessionInfoTlv_setSGAddr setSGAddr;
	CSessionInfoTlv_SetSGFriendlyHostName setSGFriendlyHostName;
	CSessionInfoTlv_setSGHostName setSGHostName;
	CSessionInfoTlv_SetTunnelingMode setTunnelingMode;
	CSessionInfoTlv_SetVpnProtocol setVpnProtocol;


public:
	CSessionInfoTlv(CModuleWrapper* moduleWrapper);
	virtual ~CSessionInfoTlv();

	BOOL ConstructInstance();
	virtual BOOL PrepareInstance();
	VOID DestructInstance();
};

class CSessionInfoTlvDumper : public CDumper {
public:
	CSessionInfoTlvDumper(CSkip* destination, CModuleWrapper* moduleWrapper)
		: CDumper(destination, new CSessionInfoTlv(moduleWrapper))
	{
	}

	~CSessionInfoTlvDumper() {
		delete this->wrappedClass;
	}
};

/**
 *
 */
extern DYN_ROUTE gDynRouteParam;
extern ROUTE gRouteParam;
extern FW_RULE gFWRuleParam;
