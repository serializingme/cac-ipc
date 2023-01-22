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
#include "cmessagetypebitmaptlv.h"

CMessageTypeBitmapTlv::CMessageTypeBitmapTlv(CModuleWrapper* moduleWrapper)
	: CIPCClassWrapper(moduleWrapper)
{
	this->constructor = this->moduleWrapper->GetExport<CMessageTypeBitmapTlv_Constructor>(
		"??0CMessageTypeBitmapTlv@@QAE@AAJABI@Z");
	this->destructor = this->moduleWrapper->GetExport<CMessageTypeBitmapTlv_Destructor>(
		"??1CIPCTLV@@UAE@XZ");
	this->setActiveClientPolicy = this->moduleWrapper->GetExport<CMessageTypeBitmapTlv_SetActiveClientPolicy>(
		"?SetActiveClientPolicy@CMessageTypeBitmapTlv@@QAEJI@Z");
	this->setApplicationName = this->moduleWrapper->GetExport<CMessageTypeBitmapTlv_setApplicationName>(
		"?setApplicationName@CMessageTypeBitmapTlv@@QAEJABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	this->setAppOperationMode = this->moduleWrapper->GetExport<CMessageTypeBitmapTlv_SetAppOperationMode>(
		"?SetAppOperatingMode@CMessageTypeBitmapTlv@@QAEJI@Z");
	this->setNotificationMode = this->moduleWrapper->GetExport<CMessageTypeBitmapTlv_SetNotificationMode>(
		"?SetNotificationFlag@CMessageTypeBitmapTlv@@QAEJ_N@Z");
	this->setNumSameAppRegstration = this->moduleWrapper->GetExport<CMessageTypeBitmapTlv_SetNumSameAppRegistration>(
		"?SetNumSameAppRegistration@CMessageTypeBitmapTlv@@QAEJI@Z");
	this->setPID = this->moduleWrapper->GetExport<CMessageTypeBitmapTlv_SetPID>(
		"?SetPID@CMessageTypeBitmapTlv@@QAEJABK@Z");
}

CMessageTypeBitmapTlv::~CMessageTypeBitmapTlv() {
}

BOOL CMessageTypeBitmapTlv::ConstructInstance() {
	LONG32 lErrorCode = 0;

	if (this->realInstance == NULL) {
		return FALSE;
	}

	this->constructor(this->realInstance, &lErrorCode, &paramUINT32);

	return (lErrorCode == 0);
}

BOOL CMessageTypeBitmapTlv::PrepareInstance() {
	if (this->realInstance == NULL) {
		return FALSE;
	}
	
	if (this->setActiveClientPolicy(this->realInstance, paramUINT32) != 0) {
		return FALSE;
	}
	if (this->setApplicationName(this->realInstance, &paramSTRING8) != 0) {
		return FALSE;
	}
	if (this->setAppOperationMode(this->realInstance, paramUINT32) != 0) {
		return FALSE;
	}
	if (this->setNotificationMode(this->realInstance, paramBOOL) != 0) {
		return FALSE;
	}
	if (this->setNumSameAppRegstration(this->realInstance, paramUINT32) != 0) {
		return FALSE;
	}
	if (this->setPID(this->realInstance, &paramULONG32) != 0) {
		return FALSE;
	}

	return TRUE;
}

VOID CMessageTypeBitmapTlv::DestructInstance() {
	if (this->realInstance != NULL) {
		this->destructor(this->realInstance);
	}
}
