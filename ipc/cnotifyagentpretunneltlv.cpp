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
#include "cnotifyagentpretunneltlv.h"

CNotifyAgentPreTunnelTlv::CNotifyAgentPreTunnelTlv(CModuleWrapper* moduleWrapper)
	: CIPCClassWrapper(moduleWrapper)
{
	this->constructor = this->moduleWrapper->GetExport<CNotifyAgentPreTunnelTlv_Constructor>(
		"??0CNotifyAgentPreTunnelTlv@@QAE@AAJW4IPC_MESSAGE_ID@@@Z");
	this->destructor = this->moduleWrapper->GetExport<CNotifyAgentPreTunnelTlv_Destructor>(
		"??1CIPCTLV@@UAE@XZ");
	this->setConnectContinue = this->moduleWrapper->GetExport<CNotifyAgentPreTunnelTlv_SetConnectContinue>(
		"?SetConnectContinue@CNotifyAgentPreTunnelTlv@@QAEJ_N@Z");
	this->setConnectStopReason = this->moduleWrapper->GetExport<CNotifyAgentPreTunnelTlv_SetConnectStopReason>(
		"?SetConnectStopReason@CNotifyAgentPreTunnelTlv@@QAEJW4CONNECT_STOP_REASON@1@@Z");
	this->setDecodedSSOToken = this->moduleWrapper->GetExport<CNotifyAgentPreTunnelTlv_SetDecodedSSOToken>(
		"?SetDecodedSSOToken@CNotifyAgentPreTunnelTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setDetermineProxy = this->moduleWrapper->GetExport<CNotifyAgentPreTunnelTlv_SetDetermineProxy>(
		"?SetDetermineProxy@CNotifyAgentPreTunnelTlv@@QAEJ_N@Z");
	this->setDeviceGlobalUniqueID = this->moduleWrapper->GetExport<CNotifyAgentPreTunnelTlv_SetDeviceGlobalUniqueID>(
		"?SetDeviceGlobalUniqueID@CNotifyAgentPreTunnelTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setDeviceName = this->moduleWrapper->GetExport<CNotifyAgentPreTunnelTlv_SetDeviceName>(
		"?SetDeviceName@CNotifyAgentPreTunnelTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setDeviceType = this->moduleWrapper->GetExport<CNotifyAgentPreTunnelTlv_SetDeviceType>(
		"?SetDeviceType@CNotifyAgentPreTunnelTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setDeviceUniqueID = this->moduleWrapper->GetExport<CNotifyAgentPreTunnelTlv_SetDeviceUniqueID>(
		"?SetDeviceUniqueID@CNotifyAgentPreTunnelTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setEncodedSSOToken = this->moduleWrapper->GetExport<CNotifyAgentPreTunnelTlv_SetEncodedSSOToken>(
		"?SetEncodedSSOToken@CNotifyAgentPreTunnelTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setHostAddress = this->moduleWrapper->GetExport<CNotifyAgentPreTunnelTlv_SetHostAddress>(
		"?SetHostAddress@CNotifyAgentPreTunnelTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setHostMightRequireProxyWithAlwaysOn = this->moduleWrapper->GetExport<CNotifyAgentPreTunnelTlv_SetHostMightRequireProxyWithAlwaysOn>(
		"?SetHostMightRequireProxyWithAlwaysOn@CNotifyAgentPreTunnelTlv@@QAEJ_N@Z");
	this->setHostProtocol = this->moduleWrapper->GetExport<CNotifyAgentPreTunnelTlv_SetHostProtocol>(
		"?SetHostProtocol@CNotifyAgentPreTunnelTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setHostRequiresProxyWithAlwaysOn = this->moduleWrapper->GetExport<CNotifyAgentPreTunnelTlv_SetHostRequiresProxyWithAlwaysOn>(
		"?SetHostRequiresProxyWithAlwaysOn@CNotifyAgentPreTunnelTlv@@QAEJ_N@Z");
	this->setMacAddresses = this->moduleWrapper->GetExport<CNotifyAgentPreTunnelTlv_SetMacAddresses>(
		"?SetMacAddresses@CNotifyAgentPreTunnelTlv@@QAEJABV?$map@V?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@_NU?$less@V?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@2@V?$allocator@U?$pair@$$CBV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@_N@std@@@2@@std@@@Z");
	this->setPlatformVersion = this->moduleWrapper->GetExport<CNotifyAgentPreTunnelTlv_SetPlatformVersion>(
		"?SetPlatformVersion@CNotifyAgentPreTunnelTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setPrimaryHostIPAddress = this->moduleWrapper->GetExport<CNotifyAgentPreTunnelTlv_SetPrimaryHostIPAddress>(
		"?SetPrimaryHostIPAddress@CNotifyAgentPreTunnelTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setProfileName = this->moduleWrapper->GetExport<CNotifyAgentPreTunnelTlv_SetProfileName>(
		"?SetProfileName@CNotifyAgentPreTunnelTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setProxyString = this->moduleWrapper->GetExport<CNotifyAgentPreTunnelTlv_SetProxyString>(
		"?SetProxyString@CNotifyAgentPreTunnelTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setSecondaryHostIPAddress = this->moduleWrapper->GetExport<CNotifyAgentPreTunnelTlv_SetSecondaryHostIPAddress>(
		"?SetSecondaryHostIPAddress@CNotifyAgentPreTunnelTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setStrapDHPublicKey = this->moduleWrapper->GetExport<CNotifyAgentPreTunnelTlv_SetStrapDHPublicKey>(
		"?SetStrapDHPublicKey@CNotifyAgentPreTunnelTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setStrapPublicKey = this->moduleWrapper->GetExport<CNotifyAgentPreTunnelTlv_SetStrapPublicKey>(
		"?SetStrapPublicKey@CNotifyAgentPreTunnelTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setUIProcessPID = this->moduleWrapper->GetExport<CNotifyAgentPreTunnelTlv_SetUIProcessPID>(
		"?SetUIProcessPID@CNotifyAgentPreTunnelTlv@@QAEJK@Z");
	this->setVpnTunnelScope = this->moduleWrapper->GetExport<CNotifyAgentPreTunnelTlv_SetVpnTunnelScope>(
		"?SetVpnTunnelScope@CNotifyAgentPreTunnelTlv@@QAEJW4VPN_TUNNEL_SCOPE@@@Z");
}

