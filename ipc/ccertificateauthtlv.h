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

typedef PVOID(__thiscall* CCertificateAuthTlv_Constructor)(PVOID, PLONG32, PVOID);
typedef VOID(__thiscall* CCertificateAuthTlv_Destructor)(PVOID);
typedef LONG(__thiscall* CCertificateAuthTlv_SetClientCertThumbprint)(PVOID, LPCSTR);
typedef LONG(__thiscall* CCertificateAuthTlv_SetEnPassword)(PVOID, PUINT8, UINT32);
typedef LONG(__thiscall* CCertificateAuthTlv_SetServerCertThumbprint)(PVOID, LPCSTR);

class CCertificateAuthTlv : public CIPCClassWrapper {
protected:
	CCertificateAuthTlv_Constructor constructor;
	CCertificateAuthTlv_Destructor destructor;
	CCertificateAuthTlv_SetClientCertThumbprint setClientCertThumbprint;
	CCertificateAuthTlv_SetEnPassword setEnPassword;
	CCertificateAuthTlv_SetServerCertThumbprint setServerCertThumbprint;

public:
	CCertificateAuthTlv(CModuleWrapper* moduleWrapper);
	virtual ~CCertificateAuthTlv();

	BOOL ConstructInstance();
	virtual BOOL PrepareInstance();
	VOID DestructInstance();
};

class CCertificateAuthTlvDumper : public CDumper {
public:
	CCertificateAuthTlvDumper(CSkip* destination, CModuleWrapper* moduleWrapper)
		: CDumper(destination, new CCertificateAuthTlv(moduleWrapper))
	{
	}

	~CCertificateAuthTlvDumper() {
		delete this->wrappedClass;
	}
};
