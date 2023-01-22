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
 * Because I had more time than sense (yay for waiting on deliveries!), decided to find out which statistis categories,
 * sub-categories, and types there are. Note that the enumeration field names may not match exactly what would be the
 * actual names in CAC's code, and there will be for sure missing entries. A specific statistic code/identifier is
 * calculated as follows (see CExtensibleStats::StatCode):
 * 
 * - (STAT_CATEGORY << 0x08 | STAT_SUB_CATEGORY) << 0x10 | STAT_TYPE
 * 
 * To get the STAT_CATEGORY from the identifier one has to calculate (CExtensibleStats::StatCategoryFromCode):
 *
 * - Code >> 0x18
 * 
 * To get the STAT_SUB_CATEGORY from the identifier (CExtensibleStats::STAT_SUB_CATEGORYFromCode):
 * 
 * - Code >> 0x10 & 0xff
 *
 * To get the STAT_TYPE from the identifier (CExtensibleStats::StatTypeFromCode):
 * 
 * - Code & 0xffff
 * 
 * The values for this enumeration come from CExtensibleStats::GetAggregatedStat, CExtensibleStats::GetUserVisibleStat,
 * and CExtensibleStats::GetStat functions.
 */ 
enum STAT_CATEGORY {
	STAT_CATEGORY_DEAULT = 0x00,
	STAT_CATEGORY_USER_VISIBLE = 0x01,
	STAT_CATEGORY_AGGREGATED = 0x02,
};

/**
 * In vpnagent.exe, found a class called CSslProtocol that has a function that adds statistics with a value of 0x04, so
 * the assumption is that 0x04 is for the SSL sub-category. There is also the CDtlsProtocol class that adds statistics
 * this time with 0x05.
 * 
 * When retrieving aggregated statistics, CAC uses STAT_CATEGORY=0x02 and StaSubCategory=0x07. Didn't find any other
 * reference to these values so the assumption is that they're used exclusively for the aggregated statistics.
 */
enum STAT_SUB_CATEGORY {
	STAT_SUB_CATEGORY_SSL = 0x04,
	STAT_SUB_CATEGORY_DTLS = 0x05,
	STAT_SUB_CATEGORY_AGGREGATED = 0x07,
};

enum STAT_TYPE {
	STAT_TYPE_ENCRYPTED_BYTES_SENT = 0x01,
	STAT_TYPE_ENCRYPTED_BYTES_RECEIVED = 0x02,
	STAT_TYPE_ENCRYPTED_PACKETS_SENT = 0x03,
	STAT_TYPE_ENCRYPTED_PACKETS_RECEIVED = 0x04,
	STAT_TYPE_BYTES_SENT = 0x05,
	STAT_TYPE_BYTES_RECEIVED = 0x06,
	STAT_TYPE_PACKETS_SENT = 0x07,
	STAT_TYPE_PACKETS_RECEIVED = 0x08,
	STAT_TYPE_CONTROL_BYTES_SENT = 0x09,
	STAT_TYPE_CONTROL_BYTES_RECEIVED = 0x0a,
	STAT_TYPE_CONTROL_PACKETS_SENT = 0x0b,
	STAT_TYPE_CONTROL_PACKETS_RECEIVED = 0x0c,
	STAT_TYPE_COMPRESSED_BYTES_SENT = 0x0d,
	STAT_TYPE_COMPRESSED_BYTES_RECEIVED = 0x0e,
	STAT_TYPE_COMPRESSED_PACKETS_SENT = 0x0f,
	STAT_TYPE_COMPRESSED_PACKETS_RECEIVED = 0x10,
	STAT_TYPE_INBOUND_DISCARDED = 0x11,
	STAT_TYPE_OUTBOUND_DISCARDED = 0x12,
	STAT_TYPE_INBOUND_BYPASSED = 0x13,
	STAT_TYPE_OUTBOUND_BYPASSED = 0x14,
	STAT_TYPE_TIME_CONNECTED = 0x15,
	STAT_TYPE_SESSION_DISCONNECT = 0x16,
};

typedef PVOID(__thiscall* CExtensibleStats_Constructor)(PVOID, PLONG32);
typedef VOID(__thiscall* CExtensibleStats_Destructor)(PVOID);
typedef VOID(__thiscall* CExtensibleStats_AddStat)(PVOID, STAT_SUB_CATEGORY, STAT_TYPE, UINT64);
typedef VOID(__thiscall* CExtensibleStats_AddUserVisibleStat)(PVOID, STAT_SUB_CATEGORY, STAT_TYPE, UINT64);

/**
 * It seems this structure is used to keep tabs on the statistics added - likely CAC is using some sort of linked list
 * or markers for the beginning/last of each statistics category. Haven't confirmed how it works as it isn't really
 * necessary for the purposes of this tool but still worth while documenting.
 * 
 * Note that when this structure is allocated, CAC doesn't seem to zero the memory out before using. So there might be
 * data from previous memory allocations in the last member of the structure. CAC allocates 0x20 bytes for this
 * structure but only seems to use 0x0e (would need digging deeper to confirm).
 */
typedef struct _CEXTENSBLESTATS_UNKNOWN2 {
	UINT32	unknown1;		// 0x00
	UINT32	unknown2;		// 0x04
	UINT32	unknown3;		// 0x08
	UINT16	unknown4;		// 0x0c
	UINT8	unknown5[12];	// 0x0e
} CEXTENSBLESTATS_UNKNOWN2, *PCEXTENSBLESTATS_UNKNOWN2;

typedef struct _CEXTENSBLESTATS_UNKNOWN1 {
	PCEXTENSBLESTATS_UNKNOWN2	unknown1;			// 0x00
	UINT32						statisticsCount;	// 0x04
} CEXTENSBLESTATS_UNKNOWN1, *PCEXTENSBLESTATS_UNKNOWN1;

/**
 * Each statistic value is a 64 bits integer. Looking at the function CExtensibleStats::getStat,
 * CExtensibleStats::DeSerialize, and CExtensibleStats::GetSerialized, it seems the statistics are serialized following
 * the format:
 * 
 * <statistics>	::= <statistic>[<statistic>...]
 * <statistic>	::= <code (4 bytes)><unknown (4 bytes)><value (8 bytes)>
 */
typedef struct _CEXTENSBLESTATS {
	PCEXTENSBLESTATS_UNKNOWN1	unknown1;	// 0x00
	PVOID						unknown2;	// 0x04
} CEXTENSBLESTATS, *PCEXTENSBLESTATS;

class CExtensibleStats : public CClassWrapper<CEXTENSBLESTATS> {
protected:
	CExtensibleStats_Constructor constructor;
	CExtensibleStats_Destructor destructor;
	CExtensibleStats_AddStat addStat;
	CExtensibleStats_AddUserVisibleStat addUserVisibleStat;

public:
	CExtensibleStats(CModuleWrapper* moduleWrapper);
	virtual ~CExtensibleStats();

	BOOL ConstructInstance();
	virtual BOOL PrepareInstance();
	VOID DestructInstance();
};
