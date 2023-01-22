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

typedef PVOID(__thiscall* CTerminateTlv_Constructor)(PVOID, PLONG32);
typedef VOID(__thiscall* CTerminateTlv_Destructor)(PVOID);
typedef LONG(__thiscall* CTerminateTlv_SetDelayLimit)(PVOID, ULONG32);
typedef LONG(__thiscall* CTerminateTlv_SetReasonCode)(PVOID, REASON_CODE);

class CTerminateTlv : public CIPCClassWrapper {
protected:
	CTerminateTlv_Constructor constructor;
	CTerminateTlv_Destructor destructor;
	CTerminateTlv_SetDelayLimit setDelayLimit;
	CTerminateTlv_SetReasonCode setReasonCode;

public:
	CTerminateTlv(CModuleWrapper* moduleWrapper);
	virtual ~CTerminateTlv();

	BOOL ConstructInstance();
	virtual BOOL PrepareInstance();
	VOID DestructInstance();
};

class CTerminateTlvDumper : public CDumper {
public:
	CTerminateTlvDumper(CSkip* destination, CModuleWrapper* moduleWrapper)
		: CDumper(destination, new CTerminateTlv(moduleWrapper))
	{
	}

	~CTerminateTlvDumper() {
		delete this->wrappedClass;
	}
};
