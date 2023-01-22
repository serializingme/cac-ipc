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
#include "ccertificateauthtlv.h"

CCertificateAuthTlv::CCertificateAuthTlv(CModuleWrapper* moduleWrapper)
	: CIPCClassWrapper(moduleWrapper)
{
	this->constructor = this->moduleWrapper->GetExport<CCertificateAuthTlv_Constructor>(
		"??0CCertificateAuthTlv@@QAE@AAJPAVIIpcResponseCB@@@Z");
	this->destructor = this->moduleWrapper->GetExport<CCertificateAuthTlv_Destructor>(
		"??1CIPCTLV@@UAE@XZ");
	this->setClientCertThumbprint = this->moduleWrapper->GetExport<CCertificateAuthTlv_SetClientCertThumbprint>(
		"?SetClientCertThumbprint@CCertificateAuthTlv@@QAEJPBD@Z");
	this->setEnPassword = this->moduleWrapper->GetExport<CCertificateAuthTlv_SetEnPassword>(
		"?SetEnPassword@CCertificateAuthTlv@@QAEJQBEI@Z");
	this->setServerCertThumbprint = this->moduleWrapper->GetExport<CCertificateAuthTlv_SetServerCertThumbprint>(
		"?SetServerCertThumbprint@CCertificateAuthTlv@@QAEJPBD@Z");
}

CCertificateAuthTlv::~CCertificateAuthTlv() {
}

BOOL CCertificateAuthTlv::ConstructInstance() {
	LONG32 lErrorCode = 0;

	if (this->realInstance == NULL) {
		return FALSE;
	}

	this->constructor(this->realInstance, &lErrorCode, (PVOID)0xffffffff);

	return (lErrorCode == 0);
}

BOOL CCertificateAuthTlv::PrepareInstance() {
	if (this->realInstance == NULL) {
		return FALSE;
	}

	if (this->setClientCertThumbprint(this->realInstance, paramSTRING8.value.pointer) != 0) {
		return FALSE;
	}
	if (this->setEnPassword(this->realInstance, paramUINT8Array, ARRAYSIZE(paramUINT8Array)) != 0) {
		return FALSE;
	}
	if (this->setServerCertThumbprint(this->realInstance, paramSTRING8.value.pointer) != 0) {
		return FALSE;
	}

	return TRUE;
}

VOID CCertificateAuthTlv::DestructInstance() {
	if (this->realInstance != NULL) {
		this->destructor(this->realInstance);
	}
}
