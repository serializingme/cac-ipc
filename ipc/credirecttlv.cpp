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
#include "credirecttlv.h"

CRedirectTlv::CRedirectTlv(CModuleWrapper* moduleWrapper)
	: CIPCClassWrapper(moduleWrapper)
{
	this->constructor = this->moduleWrapper->GetExport<CRedirectTlv_Constructor>(
		"??0CRedirectTlv@@QAE@AAJ@Z");
	this->destructor = this->moduleWrapper->GetExport<CRedirectTlv_Destructor>(
		"??1CIPCTLV@@UAE@XZ");
	this->setPrimaryIPAddress = this->moduleWrapper->GetExport<CRedirectTlv_SetPrimaryIPAddress>(
		"?SetPrimaryIPAddress@CRedirectTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setRedirectAddress = this->moduleWrapper->GetExport<CRedirectTlv_SetRedirectAddress>(
		"?SetRedirectAddress@CRedirectTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setSecondaryIPAddress = this->moduleWrapper->GetExport<CRedirectTlv_SetSecondaryIPAdddress>(
		"?SetSecondaryIPAddress@CRedirectTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
}

CRedirectTlv::~CRedirectTlv() {
}

BOOL CRedirectTlv::ConstructInstance() {
	LONG32 lErrorCode = 0;

	if (this->realInstance == NULL) {
		return FALSE;
	}

	this->constructor(this->realInstance, &lErrorCode);

	return (lErrorCode == 0);
}

BOOL CRedirectTlv::PrepareInstance() {
	if (this->realInstance == NULL) {
		return FALSE;
	}

	if (this->setPrimaryIPAddress(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setRedirectAddress(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setSecondaryIPAddress(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}

	return TRUE;
}

VOID CRedirectTlv::DestructInstance() {
	if (this->realInstance != NULL) {
		this->destructor(this->realInstance);
	}
}
