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
#include "cconnectfailuretlv.h"

CConnectFailureTlv::CConnectFailureTlv(CModuleWrapper* moduleWrapper)
	: CIPCClassWrapper(moduleWrapper)
{
	this->constructor = this->moduleWrapper->GetExport<CConnectFailureTlv_Constructor>(
		"??0CConnectFailureTlv@@QAE@AAJ@Z");
	this->destructor = this->moduleWrapper->GetExport<CConnectFailureTlv_Destructor>(
		"??1CIPCTLV@@UAE@XZ");
	this->setFailureReason = this->moduleWrapper->GetExport<CConnectFailureTlv_SetFailureReason>(
		"?SetFailureReason@CConnectFailureTlv@@QAEJW4CONNECT_FAILURE_REASON@@@Z");
}

CConnectFailureTlv::~CConnectFailureTlv() {
}

BOOL CConnectFailureTlv::ConstructInstance() {
	LONG32 lErrorCode = 0;

	if (this->realInstance == NULL) {
		return FALSE;
	}

	this->constructor(this->realInstance, &lErrorCode);

	return (lErrorCode == 0);
}

BOOL CConnectFailureTlv::PrepareInstance() {
	if (this->realInstance == NULL) {
		return FALSE;
	}

	if (this->setFailureReason(this->realInstance, CONNECT_FAILURE_REASON_TODO) != 0) {
		return FALSE;
	}

	return TRUE;
}

VOID CConnectFailureTlv::DestructInstance() {
	if (this->realInstance != NULL) {
		this->destructor(this->realInstance);
	}
}
