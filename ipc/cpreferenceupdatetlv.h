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
enum AUTO_PREFERENCE_ID {
	AUTO_PREFERENCE_ID_TODO = 0xc0c1c2c3
};

/**
 *
 */
enum PREFERENCE_ID {
	PREFERENCE_ID_TODO = 0xc0c1c2c3
};

typedef PVOID(__thiscall* CPreferenceUpdateTlv_Constructor)(PVOID, PLONG32, PVOID);
typedef VOID(__thiscall* CPreferenceUpdateTlv_Destructor)(PVOID);
typedef LONG(__thiscall* CPreferenceUpdateTlv_addAutoPreferenceSetting)(PVOID, AUTO_PREFERENCE_ID, PSTRING16);
typedef LONG(__thiscall* CPreferenceUpdateTlv_addPreferenceSetting)(PVOID, PREFERENCE_ID, PSTRING16);
typedef LONG(__thiscall* CPreferenceUpdateTlv_setAutoPreferenceCount)(PVOID, UINT32);
typedef LONG(__thiscall* CPreferenceUpdateTlv_setPreferenceCount)(PVOID, UINT32);
typedef LONG(__thiscall* CPreferenceUpdateTlv_SetProfileName)(PVOID, PSTRING16);

class CPreferenceUpdateTlv : public CIPCClassWrapper {
protected:
	CPreferenceUpdateTlv_Constructor constructor;
	CPreferenceUpdateTlv_Destructor destructor;
	CPreferenceUpdateTlv_addAutoPreferenceSetting addAutoPreferenceSetting;
	CPreferenceUpdateTlv_addPreferenceSetting addPreferenceSetting;
	CPreferenceUpdateTlv_setAutoPreferenceCount setAutoPreferenceCount;
	CPreferenceUpdateTlv_setPreferenceCount setPreferenceCount;
	CPreferenceUpdateTlv_SetProfileName setProfileName;

public:
	CPreferenceUpdateTlv(CModuleWrapper* moduleWrapper);
	virtual ~CPreferenceUpdateTlv();

	BOOL ConstructInstance();
	virtual BOOL PrepareInstance();
	VOID DestructInstance();
};

class CPreferenceUpdateTlvDumper : public CDumper {
public:
	CPreferenceUpdateTlvDumper(CSkip* destination, CModuleWrapper* moduleWrapper)
		: CDumper(destination, new CPreferenceUpdateTlv(moduleWrapper))
	{
	}

	~CPreferenceUpdateTlvDumper() {
		delete this->wrappedClass;
	}
};
