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
#include "NotifyAgentTlv.h"

NotifyAgentTlv::NotifyAgentTlv(CModuleWrapper* moduleWrapper)
	: CIPCClassWrapper(moduleWrapper)
{
	this->constructor = this->moduleWrapper->GetExport<NotifyAgentTlv_Constructor>(
		"??0NotifyAgentTlv@@QAE@AAJW4IPC_MESSAGE_ID@@@Z");
	this->destructor = this->moduleWrapper->GetExport<NotifyAgentTlv_Destructor>(
		"??1CIPCTLV@@UAE@XZ");
	this->setSCEPHostUrl = this->moduleWrapper->GetExport<NotifyAgentTlv_SetSCEPHostUrl>(
		"?SetSCEPHostUrl@NotifyAgentTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
}

NotifyAgentTlv::~NotifyAgentTlv() {
}

BOOL NotifyAgentTlv::ConstructInstance() {
	LONG32 lErrorCode = 0;

	if (this->realInstance == NULL) {
		return FALSE;
	}

	this->constructor(this->realInstance, &lErrorCode, 0x1f);

	return (lErrorCode == 0);
}

BOOL NotifyAgentTlv::PrepareInstance() {
	if (this->realInstance == NULL) {
		return FALSE;
	}

	if (this->setSCEPHostUrl(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	
	return TRUE;
}

VOID NotifyAgentTlv::DestructInstance() {
	if (this->realInstance != NULL) {
		this->destructor(this->realInstance);
	}
}
