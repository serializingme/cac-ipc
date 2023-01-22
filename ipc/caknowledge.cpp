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
#include "caknowledge.h"

CAcknowledge::CAcknowledge(CModuleWrapper* moduleWrapper)
	: CIPCClassWrapper(moduleWrapper)
{
	this->constructor = this->moduleWrapper->GetExport<CAcknowledge_Constructor>(
		"??0CAcknowledge@@QAE@AAJW4IPC_MESSAGE_ID@@PAVIIpcResponseCB@@@Z");
	this->destructor = this->moduleWrapper->GetExport<CAcknowledge_Destructor>(
		"??1CAcknowledge@@UAE@XZ");
	this->setAckValue = this->moduleWrapper->GetExport<CAcknowledge_setAckValue>(
		"?setAckValue@CAcknowledge@@QAEJABH@Z");
	this->setSystemErrorValue = this->moduleWrapper->GetExport<CAcknowledge_setSystemErrorValue>(
		"?setSystemErrorValue@CAcknowledge@@QAEJABI@Z");
}

CAcknowledge::~CAcknowledge() {
}

BOOL CAcknowledge::ConstructInstance() {
	LONG32 lErrorCode = 0;

	if (this->realInstance == NULL) {
		return FALSE;
	}

	this->constructor(this->realInstance, &lErrorCode, 0x0c, (PVOID)0xffffffff);

	return (lErrorCode == 0);
}

BOOL CAcknowledge::PrepareInstance() {
	if (this->realInstance == NULL) {
		return FALSE;
	}

	if (this->setAckValue(this->realInstance, &paramINT32) != 0) {
		return FALSE;
	}
	if (this->setSystemErrorValue(this->realInstance, &paramUINT32) != 0) {
		return FALSE;
	}

	return TRUE;
}

VOID CAcknowledge::DestructInstance() {
	if (this->realInstance != NULL) {
		this->destructor(this->realInstance);
	}
}
