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
#include "generator.h"

INT main()
{
	DWORD errorCode = 0;
	
	CModuleWrapper vpnCommon(TEXT("C:\\Program Files (x86)\\Cisco\\Cisco AnyConnect Secure Mobility Client"),
		TEXT("vpncommon.dll"), &errorCode);
	
	if (errorCode != 0) {
		return errorCode;
	}
	
	CWinSockWrapper winSockWrapper(&errorCode);
	
	if (errorCode != 0) {
		return errorCode;
	}
	
	CWinSockServer winSockServer(&errorCode, TEXT("127.0.0.2"), 62522);
	
	if (errorCode != 0) {
		return errorCode;
	}
	
	CWinSockClient winSockClient(&errorCode, TEXT("127.0.0.2"), 62522);
	
	if (errorCode != 0) {
		return errorCode;
	}
	
	CDumper* dumpers[] = {
		new CAcknowledgeDumper(&winSockClient, &vpnCommon), new CApiCommandTlvDumper(&winSockClient, &vpnCommon),
		new CCertificateAuthTlvDumper(&winSockClient, &vpnCommon), new CConnectFailureTlvDumper(&winSockClient, &vpnCommon),
		new CConnectIfcDataTLVDumper(&winSockClient, &vpnCommon), new CDnldrArgsTlvDumper(&winSockClient, &vpnCommon),
		new CKeyExchangeTLVDumper(&winSockClient, &vpnCommon), new CIpcClosingTlvDumper(&winSockClient, &vpnCommon),
		new CLaunchClientAppTlvDumper(&winSockClient, &vpnCommon), new CLocalLANDumper(&winSockClient, &vpnCommon),
		new CMessageTypeBitmapTlvDumper(&winSockClient, &vpnCommon), new CNotifyAgentPreTunnelTlvDumper(&winSockClient, &vpnCommon),
		new CPreferenceUpdateTlvDumper(&winSockClient, &vpnCommon), new CProxyAuthenticationDumper(&winSockClient, &vpnCommon),
		new CRedirectTlvDumper(&winSockClient, &vpnCommon), new CRequestDnldrArgsTlvDumper(&winSockClient, &vpnCommon),
		new CSessionCommandTlvDumper(&winSockClient, &vpnCommon), new CSessionInfoTlvDumper(&winSockClient, &vpnCommon),
		new CStartParametersDumper(&winSockClient, &vpnCommon), new CStateTlvDumper(&winSockClient, &vpnCommon),
		new CStatisticsTlvDumper(&winSockClient, &vpnCommon), new CTerminateTlvDumper(&winSockClient, &vpnCommon),
		new CUserMessageTlvDumper(&winSockClient, &vpnCommon), new NotifyAgentTlvDumper(&winSockClient, &vpnCommon),
		new SCEPTlvDumper(&winSockClient, &vpnCommon), new UserAuthenticationTlvDumper(&winSockClient, &vpnCommon)
	};
	
	for (UINT8 index = 0; index < ARRAYSIZE(dumpers); ++index) {
		CDumper* current = dumpers[index];
		
		if (current->DumpMessage() == FALSE) {
			// TODO: Add some sort of error reporting
		}
	
		delete current;
	}

	return 0;
}
