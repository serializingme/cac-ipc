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
#include "claunchclienttapptlv.h"

CLaunchClientAppTlv::CLaunchClientAppTlv(CModuleWrapper* moduleWrapper)
	: CIPCClassWrapper(moduleWrapper)
{
	this->constructor = this->moduleWrapper->GetExport<CLaunchClientAppTlv_Constructor>(
		"??0CLaunchClientAppTlv@@QAE@AAJPAVIIpcResponseCB@@@Z");
	this->destructor = this->moduleWrapper->GetExport<CLaunchClientAppTlv_Destructor>(
		"??1CIPCTLV@@UAE@XZ");
	this->setCmdLine = this->moduleWrapper->GetExport<CLaunchClientAppTlv_SetCmdLine>(
		"?SetCmdLine@CLaunchClientAppTlv@@QAEJPBD@Z");
	this->setFilePath = this->moduleWrapper->GetExport<CLaunchClientAppTlv_SetFilePath>(
		"?SetFilePath@CLaunchClientAppTlv@@QAEJPBD@Z");
	this->setGUIDesktop = this->moduleWrapper->GetExport<CLaunchClientAppTlv_SetGUIDesktop>(
		"?SetGUIDesktop@CLaunchClientAppTlv@@QAEJPBD@Z");
	this->setRelocatableFilePath = this->moduleWrapper->GetExport<CLaunchClientAppTlv_SetRelocatableFilePath>(
		"?SetRelocatableFilePath@CLaunchClientAppTlv@@QAEJPBD@Z");
	this->setUseInstalled = this->moduleWrapper->GetExport<CLaunchClientAppTlv_SetUseInstalled>(
		"?SetUseInstalled@CLaunchClientAppTlv@@QAEJ_N@Z");
}

CLaunchClientAppTlv::~CLaunchClientAppTlv() {
}

BOOL CLaunchClientAppTlv::ConstructInstance() {
	LONG32 lErrorCode = 0;

	if (this->realInstance == NULL) {
		return FALSE;
	}

	this->constructor(this->realInstance, &lErrorCode, (PVOID)0xffffffff);

	return (lErrorCode == 0);
}

BOOL CLaunchClientAppTlv::PrepareInstance() {
	if (this->realInstance == NULL) {
		return FALSE;
	}

	if (this->setCmdLine(this->realInstance, paramSTRING8.value.pointer) != 0) {
		return FALSE;
	}
	if (this->setFilePath(this->realInstance, paramSTRING8.value.pointer) != 0) {
		return FALSE;
	}
	if (this->setGUIDesktop(this->realInstance, paramSTRING8.value.pointer) != 0) {
		return FALSE;
	}
	if (this->setRelocatableFilePath(this->realInstance, paramSTRING8.value.pointer) != 0) {
		return FALSE;
	}
	if (this->setUseInstalled(this->realInstance, paramBOOL) != 0) {
		return FALSE;
	}

	return TRUE;
}

VOID CLaunchClientAppTlv::DestructInstance() {
	if (this->realInstance != NULL) {
		this->destructor(this->realInstance);
	}
}
