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

/**
 *
 */
enum USER_AUTH_TYPE {
	USER_AUTH_TYPE_AGG_AUTH = 0x01,
	USER_AUTH_TYPE_EAP_CREDENTIALS = 0x02,
	USER_AUTH_TYPE_CERT_THUMBPRINT = 0x03,
	USER_AUTH_TYPE_CERT_SIGNING = 0x04,
	USER_AUTH_TYPE_AUTH_COMPLETE = 0x05,
	USER_AUTH_TYPE_SERVER_CERT = 0x06,
	USER_AUTH_TYPE_AGG_AUTH_CERT_THUMBPRINT = 0x07
};

typedef PVOID(__thiscall* UserAuthenticationTlv_Constructor)(PVOID, PLONG32, PVOID, PVOID);
typedef VOID(__thiscall* UserAuthenticationTlv_Destructor)(PVOID);
typedef LONG(__thiscall* UserAuthenticationTlv_setAggAuthCertificateInfo)(PVOID, PCERTIFICATEINFOTLV);
typedef LONG(__thiscall* UserAuthenticationTlv_setAggAuthMessage)(PVOID, PSTRING8);
typedef LONG(__thiscall* UserAuthenticationTlv_setAuthData)(PVOID, PVECTOR);
typedef LONG(__thiscall* UserAuthenticationTlv_setAuthID)(PVOID, PSTRING16);
typedef LONG(__thiscall* UserAuthenticationTlv_setAuthToken)(PVOID, PSTRING16);
typedef LONG(__thiscall* UserAuthenticationTlv_setBanner)(PVOID, PSTRING16);
typedef LONG(__thiscall* UserAuthenticationTlv_setCertDER)(PVOID, PVECTOR);
typedef LONG(__thiscall* UserAuthenticationTlv_setCertificateInfo)(PVOID, PCERTIFICATEINFOTLV);
typedef LONG(__thiscall* UserAuthenticationTlv_setCertServerAddress)(PVOID, PSTRING16);
typedef LONG(__thiscall* UserAuthenticationTlv_setCertStoreType)(PVOID, UINT32);
typedef LONG(__thiscall* UserAuthenticationTlv_setCertType)(PVOID, USER_AUTH_METHOD);
typedef LONG(__thiscall* UserAuthenticationTlv_setCredentialsIdentity)(PVOID, PSTRING16);
typedef LONG(__thiscall* UserAuthenticationTlv_setCredentialsMessage)(PVOID, PSTRING16);
typedef LONG(__thiscall* UserAuthenticationTlv_setCredentialsPassword)(PVOID, PSTRING16);
typedef LONG(__thiscall* UserAuthenticationTlv_setCredentialsVerifyPassword)(PVOID, PSTRING16);
typedef LONG(__thiscall* UserAuthenticationTlv_setHashAlg)(PVOID, UINT32);
typedef LONG(__thiscall* UserAuthenticationTlv_setHashData)(PVOID, PVECTOR);
typedef LONG(__thiscall* UserAuthenticationTlv_setPrimarySGIPAddress)(PVOID, PSTRING16);
typedef LONG(__thiscall* UserAuthenticationTlv_setProfileHash)(PVOID, PSTRING16);
typedef LONG(__thiscall* UserAuthenticationTlv_setProfileURI)(PVOID, PSTRING16);
typedef LONG(__thiscall* UserAuthenticationTlv_setSecondarySGIPAddress)(PVOID, PSTRING16);
typedef LONG(__thiscall* UserAuthenticationTlv_setStatusCode)(PVOID, LONG32);
typedef LONG(__thiscall* UserAuthenticationTlv_setUserAcceptedBannerResult)(PVOID, BOOL);
typedef LONG(__thiscall* UserAuthenticationTlv_setUserAuthType)(PVOID, USER_AUTH_TYPE);


class UserAuthenticationTlv : public CIPCClassWrapper {
protected:
	UserAuthenticationTlv_Constructor constructor;
	UserAuthenticationTlv_Destructor destructor;
	UserAuthenticationTlv_setAggAuthCertificateInfo setAggAuthCertificateInfo;
	UserAuthenticationTlv_setAggAuthMessage setAggAuthMessage;
	UserAuthenticationTlv_setAuthData setAuthData;
	UserAuthenticationTlv_setAuthID setAuthID;
	UserAuthenticationTlv_setAuthToken setAuthToken;
	UserAuthenticationTlv_setBanner setBanner;
	UserAuthenticationTlv_setCertDER setCertDER;
	UserAuthenticationTlv_setCertificateInfo setCertificateInfo;
	UserAuthenticationTlv_setCertServerAddress setCertServerAddress;
	UserAuthenticationTlv_setCertStoreType setCertStoreType;
	UserAuthenticationTlv_setCertType setCertType;
	UserAuthenticationTlv_setCredentialsIdentity setCredentialsIdentity;
	UserAuthenticationTlv_setCredentialsMessage setCredentialsMessage;
	UserAuthenticationTlv_setCredentialsPassword setCredentialsPassword;
	UserAuthenticationTlv_setCredentialsVerifyPassword setCredentialsVerifyPassword;
	UserAuthenticationTlv_setHashAlg setHashAlg;
	UserAuthenticationTlv_setHashData setHashData;
	UserAuthenticationTlv_setPrimarySGIPAddress setPrimarySGIPAddress;
	UserAuthenticationTlv_setProfileHash setProfileHash;
	UserAuthenticationTlv_setProfileURI setProfileURI;
	UserAuthenticationTlv_setSecondarySGIPAddress setSecondarySGIPAddress;
	UserAuthenticationTlv_setStatusCode setStatusCode;
	UserAuthenticationTlv_setUserAcceptedBannerResult setUserAcceptedBannerResult;
	UserAuthenticationTlv_setUserAuthType setUserAuthType;

private:
	static LONG __cdecl Callback(UINT32 dataCrypt);

public:
	UserAuthenticationTlv(CModuleWrapper* moduleWrapper);
	virtual ~UserAuthenticationTlv();

	BOOL ConstructInstance();
	virtual BOOL PrepareInstance();
	VOID DestructInstance();
};

class UserAuthenticationTlvDumper : public CDumper {
public:
	UserAuthenticationTlvDumper(CSkip* destination, CModuleWrapper* moduleWrapper)
		: CDumper(destination, new UserAuthenticationTlv(moduleWrapper))
	{
	}

	~UserAuthenticationTlvDumper() {
		delete this->wrappedClass;
	}
};
