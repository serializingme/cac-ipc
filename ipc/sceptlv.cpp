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
#include "sceptlv.h"

SCEPTlv::SCEPTlv(CModuleWrapper* moduleWrapper)
	: CIPCClassWrapper(moduleWrapper)
{
	this->constructor = this->moduleWrapper->GetExport<SCEPTlv_Constructor>(
		"??0SCEPTlv@@QAE@AAJW4IPC_MESSAGE_ID@@@Z");
	this->destructor = this->moduleWrapper->GetExport<SCEPTlv_Destructor>(
		"??1CIPCTLV@@UAE@XZ");
	this->setCAPass = this->moduleWrapper->GetExport<SCEPTlv_SetCAPass>(
		"?SetCAPass@SCEPTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setCertAccessControl = this->moduleWrapper->GetExport<SCEPTlv_SetCertAccessControl>(
		"?SetCertAccessControl@SCEPTlv@@QAEJH@Z");
	this->setCertExpiry = this->moduleWrapper->GetExport<SCEPTlv_SetCertExpiry>(
		"?SetCertExpiry@SCEPTlv@@QAEJ_J@Z");
	this->setCertThumbprint = this->moduleWrapper->GetExport<SCEPTlv_SetCertThumbprint>(
		"?SetCertThumbprint@SCEPTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setDistName = this->moduleWrapper->GetExport<SCEPTlv_SetDistName>(
		"?SetDistName@SCEPTlv@@QAEJABV?$vector@EV?$allocator@E@std@@@std@@@Z");
	this->setInfoRequestType = this->moduleWrapper->GetExport<SCEPTlv_SetInfoRequestType>(
		"?SetInfoRequestType@SCEPTlv@@QAEJW4SCEP_INFO_REQUEST_TYPE@@@Z");
	this->setMessageStatus = this->moduleWrapper->GetExport<SCEPTlv_SetMessageStatus>(
		"?SetMessageStatus@SCEPTlv@@QAEJJ@Z");
	this->setMessageType = this->moduleWrapper->GetExport<SCEPTlv_SetMessageType>(
		"?SetMessageType@SCEPTlv@@QAEJW4SCEP_TLV_TYPE@@@Z");
	this->setNotificationID = this->moduleWrapper->GetExport<SCEPTlv_SetNotificationID>(
		"?SetNotificationID@SCEPTlv@@QAEJW4SCEP_NOTIFICATION_TYPE@@@Z");
	this->setP12Cookie = this->moduleWrapper->GetExport<SCEPTlv_SetP12Cookie>(
		"?SetP12Cookie@SCEPTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setP12Data = this->moduleWrapper->GetExport<SCEPTlv_SetP12Data>(
		"?SetP12Data@SCEPTlv@@QAEJABV?$vector@EV?$allocator@E@std@@@std@@@Z");
	this->setProfileName = this->moduleWrapper->GetExport<SCEPTlv_SetProfileName>(
		"?SetProfileName@SCEPTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setSGHost = this->moduleWrapper->GetExport<SCEPTlv_SetSGHost>(
		"?SetSGHost@SCEPTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
}

SCEPTlv::~SCEPTlv() {
}

BOOL SCEPTlv::ConstructInstance() {
	LONG32 lErrorCode = 0;

	if (this->realInstance == NULL) {
		return FALSE;
	}

	this->constructor(this->realInstance, &lErrorCode, 0x1b);

	return (lErrorCode == 0);
}

BOOL SCEPTlv::PrepareInstance() {
	if (this->realInstance == NULL) {
		return FALSE;
	}

	if (this->setCAPass(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setCertAccessControl(this->realInstance, paramINT32) != 0) {
		return FALSE;
	}
	if (this->setCertExpiry(this->realInstance, paramINT64) != 0) {
		return FALSE;
	}
	if (this->setCertThumbprint(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setDistName(this->realInstance, &paramUINT8Vector) != 0) {
		return FALSE;
	}
	if (this->setInfoRequestType(this->realInstance, SCEP_INFO_REQUEST_TYPE_TODO) != 0) {
		return FALSE;
	}
	if (this->setMessageStatus(this->realInstance, paramLONG32) != 0) {
		return FALSE;
	}
	if (this->setMessageType(this->realInstance, SCEP_TLV_TYPE_TODO) != 0) {
		return FALSE;
	}
	if (this->setNotificationID(this->realInstance, SCEP_NOTIFICATION_TYPE_TODO) != 0) {
		return FALSE;
	}
	if (this->setP12Cookie(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setP12Data(this->realInstance, &paramUINT8Vector) != 0) {
		return FALSE;
	}
	if (this->setProfileName(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setSGHost(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}

	return TRUE;
}

VOID SCEPTlv::DestructInstance() {
	if (this->realInstance != NULL) {
		this->destructor(this->realInstance);
	}
}
