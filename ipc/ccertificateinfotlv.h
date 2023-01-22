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

typedef PVOID(__thiscall* CCertificateInfoTlv_Constructor)(PVOID);
typedef VOID(__thiscall* CCertificateInfoTlv_Destructor)(PVOID);
typedef LONG(__thiscall* CCertificateInfoTlv_SetCertAuthSignatureBase64)(PVOID, PSTRING16);
typedef LONG(__thiscall* CCertificateInfoTlv_SetCertAuthSignatureHashAlg)(PVOID, PSTRING16);
typedef LONG(__thiscall* CCertificateInfoTlv_SetCertBase64)(PVOID, PSTRING16);
typedef LONG(__thiscall* CCertificateInfoTlv_SetCertExchangedViaProtocol)(PVOID, PBOOL);
typedef LONG(__thiscall* CCertificateInfoTlv_SetCertFormat)(PVOID, PSTRING16);
typedef LONG(__thiscall* CCertificateInfoTlv_SetCertPKCS7)(PVOID, PVECTOR);
typedef LONG(__thiscall* CCertificateInfoTlv_SetCertStore)(PVOID, PUINT32);
typedef LONG(__thiscall* CCertificateInfoTlv_SetCertStoreMultiCertAuth)(PVOID, PSTRING16);
typedef LONG(__thiscall* CCertificateInfoTlv_SetContainerName)(PVOID, PSTRING16);
typedef LONG(__thiscall* CCertificateInfoTlv_SetFromSmartcard)(PVOID, PBOOL);
typedef LONG(__thiscall* CCertificateInfoTlv_SetKSPName)(PVOID, PSTRING16);
typedef LONG(__thiscall* CCertificateInfoTlv_SetProviderName)(PVOID, PSTRING16);
typedef LONG(__thiscall* CCertificateInfoTlv_SetProviderType)(PVOID, PUINT32);
typedef LONG(__thiscall* CCertificateInfoTlv_SetReaderName)(PVOID, PSTRING16);
typedef LONG(__thiscall* CCertificateInfoTlv_SetThumbprint)(PVOID, PSTRING16);

typedef struct _CCERTIFICATEINFOTLV {
	PVOID	vftableCTLV;					// 0x00
	UINT32	unknown1;						// 0x04
	PVOID	vftableCOpaqueDataAccessorBase;	// 0x08
	UINT32	unknown2;						// 0x0c
} CCERTIFICATEINFOTLV, *PCERTIFICATEINFOTLV;

class CCertificateInfoTlv : public CClassWrapper<CCERTIFICATEINFOTLV> {
protected:
	CCertificateInfoTlv_Constructor constructor;
	CCertificateInfoTlv_Destructor destructor;
	CCertificateInfoTlv_SetCertAuthSignatureBase64 setCertAuthSignatureBase64;
	CCertificateInfoTlv_SetCertAuthSignatureHashAlg setCertAuthSignatureHashAlg;
	CCertificateInfoTlv_SetCertBase64 setCertBase64;
	CCertificateInfoTlv_SetCertExchangedViaProtocol setCertExchangedViaProtocol;
	CCertificateInfoTlv_SetCertFormat setCertFormat;
	CCertificateInfoTlv_SetCertPKCS7 setCertPKCS7;
	CCertificateInfoTlv_SetCertStore setCertStore;
	CCertificateInfoTlv_SetCertStoreMultiCertAuth setCertStoreMultiCertAuth;
	CCertificateInfoTlv_SetContainerName setContainerName;
	CCertificateInfoTlv_SetFromSmartcard setFromSmartcard;
	CCertificateInfoTlv_SetKSPName setKSPName;
	CCertificateInfoTlv_SetProviderName setProviderName;
	CCertificateInfoTlv_SetProviderType setProviderType;
	CCertificateInfoTlv_SetReaderName setReaderName;
	CCertificateInfoTlv_SetThumbprint setThumbprint;

public:
	CCertificateInfoTlv(CModuleWrapper* moduleWrapper);
	virtual ~CCertificateInfoTlv();

	BOOL ConstructInstance();
	virtual BOOL PrepareInstance();
	VOID DestructInstance();
};
