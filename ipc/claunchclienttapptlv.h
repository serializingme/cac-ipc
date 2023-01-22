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

typedef PVOID(__thiscall* CLaunchClientAppTlv_Constructor)(PVOID, PLONG32, PVOID);
typedef VOID(__thiscall* CLaunchClientAppTlv_Destructor)(PVOID);
typedef LONG(__thiscall* CLaunchClientAppTlv_SetCmdLine)(PVOID, LPCSTR);
typedef LONG(__thiscall* CLaunchClientAppTlv_SetFilePath)(PVOID, LPCSTR);
typedef LONG(__thiscall* CLaunchClientAppTlv_SetGUIDesktop)(PVOID, LPCSTR);
typedef LONG(__thiscall* CLaunchClientAppTlv_SetRelocatableFilePath)(PVOID, LPCSTR);
typedef LONG(__thiscall* CLaunchClientAppTlv_SetUseInstalled)(PVOID, BOOL);

class CLaunchClientAppTlv : public CIPCClassWrapper {
protected:
	CLaunchClientAppTlv_Constructor constructor;
	CLaunchClientAppTlv_Destructor destructor;
	CLaunchClientAppTlv_SetCmdLine setCmdLine;
	CLaunchClientAppTlv_SetFilePath setFilePath;
	CLaunchClientAppTlv_SetGUIDesktop setGUIDesktop;
	CLaunchClientAppTlv_SetRelocatableFilePath setRelocatableFilePath;
	CLaunchClientAppTlv_SetUseInstalled setUseInstalled;

public:
	CLaunchClientAppTlv(CModuleWrapper* moduleWrapper);
	virtual ~CLaunchClientAppTlv();

	BOOL ConstructInstance();
	virtual BOOL PrepareInstance();
	VOID DestructInstance();
};

class CLaunchClientAppTlvDumper : public CDumper {
public:
	CLaunchClientAppTlvDumper(CSkip* destination, CModuleWrapper* moduleWrapper)
		: CDumper(destination, new CLaunchClientAppTlv(moduleWrapper))
	{
	}

	~CLaunchClientAppTlvDumper() {
		delete this->wrappedClass;
	}
};
