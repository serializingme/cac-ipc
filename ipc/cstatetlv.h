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

typedef PVOID(__thiscall* CStateTlv_Constructor)(PVOID, PLONG32);
typedef VOID(__thiscall* CStateTlv_Destructor)(PVOID);
typedef LONG(__thiscall* CStateTlv_addTunnelComprAlgorithm)(PVOID, COMPR_ALGORITHM);
typedef LONG(__thiscall* CStateTlv_addTunnelProtocolCipher)(PVOID, PROTOCOL_CIPHER);
typedef LONG(__thiscall* CStateTlv_addTunnelProtocolVersion)(PVOID, PROTOCOL_VERSION);
typedef LONG(__thiscall* CStateTlv_addTunnelState)(PVOID, VPN_TUNNEL_STATE);
typedef LONG(__thiscall* CStateTlv_setACBrowserForCPRemediation)(PVOID, BOOL);
typedef LONG(__thiscall* CStateTlv_setActiveTunnelIndex)(PVOID, UINT32);
typedef LONG(__thiscall* CStateTlv_setAggregateTunnelState)(PVOID, VPN_TUNNEL_STATE);
typedef LONG(__thiscall* CStateTlv_setMgmtTunSessionState)(PVOID, VPN_TUNNEL_STATE);
typedef LONG(__thiscall* CStateTlv_setMgmtTunSessionSubState)(PVOID, VPNCON_SUBSTATE);
typedef LONG(__thiscall* CStateTlv_setMgmtTunSGHostName)(PVOID, PSTRING16);
typedef LONG(__thiscall* CStateTlv_SetMUSHostAddr)(PVOID, PSTRING16);
typedef LONG(__thiscall* CStateTlv_SetMUSStatus)(PVOID, MUS_STATUS);
typedef LONG(__thiscall* CStateTlv_setNetCtrlState)(PVOID, NETCTRL_STATE);
typedef LONG(__thiscall* CStateTlv_setNetEnvState)(PVOID, NETENV_STATE);
typedef LONG(__thiscall* CStateTlv_setNetType)(PVOID, NETWORK_TYPE);
typedef LONG(__thiscall* CStateTlv_setSessionState)(PVOID, VPN_TUNNEL_STATE);
typedef LONG(__thiscall* CStateTlv_setSessionSubState)(PVOID, VPNCON_SUBSTATE);
typedef LONG(__thiscall* CStateTlv_setTunnelCount)(PVOID, UINT32);
typedef LONG(__thiscall* CStateTlv_setUserTunnelStateOnly)(PVOID, BOOL);

class CStateTlv : public CIPCClassWrapper {
protected:
	CStateTlv_Constructor constructor;
	CStateTlv_Destructor destructor;
	CStateTlv_addTunnelComprAlgorithm addTunnelComprAlgorithm;
	CStateTlv_addTunnelProtocolCipher addTunnelProtocolCipher;
	CStateTlv_addTunnelProtocolVersion addTunnelProtocolVersion;
	CStateTlv_addTunnelState addTunnelState;
	CStateTlv_setACBrowserForCPRemediation setACBrowserForCPRemediation;
	CStateTlv_setActiveTunnelIndex setActiveTunnelIndex;
	CStateTlv_setAggregateTunnelState setAggregateTunnelState;
	CStateTlv_setMgmtTunSessionState setMgmtTunSessionState;
	CStateTlv_setMgmtTunSessionSubState setMgmtTunSessionSubState;
	CStateTlv_setMgmtTunSGHostName setMgmtTunSGHostName;
	CStateTlv_SetMUSHostAddr SetMUSHostAddr;
	CStateTlv_SetMUSStatus SetMUSStatus;
	CStateTlv_setNetCtrlState setNetCtrlState;
	CStateTlv_setNetEnvState setNetEnvState;
	CStateTlv_setNetType setNetType;
	CStateTlv_setSessionState setSessionState;
	CStateTlv_setSessionSubState setSessionSubState;
	CStateTlv_setTunnelCount setTunnelCount;
	CStateTlv_setUserTunnelStateOnly setUserTunnelStateOnly;

public:
	CStateTlv(CModuleWrapper* moduleWrapper);
	virtual ~CStateTlv();

	BOOL ConstructInstance();
	virtual BOOL PrepareInstance();
	VOID DestructInstance();
};

class CStateTlvDumper : public CDumper {
public:
	CStateTlvDumper(CSkip* destination, CModuleWrapper* moduleWrapper)
		: CDumper(destination, new CStateTlv(moduleWrapper))
	{
	}

	~CStateTlvDumper() {
		delete this->wrappedClass;
	}
};