CNotifyAgentPreTunnelTlv::~CNotifyAgentPreTunnelTlv() {
}

BOOL CNotifyAgentPreTunnelTlv::ConstructInstance() {
	LONG32 lErrorCode = 0;

	if (this->realInstance == NULL) {
		return FALSE;
	}

	this->constructor(this->realInstance, &lErrorCode, 0x15);

	return (lErrorCode == 0);
}

BOOL CNotifyAgentPreTunnelTlv::PrepareInstance() {
	if (this->realInstance == NULL) {
		return FALSE;
	}

	if (this->setConnectContinue(this->realInstance, paramBOOL) != 0) {
		return FALSE;
	}
	if (this->setConnectStopReason(this->realInstance, CONNECT_STOP_REASON_TODO) != 0) {
		return FALSE;
	}
	if (this->setDecodedSSOToken(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setDetermineProxy(this->realInstance, paramBOOL) != 0) {
		return FALSE;
	}
	if (this->setDeviceGlobalUniqueID(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setDeviceName(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setDeviceType(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setDeviceUniqueID(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setEncodedSSOToken(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setHostAddress(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setHostMightRequireProxyWithAlwaysOn(this->realInstance, paramBOOL) != 0) {
		return FALSE;
	}
	if (this->setHostProtocol(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setHostRequiresProxyWithAlwaysOn(this->realInstance, paramBOOL) != 0) {
		return FALSE;
	}
	if (this->setMacAddresses(this->realInstance, &paramMAP) != 0) {
		return FALSE;
	}
	if (this->setPlatformVersion(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setPrimaryHostIPAddress(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setProfileName(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setProxyString(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setSecondaryHostIPAddress(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setStrapDHPublicKey(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setStrapPublicKey(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setUIProcessPID(this->realInstance, paramULONG32) != 0) {
		return FALSE;
	}
	if (this->setVpnTunnelScope(this->realInstance, VPN_TUNNEL_SCOPE_1) != 0) {
		return FALSE;
	}

	return TRUE;
}

VOID CNotifyAgentPreTunnelTlv::DestructInstance() {
	if (this->realInstance != NULL) {
		this->destructor(this->realInstance);
	}
}
