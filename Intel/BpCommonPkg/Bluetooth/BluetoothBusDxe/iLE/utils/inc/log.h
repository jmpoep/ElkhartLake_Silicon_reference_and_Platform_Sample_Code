/** @file
  Log utility.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef LOG_H
#define LOG_H

#include "config_host.h"
#if (TARGET_UEFI != TRUE)
/* These libraries are not available on UEFI platform */
#include <stdio.h>
#include <string.h>
#endif

#if (TARGET_UEFI == TRUE)
#include <Library/DebugLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiLib.h>
#include <Library/BaseMemoryLib.h>
#endif

#if (LOG_ENABLED == TRUE)

#if ((TARGET_LINUX == TRUE || TARGET_THREADX_RW == TRUE) && (TARGET_ANDROID == FALSE))
#define KRED  "\x1B[31m"
#define KYEL  "\x1B[33m"
#define RESET "\033[0m"

#include <errno.h>

#ifdef TARGET_THREADX_RW
extern UINT8 dev_id;
#endif

extern long long unsigned int stack_start_time;
extern double gettimestamp();

#define log(param, ...) { printf(param, ##__VA_ARGS__); fflush(stdout); }

#define hex_dump(tag, buf, len) \
{ \
	UINT16 mno;\
	log(tag" ");\
	for(mno=0; mno<len; mno++)\
	{\
		log("%02x ", *(((UINT8*)buf)+mno));\
	}\
	log("\n");\
} \

#if (TARGET_LINUX == TRUE)
#define logln(param, ...) printf("[% 9.3f] " param "\n", gettimestamp() / 1000, ##__VA_ARGS__)
#define logi(param, ...) printf( "[% 9.3f] (%s):I:" param "\n",gettimestamp() / 1000,  __func__, ##__VA_ARGS__)
#define logd(param, ...) printf( "[% 9.3f] (%s):D:" param "\n", gettimestamp() / 1000, __func__, ##__VA_ARGS__)
#define logw(param, ...) printf(KYEL "[% 9.3f] (%s):W:" param "%s\n", gettimestamp() / 1000, __func__, ##__VA_ARGS__, RESET)
#define loge(param, ...) printf(KRED  "[% 9.3f] (%s):E:" param "%s\n", gettimestamp() / 1000, __func__, ##__VA_ARGS__, RESET)
#define logex(param, ...) printf(KRED  "[% 9.3f] (%s):Ex:(errno:%d strerror:%s) " param "%s\n",  gettimestamp() / 1000, __func__, errno, strerror(errno), ##__VA_ARGS__, RESET)
#endif

#if (TARGET_THREADX_RW == TRUE)
#if (ATP_BT_SNOOP == TRUE)
#include "hci_host.h"

char logmsg[255];
#undef log
#define log(param, ...) { sprintf(logmsg, param, ##__VA_ARGS__); btsnoop_log(logmsg); }
#undef hex_dump
#define hex_dump(tag, buf, len) {}
#endif //#if (ATP_BT_SNOOP == TRUE)

#define logln(param, ...) log("(%d)" param "\n", dev_id, ##__VA_ARGS__)
#define logi(param, ...) log("(%d)" "(%s):I:" param "\n", dev_id, __func__, ##__VA_ARGS__)
#define logd(param, ...) log("(%d)" "(%s):D:" param "\n", dev_id, __func__, ##__VA_ARGS__)
#define logw(param, ...) log( "(%d)" "(%s):W:" param "\n", dev_id, __func__, ##__VA_ARGS__)
#define loge(param, ...) log( "(%d)" "(%s):E:" param "\n", dev_id, __func__, ##__VA_ARGS__)
#define logex(param, ...) log( "(%d)" "(%s):Ex:" param "\n",  dev_id, __func__, ##__VA_ARGS__)
#endif //#if (TARGET_THREADX_RW == TRUE)

//#if ((TARGET_LINUX == TRUE || TARGET_THREADX_RW == TRUE) && (TARGET_ANDROID == FALSE))
#elif (TARGET_ANDROID == TRUE)

#include <utils/Log.h>

#define logi(param, ...) {ALOGI("(%s):I:" param "\n",  __func__, ##__VA_ARGS__);}
#define logd(param, ...) {ALOGD("(%s):D:" param "\n",  __func__, ##__VA_ARGS__);}
#define logw(param, ...) {ALOGW("(%s):W:" param "\n",  __func__, ##__VA_ARGS__);}
#define loge(param, ...) {ALOGE("(%s):E:" param "\n",  __func__, ##__VA_ARGS__);}
#define logex(param, ...) {ALOGE("(%s):Ex:" param "\n",  __func__, ##__VA_ARGS__);}

#define log(param, ...) {ALOGD("(%s):" param "\n",  __func__, ##__VA_ARGS__);}
#define logln(param, ...) {ALOGD("(%s):" param "\n",  __func__, ##__VA_ARGS__);}

#define hex_dump(tag, buf, len) \
{\
	UINT16 ijk;\
	char str[1024];\
	for (ijk = 0; ijk < len; ijk++)\
	{\
		sprintf(&str[ijk * 3], "%02x ", *(((UINT8*)buf)+ijk));\
	}\
	str[len * 3] = '\0';\
	ALOGD("%s:%s", tag, str);\
}\

#elif (TARGET_UEFI == TRUE)
extern void gettimestamp(UINT64 *_sec, UINT64 *_msec);

