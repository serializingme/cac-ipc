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
#include "cconnectifcdatatlv.h"

CConnectIfcDataTLV::CConnectIfcDataTLV(CModuleWrapper* moduleWrapper)
	: CIPCClassWrapper(moduleWrapper)
{
	this->constructor = this->moduleWrapper->GetExport<CConnectIfcDataTLV_Constructor>(
		"??0CConnectIfcDataTLV@@QAE@AAJPAVIIpcResponseCB@@P6AJAAPAVIDataCrypt@@@Z@Z");
	this->destructor = this->moduleWrapper->GetExport<CConnectIfcDataTLV_Destructor>(
		"??1CIPCTLV@@UAE@XZ");
	this->addCredentialsName = this->moduleWrapper->GetExport<CConnectIfcDataTLV_AddCredentialsName>(
		"?AddCredentialsName@CConnectIfcDataTLV@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->addCredentialsValue = this->moduleWrapper->GetExport<CConnectIfcDataTLV_AddCredentialsValue>(
		"?AddCredentialsValue@CConnectIfcDataTLV@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setAggAuthFlag = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetAggAuthFlag>(
		"?SetAggAuthFlag@CConnectIfcDataTLV@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setAggAuthRequest = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetAggAuthRequest>(
		"?SetAggAuthRequest@CConnectIfcDataTLV@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setAuthCookie = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetAuthCookie>(
		"?SetAuthCookie@CConnectIfcDataTLV@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setCertMatchPattern = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetCertMatchPattern>(
		"?SetCertMatchPattern@CConnectIfcDataTLV@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setClientAuthCertNeeded = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetClientAuthCertNeeded>(
		"?SetClientAuthCertNeeded@CConnectIfcDataTLV@@QAEJ_N@Z");
	this->setClientCertStoreType = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetClientCertStoreType>(
		"?SetClientCertStoreType@CConnectIfcDataTLV@@QAEJI@Z");
	this->setClientCertThumbprint = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetClientCertThumbprint>(
		"?SetClientCertThumbprint@CConnectIfcDataTLV@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setConfigCookie = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetConfigCookie>(
		"?SetConfigCookie@CConnectIfcDataTLV@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setConnectMessageResult = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetConnectMessageResult>(
		"?SetConnectMessageResult@CConnectIfcDataTLV@@QAEJJ@Z");
	this->setConnectMessageType = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetConnectMessageType>(
		"?SetConnectMessageType@CConnectIfcDataTLV@@QAEJG@Z");
	this->setContentType = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetContentType>(
		"?SetContentType@CConnectIfcDataTLV@@QAEJG@Z");
	this->setCredentialsCount = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetCredentialsCount>(
		"?SetCredentialsCount@CConnectIfcDataTLV@@QAEJG@Z");
	this->setCSDEventFired = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetCSDEventFired>(
		"?SetCSDEventFired@CConnectIfcDataTLV@@QAEJH@Z");
	this->setCSDStartUrl = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetCSDStartUrl>(
		"?SetCSDStartUrl@CConnectIfcDataTLV@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setCSDStubUrl = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetCSDStubUrl>(
		"?SetCSDStubUrl@CConnectIfcDataTLV@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setCSDTicket = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetCSDTicket>(
		"?SetCSDTicket@CConnectIfcDataTLV@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setCSDToken = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetCSDToken>(
		"?SetCSDToken@CConnectIfcDataTLV@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setCSDTokenVerified = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetCSDTokenVerified>(
		"?SetCSDTokenVerified@CConnectIfcDataTLV@@QAEJH@Z");
	this->setDataBlobBuffer = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetDataBlobBuffer>(
		"?SetDataBlobBuffer@CConnectIfcDataTLV@@QAEJGPAE@Z");
	this->setDestFilePath = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetDestFilePath>(
		"?SetDestFilePath@CConnectIfcDataTLV@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setEnrollmentCAHref = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetEnrollmentCAHref>(
		"?SetEnrollmentCAHref@CConnectIfcDataTLV@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setGroupURLCookie = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetGroupURLCookie>(
		"?SetGroupURLCookie@CConnectIfcDataTLV@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setIKEAuthMethod = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetIKEAuthMethod>(
		"?SetIKEAuthMethod@CConnectIfcDataTLV@@QAEJW4USER_AUTH_METHOD@@@Z");
	this->setIKEIdentity = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetIKEIdentity>(
		"?SetIKEIdentity@CConnectIfcDataTLV@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setIsSBL = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetIsSBL>(
		"?SetIsSBL@CConnectIfcDataTLV@@QAEJ_N@Z");
	this->setLastConnectError = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetLastConnectError>(
		"?SetLastConnectError@CConnectIfcDataTLV@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setOpCode = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetOpCode>(
		"?SetOpCode@CConnectIfcDataTLV@@QAEJG@Z");
	this->setOrigPeerUrl = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetOrigPeerUrl>(
		"?SetOrigPeerUrl@CConnectIfcDataTLV@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setPeerPrimaryIPAddress = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetPeerPrimaryIPAddress>(
		"?SetPeerPrimaryIPAddress@CConnectIfcDataTLV@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setPeerSecondaryIPAddress = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetPeerSecondaryIPAddress>(
		"?SetPeerSecondaryIPAddress@CConnectIfcDataTLV@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setPeerUrl = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetPeerUrl>(
		"?SetPeerUrl@CConnectIfcDataTLV@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setPID = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetPID>(
		"?SetPID@CConnectIfcDataTLV@@QAEJK@Z");
	this->setProcessedCSDData = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetProcessedCSDData>(
		"?SetProcessedCSDData@CConnectIfcDataTLV@@QAEJH@Z");
	this->setProtocolType = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetProtocolType>(
		"?SetProtocolType@CConnectIfcDataTLV@@QAEJW4ConnectProtocolType@@@Z");
	this->setProtocolVersion = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetProtocolVersion>(
		"?SetProtocolVersion@CConnectIfcDataTLV@@QAEJW4ProtocolVersion@@@Z");
	this->setProxyEnAuthority = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetProxyEnAuthority>(
		"?SetProxyEnAuthority@CConnectIfcDataTLV@@QAEJGPAE@Z");
	this->setProxyEnPassword = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetProxyEnPassword>(
		"?SetProxyEnPassword@CConnectIfcDataTLV@@QAEJGPAE@Z");
	this->setProxyEnPrincipal = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetProxyEnPrincipal>(
		"?SetProxyEnPrincipal@CConnectIfcDataTLV@@QAEJGPAE@Z");
	this->setProxyHost = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetProxyHost>(
		"?SetProxyHost@CConnectIfcDataTLV@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setProxyMessage = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetProxyMessage>(
		"?SetProxyMessage@CConnectIfcDataTLV@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setProxyPort = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetProxyPort>(
		"?SetProxyPort@CConnectIfcDataTLV@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setProxyRealm = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetProxyRealm>(
		"?SetProxyRealm@CConnectIfcDataTLV@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setProxyString = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetProxyString>(
		"?SetProxyString@CConnectIfcDataTLV@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setProxyType = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetProxyType>(
		"?SetProxyType@CConnectIfcDataTLV@@QAEJG@Z");
	this->setResponseString = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetResponseString>(
		"?SetResponseString@CConnectIfcDataTLV@@QAEJABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	this->setResponseType = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetResponseType>(
		"?SetResponseType@CConnectIfcDataTLV@@QAEJG@Z");
	this->setServerCertThumbprint = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetServerCertThumbprint>(
		"?SetServerCertThumbprint@CConnectIfcDataTLV@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setSGFriendlyHostName = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetSGFriendlyHostName>(
		"?SetSGFriendlyHostName@CConnectIfcDataTLV@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setStrapPubKey = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetStrapPubKey>(
		"?SetStrapPubKey@CConnectIfcDataTLV@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@0@Z");
	this->setUsePeerPrimaryIPAddress = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetUsePeerPrimaryIPAddress>(
		"?SetUsePeerPrimaryIPAddress@CConnectIfcDataTLV@@QAEJ_N@Z");
	this->setVerifyCSDTokenOnly = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetVerifyCSDTokenOnly>(
		"?SetVerifyCSDTokenOnly@CConnectIfcDataTLV@@QAEJH@Z");
	this->setVpnTunnelScope = this->moduleWrapper->GetExport<CConnectIfcDataTLV_SetVpnTunnelScope>(
		"?SetVpnTunnelScope@CConnectIfcDataTLV@@QAEJW4VPN_TUNNEL_SCOPE@@@Z");
}

