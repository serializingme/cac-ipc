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

typedef PVOID(__thiscall* CKeyExchangeTLV_Constructor)(PVOID, PLONG32, PVOID);
typedef VOID(__thiscall* CKeyExchangeTLV_Destructor)(PVOID);
typedef LONG(__thiscall* CKeyExchangeTLV_SetEncryptedKey)(PVOID, PUINT8, UINT32);
typedef LONG(__thiscall* CKeyExchangeTLV_SetPublicKey)(PVOID, PUINT8, UINT32);
typedef LONG(__thiscall* CKeyExchangeTLV_SetVpnTunnelScope)(PVOID, VPN_TUNNEL_SCOPE);

class CKeyExchangeTLV : public CIPCClassWrapper {
protected:
	CKeyExchangeTLV_Constructor constructor;
	CKeyExchangeTLV_Destructor destructor;
	CKeyExchangeTLV_SetEncryptedKey setEncryptedKey;
	CKeyExchangeTLV_SetPublicKey setPublicKey;
	CKeyExchangeTLV_SetVpnTunnelScope setVpnTunnelScope;

public:
	CKeyExchangeTLV(CModuleWrapper* moduleWrapper);
	virtual ~CKeyExchangeTLV();

	BOOL ConstructInstance();
	virtual BOOL PrepareInstance();
	VOID DestructInstance();
};

class CKeyExchangeTLVDumper : public CDumper {
public:
	CKeyExchangeTLVDumper(CSkip* destination, CModuleWrapper* moduleWrapper)
		: CDumper(destination, new CKeyExchangeTLV(moduleWrapper))
	{
	}

	~CKeyExchangeTLVDumper() {
		delete this->wrappedClass;
	}
};
