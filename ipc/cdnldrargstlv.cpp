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
#include "ccertificateinfotlv.h"
#include "cdnldrargstlv.h"

CDnldrArgsTlv::CDnldrArgsTlv(CModuleWrapper* moduleWrapper)
 : CIPCClassWrapper(moduleWrapper)
{
	this->constructor = this->moduleWrapper->GetExport<CDnldrArgsTlv_Constructor>(
		"??0CDnldrArgsTlv@@QAE@AAJ@Z");
	this->destructor = this->moduleWrapper->GetExport<CDnldrArgsTlv_Destructor>(
		"??1CIPCTLV@@UAE@XZ");
	this->setUsingSmartCard = this->moduleWrapper->GetExport<CDnldrArgsTlv_SetUsingSmartCard>(
		"?SetUsingSmartcard@CDnldrArgsTlv@@QAEJ_N@Z");
	this->setTunnelState = this->moduleWrapper->GetExport<CDnldrArgsTlv_SetTunnelState>(
		"?SetTunnelState@CDnldrArgsTlv@@QAEJW4STATE@@@Z");
	this->setSGFriendlyHostName = this->moduleWrapper->GetExport<CDnldrArgsTlv_SetSGFriendlyHostName>(
		"?SetSGFriendlyHostName@CDnldrArgsTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setSessionToken = this->moduleWrapper->GetExport<CDnldrArgsTlv_SetSessionToken>(
		"?SetSessionToken@CDnldrArgsTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setSessionID = this->moduleWrapper->GetExport<CDnldrArgsTlv_SetSessionID>(
		"?SetSessionID@CDnldrArgsTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setServerCertHash = this->moduleWrapper->GetExport<CDnldrArgsTlv_SetServerCertHash>(
		"?SetServerCertHash@CDnldrArgsTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setProxyUser = this->moduleWrapper->GetExport<CDnldrArgsTlv_SetProxyUser>(
		"?SetProxyUser@CDnldrArgsTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setPoxyType = this->moduleWrapper->GetExport<CDnldrArgsTlv_SetPoxyType>(
		"?SetProxyType@CDnldrArgsTlv@@QAEJABG@Z");
	this->setProxyString = this->moduleWrapper->GetExport<CDnldrArgsTlv_SetProxyString>(
		"?SetProxyString@CDnldrArgsTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setProxyRealm = this->moduleWrapper->GetExport<CDnldrArgsTlv_SetProxyReam>(
		"?SetProxyRealm@CDnldrArgsTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setProxyPort = this->moduleWrapper->GetExport<CDnldrArgsTlv_SetProxyPort>(
		"?SetProxyPort@CDnldrArgsTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setProxyPassword = this->moduleWrapper->GetExport<CDnldrArgsTlv_SetProxyPassword>(
		"?SetProxyPassword@CDnldrArgsTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setProxyMessage = this->moduleWrapper->GetExport<CDnldrArgsTlv_SetProxyMessage>(
		"?SetProxyMessage@CDnldrArgsTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setProxyHost = this->moduleWrapper->GetExport<CDnldrArgsTlv_SetProxyHost>(
		"?SetProxyHost@CDnldrArgsTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setProxyAuthority = this->moduleWrapper->GetExport<CDnldrArgsTlv_SetProxyAuthority>(
		"?SetProxyAuthority@CDnldrArgsTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setProfileURI = this->moduleWrapper->GetExport<CDnldrArgsTlv_SetProfileURI>(
		"?SetProfileURI@CDnldrArgsTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setProfileHash = this->moduleWrapper->GetExport<CDnldrArgsTlv_SetProfileHash>(
		"?SetProfileHash@CDnldrArgsTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setOptionalModules = this->moduleWrapper->GetExport<CDnldrArgsTlv_SetOptionalModules>(
		"?SetOptionalModules@CDnldrArgsTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setOperationMode = this->moduleWrapper->GetExport<CDnldrArgsTlv_SetOperationMode>(
		"?SetOperatingMode@CDnldrArgsTlv@@QAEJW4DnldrOperatingMode@@@Z");
	this->setL10NURI = this->moduleWrapper->GetExport<CDnldrArgsTlv_SetL10NURI>(
		"?SetL10nURI@CDnldrArgsTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setGatewayURL = this->moduleWrapper->GetExport<CDnldrArgsTlv_SetGatewayURL>(
		"?SetGatewayURL@CDnldrArgsTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setGatewaySecondaryIPAddress = this->moduleWrapper->GetExport<CDnldrArgsTlv_SetGatewaySecodaryIPAddress>(
		"?SetGatewaySecondaryIPAddress@CDnldrArgsTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setGatewayPrimaryIPAddress = this->moduleWrapper->GetExport<CDnldrArgsTlv_SetGatewayPrimaryIPAddress>(
		"?SetGatewayPrimaryIPAddress@CDnldrArgsTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setDetermineProxy = this->moduleWrapper->GetExport<CDnldrArgsTlv_SetDetermneProxy>(
		"?SetDetermineProxy@CDnldrArgsTlv@@QAEJAB_N@Z");
	this->setConnectionType = this->moduleWrapper->GetExport<CDnldrArgsTlv_SetConnectionType>(
		"?SetConnectionType@CDnldrArgsTlv@@QAEJW4ConnectProtocolType@@@Z");
	this->setConfigXml = this->moduleWrapper->GetExport<CDnldrArgsTlv_SetConfigXml>(
		"?SetConfigXml@CDnldrArgsTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setClientCertHash = this->moduleWrapper->GetExport<CDnldrArgsTlv_SetClientCertHash>(
		"?SetClientCertHash@CDnldrArgsTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setCfgCookie = this->moduleWrapper->GetExport<CDnldrArgsTlv_SetCfgCookie>(
		"?SetCfgCookie@CDnldrArgsTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setCertificateInfo = this->moduleWrapper->GetExport<CDnldrArgsTlv_SetCertificateInfo>(
		"?SetCertificateInfo@CDnldrArgsTlv@@QAEJABVCCertificateInfoTlv@@@Z");
	this->setBaseURI = this->moduleWrapper->GetExport<CDnldrArgsTlv_SetBaseURI>(
		"?SetBaseURI@CDnldrArgsTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setAggAuthCertficateInfo = this->moduleWrapper->GetExport<CDnldrArgsTlv_SetAggAuthCertficateInfo>(
		"?SetAggAuthCertificateInfo@CDnldrArgsTlv@@QAEJABVCCertificateInfoTlv@@@Z");
}

