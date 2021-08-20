/** @file
  BT Types declarations.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef BT_TYPES_H
#define BT_TYPES_H

#include "osa_types.h"

typedef struct
{
	UINT16 length;
	UINT16 offset;
	UINT8 data[0];
} buffer_t;

typedef struct
{
#define UUID_NULL_LEN		0
#define UUID_16BIT_TYPE_LEN	2
#define UUID_32BIT_TYPE_LEN	4
#define UUID_128BIT_TYPE_LEN	16
	UINT8 length;
	union
	{
		UINT16 	uuid16;
		UINT32 	uuid32;
		UINT8	uuid128[UUID_128BIT_TYPE_LEN];
	}value;
} uuid_t;

#define UUID_NULL_VALUE		0x0000 /* Special UUID value */

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE  1
#endif

#define HCI_CMD_PREAMBLE_SIZE 	3
#define HCI_EVT_PREAMBLE_SIZE 	2
#define HCI_ACL_PREAMBLE_SIZE   4 /* 2 bytes : acl handle + flags, 2 bytes: length */
#define UART_HDR_SIZE 			1
#define HCI_CMD_EVT_MAX_SIZE    255 /* FIXME: Is this correct? Shouldn't this be dynamic? */
#define L2CAP_HDR_SIZE 			4

#define JUMP_UART_HEADER(buf) {buf+=UART_HDR_SIZE;}
#define JUMP_HCI_HEADER(buf) {buf+=HCI_CMD_PREAMBLE_SIZE;}
#define JUMP_CUSTOM_LEN(buf,len) {buf+=len;}
#define JUMP_BDADDR(buf){buf+= BD_ADDR_LEN;}

#ifndef BD_ADDR_LEN
#define BD_ADDR_LEN 6
#endif
#ifndef BD_ADDR_STR_LEN
#define BD_ADDR_STR_LEN 20
#endif


#define CONVERT_U16_TO_STREAM(p, u16) { \
		*(p) = (UINT8)((u16) & 0xFF); \
		*(p+1) = (UINT8)((u16)>> 8 ) & 0xFF; \
		(p)+= 2; \
}

#define CONVERT_U8_TO_STREAM(p, u8) { \
	*(p) = (UINT8)u8; \
	(p)+= 1; \
}

#define CONVERT_ARRAY8_TO_STREAM(p, a) { \
	UINT8 pqr = 8; \
	while(pqr) { \
		*(p)++ = (UINT8)(a[pqr-1]); \
		pqr--; \
	} \
}
#define CONVERT_ARRAY_TO_STREAM(p, a, len) { \
	UINT16 pqr = len; \
	while(pqr) { \
		*(p + pqr -1) = a[pqr -1]; \
		pqr--; \
	} \
	(p) += len; \
}

#define CONVERT_REV_ARRAY_TO_STREAM(p, a, len) { \
	UINT16 pqr = len; \
	while(pqr) { \
		*(p)++ = a[pqr -1]; \
		pqr--; \
	} \
}

#define CONVERT_STREAM_TO_U16(u16, p) { \
	u16 = 0; \
	u16 |= ((UINT16)*((p))); \
	u16 |= ((UINT16)*((p) +1)) << 8; \
	(p) += 2; \
}

#define CONVERT_STREAM_TO_U8(u8, p) { \
	u8 = 0; \
	u8 = *((p));\
	(p)+= 1;\
}

#define CONVERT_STREAM_TO_I8(i8, p) { \
	i8 = 0; \
	i8 = *((p));\
	(p)+= 1;\
}

#define CONVERT_STREAM_TO_BDADDR(a, p) { \
	UINT8 *abc = (UINT8 *)a; \
	UINT8 pqr = BD_ADDR_LEN; \
	while(pqr) { \
	*(abc + pqr-1) = *p++; \
	pqr--; \
	} \
}

#define CONVERT_STREAM_TO_ARRAY(a, p,len) { \
		UINT16 pqr = 0; \
		while(pqr < len) { \
			a[pqr] = *(p+pqr); \
			pqr++; \
		} \
}

#define CONVERT_REVERSE_STREAM_TO_ARRAY(a, p, len)	{\
	UINT16 pqr = len; \
	while(pqr > 0){ \
		a[--pqr] = *p++; \
	} \
}

#define UINT32_TO_STREAM(p, u32) {*(p)++ = (UINT8)(u32); *(p)++ = (UINT8)((u32) >> 8); *(p)++ = (UINT8)((u32) >> 16); *(p)++ = (UINT8)((u32) >> 24);}
#define STREAM_TO_UINT32(u32, p) {u32 = (((UINT32)(*(p))) + ((((UINT32)(*((p) + 1)))) << 8) + ((((UINT32)(*((p) + 2)))) << 16) + ((((UINT32)(*((p) + 3)))) << 24)); (p) += 4;}

#define UINT16_TO_STREAM(p, u16) CONVERT_U16_TO_STREAM (p, u16)
#define UINT8_TO_STREAM(p, u8)   CONVERT_U8_TO_STREAM(p, u8)
#define ARRAY8_TO_STREAM(p, a)   CONVERT_ARRAY8_TO_STREAM (p, a)
#define ARRAY_TO_STREAM(p, a, len) CONVERT_ARRAY_TO_STREAM(p, a, len)
#define REVERSE_ARRAY_TO_STREAM(p, a, len)  CONVERT_REV_ARRAY_TO_STREAM(p, a, len)

