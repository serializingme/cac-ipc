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
#pragma once

/**
 *
 */
enum SCEP_NOTIFICATION_TYPE {
	SCEP_NOTIFICATION_TYPE_TODO = 0xc0c1c2c3
};

/**
 *
 */
enum SCEP_TLV_TYPE {
	SCEP_TLV_TYPE_TODO = 0xc0c1c2c3
};

/**
 *
 */
enum SCEP_INFO_REQUEST_TYPE {
	SCEP_INFO_REQUEST_TYPE_TODO = 0xc0c1c2c3
};

typedef PVOID(__thiscall* SCEPTlv_Constructor)(PVOID, PLONG32, UINT32);
typedef VOID(__thiscall* SCEPTlv_Destructor)(PVOID);
typedef LONG(__thiscall* SCEPTlv_SetCAPass)(PVOID, PSTRING16);
typedef LONG(__thiscall* SCEPTlv_SetCertAccessControl)(PVOID, INT32);
typedef LONG(__thiscall* SCEPTlv_SetCertExpiry)(PVOID, INT64);
typedef LONG(__thiscall* SCEPTlv_SetCertThumbprint)(PVOID, PSTRING16);
typedef LONG(__thiscall* SCEPTlv_SetDistName)(PVOID, PVECTOR);
typedef LONG(__thiscall* SCEPTlv_SetInfoRequestType)(PVOID, SCEP_INFO_REQUEST_TYPE);
typedef LONG(__thiscall* SCEPTlv_SetMessageStatus)(PVOID, ULONG32);
typedef LONG(__thiscall* SCEPTlv_SetMessageType)(PVOID, SCEP_TLV_TYPE);
typedef LONG(__thiscall* SCEPTlv_SetNotificationID)(PVOID, SCEP_NOTIFICATION_TYPE);
typedef LONG(__thiscall* SCEPTlv_SetP12Cookie)(PVOID, PSTRING16);
typedef LONG(__thiscall* SCEPTlv_SetP12Data)(PVOID, PVECTOR);
typedef LONG(__thiscall* SCEPTlv_SetProfileName)(PVOID, PSTRING16);
typedef LONG(__thiscall* SCEPTlv_SetSGHost)(PVOID, PSTRING16);

class SCEPTlv : public CIPCClassWrapper {
protected:
	SCEPTlv_Constructor constructor;
	SCEPTlv_Destructor destructor;
	SCEPTlv_SetCAPass setCAPass;
	SCEPTlv_SetCertAccessControl setCertAccessControl;
	SCEPTlv_SetCertExpiry setCertExpiry;
	SCEPTlv_SetCertThumbprint setCertThumbprint;
	SCEPTlv_SetDistName setDistName;
	SCEPTlv_SetInfoRequestType setInfoRequestType;
	SCEPTlv_SetMessageStatus setMessageStatus;
	SCEPTlv_SetMessageType setMessageType;
	SCEPTlv_SetNotificationID setNotificationID;
	SCEPTlv_SetP12Cookie setP12Cookie;
	SCEPTlv_SetP12Data setP12Data;
	SCEPTlv_SetProfileName setProfileName;
	SCEPTlv_SetSGHost setSGHost;

public:
	SCEPTlv(CModuleWrapper* moduleWrapper);
	virtual ~SCEPTlv();

	BOOL ConstructInstance();
	virtual BOOL PrepareInstance();
	VOID DestructInstance();
};

class SCEPTlvDumper : public CDumper {
public:
	SCEPTlvDumper(CSkip* destination, CModuleWrapper* moduleWrapper)
		: CDumper(destination, new SCEPTlv(moduleWrapper))
	{
	}

	~SCEPTlvDumper() {
		delete this->wrappedClass;
	}
};
