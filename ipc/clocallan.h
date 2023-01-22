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

typedef PVOID(__thiscall* CLocalLAN_Constructor)(PVOID, PLONG32, PVOID);
typedef VOID(__thiscall* CLocalLAN_Destructor)(PVOID);
typedef LONG(__thiscall* CLocalLAN_SetLocalLANFlag)(PVOID, BOOL);

class CLocalLAN : public CIPCClassWrapper {
protected:
	CLocalLAN_Constructor constructor;
	CLocalLAN_Destructor destructor;
	CLocalLAN_SetLocalLANFlag setLocalLANFlag;

public:
	CLocalLAN(CModuleWrapper* moduleWrapper);
	virtual ~CLocalLAN();

	BOOL ConstructInstance();
	virtual BOOL PrepareInstance();
	VOID DestructInstance();
};

class CLocalLANDumper : public CDumper {
public:
	CLocalLANDumper(CSkip* destination, CModuleWrapper* moduleWrapper)
		: CDumper(destination, new CLocalLAN(moduleWrapper))
	{
	}

	~CLocalLANDumper() {
		delete this->wrappedClass;
	}
};
