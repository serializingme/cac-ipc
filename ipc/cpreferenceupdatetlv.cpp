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
#include "cpreferenceupdatetlv.h"

CPreferenceUpdateTlv::CPreferenceUpdateTlv(CModuleWrapper* moduleWrapper)
	: CIPCClassWrapper(moduleWrapper)
{
	this->constructor = this->moduleWrapper->GetExport<CPreferenceUpdateTlv_Constructor>(
		"??0CPreferenceUpdateTlv@@QAE@AAJPAVIIpcResponseCB@@@Z");
	this->destructor = this->moduleWrapper->GetExport<CPreferenceUpdateTlv_Destructor>(
		"??1CIPCTLV@@UAE@XZ");
	this->addAutoPreferenceSetting = this->moduleWrapper->GetExport<CPreferenceUpdateTlv_addAutoPreferenceSetting>(
		"?addAutoPreferenceSetting@CPreferenceUpdateTlv@@QAEJW4AutoPreferenceId@@ABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->addPreferenceSetting = this->moduleWrapper->GetExport<CPreferenceUpdateTlv_addPreferenceSetting>(
		"?addPreferenceSetting@CPreferenceUpdateTlv@@QAEJW4PreferenceId@@ABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setAutoPreferenceCount = this->moduleWrapper->GetExport<CPreferenceUpdateTlv_setAutoPreferenceCount>(
		"?setAutoPreferenceCount@CPreferenceUpdateTlv@@QAEJI@Z");
	this->setPreferenceCount = this->moduleWrapper->GetExport<CPreferenceUpdateTlv_setPreferenceCount>(
		"?setPreferenceCount@CPreferenceUpdateTlv@@QAEJI@Z");
	this->setProfileName = this->moduleWrapper->GetExport<CPreferenceUpdateTlv_SetProfileName>(
		"?SetProfileName@CPreferenceUpdateTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
}

CPreferenceUpdateTlv::~CPreferenceUpdateTlv() {
}

BOOL CPreferenceUpdateTlv::ConstructInstance() {
	LONG32 lErrorCode = 0;

	if (this->realInstance == NULL) {
		return FALSE;
	}

	this->constructor(this->realInstance, &lErrorCode, (PVOID)0xffffffff);

	return (lErrorCode == 0);
}

BOOL CPreferenceUpdateTlv::PrepareInstance() {
	if (this->realInstance == NULL) {
		return FALSE;
	}

	if (this->addAutoPreferenceSetting(this->realInstance, AUTO_PREFERENCE_ID_TODO, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->addPreferenceSetting(this->realInstance, PREFERENCE_ID_TODO, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setAutoPreferenceCount(this->realInstance, paramUINT32) != 0) {
		return FALSE;
	}
	if (this->setPreferenceCount(this->realInstance, paramUINT32) != 0) {
		return FALSE;
	}
	if (this->setProfileName(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	
	return TRUE;
}

VOID CPreferenceUpdateTlv::DestructInstance() {
	if (this->realInstance != NULL) {
		this->destructor(this->realInstance);
	}
}
