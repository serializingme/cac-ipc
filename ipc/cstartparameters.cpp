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
#include "cstartparameters.h"

CStartParameters::CStartParameters(CModuleWrapper* moduleWrapper)
	: CIPCClassWrapper(moduleWrapper)
{
	this->constructor = this->moduleWrapper->GetExport<CStartParameters_Constructor>(
		"??0CStartParameters@@QAE@AAJPAVIIpcResponseCB@@@Z");
	this->destructor = this->moduleWrapper->GetExport<CStartParameters_Destructor>(
		"??1CIPCTLV@@UAE@XZ");
	this->setAggAuthCertificateInfo = this->moduleWrapper->GetExport<CStartParameters_SetAggAuthCertificateInfo>(
		"?SetAggAuthCertificateInfo@CStartParameters@@QAEJABVCCertificateInfoTlv@@@Z");
	this->setAuthMethod = this->moduleWrapper->GetExport<CStartParameters_SetAuthMethod>(
		"?SetAuthMethod@CStartParameters@@QAEJW4USER_AUTH_METHOD@@@Z");
	this->setCertificateInfo = this->moduleWrapper->GetExport<CStartParameters_SetCertificateInfo>(
		"?SetCertificateInfo@CStartParameters@@QAEJABVCCertificateInfoTlv@@@Z");
	this->setCfgClientCertTp = this->moduleWrapper->GetExport<CStartParameters_SetCfgClientCertTp>(
		"?SetCfgClientCertTp@CStartParameters@@QAEJPBD@Z");
	this->setCfgModules = this->moduleWrapper->GetExport<CStartParameters_SetCfgModules>(
		"?SetCfgModules@CStartParameters@@QAEJPBD@Z");
	this->setCfgProtocol = this->moduleWrapper->GetExport<CStartParameters_SetCfgProtocol>(
		"?SetCfgProtocol@CStartParameters@@QAEJPBD@Z");
	this->setCfgServerCertTp = this->moduleWrapper->GetExport<CStartParameters_SetCfgServerCertTp>(
		"?SetCfgServerCertTp@CStartParameters@@QAEJPBD@Z");
	this->setDetermineProxy = this->moduleWrapper->GetExport<CStartParameters_SetDetermineProxy>(
		"?SetDetermineProxy@CStartParameters@@QAEJ_N@Z");
	this->setGUICmdLine = this->moduleWrapper->GetExport<CStartParameters_SetGUICmdLine>(
		"?SetGUICmdLine@CStartParameters@@QAEJPB_W@Z");
	this->setGUIDesktop = this->moduleWrapper->GetExport<CStartParameters_SetGUIDesktop>(
		"?SetGUIDesktop@CStartParameters@@QAEJPBD@Z");
	this->setGUIEnv = this->moduleWrapper->GetExport<CStartParameters_SetGUIEnv>(
		"?SetGUIEnv@CStartParameters@@QAEJPB_W@Z");
	this->setGUIFilePath = this->moduleWrapper->GetExport<CStartParameters_SetGUIFilePath>(
		"?SetGUIFilePath@CStartParameters@@QAEJPB_W@Z");
	this->setIkeIdentity = this->moduleWrapper->GetExport<CStartParameters_SetIkeIdentity>(
		"?SetIkeIdentity@CStartParameters@@QAEJABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	this->setInitiatorPID = this->moduleWrapper->GetExport<CStartParameters_SetInitiatorPID>(
		"?SetInitiatorPID@CStartParameters@@QAEJABK@Z");
	this->setInvokedByCode = this->moduleWrapper->GetExport<CStartParameters_SetInvokedByCode>(
		"?SetInvokedByCode@CStartParameters@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setPrimarySGIPAddr = this->moduleWrapper->GetExport<CStartParameters_SetPrimarySGIPAddr>(
		"?SetPrimarySGIPAddr@CStartParameters@@QAEJPBD@Z");
	this->setProfileName = this->moduleWrapper->GetExport<CStartParameters_SetProfileName>(
		"?SetProfileName@CStartParameters@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setProxyAuthority = this->moduleWrapper->GetExport<CStartParameters_SetProxyAuthority>(
		"?SetProxyAuthority@CStartParameters@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setProxyEnAuthority = this->moduleWrapper->GetExport<CStartParameters_SetProxyEnAuthority>(
		"?SetProxyEnAuthority@CStartParameters@@QAEJGPBE@Z");
	this->setProxyEnPswd = this->moduleWrapper->GetExport<CStartParameters_SetProxyEnPswd>(
		"?SetProxyEnPswd@CStartParameters@@QAEJGPBE@Z");
	this->setProxyEnUser = this->moduleWrapper->GetExport<CStartParameters_SetProxyEnUser>(
		"?SetProxyEnUser@CStartParameters@@QAEJGPBE@Z");
	this->setProxyHost = this->moduleWrapper->GetExport<CStartParameters_SetProxyHost>(
		"?SetProxyHost@CStartParameters@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setProxyMessage = this->moduleWrapper->GetExport<CStartParameters_SetProxyMessage>(
		"?SetProxyMessage@CStartParameters@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setProxyPort = this->moduleWrapper->GetExport<CStartParameters_SetProxyPort>(
		"?SetProxyPort@CStartParameters@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setProxyPswd = this->moduleWrapper->GetExport<CStartParameters_SetProxyPswd>(
		"?SetProxyPswd@CStartParameters@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setProxyRealm = this->moduleWrapper->GetExport<CStartParameters_SetProxyRealm>(
		"?SetProxyRealm@CStartParameters@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setProxyString = this->moduleWrapper->GetExport<CStartParameters_SetProxyString>(
		"?SetProxyString@CStartParameters@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setProxyType = this->moduleWrapper->GetExport<CStartParameters_SetProxyType>(
		"?SetProxyType@CStartParameters@@QAEJABG@Z");
	this->setProxyUser = this->moduleWrapper->GetExport<CStartParameters_SetProxyUser>(
		"?SetProxyUser@CStartParameters@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setSecondarySGIPAddr = this->moduleWrapper->GetExport<CStartParameters_SetSecondarySGIPAddr>(
		"?SetSecondarySGIPAddr@CStartParameters@@QAEJPBD@Z");
	this->setSGCookie = this->moduleWrapper->GetExport<CStartParameters_SetSGCookie>(
		"?SetSGCookie@CStartParameters@@QAEJPBD@Z");
	this->setSGFriendlyHostName = this->moduleWrapper->GetExport<CStartParameters_SetSGFriendlyHostName>(
		"?SetSGFriendlyHostName@CStartParameters@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setSGURL = this->moduleWrapper->GetExport<CStartParameters_SetSGURL>(
		"?SetSGURL@CStartParameters@@QAEJPBD@Z");
	this->setUsingSmartcard = this->moduleWrapper->GetExport<CStartParameters_SetUsingSmartcard>(
		"?SetUsingSmartcard@CStartParameters@@QAEJ_N@Z");
	this->setVpnType = this->moduleWrapper->GetExport<CStartParameters_SetVpnType>(
		"?SetVpnType@CStartParameters@@QAEJW4ConnectProtocolType@@@Z");
	this->setWaitForGUI = this->moduleWrapper->GetExport<CStartParameters_SetWaitForGUI>(
		"?SetWaitForGUI@CStartParameters@@QAEJ_N@Z");
}