CDnldrArgsTlv::~CDnldrArgsTlv() {
}

BOOL CDnldrArgsTlv::ConstructInstance() {
	LONG32 lErrorCode = 0;

	if (this->realInstance == NULL) {
		return FALSE;
	}

	this->constructor(this->realInstance, &lErrorCode);

	return (lErrorCode == 0);
}

BOOL CDnldrArgsTlv::PrepareInstance() {
	if (this->realInstance == NULL) {
		return FALSE;
	}

	CCertificateInfoTlv* certificateInfoParam = new CCertificateInfoTlv(this->moduleWrapper);

	if (certificateInfoParam->ConstructInstance() == FALSE || certificateInfoParam->PrepareInstance() == FALSE) {
		return FALSE;
	}
	
	if (this->setAggAuthCertficateInfo(this->realInstance, certificateInfoParam->GetInstance()) != 0) {
		return FALSE;
	}
	if (this->setCertificateInfo(this->realInstance, certificateInfoParam->GetInstance()) != 0) {
		return FALSE;
	}

	certificateInfoParam->DestructInstance();
	delete certificateInfoParam;

	if (this->setBaseURI(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setCfgCookie(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setClientCertHash(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setConfigXml(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setConnectionType(this->realInstance, CONNECT_PROTOCOL_TYPE_TODO) != 0) {
		return FALSE;
	}
	if (this->setDetermineProxy(this->realInstance, &paramBOOL) != 0) {
		return FALSE;
	}
	if (this->setGatewayPrimaryIPAddress(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setGatewaySecondaryIPAddress(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setGatewayURL(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setL10NURI(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setOperationMode(this->realInstance, DNLDR_OPERATING_MODE_TODO) != 0) {
		return FALSE;
	}
	if (this->setOptionalModules(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setPoxyType(this->realInstance, &paramUINT16) != 0) {
		return FALSE;
	}
	if (this->setProfileURI(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setProfileHash(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setProxyAuthority(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setProxyHost(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setProxyMessage(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setProxyPassword(this->realInstance, &paramSTRING16) != 0) {
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
	if (this->setProxyUser(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setServerCertHash(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setSessionID(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setSessionToken(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setSGFriendlyHostName(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setTunnelState(this->realInstance, VPN_TUNNEL_STATE_TODO) != 0) {
		return FALSE;
	}
	if (this->setUsingSmartCard(this->realInstance, paramBOOL) != 0) {
		return FALSE;
	}

	return TRUE;
}

VOID CDnldrArgsTlv::DestructInstance() {
	if (this->realInstance != NULL) {
		this->destructor(this->realInstance);
	}
}
