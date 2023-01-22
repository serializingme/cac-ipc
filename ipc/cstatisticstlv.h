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


typedef PVOID(__thiscall* CStatisticsTlv_Constructor)(PVOID, PLONG32);
typedef VOID(__thiscall* CStatisticsTlv_Destructor)(PVOID);
typedef LONG(__thiscall* CStatisticsTlv_SetStatisticsInfo)(PVOID, PVOID);

class CStatisticsTlv : public CIPCClassWrapper {
protected:

	CStatisticsTlv_Constructor constructor;
	CStatisticsTlv_Destructor destructor;
	CStatisticsTlv_SetStatisticsInfo setStatisticsInfo;

public:
	CStatisticsTlv(CModuleWrapper* moduleWrapper);
	virtual ~CStatisticsTlv();

	BOOL ConstructInstance();
	virtual BOOL PrepareInstance();
	VOID DestructInstance();
};

class CStatisticsTlvDumper : public CDumper {
public:
	CStatisticsTlvDumper(CSkip* destination, CModuleWrapper* moduleWrapper)
		: CDumper(destination, new CStatisticsTlv(moduleWrapper))
	{
	}

	~CStatisticsTlvDumper() {
		delete this->wrappedClass;
	}
};
