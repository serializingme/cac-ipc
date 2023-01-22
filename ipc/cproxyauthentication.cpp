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
#include "cproxyauthentication.h"

CProxyAuthentication::CProxyAuthentication(CModuleWrapper* moduleWrapper)
	: CIPCClassWrapper(moduleWrapper)
{
	this->constructor = this->moduleWrapper->GetExport<CProxyAuthentication_Constructor>(
		"??0CProxyAuthentication@@QAE@AAJPAVIIpcResponseCB@@@Z");
	this->destructor = this->moduleWrapper->GetExport<CProxyAuthentication_Destructor>(
		"??1CIPCTLV@@UAE@XZ");
	this->setEnAuthority = this->moduleWrapper->GetExport<CProxyAuthentication_SetEnAuthority>(
		"?SetEnAuthority@CProxyAuthentication@@QAEJQBEI@Z");
	this->setEnPassword = this->moduleWrapper->GetExport<CProxyAuthentication_SetEnPassword>(
		"?SetEnPassword@CProxyAuthentication@@QAEJQBEI@Z");
	this->setEnPrincipal = this->moduleWrapper->GetExport<CProxyAuthentication_SetEnPrincipal>(
		"?SetEnPrincipal@CProxyAuthentication@@QAEJQBEI@Z");
	this->setErrorMessage = this->moduleWrapper->GetExport<CProxyAuthentication_SetErrorMessage>(
		"?SetErrorMessage@CProxyAuthentication@@QAEJABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	this->setRealm = this->moduleWrapper->GetExport<CProxyAuthentication_SetRealm>(
		"?SetRealm@CProxyAuthentication@@QAEJABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	this->setScheme = this->moduleWrapper->GetExport<CProxyAuthentication_SetScheme>(
		"?SetScheme@CProxyAuthentication@@QAEJABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	this->setServerName = this->moduleWrapper->GetExport<CProxyAuthentication_SetServerName>(
		"?SetServerName@CProxyAuthentication@@QAEJABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	this->setSGDomainName = this->moduleWrapper->GetExport<CProxyAuthentication_SetSGDomainName>(
		"?SetSGDomainName@CProxyAuthentication@@QAEJABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
}

CProxyAuthentication::~CProxyAuthentication() {
}

BOOL CProxyAuthentication::ConstructInstance() {
	LONG32 lErrorCode = 0;

	if (this->realInstance == NULL) {
		return FALSE;
	}

	this->constructor(this->realInstance, &lErrorCode, (PVOID)0xffffffff);

	return (lErrorCode == 0);
}

BOOL CProxyAuthentication::PrepareInstance() {
	if (this->realInstance == NULL) {
		return FALSE;
	}

	if (this->setEnAuthority(this->realInstance, paramUINT8Array, ARRAYSIZE(paramUINT8Array)) != 0) {
		return FALSE;
	}
	if (this->setEnPassword(this->realInstance, paramUINT8Array, ARRAYSIZE(paramUINT8Array)) != 0) {
		return FALSE;
	}
	if (this->setEnPrincipal(this->realInstance, paramUINT8Array, ARRAYSIZE(paramUINT8Array)) != 0) {
		return FALSE;
	}
	if (this->setErrorMessage(this->realInstance, &paramSTRING8) != 0) {
		return FALSE;
	}
	if (this->setRealm(this->realInstance, &paramSTRING8) != 0) {
		return FALSE;
	}
	if (this->setScheme(this->realInstance, &paramSTRING8) != 0) {
		return FALSE;
	}
	if (this->setServerName(this->realInstance, &paramSTRING8) != 0) {
		return FALSE;
	}
	if (this->setSGDomainName(this->realInstance, &paramSTRING8) != 0) {
		return FALSE;
	}

	return TRUE;
}

VOID CProxyAuthentication::DestructInstance() {
	if (this->realInstance != NULL) {
		this->destructor(this->realInstance);
	}
}
