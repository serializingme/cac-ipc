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
#include "ccertificateinfotlv.h"

CCertificateInfoTlv::CCertificateInfoTlv(CModuleWrapper* moduleWrapper)
	: CClassWrapper(moduleWrapper)
{
	this->constructor = this->moduleWrapper->GetExport<CCertificateInfoTlv_Constructor>(
		"??0CCertificateInfoTlv@@QAE@XZ");
	this->destructor = this->moduleWrapper->GetExport<CCertificateInfoTlv_Destructor>(
		"??1CCertificateInfoTlv@@UAE@XZ");
	this->setCertAuthSignatureBase64 = this->moduleWrapper->GetExport<CCertificateInfoTlv_SetCertAuthSignatureBase64>(
		"?SetCertAuthSignatureBase64@CCertificateInfoTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setCertAuthSignatureHashAlg = this->moduleWrapper->GetExport<CCertificateInfoTlv_SetCertAuthSignatureHashAlg>(
		"?SetCertAuthSignatureHashAlg@CCertificateInfoTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setCertBase64 = this->moduleWrapper->GetExport<CCertificateInfoTlv_SetCertBase64>(
		"?SetCertBase64@CCertificateInfoTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setCertExchangedViaProtocol = this->moduleWrapper->GetExport<CCertificateInfoTlv_SetCertExchangedViaProtocol>(
		"?SetCertExchangedViaProtocol@CCertificateInfoTlv@@QAEJ_N@Z");
	this->setCertFormat = this->moduleWrapper->GetExport<CCertificateInfoTlv_SetCertFormat>(
		"?SetCertFormat@CCertificateInfoTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setCertPKCS7 = this->moduleWrapper->GetExport<CCertificateInfoTlv_SetCertPKCS7>(
		"?SetCertPKCS7@CCertificateInfoTlv@@QAEJABV?$vector@EV?$allocator@E@std@@@std@@@Z");
	this->setCertStore = this->moduleWrapper->GetExport<CCertificateInfoTlv_SetCertStore>(
		"?SetCertStore@CCertificateInfoTlv@@QAEJABI@Z");
	this->setCertStoreMultiCertAuth = this->moduleWrapper->GetExport<CCertificateInfoTlv_SetCertStoreMultiCertAuth>(
		"?SetCertStoreMultiCertAuth@CCertificateInfoTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setContainerName = this->moduleWrapper->GetExport<CCertificateInfoTlv_SetContainerName>(
		"?SetContainerName@CCertificateInfoTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setFromSmartcard = this->moduleWrapper->GetExport<CCertificateInfoTlv_SetFromSmartcard>(
		"?SetFromSmartcard@CCertificateInfoTlv@@QAEJ_N@Z");
	this->setKSPName = this->moduleWrapper->GetExport<CCertificateInfoTlv_SetKSPName>(
		"?SetKSPName@CCertificateInfoTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setProviderName = this->moduleWrapper->GetExport<CCertificateInfoTlv_SetProviderName>(
		"?SetProviderName@CCertificateInfoTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setProviderType = this->moduleWrapper->GetExport<CCertificateInfoTlv_SetProviderType>(
		"?SetProviderType@CCertificateInfoTlv@@QAEJABK@Z");
	this->setReaderName = this->moduleWrapper->GetExport<CCertificateInfoTlv_SetReaderName>(
		"?SetReaderName@CCertificateInfoTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setThumbprint = this->moduleWrapper->GetExport<CCertificateInfoTlv_SetThumbprint>(
		"?SetThumbprint@CCertificateInfoTlv@@QAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");

	this->realInstance = AllocateMemory<CCERTIFICATEINFOTLV>();
}

CCertificateInfoTlv::~CCertificateInfoTlv() {
	if (this->realInstance != NULL) {
		FreeMemory<CCERTIFICATEINFOTLV>(this->realInstance);
	}

	this->realInstance = NULL;
}

BOOL CCertificateInfoTlv::ConstructInstance() {
	if (this->realInstance == NULL) {
		return FALSE;
	}

	this->constructor(this->realInstance);
	
	return TRUE;
}

BOOL CCertificateInfoTlv::PrepareInstance() {
	if (this->realInstance == NULL) {
		return FALSE;
	}

	if (this->setCertAuthSignatureBase64(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setCertAuthSignatureHashAlg(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setCertBase64(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setCertExchangedViaProtocol(this->realInstance, &paramBOOL) != 0) {
		return FALSE;
	}
	if (this->setCertFormat(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setCertPKCS7(this->realInstance, &paramUINT8Vector) != 0) {
		return FALSE;
	}
	if (this->setCertStore(this->realInstance, &paramUINT32) != 0) {
		return FALSE;
	}
	if (this->setCertStoreMultiCertAuth(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setContainerName(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setFromSmartcard(this->realInstance, &paramBOOL) != 0) {
		return FALSE;
	}
	if (this->setKSPName(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setProviderName(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setProviderType(this->realInstance, &paramUINT32) != 0) {
		return FALSE;
	}
	if (this->setReaderName(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setThumbprint(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}

	return TRUE;
}

VOID CCertificateInfoTlv::DestructInstance() {
	if (this->realInstance != NULL) {
		this->destructor(this->realInstance);
	}
}