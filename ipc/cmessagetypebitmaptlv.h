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

typedef PVOID(__thiscall* CMessageTypeBitmapTlv_Constructor)(PVOID, PLONG32, PUINT32);
typedef VOID(__thiscall* CMessageTypeBitmapTlv_Destructor)(PVOID);
typedef LONG(__thiscall* CMessageTypeBitmapTlv_SetActiveClientPolicy)(PVOID, UINT32);
typedef LONG(__thiscall* CMessageTypeBitmapTlv_setApplicationName)(PVOID, PSTRING8);
typedef LONG(__thiscall* CMessageTypeBitmapTlv_SetAppOperationMode)(PVOID, UINT32);
typedef LONG(__thiscall* CMessageTypeBitmapTlv_SetNotificationMode)(PVOID, BOOL);
typedef LONG(__thiscall* CMessageTypeBitmapTlv_SetNumSameAppRegistration)(PVOID, UINT32);
typedef LONG(__thiscall* CMessageTypeBitmapTlv_SetPID)(PVOID, PULONG32);

class CMessageTypeBitmapTlv : public CIPCClassWrapper {
protected:
	CMessageTypeBitmapTlv_Constructor constructor;
	CMessageTypeBitmapTlv_Destructor destructor;
	CMessageTypeBitmapTlv_SetActiveClientPolicy setActiveClientPolicy;
	CMessageTypeBitmapTlv_setApplicationName setApplicationName;
	CMessageTypeBitmapTlv_SetAppOperationMode setAppOperationMode;
	CMessageTypeBitmapTlv_SetNotificationMode setNotificationMode;
	CMessageTypeBitmapTlv_SetNumSameAppRegistration setNumSameAppRegstration;
	CMessageTypeBitmapTlv_SetPID setPID;

public:
	CMessageTypeBitmapTlv(CModuleWrapper* moduleWrapper);
	virtual ~CMessageTypeBitmapTlv();

	BOOL ConstructInstance();
	virtual BOOL PrepareInstance();
	VOID DestructInstance();
};

class CMessageTypeBitmapTlvDumper : public CDumper {
public:
	CMessageTypeBitmapTlvDumper(CSkip* destination, CModuleWrapper* moduleWrapper)
		: CDumper(destination, new CMessageTypeBitmapTlv(moduleWrapper))
	{
	}

	~CMessageTypeBitmapTlvDumper() {
		delete this->wrappedClass;
	}
};