CConnectIfcDataTLV::~CConnectIfcDataTLV() {
}

BOOL CConnectIfcDataTLV::ConstructInstance() {
	LONG32 lErrorCode = 0;

	if (this->realInstance == NULL) {
		return FALSE;
	}

	this->constructor(this->realInstance, &lErrorCode, (PVOID)0xffffffff, NULL);

	return (lErrorCode == 0);
}

BOOL CConnectIfcDataTLV::PrepareInstance() {
	if (this->realInstance == NULL) {
		return FALSE;
	}

	if (this->addCredentialsName(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->addCredentialsValue(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setAggAuthFlag(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setAggAuthRequest(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setAuthCookie(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setCertMatchPattern(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setClientAuthCertNeeded(this->realInstance, paramBOOL) != 0) {
		return FALSE;
	}
	if (this->setClientCertStoreType(this->realInstance, paramUINT32) != 0) {
		return FALSE;
	}
	if (this->setClientCertThumbprint(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setConfigCookie(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setConnectMessageResult(this->realInstance, paramLONG32) != 0) {
		return FALSE;
	}
	if (this->setConnectMessageType(this->realInstance, paramUINT16) != 0) {
		return FALSE;
	}
	if (this->setContentType(this->realInstance, paramUINT16) != 0) {
		return FALSE;
	}
	if (this->setCredentialsCount(this->realInstance, paramUINT16) != 0) {
		return FALSE;
	}
	if (this->setCSDEventFired(this->realInstance, paramINT32) != 0) {
		return FALSE;
	}
	if (this->setCSDStartUrl(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setCSDStubUrl(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setCSDTicket(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setCSDToken(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setCSDTokenVerified(this->realInstance, paramINT32) != 0) {
		return FALSE;
	}
	if (this->setDataBlobBuffer(this->realInstance, ARRAYSIZE(paramUINT8Array), paramUINT8Array) != 0) {
		return FALSE;
	}
	if (this->setDestFilePath(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setEnrollmentCAHref(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setGroupURLCookie(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setIKEAuthMethod(this->realInstance, USER_AUTH_METHOD_TODO) != 0) {
		return FALSE;
	}
	if (this->setIKEIdentity(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setIsSBL(this->realInstance, paramBOOL) != 0) {
		return FALSE;
	}
	if (this->setLastConnectError(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setOpCode(this->realInstance, paramUINT16) != 0) {
		return FALSE;
	}
	if (this->setOrigPeerUrl(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setPeerPrimaryIPAddress(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setPeerSecondaryIPAddress(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setPeerUrl(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setPID(this->realInstance, paramULONG32) != 0) {
		return FALSE;
	}
	if (this->setProcessedCSDData(this->realInstance, paramINT32) != 0) {
		return FALSE;
	}
	if (this->setProtocolType(this->realInstance, CONNECT_PROTOCOL_TYPE_TODO) != 0) {
		return FALSE;
	}
	if (this->setProtocolVersion(this->realInstance, CONNECT_PROTOCOL_VERSION_TODO) != 0) {
		return FALSE;
	}
	if (this->setProxyEnAuthority(this->realInstance, ARRAYSIZE(paramUINT8Array), paramUINT8Array) != 0) {
		return FALSE;
	}
	if (this->setProxyEnPassword(this->realInstance, ARRAYSIZE(paramUINT8Array), paramUINT8Array) != 0) {
		return FALSE;
	}
	if (this->setProxyEnPrincipal(this->realInstance, ARRAYSIZE(paramUINT8Array), paramUINT8Array) != 0) {
		return FALSE;
	}
	if (this->setProxyHost(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setProxyMessage(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setProxyPort(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setProxyRealm(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setProxyString(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setProxyType(this->realInstance, paramUINT16) != 0) {
		return FALSE;
	}
	if (this->setResponseString(this->realInstance, &paramSTRING8) != 0) {
		return FALSE;
	}
	if (this->setResponseType(this->realInstance, paramUINT16) != 0) {
		return FALSE;
	}
	if (this->setServerCertThumbprint(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setSGFriendlyHostName(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setStrapPubKey(this->realInstance, &paramSTRING16, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setUsePeerPrimaryIPAddress(this->realInstance, paramBOOL) != 0) {
		return FALSE;
	}
	if (this->setVerifyCSDTokenOnly(this->realInstance, paramINT32) != 0) {
		return FALSE;
	}
	if (this->setVpnTunnelScope(this->realInstance, VPN_TUNNEL_SCOPE_1) != 0) {
		return FALSE;
	}

	return TRUE;
}

VOID CConnectIfcDataTLV::DestructInstance() {
	if (this->realInstance != NULL) {
		this->destructor(this->realInstance);
	}
}
