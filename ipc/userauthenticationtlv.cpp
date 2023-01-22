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
#include "userauthenticationtlv.h"

UserAuthenticationTlv::UserAuthenticationTlv(CModuleWrapper* moduleWrapper)
	: CIPCClassWrapper(moduleWrapper)
{
	this->constructor = this->moduleWrapper->GetExport<UserAuthenticationTlv_Constructor>(
		"??0UserAuthenticationTlv@@QAE@AAJPAVIIpcResponseCB@@P6AJAAPAVIDataCrypt@@@Z@Z");
	this->destructor = this->moduleWrapper->GetExport<UserAuthenticationTlv_Destructor>(
		"??1UserAuthenticationTlv@@UAE@XZ");
	this->setAggAuthCertificateInfo = this->moduleWrapper->GetExport<UserAuthenticationTlv_setAggAuthCertificateInfo>(
		"?setAggAuthCertificateInfo@UserAuthenticationTlv@@AAEJABVCCertificateInfoTlv@@@Z");
	this->setAggAuthMessage = this->moduleWrapper->GetExport<UserAuthenticationTlv_setAggAuthMessage>(
		"?setAggAuthMessage@UserAuthenticationTlv@@AAEJABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
	this->setAuthData = this->moduleWrapper->GetExport<UserAuthenticationTlv_setAuthData>(
		"?setAuthData@UserAuthenticationTlv@@AAEJABV?$vector@EV?$allocator@E@std@@@std@@@Z");
	this->setAuthID = this->moduleWrapper->GetExport<UserAuthenticationTlv_setAuthID>(
		"?setAuthID@UserAuthenticationTlv@@AAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setAuthToken = this->moduleWrapper->GetExport<UserAuthenticationTlv_setAuthToken>(
		"?setAuthToken@UserAuthenticationTlv@@AAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setBanner = this->moduleWrapper->GetExport<UserAuthenticationTlv_setBanner>(
		"?setBanner@UserAuthenticationTlv@@AAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setCertDER = this->moduleWrapper->GetExport<UserAuthenticationTlv_setCertDER>(
		"?setCertDER@UserAuthenticationTlv@@AAEJABV?$vector@EV?$allocator@E@std@@@std@@@Z");
	this->setCertificateInfo = this->moduleWrapper->GetExport<UserAuthenticationTlv_setCertificateInfo>(
		"?setCertificateInfo@UserAuthenticationTlv@@AAEJABVCCertificateInfoTlv@@@Z");
	this->setCertServerAddress = this->moduleWrapper->GetExport<UserAuthenticationTlv_setCertServerAddress>(
		"?setCertServerAddress@UserAuthenticationTlv@@AAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setCertStoreType = this->moduleWrapper->GetExport<UserAuthenticationTlv_setCertStoreType>(
		"?setCertStoreType@UserAuthenticationTlv@@AAEJI@Z");
	this->setCertType = this->moduleWrapper->GetExport<UserAuthenticationTlv_setCertType>(
		"?setCertType@UserAuthenticationTlv@@AAEJW4USER_AUTH_METHOD@@@Z");
	this->setCredentialsIdentity = this->moduleWrapper->GetExport<UserAuthenticationTlv_setCredentialsIdentity>(
		"?setCredentialsIdentity@UserAuthenticationTlv@@AAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setCredentialsMessage = this->moduleWrapper->GetExport<UserAuthenticationTlv_setCredentialsMessage>(
		"?setCredentialsMessage@UserAuthenticationTlv@@AAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setCredentialsPassword = this->moduleWrapper->GetExport<UserAuthenticationTlv_setCredentialsPassword>(
		"?setCredentialsPassword@UserAuthenticationTlv@@AAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setCredentialsVerifyPassword = this->moduleWrapper->GetExport<UserAuthenticationTlv_setCredentialsVerifyPassword>(
		"?setCredentialsVerifyPassword@UserAuthenticationTlv@@AAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setHashAlg = this->moduleWrapper->GetExport<UserAuthenticationTlv_setHashAlg>(
		"?setHashAlg@UserAuthenticationTlv@@AAEJI@Z");
	this->setHashData = this->moduleWrapper->GetExport<UserAuthenticationTlv_setHashData>(
		"?setHashData@UserAuthenticationTlv@@AAEJABV?$vector@EV?$allocator@E@std@@@std@@@Z");
	this->setPrimarySGIPAddress = this->moduleWrapper->GetExport<UserAuthenticationTlv_setPrimarySGIPAddress>(
		"?setPrimarySGIPAddress@UserAuthenticationTlv@@AAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setProfileHash = this->moduleWrapper->GetExport<UserAuthenticationTlv_setProfileHash>(
		"?setProfileHash@UserAuthenticationTlv@@AAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setProfileURI = this->moduleWrapper->GetExport<UserAuthenticationTlv_setProfileURI>(
		"?setProfileURI@UserAuthenticationTlv@@AAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setSecondarySGIPAddress = this->moduleWrapper->GetExport<UserAuthenticationTlv_setSecondarySGIPAddress>(
		"?setSecondarySGIPAddress@UserAuthenticationTlv@@AAEJABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@Z");
	this->setStatusCode = this->moduleWrapper->GetExport<UserAuthenticationTlv_setStatusCode>(
		"?setStatusCode@UserAuthenticationTlv@@AAEJJ@Z");
	this->setUserAcceptedBannerResult = this->moduleWrapper->GetExport<UserAuthenticationTlv_setUserAcceptedBannerResult>(
		"?setUserAcceptedBannerResult@UserAuthenticationTlv@@AAEJ_N@Z");
	this->setUserAuthType = this->moduleWrapper->GetExport<UserAuthenticationTlv_setUserAuthType>(
		"?setUserAuthType@UserAuthenticationTlv@@AAEJW4USERAUTHTYPE@1@@Z");
}

UserAuthenticationTlv::~UserAuthenticationTlv() {
}

BOOL UserAuthenticationTlv::ConstructInstance() {
	LONG32 lErrorCode = 0;

	if (this->realInstance == NULL) {
		return FALSE;
	}

	this->constructor(this->realInstance, &lErrorCode, (PVOID)0xffffffff, (PVOID)UserAuthenticationTlv::Callback);

	return (lErrorCode == 0);
}

BOOL UserAuthenticationTlv::PrepareInstance() {
	if (this->realInstance == NULL) {
		return FALSE;
	}

	CCertificateInfoTlv* certificateInfoParam = new CCertificateInfoTlv(this->moduleWrapper);
	
	if (certificateInfoParam->ConstructInstance() == FALSE || certificateInfoParam->PrepareInstance() == FALSE) {
		return FALSE;
	}
	
	if (this->setAggAuthCertificateInfo(this->realInstance, certificateInfoParam->GetInstance()) != 0) {
		return FALSE;
	}
	if (this->setCertificateInfo(this->realInstance, certificateInfoParam->GetInstance()) != 0) {
		return FALSE;
	}
	
	certificateInfoParam->DestructInstance();
	delete certificateInfoParam;
	
	if (this->setAggAuthMessage(this->realInstance, &paramSTRING8) != 0) {
		return FALSE;
	}
	if (this->setAuthData(this->realInstance, &paramUINT8Vector) != 0) {
		return FALSE;
	}
	if (this->setAuthID(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setAuthToken(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setBanner(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setCertDER(this->realInstance, &paramUINT8Vector) != 0) {
		return FALSE;
	}
	if (this->setCertServerAddress(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setCertStoreType(this->realInstance, paramUINT32) != 0) {
		return FALSE;
	}
	if (this->setCertType(this->realInstance, USER_AUTH_METHOD_TODO) != 0) {
		return FALSE;
	}
	if (this->setCredentialsIdentity(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setCredentialsMessage(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setCredentialsPassword(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setCredentialsVerifyPassword(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setHashAlg(this->realInstance, paramUINT32) != 0) {
		return FALSE;
	}
	if (this->setHashData(this->realInstance, &paramUINT8Vector) != 0) {
		return FALSE;
	}
	if (this->setPrimarySGIPAddress(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setProfileHash(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setProfileURI(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setSecondarySGIPAddress(this->realInstance, &paramSTRING16) != 0) {
		return FALSE;
	}
	if (this->setStatusCode(this->realInstance, paramLONG32) != 0) {
		return FALSE;
	}
	if (this->setUserAcceptedBannerResult(this->realInstance, TRUE) != 0) {
		return FALSE;
	}
	if (this->setUserAuthType(this->realInstance, USER_AUTH_TYPE_AGG_AUTH_CERT_THUMBPRINT) != 0) {
		return FALSE;
	}

	return TRUE;
}

VOID UserAuthenticationTlv::DestructInstance() {
	if (this->realInstance != NULL) {
		this->destructor(this->realInstance);
	}
}

LONG __cdecl UserAuthenticationTlv::Callback(UINT32 dataCrypt) {
	return 0;
}