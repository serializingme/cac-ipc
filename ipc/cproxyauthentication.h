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

typedef PVOID(__thiscall* CProxyAuthentication_Constructor)(PVOID, PLONG32, PVOID);
typedef VOID(__thiscall* CProxyAuthentication_Destructor)(PVOID);
typedef LONG(__thiscall* CProxyAuthentication_SetEnAuthority)(PVOID, PUINT8, UINT32);
typedef LONG(__thiscall* CProxyAuthentication_SetEnPassword)(PVOID, PUINT8, UINT32);
typedef LONG(__thiscall* CProxyAuthentication_SetEnPrincipal)(PVOID, PUINT8, UINT32);
typedef LONG(__thiscall* CProxyAuthentication_SetErrorMessage)(PVOID, PSTRING8);
typedef LONG(__thiscall* CProxyAuthentication_SetRealm)(PVOID, PSTRING8);
typedef LONG(__thiscall* CProxyAuthentication_SetScheme)(PVOID, PSTRING8);
typedef LONG(__thiscall* CProxyAuthentication_SetServerName)(PVOID, PSTRING8);
typedef LONG(__thiscall* CProxyAuthentication_SetSGDomainName)(PVOID, PSTRING8);

class CProxyAuthentication : public CIPCClassWrapper {
protected:
	CProxyAuthentication_Constructor constructor;
	CProxyAuthentication_Destructor destructor;
	CProxyAuthentication_SetEnAuthority setEnAuthority;
	CProxyAuthentication_SetEnPassword setEnPassword;
	CProxyAuthentication_SetEnPrincipal setEnPrincipal;
	CProxyAuthentication_SetErrorMessage setErrorMessage;
	CProxyAuthentication_SetRealm setRealm;
	CProxyAuthentication_SetScheme setScheme;
	CProxyAuthentication_SetServerName setServerName;
	CProxyAuthentication_SetSGDomainName setSGDomainName;

public:
	CProxyAuthentication(CModuleWrapper* moduleWrapper);
	virtual ~CProxyAuthentication();

	BOOL ConstructInstance();
	virtual BOOL PrepareInstance();
	VOID DestructInstance();
};

class CProxyAuthenticationDumper : public CDumper {
public:
	CProxyAuthenticationDumper(CSkip* destination, CModuleWrapper* moduleWrapper)
		: CDumper(destination, new CProxyAuthentication(moduleWrapper))
	{
	}

	~CProxyAuthenticationDumper() {
		delete this->wrappedClass;
	}
};
