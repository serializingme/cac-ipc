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
#include "cextensiblestats.h"

CExtensibleStats::CExtensibleStats(CModuleWrapper* moduleWrapper)
	: CClassWrapper(moduleWrapper)
{
	this->constructor = this->moduleWrapper->GetExport<CExtensibleStats_Constructor>(
		"??0CExtensibleStats@@QAE@AAJ@Z");
	this->destructor = this->moduleWrapper->GetExport<CExtensibleStats_Destructor>(
		"??1CExtensibleStats@@QAE@XZ");
	this->addStat = this->moduleWrapper->GetExport<CExtensibleStats_AddStat>(
		"?AddStat@CExtensibleStats@@QAEXW4StatSubCategory@@W4StatType@@_K@Z");
	this->addUserVisibleStat = this->moduleWrapper->GetExport<CExtensibleStats_AddUserVisibleStat>(
		"?AddUserVisibleStat@CExtensibleStats@@QAEXW4StatSubCategory@@W4StatType@@_K@Z");

	this->realInstance = AllocateMemory<CEXTENSBLESTATS>();
}

CExtensibleStats::~CExtensibleStats() {
	if (this->realInstance != NULL) {
		FreeMemory<CEXTENSBLESTATS>(this->realInstance);
	}

	this->realInstance = NULL;
}

BOOL CExtensibleStats::ConstructInstance() {
	LONG32 lError = 0;

	if (this->realInstance == NULL) {
		return FALSE;
	}

	this->constructor(this->realInstance, &lError);

	if (lError != 0) {
		return FALSE;
	}
	
	return TRUE;
}

BOOL CExtensibleStats::PrepareInstance() {
	if (this->realInstance == NULL) {
		return FALSE;
	}

	this->addStat(this->realInstance, STAT_SUB_CATEGORY_SSL, STAT_TYPE_BYTES_RECEIVED, paramUINT64);
	this->addStat(this->realInstance, STAT_SUB_CATEGORY_SSL, STAT_TYPE_BYTES_SENT, paramUINT64);
	this->addStat(this->realInstance, STAT_SUB_CATEGORY_DTLS, STAT_TYPE_COMPRESSED_BYTES_RECEIVED, paramUINT64);
	this->addStat(this->realInstance, STAT_SUB_CATEGORY_DTLS, STAT_TYPE_COMPRESSED_BYTES_SENT, paramUINT64);
	this->addUserVisibleStat(this->realInstance, STAT_SUB_CATEGORY_AGGREGATED, STAT_TYPE_COMPRESSED_BYTES_RECEIVED, paramUINT64);
	this->addUserVisibleStat(this->realInstance, STAT_SUB_CATEGORY_AGGREGATED, STAT_TYPE_COMPRESSED_BYTES_SENT, paramUINT64);

	return TRUE;
}

VOID CExtensibleStats::DestructInstance() {
	if (this->realInstance != NULL) {
		this->destructor(this->realInstance);
	}
}