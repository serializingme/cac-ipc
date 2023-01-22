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
#include "cstatetlv.h"

CStateTlv::CStateTlv(CModuleWrapper* moduleWrapper)
	: CIPCClassWrapper(moduleWrapper)
{
	this->constructor = this->moduleWrapper->GetExport<CStateTlv_Constructor>(
		"??0CStateTlv@@QAE@AAJ@Z");
	this->destructor = this->moduleWrapper->GetExport<CStateTlv_Destructor>(
		"??1CIPCTLV@@UAE@XZ");
	this->addTunnelComprAlgorithm = this->moduleWrapper->GetExport<CStateTlv_addTunnelComprAlgorithm>(
		"?addTunnelComprAlgorithm@CStateTlv@@QAEJW4COMPR_ALGORITHM@@@Z");
	this->addTunnelProtocolCipher = this->moduleWrapper->GetExport<CStateTlv_addTunnelProtocolCipher>(
		"?addTunnelProtocolCipher@CStateTlv@@QAEJW4ProtocolCipher@@@Z");
	this->addTunnelProtocolVersion = this->moduleWrapper->GetExport<CStateTlv_addTunnelProtocolVersion>(
		"?addTunnelProtocolVersion@CStateTlv@@QAEJW4ProtocolVersion@@@Z");
	this->addTunnelState = this->moduleWrapper->GetExport<CStateTlv_addTunnelState>(
		"?addTunnelState@CStateTlv@@QAEJW4STATE@@@Z");
	this->setACBrowserForCPRemediation = this->moduleWrapper->GetExport<CStateTlv_setACBrowserForCPRemediation>(
		"?setACBrowserForCPRemediation@CStateTlv@@QAEJ_N@Z");
	this->setActiveTunnelIndex = this->moduleWrapper->GetExport<CStateTlv_setActiveTunnelIndex>(
		"?setActiveTunnelIndex@CStateTlv@@QAEJI@Z");
	this->setAggregateTunnelState = this->moduleWrapper->GetExport<CStateTlv_setAggregateTunnelState>(
		"?setAggregateTunnelState@CStateTlv@@QAEJW4STATE@@@Z");
	this->setMgmtTunSessionState = this->moduleWrapper->GetExport<CStateTlv_setMgmtTunSessionState>(
		"?setMgmtTunSessionState@CStateTlv@@QAEJW4STATE@@@Z");
	this->setMgmtTunSessionSubState = this->moduleWrapper->GetExport<CStateTlv_setMgmtTunSessionSubState>(
		"?setMgmtTunSessionSubState@CStateTlv@@QAEJW4VPNCON_SUBSTATE@@@Z");
	this->setMgmtTunSGHostName = this->moduleWrapper->GetExport<CStateTlv_setMgmtTunSGHostName>(
		"?setMgmtTunSGHostName@CStateTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->SetMUSHostAddr = this->moduleWrapper->GetExport<CStateTlv_SetMUSHostAddr>(
		"?SetMUSHostAddr@CStateTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->SetMUSStatus = this->moduleWrapper->GetExport<CStateTlv_SetMUSStatus>(
		"?SetMUSStatus@CStateTlv@@QAEJW4MUS_STATUS@@@Z");
	this->setNetCtrlState = this->moduleWrapper->GetExport<CStateTlv_setNetCtrlState>(
		"?setNetCtrlState@CStateTlv@@QAEJW4NETCTRL_STATE@@@Z");
	this->setNetEnvState = this->moduleWrapper->GetExport<CStateTlv_setNetEnvState>(
		"?setNetEnvState@CStateTlv@@QAEJW4NETENV_STATE@@@Z");
	this->setNetType = this->moduleWrapper->GetExport<CStateTlv_setNetType>(
		"?setNetType@CStateTlv@@QAEJW4NETWORK_TYPE@@@Z");
	this->setSessionState = this->moduleWrapper->GetExport<CStateTlv_setSessionState>(
		"?setSessionState@CStateTlv@@QAEJW4STATE@@@Z");
	this->setSessionSubState = this->moduleWrapper->GetExport<CStateTlv_setSessionSubState>(
		"?setSessionSubState@CStateTlv@@QAEJW4VPNCON_SUBSTATE@@@Z");
	this->setTunnelCount = this->moduleWrapper->GetExport<CStateTlv_setTunnelCount>(
		"?setTunnelCount@CStateTlv@@QAEJI@Z");
	this->setUserTunnelStateOnly = this->moduleWrapper->GetExport<CStateTlv_setUserTunnelStateOnly>(
		"?setUserTunnelStateOnly@CStateTlv@@QAEJ_N@Z");
}

CStateTlv::~CStateTlv() {
}

BOOL CStateTlv::ConstructInstance() {
	LONG32 lErrorCode = 0;

	if (this->realInstance == NULL) {
		return FALSE;
	}

	this->constructor(this->realInstance, &lErrorCode);

	return (lErrorCode == 0);
}

BOOL CStateTlv::PrepareInstance() {
	if (this->realInstance == NULL) {
		return FALSE;
	}

	if (this->addTunnelComprAlgorithm(this->realInstance, COMPR_ALGORITHM_TODO) != 0) {
		return FALSE;
	}
	if (this->addTunnelProtocolCipher(this->realInstance, PROTOCOL_CIPHER_TODO) != 0) {
		return FALSE;
	}
	if (this->addTunnelProtocolVersion(this->realInstance, PROTOCOL_VERSION_TODO) != 0) {
		return FALSE;
	}
	if (this->addTunnelState(this->realInstance, VPN_TUNNEL_STATE_TODO) != 0) {
		return FALSE;
	}
	if (this->setACBrowserForCPRemediation(this->realInstance, paramBOOL) != 0) {
		return FALSE;
	}
	if (this->setActiveTunnelIndex(this->realInstance, paramUINT32) != 0) {
		return FALSE;
	}
	if (this->setAggregateTunnelState(this->realInstance, VPN_TUNNEL_STATE_TODO) != 0) {
		return FALSE;
	}
	if (this->setMgmtTunSessionState(this->realInstance, VPN_TUNNEL_STATE_TODO) != 0) {
		return FALSE;
	}
	if (this->setMgmtTunSessionSubState(this->realInstance, VPNCON_SUBSTATE_TODO) != 0) {
		return FALSE;
	}
	if (this->setMgmtTunSGHostName(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->SetMUSHostAddr(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->SetMUSStatus(this->realInstance, MUS_STATUS_TODO) != 0) {
		return FALSE;
	}
	if (this->setNetCtrlState(this->realInstance, NETCTRL_STATE_TODO) != 0) {
		return FALSE;
	}
	if (this->setNetEnvState(this->realInstance, NETENV_STATE_TODO) != 0) {
		return FALSE;
	}
	if (this->setNetType(this->realInstance, NETWORK_TYPE_TODO) != 0) {
		return FALSE;
	}
	if (this->setSessionState(this->realInstance, VPN_TUNNEL_STATE_TODO) != 0) {
		return FALSE;
	}
	if (this->setSessionSubState(this->realInstance, VPNCON_SUBSTATE_TODO) != 0) {
		return FALSE;
	}
	if (this->setTunnelCount(this->realInstance, paramUINT32) != 0) {
		return FALSE;
	}
	if (this->setUserTunnelStateOnly(this->realInstance, paramBOOL) != 0) {
		return FALSE;
	}

	return TRUE;
}

VOID CStateTlv::DestructInstance() {
	if (this->realInstance != NULL) {
		this->destructor(this->realInstance);
	}
}
