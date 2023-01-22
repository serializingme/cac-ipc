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
#include "clocallan.h"

CLocalLAN::CLocalLAN(CModuleWrapper* moduleWrapper)
	: CIPCClassWrapper(moduleWrapper)
{
	LONG32 lErrorCode = 0;

	this->constructor = this->moduleWrapper->GetExport<CLocalLAN_Constructor>(
		"??0CLocalLAN@@QAE@AAJPAVIIpcResponseCB@@@Z");
	this->destructor = this->moduleWrapper->GetExport<CLocalLAN_Destructor>(
		"??1CIPCTLV@@UAE@XZ");
	this->setLocalLANFlag = this->moduleWrapper->GetExport<CLocalLAN_SetLocalLANFlag>(
		"?SetLocalLANFlag@CLocalLAN@@QAEJ_N@Z");
}

CLocalLAN::~CLocalLAN() {
}

BOOL CLocalLAN::ConstructInstance() {
	LONG32 lErrorCode = 0;

	if (this->realInstance == NULL) {
		return FALSE;
	}

	this->constructor(this->realInstance, &lErrorCode, (PVOID)0xffffffff);

	return (lErrorCode == 0);
}

BOOL CLocalLAN::PrepareInstance() {
	if (this->realInstance == NULL) {
		return FALSE;
	}

	if (this->setLocalLANFlag(this->realInstance, paramBOOL) != 0) {
		return FALSE;
	}

	return TRUE;
}

VOID CLocalLAN::DestructInstance() {
	if (this->realInstance != NULL) {
		this->destructor(this->realInstance);
	}
}
