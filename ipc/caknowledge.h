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

typedef PVOID(__thiscall* CAcknowledge_Constructor)(PVOID, PLONG32, UINT32, PVOID);
typedef VOID(__thiscall* CAcknowledge_Destructor)(PVOID);
typedef LONG(__thiscall* CAcknowledge_setAckValue)(PVOID, PINT32);
typedef LONG(__thiscall* CAcknowledge_setSystemErrorValue)(PVOID, PUINT32);

class CAcknowledge : public CIPCClassWrapper {
protected:
	CAcknowledge_Constructor constructor;
	CAcknowledge_Destructor destructor;
	CAcknowledge_setAckValue setAckValue;
	CAcknowledge_setSystemErrorValue setSystemErrorValue;

public:
	CAcknowledge(CModuleWrapper* moduleWrapper);
	virtual ~CAcknowledge();

	BOOL ConstructInstance();
	virtual BOOL PrepareInstance();
	VOID DestructInstance();
};

class CAcknowledgeDumper : public CDumper {
public:
	CAcknowledgeDumper(CSkip* destination, CModuleWrapper* moduleWrapper)
		: CDumper(destination, new CAcknowledge(moduleWrapper))
	{
	}

	~CAcknowledgeDumper() {
		delete this->wrappedClass;
	}
};