#define flog(_param, ...)\
{\
	UINT16 _str_len, _idx;\
	char _new_param[LOGBUF_SIZE];\
	_str_len = sizeof(_param);\
	CopyMem(_new_param, _param, _str_len);\
	for(_idx = 0; _idx < _str_len; _idx++)\
	{\
		if(_new_param[_idx] == '%' && _new_param[_idx+1] == 's')\
		{\
			_new_param[_idx+1] = 'a';\
			_idx++;\
		}\
	}\
	_new_param[_str_len + 1] = '\0';\
	_DEBUG_PRINT (EFI_D_INFO, _new_param, ##__VA_ARGS__);\
	DEBUG ((EFI_D_INFO, "\n"));\
	if (log_file)\
	{\
		CHAR8 _aout[LOGBUF_SIZE];\
		UINTN _size = AsciiSPrint(_aout, sizeof(_aout), "[%u.%03u] ", _sec, _msec);\
		log_file->Write(log_file, &_size, _aout);\
		_size = AsciiSPrint(_aout, sizeof(_aout), "(%a):", __func__);\
		log_file->Write(log_file, &_size, _aout);\
		_size = AsciiSPrint(_aout, sizeof(_aout), _new_param, ##__VA_ARGS__);\
		log_file->Write(log_file, &_size, _aout);\
		_aout[0] = '\n';\
		_size = 1;\
		log_file->Write(log_file, &_size, _aout);\
		logbuf_count++;\
		if ((logbuf_count % LOGFLUSH_GAP) == 0)\
			log_file->Flush(log_file);\
	}\
}\

#define log(param, ...)   { UINT64 _sec, _msec; gettimestamp(&_sec, &_msec); flog(param, ##__VA_ARGS__);}
#define logln(param, ...) { UINT64 _sec, _msec; gettimestamp(&_sec, &_msec); DEBUG ((EFI_D_INFO, "[%u.%03u] (%a)", _sec, _msec, __func__));     flog(param, ##__VA_ARGS__);}
#define logi(param, ...)  { UINT64 _sec, _msec; gettimestamp(&_sec, &_msec); DEBUG ((EFI_D_INFO, "[%u.%03u] (%a):I:", _sec, _msec, __func__));  flog(param, ##__VA_ARGS__);}
#define logd(param, ...)  { UINT64 _sec, _msec; gettimestamp(&_sec, &_msec); DEBUG ((EFI_D_INFO, "[%u.%03u] (%a):D:", _sec, _msec, __func__));  flog(param, ##__VA_ARGS__);}
#define logw(param, ...)  { UINT64 _sec, _msec; gettimestamp(&_sec, &_msec); DEBUG ((EFI_D_INFO, "[%u.%03u] (%a):W:", _sec, _msec, __func__));  flog(param, ##__VA_ARGS__);}
#define loge(param, ...)  { UINT64 _sec, _msec; gettimestamp(&_sec, &_msec); DEBUG ((EFI_D_INFO, "[%u.%03u] (%a):E:", _sec, _msec, __func__));  flog(param, ##__VA_ARGS__);}
#define logex(param, ...) { UINT64 _sec, _msec; gettimestamp(&_sec, &_msec); DEBUG ((EFI_D_INFO, "[%u.%03u] (%a):X:", _sec, _msec, __func__));  flog(param, ##__VA_ARGS__);}
#define hex_dump(tag, buf, len) \
{\
	UINT16 ijk;\
	UINT8 *b = (UINT8*)buf;\
	DEBUG ((EFI_D_INFO, "%a", tag));\
	for (ijk = 0; ijk < len; ijk++)\
	{\
		DEBUG ((EFI_D_INFO, " %02x", b[ijk]));\
	}\
	DEBUG ((EFI_D_INFO, "\n"));\
	if (log_file)\
	{\
		CHAR8 aout[LOGBUF_SIZE];\
		UINTN size = AsciiSPrint(aout, sizeof(aout), "%a", tag);\
		log_file->Write(log_file, &size, aout);\
		for (ijk = 0; ijk < len; ijk++)\
		{\
			size = AsciiSPrint( aout, sizeof(aout), "%02x ", b[ijk]);\
			log_file->Write(log_file, &size, aout);\
		}\
		aout[0] = '\n';\
		size = 1;\
		log_file->Write(log_file, &size, aout);\
		logbuf_count++;\
		if ((logbuf_count % LOGFLUSH_GAP) == 0)\
			log_file->Flush(log_file);\
	}\
}\

#endif /* TARGET_* */

/* NOTE: Please declare MODULE_DBG_LVL macro with appropriate debug level (as mentioned in config.h)
 *		 in respective module files before including log.h file in the module.
 */
#ifndef MODULE_DBG_LVL
#define MODULE_DBG_LVL	0
#endif
#if (MODULE_DBG_LVL < DBG_LVL_INFO)
	#undef logi
	#define logi(param, ...) {}
#endif
#if (MODULE_DBG_LVL < DBG_LVL_DEBUG)
	#undef logd
	#define logd(param, ...) {}
	#undef hex_dump
	#define hex_dump(tag, buf, len) {}
#endif
#if (MODULE_DBG_LVL < DBG_LVL_WARNING)
	#undef logw
	#define logw(param, ...) {}
#endif
#if (MODULE_DBG_LVL < DBG_LVL_ERROR)
	#undef loge
	#define loge(param, ...) {}
#endif
#if (MODULE_DBG_LVL < DBG_LVL_EXCEPTION)
	#undef logex
	#define logex(param, ...) {}
#endif
#else

#define log(param, ...)  {}
#define logln(param, ...) {}
#define logi(param, ...) {}
#define logd(param, ...) {}
#define logw(param, ...) {}
#define loge(param, ...) {}
#define logex(param, ...) {}
#define hex_dump(tag, buf, len) {}

#endif /* #if (LOG_ENABLED == TRUE) */

#endif // #ifndef LOG_H
