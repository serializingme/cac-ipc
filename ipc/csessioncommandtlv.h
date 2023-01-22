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

typedef PVOID(__thiscall* CSessionCommandTlv_Constructor)(PVOID, PLONG32, UINT32);
typedef VOID(__thiscall* CSessionCommandTlv_Destructor)(PVOID);

class CSessionCommandTlv : public CIPCClassWrapper {
protected:
	CSessionCommandTlv_Constructor constructor;
	CSessionCommandTlv_Destructor destructor;

public:
	CSessionCommandTlv(CModuleWrapper* moduleWrapper);
	virtual ~CSessionCommandTlv();

	BOOL ConstructInstance();
	virtual BOOL PrepareInstance();
	VOID DestructInstance();
};

class CSessionCommandTlvDumper : public CDumper {
public:
	CSessionCommandTlvDumper(CSkip* destination, CModuleWrapper* moduleWrapper)
		: CDumper(destination, new CSessionCommandTlv(moduleWrapper))
	{
	}

	~CSessionCommandTlvDumper() {
		delete this->wrappedClass;
	}
};
