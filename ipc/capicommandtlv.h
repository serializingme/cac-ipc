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

typedef PVOID(__thiscall* CApiCommandTlv_Constructor)(PVOID, PLONG32, UINT32, PVOID);
typedef VOID(__thiscall* CApiCommandTlv_Destructor)(PVOID);
typedef LONG(__thiscall* CApiCommandTlv_SetStringParam)(PVOID, PSTRING16);

class CApiCommandTlv : public CIPCClassWrapper {
protected:
	CApiCommandTlv_Constructor constructor;
	CApiCommandTlv_Destructor destructor;
	CApiCommandTlv_SetStringParam setStringParam;

public:
	CApiCommandTlv(CModuleWrapper* moduleWrapper);
	virtual ~CApiCommandTlv();

	BOOL ConstructInstance();
	virtual BOOL PrepareInstance();
	VOID DestructInstance();
};

class CApiCommandTlvDumper : public CDumper {
public:
	CApiCommandTlvDumper(CSkip* destination, CModuleWrapper* moduleWrapper)
		: CDumper(destination, new CApiCommandTlv(moduleWrapper))
	{
	}

	~CApiCommandTlvDumper() {
		delete this->wrappedClass;
	}
};