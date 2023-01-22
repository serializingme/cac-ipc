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

typedef PVOID(__thiscall* CUserMessageTlv_Constructor)(PVOID, PLONG32, UINT32);
typedef VOID(__thiscall* CUserMessageTlv_Destructor)(PVOID);
typedef LONG(__thiscall* CUserMessageTlv_AddMessage)(PVOID, PSTRING8, BOOL);
typedef LONG(__thiscall* CUserMessageTlv_AddMessageArg)(PVOID, PSTRING8);
typedef LONG(__thiscall* CUserMessageTlv_setArgumentCount)(PVOID, UINT32);
typedef LONG(__thiscall* CUserMessageTlv_SetMessageCount)(PVOID, UINT32);
typedef LONG(__thiscall* CUserMessageTlv_setMessageText)(PVOID, PSTRING8);
typedef LONG(__thiscall* CUserMessageTlv_setProgressPercentage)(PVOID, UINT32);

class CUserMessageTlv : public CIPCClassWrapper {
protected:
	CUserMessageTlv_Constructor constructor;
	CUserMessageTlv_Destructor destructor;
	CUserMessageTlv_AddMessage addMessage;
	CUserMessageTlv_AddMessageArg addMessageArg;
	CUserMessageTlv_setArgumentCount setArgumentCount;
	CUserMessageTlv_SetMessageCount setMessageCount;
	CUserMessageTlv_setMessageText setMessageText;
	CUserMessageTlv_setProgressPercentage setProgressPercentage;

public:
	CUserMessageTlv(CModuleWrapper* moduleWrapper);
	virtual ~CUserMessageTlv();

	BOOL ConstructInstance();
	virtual BOOL PrepareInstance();
	VOID DestructInstance();
};

class CUserMessageTlvDumper : public CDumper {
public:
	CUserMessageTlvDumper(CSkip* destination, CModuleWrapper* moduleWrapper)
		: CDumper(destination, new CUserMessageTlv(moduleWrapper))
	{
	}

	~CUserMessageTlvDumper() {
		delete this->wrappedClass;
	}
};