CStartParameters::~CStartParameters() {
}

BOOL CStartParameters::ConstructInstance() {
	LONG32 lErrorCode = 0;

	if (this->realInstance == NULL) {
		return FALSE;
	}

	this->constructor(this->realInstance, &lErrorCode, (PVOID)0xffffffff);

	return (lErrorCode == 0);
}

BOOL CStartParameters::PrepareInstance() {
	if (this->realInstance == NULL) {
		return FALSE;
	}

	CCertificateInfoTlv* certificateInfoParam = new CCertificateInfoTlv(this->moduleWrapper);

	if (certificateInfoParam->ConstructInstance() == FALSE || certificateInfoParam->PrepareInstance() == FALSE) {
		return FALSE;
	}

	if (this->setAggAuthCertificateInfo(this->realInstance, certificateInfoParam->GetInstance()) != 0) {
		return FALSE;
	}
	if (this->setCertificateInfo(this->realInstance, certificateInfoParam->GetInstance()) != 0) {
		return FALSE;
	}

	certificateInfoParam->DestructInstance();
	delete certificateInfoParam;

	if (this->setAuthMethod(this->realInstance, USER_AUTH_METHOD_TODO) != 0) {
		return FALSE;
	}
	if (this->setCfgClientCertTp(this->realInstance, paramSTRING8.value.pointer) != 0) {
		return FALSE;
	}
	if (this->setCfgModules(this->realInstance, paramSTRING8.value.pointer) != 0) {
		return FALSE;
	}
	if (this->setCfgProtocol(this->realInstance, paramSTRING8.value.pointer) != 0) {
		return FALSE;
	}
	if (this->setCfgServerCertTp(this->realInstance, paramSTRING8.value.pointer) != 0) {
		return FALSE;
	}
	if (this->setDetermineProxy(this->realInstance, paramBOOL) != 0) {
		return FALSE;
	}
	if (this->setGUICmdLine(this->realInstance, paramSTRING16.value.pointer) != 0) {
		return FALSE;
	}
	if (this->setGUIDesktop(this->realInstance, paramSTRING8.value.pointer) != 0) {
		return FALSE;
	}
	if (this->setGUIEnv(this->realInstance, paramSTRING16.value.pointer) != 0) {
		return FALSE;
	}
	if (this->setGUIFilePath(this->realInstance, paramSTRING16.value.pointer) != 0) {
		return FALSE;
	}
	if (this->setIkeIdentity(this->realInstance, &paramSTRING8) != 0) {
		return FALSE;
	}
	if (this->setInitiatorPID(this->realInstance, &paramULONG32) != 0) {
		return FALSE;
	}
	if (this->setInvokedByCode(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setPrimarySGIPAddr(this->realInstance, paramSTRING8.value.pointer) != 0) {
		return FALSE;
	}
	if (this->setProfileName(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setProxyAuthority(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setProxyEnAuthority(this->realInstance, ARRAYSIZE(paramUINT8Array), paramUINT8Array) != 0) {
		return FALSE;
	}
	if (this->setProxyEnPswd(this->realInstance, ARRAYSIZE(paramUINT8Array), paramUINT8Array) != 0) {
		return FALSE;
	}
	if (this->setProxyEnUser(this->realInstance, ARRAYSIZE(paramUINT8Array), paramUINT8Array) != 0) {
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
	if (this->setProxyPswd(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setProxyRealm(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setProxyString(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setProxyType(this->realInstance, &paramUINT16) != 0) {
		return FALSE;
	}
	if (this->setProxyUser(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setSecondarySGIPAddr(this->realInstance, paramSTRING8.value.pointer) != 0) {
		return FALSE;
	}
	if (this->setSGCookie(this->realInstance, paramSTRING8.value.pointer) != 0) {
		return FALSE;
	}
	if (this->setSGFriendlyHostName(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setSGURL(this->realInstance, paramSTRING8.value.pointer) != 0) {
		return FALSE;
	}
	if (this->setUsingSmartcard(this->realInstance, paramBOOL) != 0) {
		return FALSE;
	}
	if (this->setVpnType(this->realInstance, CONNECT_PROTOCOL_TYPE_TODO) != 0) {
		return FALSE;
	}
	if (this->setWaitForGUI(this->realInstance, paramBOOL) != 0) {
		return FALSE;
	}
	
	return TRUE;
}

VOID CStartParameters::DestructInstance() {
	if (this->realInstance != NULL) {
		this->destructor(this->realInstance);
	}
}
