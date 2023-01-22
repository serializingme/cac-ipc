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
#include "cterminatetlv.h"

CTerminateTlv::CTerminateTlv(CModuleWrapper* moduleWrapper)
	: CIPCClassWrapper(moduleWrapper) {
	LONG32 lErrorCode = 0;

	this->constructor = this->moduleWrapper->GetExport<CTerminateTlv_Constructor>(
		"??0CTerminateTlv@@QAE@AAJ@Z");
	this->destructor = this->moduleWrapper->GetExport<CTerminateTlv_Destructor>(
		"??1CTerminateTlv@@UAE@XZ");
	this->setDelayLimit = this->moduleWrapper->GetExport<CTerminateTlv_SetDelayLimit>(
		"?SetDelayLimit@CTerminateTlv@@QAEJK@Z");
	this->setReasonCode = this->moduleWrapper->GetExport<CTerminateTlv_SetReasonCode>(
		"?SetReasonCode@CTerminateTlv@@QAEJW4REASON_CODE@1@@Z");
}

CTerminateTlv::~CTerminateTlv() {
}

BOOL CTerminateTlv::ConstructInstance() {
	LONG32 lErrorCode = 0;

	if (this->realInstance == NULL) {
		return FALSE;
	}

	this->constructor(this->realInstance, &lErrorCode);

	return (lErrorCode == 0);
}

BOOL CTerminateTlv::PrepareInstance() {
	if (this->realInstance == NULL) {
		return FALSE;
	}
	
	if (this->setDelayLimit(this->realInstance, paramULONG32) != 0) {
		return FALSE;
	}
	if (this->setReasonCode(this->realInstance, REASON_CODE_TODO) != 0) {
		return FALSE;
	}

	return TRUE;
}

VOID CTerminateTlv::DestructInstance() {
	if (this->realInstance != NULL) {
		this->destructor(this->realInstance);
	}
}
