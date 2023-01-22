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
#include "csessioninfotlv.h"

/**
 *
 */
static DYN_ROUTE gDynRouteParam = {};
static ROUTE gRouteParam = {};
static FW_RULE gFWRuleParam = {};


CSessionInfoTlv::CSessionInfoTlv(CModuleWrapper* moduleWrapper)
	: CIPCClassWrapper(moduleWrapper)
{
	this->constructor = this->moduleWrapper->GetExport<CSessionInfoTlv_Constructor>(
		"??0CSessionInfoTlv@@QAE@AAJ@Z");
	this->destructor = this->moduleWrapper->GetExport<CSessionInfoTlv_Destructor>(
		"??1CIPCTLV@@UAE@XZ");
	this->addDynamicNonsecureRoute = this->moduleWrapper->GetExport<CSessionInfoTlv_AddDynamicNonsecureRoute>(
		"?AddDynamicNonsecureRoute@CSessionInfoTlv@@QAEJW4ADDR_FAMILY@@ABUDYN_ROUTE@@_N@Z");
	this->addDynamicSecureRoute = this->moduleWrapper->GetExport<CSessionInfoTlv_AddDynamicSecureRoute>(
		"?AddDynamicSecureRoute@CSessionInfoTlv@@QAEJW4ADDR_FAMILY@@ABUDYN_ROUTE@@_N@Z");
	this->addFwRule = this->moduleWrapper->GetExport<CSessionInfoTlv_AddFwRule>(
		"?AddFwRule@CSessionInfoTlv@@QAEJABUFW_RULE@@@Z");
	this->addNonsecureRoute = this->moduleWrapper->GetExport<CSessionInfoTlv_AddNonsecureRoute>(
		"?AddNonsecureRoute@CSessionInfoTlv@@QAEJW4ADDR_FAMILY@@ABUROUTE@@_N@Z");
	this->addSecureRoute = this->moduleWrapper->GetExport<CSessionInfoTlv_AddSecureRoute>(
		"?AddSecureRoute@CSessionInfoTlv@@QAEJW4ADDR_FAMILY@@ABUROUTE@@_N@Z");
	this->setAdministrativeDomain = this->moduleWrapper->GetExport<CSessionInfoTlv_SetAdministrativeDomain>(
		"?SetAdministrativeDomain@CSessionInfoTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setAlwaysOnVPN = this->moduleWrapper->GetExport<CSessionInfoTlv_SetAlwaysOnVPN>(
		"?SetAlwaysOnVPN@CSessionInfoTlv@@QAEJW4ALWAYS_ON_VPN@@@Z");
	this->setAppliedNonsecureRouteCount = this->moduleWrapper->GetExport<CSessionInfoTlv_SetAppliedNonsecureRouteCount>(
		"?SetAppliedNonsecureRouteCount@CSessionInfoTlv@@QAEJW4ADDR_FAMILY@@G@Z");
	this->setAppliedSecureRouteCount = this->moduleWrapper->GetExport<CSessionInfoTlv_SetAppliedSecureRouteCount>(
		"?SetAppliedSecureRouteCount@CSessionInfoTlv@@QAEJW4ADDR_FAMILY@@G@Z");
	this->setClientIPv4Addr = this->moduleWrapper->GetExport<CSessionInfoTlv_setClientIPv4Addr>(
		"?setClientIPv4Addr@CSessionInfoTlv@@QAEJABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	this->setClientIPv6Addr = this->moduleWrapper->GetExport<CSessionInfoTlv_setClientIPv6Addr>(
		"?setClientIPv6Addr@CSessionInfoTlv@@QAEJABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	this->setClientOperatingMode = this->moduleWrapper->GetExport<CSessionInfoTlv_SetClientOperatingMode>(
		"?SetClientOperatingMode@CSessionInfoTlv@@QAEJI@Z");
	this->setDAPUserMessage = this->moduleWrapper->GetExport<CSessionInfoTlv_SetDAPUserMessage>(
		"?SetDAPUserMessage@CSessionInfoTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setDynamicSplitTunDomains = this->moduleWrapper->GetExport<CSessionInfoTlv_SetDynamicSplitTunDomains>(
		"?SetDynamicSplitTunDomains@CSessionInfoTlv@@QAEJW4DYN_SPLIT_TUN_TYPE@@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	this->setInvokedByCode = this->moduleWrapper->GetExport<CSessionInfoTlv_SetInvokedByCode>(
		"?SetInvokedByCode@CSessionInfoTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setOnConnectScriptName = this->moduleWrapper->GetExport<CSessionInfoTlv_SetOnConnectScriptName>(
		"?SetOnConnectScriptName@CSessionInfoTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setOnDisconnectScriptName = this->moduleWrapper->GetExport<CSessionInfoTlv_SetOnDisconnectScriptName>(
		"?SetOnDisconnectScriptName@CSessionInfoTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setProfileName = this->moduleWrapper->GetExport<CSessionInfoTlv_SetProfileName>(
		"?SetProfileName@CSessionInfoTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setProxyHostName = this->moduleWrapper->GetExport<CSessionInfoTlv_setProxyHostName>(
		"?setProxyHostName@CSessionInfoTlv@@QAEJABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	this->setProxyIPAddr = this->moduleWrapper->GetExport<CSessionInfoTlv_setProxyIPAddr>(
		"?setProxyIPAddr@CSessionInfoTlv@@QAEJABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	this->setProxyPort = this->moduleWrapper->GetExport<CSessionInfoTlv_setProxyPort>(
		"?setProxyPort@CSessionInfoTlv@@QAEJG@Z");
	this->setQuarantineState = this->moduleWrapper->GetExport<CSessionInfoTlv_SetQuarantineState>(
		"?setProxyPort@CSessionInfoTlv@@QAEJG@Z");
	this->setSessionInfoScope = this->moduleWrapper->GetExport<CSessionInfoTlv_SetSessionInfoScope>(
		"?SetSessionInfoScope@CSessionInfoTlv@@QAEJW4SESSION_INFO_SCOPE@1@@Z");
	this->setSGAddr = this->moduleWrapper->GetExport<CSessionInfoTlv_setSGAddr>(
		"?setSGAddr@CSessionInfoTlv@@QAEJABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	this->setSGFriendlyHostName = this->moduleWrapper->GetExport<CSessionInfoTlv_SetSGFriendlyHostName>(
		"?SetSGFriendlyHostName@CSessionInfoTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setSGHostName = this->moduleWrapper->GetExport<CSessionInfoTlv_setSGHostName>(
		"?setSGHostName@CSessionInfoTlv@@QAEJABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	this->setTunnelingMode = this->moduleWrapper->GetExport<CSessionInfoTlv_SetTunnelingMode>(
		"?SetTunnelingMode@CSessionInfoTlv@@QAEJW4ADDR_FAMILY@@W4TUNNELING_MODE@@@Z");
	this->setVpnProtocol = this->moduleWrapper->GetExport<CSessionInfoTlv_SetVpnProtocol>(
		"?SetVpnProtocol@CSessionInfoTlv@@QAEJW4ConnectProtocolType@@@Z");
}

