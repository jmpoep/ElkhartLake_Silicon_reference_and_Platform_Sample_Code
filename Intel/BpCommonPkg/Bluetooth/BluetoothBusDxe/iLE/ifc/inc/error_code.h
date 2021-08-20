/** @file
  Error code declarations.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef ERROR_CODE_H_
#define ERROR_CODE_H_

/* The operation is finished in the local device */
#define STATUS_OPERATION_FINISHED_LOCAL_SUCCESS		1

/* Status codes to be used through out the stack and to apps */
#define STATUS_SUCCESS								0	/* 0x00 */
#define STATUS_ERR_STACK_NOT_INIT					-1	/* 0xFF */
/**
 * @def STATUS_ERR_INVALID_PARAM
 * In each function, if any condition check fails in the validity of the
 * input parameter then this error is to be sent up.
 */
#define STATUS_ERR_INVALID_PARAM					-2	/* 0xFE */
/**
 * @def STATUS_ERR_INSUFFICIENT_RESOURCES
 * For
 * 1. alloc/dealloc failure
 * 2. timer create/delete/star/stop
 * 3. Queue full
 * 4. other system resource related availability
 * this error should be sent up.
 */
#define STATUS_ERR_INSUFFICIENT_RESOURCES			-3	/* 0xFD */
/**
 * @def STATUS_ERR_BUSY
 * For stack/layer to say that this operation cannot happen because of it is
 * doing something else this error should be used. Upon receiving this error
 * interface layer can schedule this operation later.
 */
#define STATUS_ERR_BUSY								-4	/* 0xFC */
/**
 * @def STATUS_ERR_INVALID_APP_HANDLE
 * For API calls from application, if application handle is not valid then this
 * error should be sent. FIXME: This validity is not checked currently.
 */
#define STATUS_ERR_INVALID_APP_HANDLE				-5	/* 0xFB */
/**
 * @def STATUS_ERR_INAVLID_CONNENCTION
 * For scenarios where we refer to a connection which is not valid this error
 * should be returned. Many functions we refer to the device variable, when device
 * is NULL this error should be sent. (However, this has lower priority than
 * STATUS_ERR_INVALID_PARAM). So, if device is an input param to a function,
 * then STATUS_ERR_INVALID_PARAM should be sent.
 */
#define STATUS_ERR_INAVALID_CONNENCTION				-6	/* 0xFA */
/**
 * @def STATUS_ERR_INVALID_ATTRIBUTE
 * If any GATT related attribute is not valid then this error should be sent.
 * However, this also has lower priority than STATUS_ERR_INVALID_ATTRIBUTE.
 * This is sent also of certain gatt attribute doesn't allow requested operation.
 */
#define STATUS_ERR_INVALID_ATTRIBUTE				-7	/* 0xF9 */
/**
 * @def STATUS_ERR_LAYER_SPECIFIC
 * If any layer specific error happens then this error code is sent. This error
 * signifies that the error code is not relevant for the upper layer to take any
 * action depending on it.
 */
#define STATUS_ERR_LAYER_SPECIFIC					-8	/* 0xF8 */
/**
 * @def STATUS_ERR_OPERATION_NOT_SUPPORTED
 * If the requested operation is not supported then this erro has to be used.
 */
#define STATUS_ERR_OPERATION_NOT_SUPPORTED			-9	/* 0xF7 */
/**
 * @def STATUS_ERR_UNKNOWN
 * Any other error can be categorised here.
 */
#define STATUS_ERR_UNKNOWN							-10	/* 0xF6 */

/**
 * @def STATUS_PROCESS_ONGOING
 * This status is used by Manager layers to notify interface layer
 * that the request processing is ongoing. And seeing this interface layer
 * wouldn't free up the request memory
 */
#define STATUS_PROCESS_ONGOING						-11	/* 0xF5 */

/**
 * @def STATUS_ERR_GATT_SERVICE_NOT_STARTED
 * If GATT Server App adds new GATT Service without starting the previously
 * added GATT Service then this error code will be sent.
 */
#define STATUS_ERR_GATT_PREV_SVC_NOT_STARTED		-12	/* 0xF4 */

/**
 * @def STATUS_ERR_GATT_MAX_NUM_ATTR_REACHED
 * If GATT Server App adds new attribute(s) and there is no more
 * space available then this error code will be sent.
 */
#define STATUS_ERR_GATT_MAX_NUM_ATTR_REACHED		-13	/* 0xF3 */

/**
 * @def STATUS_ERR_GATT_NO_PRIM_SVC_ADDED
 * If GATT Server App adds characteristic(s)/descriptor(s) before adding
 * any Primary Service then this error code will be sent.
 */
#define STATUS_ERR_GATT_NO_PRIM_SVC_ADDED			-14	/* 0xF2 */

/**
 * @def STATUS_ERR_GATT_SVC_ADD_ATTR_INCOMPLETE
 * If GATT Server App starts a service and number of attributes added in the
 * service is less than declared (during Add Primary Service) then this
 * error code will be sent.
 */
#define STATUS_ERR_GATT_SVC_ADD_ATTR_INCOMPLETE		-15	/* 0xF1 */

/**
 * @def STATUS_ERR_GATT_SVC_ADD_ATTR_EXCEEDED
 * If GATT Server App starts a service and number of attributes added in the
 * service is greater than declared (during Add Primary Service) then this
 * error code will be sent.
 */
#define STATUS_ERR_GATT_SVC_ADD_ATTR_EXCEEDED		-16	/* 0xF0 */

/**
 * @def STATUS_ERR_DEVICE_ERROR
 * If the controller was detached or gone to bad state during a ongoing connection.
 * This error code is used to indicate the device error.
 */
#define STATUS_ERR_DEVICE_ERROR                 -17
#endif /* ERROR_CODE_H_ */
