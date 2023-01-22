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

typedef PVOID(__thiscall* CRedirectTlv_Constructor)(PVOID, PLONG32);
typedef VOID(__thiscall* CRedirectTlv_Destructor)(PVOID);
typedef LONG(__thiscall* CRedirectTlv_SetPrimaryIPAddress)(PVOID, PSTRING16);
typedef LONG(__thiscall* CRedirectTlv_SetRedirectAddress)(PVOID, PSTRING16);
typedef LONG(__thiscall* CRedirectTlv_SetSecondaryIPAdddress)(PVOID, PSTRING16);

class CRedirectTlv : public CIPCClassWrapper {
protected:
	CRedirectTlv_Constructor constructor;
	CRedirectTlv_Destructor destructor;
	CRedirectTlv_SetPrimaryIPAddress setPrimaryIPAddress;
	CRedirectTlv_SetRedirectAddress setRedirectAddress;
	CRedirectTlv_SetSecondaryIPAdddress setSecondaryIPAddress;

public:
	CRedirectTlv(CModuleWrapper* moduleWrapper);
	virtual ~CRedirectTlv();

	BOOL ConstructInstance();
	virtual BOOL PrepareInstance();
	VOID DestructInstance();
};

class CRedirectTlvDumper : public CDumper {
public:
	CRedirectTlvDumper(CSkip* destination, CModuleWrapper* moduleWrapper)
		: CDumper(destination, new CRedirectTlv(moduleWrapper))
	{
	}

	~CRedirectTlvDumper() {
		delete this->wrappedClass;
	}
};
