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
#include "cusermessagetlv.h"

CUserMessageTlv::CUserMessageTlv(CModuleWrapper* moduleWrapper)
	: CIPCClassWrapper(moduleWrapper)
{
	this->constructor = this->moduleWrapper->GetExport<CUserMessageTlv_Constructor>(
		"??0CUserMessageTlv@@QAE@AAJW4USER_MESSAGE_TYPE@@@Z");
	this->destructor = this->moduleWrapper->GetExport<CUserMessageTlv_Destructor>(
		"??1CUserMessageTlv@@UAE@XZ");
	this->addMessage = this->moduleWrapper->GetExport<CUserMessageTlv_AddMessage>(
		"?AddMessage@CUserMessageTlv@@QAEJABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_N@Z");
	this->addMessageArg = this->moduleWrapper->GetExport<CUserMessageTlv_AddMessageArg>(
		"?addMessageArg@CUserMessageTlv@@QAEJABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	this->setArgumentCount = this->moduleWrapper->GetExport<CUserMessageTlv_setArgumentCount>(
		"?setArgumentCount@CUserMessageTlv@@QAEJI@Z");
	this->setMessageCount = this->moduleWrapper->GetExport<CUserMessageTlv_SetMessageCount>(
		"?SetMessageCount@CUserMessageTlv@@QAEJI@Z");
	this->setMessageText = this->moduleWrapper->GetExport<CUserMessageTlv_setMessageText>(
		"?setMessageText@CUserMessageTlv@@QAEJABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	this->setProgressPercentage = this->moduleWrapper->GetExport<CUserMessageTlv_setProgressPercentage>(
		"?setProgressPercentage@CUserMessageTlv@@QAEJI@Z");
}

CUserMessageTlv::~CUserMessageTlv() {
}

BOOL CUserMessageTlv::ConstructInstance() {
	LONG32 lErrorCode = 0;

	if (this->realInstance == NULL) {
		return FALSE;
	}

	this->constructor(this->realInstance, &lErrorCode, 0x03);

	return (lErrorCode == 0);
}

BOOL CUserMessageTlv::PrepareInstance() {
	if (this->realInstance == NULL) {
		return FALSE;
	}

	if (this->setMessageCount(this->realInstance, paramUINT32) != 0) {
		return FALSE;
	}
	if (this->setMessageText(this->realInstance, &paramSTRING8) != 0) {
		return FALSE;
	}
	if (this->setArgumentCount(this->realInstance, paramUINT32) != 0) {
		return FALSE;
	}
	if (this->addMessageArg(this->realInstance, &paramSTRING8) != 0) {
		return FALSE;
	}
	if (this->setProgressPercentage(this->realInstance, paramUINT32) != 0) {
		return FALSE;
	}
	if (this->addMessage(this->realInstance, &paramSTRING8, FALSE) != 0) {
		return FALSE;
	}

	return TRUE;
}

VOID CUserMessageTlv::DestructInstance() {
	if (this->realInstance != NULL) {
		this->destructor(this->realInstance);
	}
}