#define STREAM_TO_UINT8(u8, p)     CONVERT_STREAM_TO_U8(u8, p)
#define STREAM_TO_INT8(i8, p)      CONVERT_STREAM_TO_I8(i8, p)
#define STREAM_TO_UINT16(u16, p)   CONVERT_STREAM_TO_U16 (u16, p)
#define STREAM_TO_BDADDR(a, p)     CONVERT_STREAM_TO_BDADDR(a, p)
#define STREAM_TO_ARRAY(a, p, len) CONVERT_STREAM_TO_ARRAY(a, p, len)
#define REVERSE_STREAM_TO_ARRAY(a, p, len)	CONVERT_REVERSE_STREAM_TO_ARRAY(a, p, len)

#define UUID_TO_STREAM(p, p_uu) {if (p_uu->length == UUID_16BIT_TYPE_LEN){UINT16_TO_STREAM(p, p_uu->value.uuid16);}\
							else if (p_uu->length == UUID_32BIT_TYPE_LEN){UINT32_TO_STREAM(p, p_uu->value.uuid32);}\
							else if (p_uu->length == UUID_128BIT_TYPE_LEN){REVERSE_ARRAY_TO_STREAM(p, p_uu->value.uuid128, UUID_128BIT_TYPE_LEN);}}

#define UINT16_TO_UUID(u, uu) {uu.length = UUID_16BIT_TYPE_LEN; uu.value.uuid16 = u;}
#define UINT32_TO_UUID(u, uu) {uu.length = UUID_32BIT_TYPE_LEN; uu.value.uuid32 = u;}
#define UINT128_TO_UUID(u, uu) {uu.length = UUID_128BIT_TYPE_LEN; register int ijk; for(ijk=0; ijk<UUID_128BIT_TYPE_LEN;ijk++)uu.value.uuid128[ijk] = u[ijk];}
#define COMPARE_UUID(u1, u2)	(((u1->length == u2->length) && (((u1->length == UUID_16BIT_TYPE_LEN) && u1->value.uuid16 == u2->value.uuid16) \
							|| ((u1->length == UUID_32BIT_TYPE_LEN) && u1->value.uuid32 == u2->value.uuid32) \
							|| ((u1->length == UUID_128BIT_TYPE_LEN) && memcmp(u1->value.uuid128, u2->value.uuid128, UUID_128BIT_TYPE_LEN) == 0))) ? TRUE : FALSE)


#if (TARGET_LINUX == TRUE || TARGET_THREADX_RW == TRUE)
#define BDADDR_TO_STRING(a, p)	{register int ijk; for (ijk = 0; ijk < 6; ijk++) sprintf(&a[ijk*3], "%02x:", p[ijk]); a[ijk*3 -1] = 0; }
#define UUID128_TO_STRING(a, p, len)	{register int ijk, xyz; for (ijk = 0, xyz = 0; ijk < len; ijk++, xyz+=2) {sprintf(&a[xyz], "%02x", p[ijk]);} a[xyz] = 0; }
#define ARRAY_TO_STRING(a, p, len)	{ memset(a, 0, sizeof(a)); memcpy(a, p, len); }
#define UUID_TO_STRING(str, uuid)	{if (uuid.length == UUID_16BIT_TYPE_LEN){sprintf(str, "%02x", uuid.value.uuid16);}\
								else if (uuid.length == UUID_32BIT_TYPE_LEN){sprintf(str, "%x", uuid.value.uuid32);}\
								else if (uuid.length == UUID_128BIT_TYPE_LEN){UUID128_TO_STRING(str, uuid.value.uuid128, UUID_128BIT_TYPE_LEN);}}
#elif (TARGET_UEFI == TRUE)
#define BDADDR_TO_STRING(a, p) {register int ijk; for (ijk = 0; ijk < 6; ijk++) AsciiSPrint(&a[ijk*3], (BD_ADDR_STR_LEN - ijk*3), "%02x:", p[ijk]); a[ijk*3 -1] = 0; }
#define UUID128_TO_STRING(a, p, len)	{register int ijk, xyz; for (ijk = 0, xyz = 0; ijk < len; ijk++, xyz+=2) {AsciiSPrint(&a[xyz], 10, "%02x", p[ijk]);} a[xyz] = 0; }
#define ARRAY_TO_STRING(a, p, len) { ZeroMem(a, sizeof(a)); CopyMem(a, p, len); }
#define UUID_TO_STRING(str, uuid)	{if (uuid.length == UUID_16BIT_TYPE_LEN){AsciiSPrint(str, 10, "%02x", uuid.value.uuid16);}\
								else if (uuid.length == UUID_32BIT_TYPE_LEN){AsciiSPrint(str, 10, "%x", uuid.value.uuid32);}\
								else if (uuid.length == UUID_128BIT_TYPE_LEN){UUID128_TO_STRING(str, uuid.value.uuid128, UUID_128BIT_TYPE_LEN);}}
#else
#define BDADDR_TO_STRING(a, p) {a[0]='\0';}
#define ARRAY_TO_STRING(a, p, len) { memset(a, 0, sizeof(a)); memcpy(a, p, len); }
#define UUID_TO_STRING(str, uuid) {str[0] = '\0';}
#endif


#if TRANS_ID_SIZE_BYTES == 4	/* 32 bits */
	typedef UINT32 trans_id_t;
#elif TRANS_ID_SIZE_BYTES == 2	/* 16 bits */
	typedef UINT16 trans_id_t;
#else							/* 8 bits */
	typedef UINT8 trans_id_t;

#endif
#endif