CSessionInfoTlv::~CSessionInfoTlv() {
}

BOOL CSessionInfoTlv::ConstructInstance() {
	LONG32 lErrorCode = 0;

	if (this->realInstance == NULL) {
		return FALSE;
	}

	this->constructor(this->realInstance, &lErrorCode);

	return (lErrorCode == 0);
}

BOOL CSessionInfoTlv::PrepareInstance() {
	if (this->realInstance == NULL) {
		return FALSE;
	}

	if (this->addDynamicNonsecureRoute(this->realInstance, ADDR_FAMILY_IPV4, &gDynRouteParam, FALSE) != 0) {
		return FALSE;
	}
	if (this->addDynamicNonsecureRoute(this->realInstance, ADDR_FAMILY_IPV6, &gDynRouteParam, FALSE) != 0) {
		return FALSE;
	}
	if (this->addDynamicSecureRoute(this->realInstance, ADDR_FAMILY_IPV4, &gDynRouteParam, FALSE) != 0) {
		return FALSE;
	}
	if (this->addDynamicSecureRoute(this->realInstance, ADDR_FAMILY_IPV6, &gDynRouteParam, FALSE) != 0) {
		return FALSE;
	}
	if (this->addFwRule(this->realInstance, &gFWRuleParam) != 0) {
		return FALSE;
	}
	if (this->addNonsecureRoute(this->realInstance, ADDR_FAMILY_IPV4, &gRouteParam, FALSE) != 0) {
		return FALSE;
	}
	if (this->addNonsecureRoute(this->realInstance, ADDR_FAMILY_IPV6, &gRouteParam, FALSE) != 0) {
		return FALSE;
	}
	if (this->addSecureRoute(this->realInstance, ADDR_FAMILY_IPV4, &gRouteParam, FALSE) != 0) {
		return FALSE;
	}
	if (this->addSecureRoute(this->realInstance, ADDR_FAMILY_IPV6, &gRouteParam, FALSE) != 0) {
		return FALSE;
	}
	if (this->setAdministrativeDomain(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setAlwaysOnVPN(this->realInstance, ALWAYS_ON_VPN_TODO) != 0) {
		return FALSE;
	}
	if (this->setAppliedNonsecureRouteCount(this->realInstance, ADDR_FAMILY_IPV4, paramUINT16) != 0) {
		return FALSE;
	}
	if (this->setAppliedNonsecureRouteCount(this->realInstance, ADDR_FAMILY_IPV6, paramUINT16) != 0) {
		return FALSE;
	}
	if (this->setAppliedSecureRouteCount(this->realInstance, ADDR_FAMILY_IPV4, paramUINT16) != 0) {
		return FALSE;
	}
	if (this->setAppliedSecureRouteCount(this->realInstance, ADDR_FAMILY_IPV6, paramUINT16) != 0) {
		return FALSE;
	}
	if (this->setClientIPv4Addr(this->realInstance, &paramSTRING8) != 0) {
		return FALSE;
	}
	if (this->setClientIPv6Addr(this->realInstance, &paramSTRING8) != 0) {
		return FALSE;
	}
	if (this->setClientOperatingMode(this->realInstance, paramUINT32) != 0) {
		return FALSE;
	}
	if (this->setDAPUserMessage(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setDynamicSplitTunDomains(this->realInstance, DYN_SPLIT_TUN_TYPE_TODO_0, &paramSTRING8) != 0) {
		return FALSE;
	}
	if (this->setDynamicSplitTunDomains(this->realInstance, DYN_SPLIT_TUN_TYPE_TODO_1, &paramSTRING8) != 0) {
		return FALSE;
	}
	if (this->setInvokedByCode(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setOnConnectScriptName(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setOnDisconnectScriptName(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setProfileName(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setProxyHostName(this->realInstance, &paramSTRING8) != 0) {
		return FALSE;
	}
	if (this->setProxyIPAddr(this->realInstance, &paramSTRING8) != 0) {
		return FALSE;
	}
	if (this->setProxyPort(this->realInstance, paramUINT16) != 0) {
		return FALSE;
	}
	if (this->setQuarantineState(this->realInstance, QUARANTINE_STATE_TODO) != 0) {
		return FALSE;
	}
	if (this->setSessionInfoScope(this->realInstance, SESSION_INFO_SCOPE_TODO) != 0) {
		return FALSE;
	}
	if (this->setSGAddr(this->realInstance, &paramSTRING8) != 0) {
		return FALSE;
	}
	if (this->setSGFriendlyHostName(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setSGHostName(this->realInstance, &paramSTRING8) != 0) {
		return FALSE;
	}
	if (this->setTunnelingMode(this->realInstance, ADDR_FAMILY_IPV6, TUNNELING_MODE_TODO) != 0) {
		return FALSE;
	}
	if (this->setVpnProtocol(this->realInstance, CONNECT_PROTOCOL_TYPE_TODO) != 0) {
		return FALSE;
	}

	return TRUE;
}

VOID CSessionInfoTlv::DestructInstance() {
	if (this->realInstance != NULL) {
		this->destructor(this->realInstance);
	}
}
