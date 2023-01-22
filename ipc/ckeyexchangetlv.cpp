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
#include "common.h"
#include "ckeyexchangetlv.h"

CKeyExchangeTLV::CKeyExchangeTLV(CModuleWrapper* moduleWrapper)
	: CIPCClassWrapper(moduleWrapper)
{
	this->constructor = this->moduleWrapper->GetExport<CKeyExchangeTLV_Constructor>(
		"??0CKeyExchangeTLV@@QAE@AAJPAVIIpcResponseCB@@@Z");
	this->destructor = this->moduleWrapper->GetExport<CKeyExchangeTLV_Destructor>(
		"??1CIPCTLV@@UAE@XZ");
	this->setEncryptedKey = this->moduleWrapper->GetExport<CKeyExchangeTLV_SetEncryptedKey>(
		"?SetEncryptedKey@CKeyExchangeTLV@@QAEJPBEI@Z");
	this->setPublicKey = this->moduleWrapper->GetExport<CKeyExchangeTLV_SetPublicKey>(
		"?SetPublicKey@CKeyExchangeTLV@@QAEJPBEI@Z");
	this->setVpnTunnelScope = this->moduleWrapper->GetExport<CKeyExchangeTLV_SetVpnTunnelScope>(
		"?SetVpnTunnelScope@CKeyExchangeTLV@@QAEJW4VPN_TUNNEL_SCOPE@@@Z");
}

CKeyExchangeTLV::~CKeyExchangeTLV() {
}

	LONG32 lErrorCode = 0;

	if (this->realInstance == NULL) {
		return FALSE;
	}

	this->constructor(this->realInstance, &lErrorCode, (PVOID)0xffffffff);

	return (lErrorCode == 0);
}


	if (this->setEncryptedKey(this->realInstance, paramUINT8Array, ARRAYSIZE(paramUINT8Array)) != 0) {
		return FALSE;
	}
	if (this->setPublicKey(this->realInstance, paramUINT8Array, ARRAYSIZE(paramUINT8Array)) != 0) {
		return FALSE;
	}
	if (this->setVpnTunnelScope(this->realInstance, VPN_TUNNEL_SCOPE_1) != 0) {
		return FALSE;
	}

	return TRUE;
}

VOID CKeyExchangeTLV::DestructInstance() {
}
