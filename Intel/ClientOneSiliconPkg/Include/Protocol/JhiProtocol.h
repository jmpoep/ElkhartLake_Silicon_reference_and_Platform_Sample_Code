/** @file
  Header file for JHI (Intel DAL Host Interface Service) Protocol.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2018 Intel Corporation.

  The source code contained or described herein and all documents related to the
  source code ("Material") are owned by Intel Corporation or its suppliers or
  licensors. Title to the Material remains with Intel Corporation or its suppliers
  and licensors. The Material may contain trade secrets and proprietary and
  confidential information of Intel Corporation and its suppliers and licensors,
  and is protected by worldwide copyright and trade secret laws and treaty
  provisions. No part of the Material may be used, copied, reproduced, modified,
  published, uploaded, posted, transmitted, distributed, or disclosed in any way
  without Intel's prior express written permission.

  No license under any patent, copyright, trade secret or other intellectual
  property right is granted to or conferred upon you by disclosure or delivery
  of the Materials, either expressly, by implication, inducement, estoppel or
  otherwise. Any license under such intellectual property rights must be
  express and approved by Intel in writing.

  Unless otherwise agreed by Intel in writing, you may not remove or alter
  this notice or any other notice embedded in Materials by Intel or
  Intel's suppliers or licensors in any way.

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/

#ifndef __JHI_PROTOCOL_H__
#define __JHI_PROTOCOL_H__

typedef UINT32                                JHI_RET;
typedef VOID*                                 JHI_HANDLE;
typedef VOID*                                 JHI_SESSION_HANDLE;

//------------------------------------------------------------
// JHI return codes
//------------------------------------------------------------
#define JHI_FILE_MISSING_SRC                  0x101   ///< Source File not found in install/uninstall or unable to load file in SendAndRecv
#define JHI_FILE_ERROR_AUTH                   0x102   ///< Attempted to load the file, but FW returned back a manifest failure check and rejected it
#define JHI_FILE_ERROR_DELETE                 0x104   ///< Unable to remove file corresponding to the UUID in uninstall Maybe permission issues
#define JHI_FILE_INVALID                      0x105   ///< Invalid file - bad characters or larger than 64K
#define JHI_FILE_ERROR_OPEN                   0x106   ///< Unable to open file. Maybe permission issues
#define JHI_FILE_UUID_MISMATCH                0x107   ///< UUIDs dont match between applet file and function input
#define JHI_FILE_IDENTICAL                    0x108   ///< downloaded applet matches existing one in Jom

#define JHI_INVALID_COMMAND                   0x202   ///< invalid JHI interface command
#define JHI_ILLEGAL_VALUE                     0x204   ///< validation failed on input parameters

#define JHI_COMMS_ERROR                       0x300   ///< Communications error due to HECI timeouts or ME auto resets or any other COMMS error
#define JHI_SERVICE_INVALID_GUID              0x302   ///< Invalid COM guid (from DLL)

#define JHI_APPLET_TIMEOUT                    0x401   ///< This may be a result of a Java code in VM in an infinite loop. TL will kill applet in JOM and return error code
#define JHI_APPID_NOT_EXIST                   0x402   ///< If appid is not present in app table
#define JHI_JOM_FATAL                         0x403   ///< JOM fatal error
#define JHI_JOM_OVERFLOW                      0x404   ///< exceeds max installed applets or active sessions in JOM
#define JHI_JOM_ERROR_DOWNLOAD                0x405   ///< JOM download error
#define JHI_JOM_ERROR_UNLOAD                  0x406   ///< JOM unload error

#define JHI_ERROR_LOGGING                     0x500   ///< Error in logging

#define JHI_UNKNOWN_ERROR                     0x600   ///< Any other error

// General JHI Return Code
#define JHI_SUCCESS                           0x00    ///< general success response
#define JHI_INVALID_HANDLE                    0x201   ///< invalid JHI handle
#define JHI_INVALID_PARAMS                    0x203   ///< passed a null pointer to a required argument / illegal arguments passed to API function
#define JHI_INVALID_APPLET_GUID               JHI_ILLEGAL_VALUE   ///< the applet UUID is invalid
#define JHI_SERVICE_UNAVAILABLE               0x301   ///< there is no connection to JHI service
#define JHI_ERROR_REGISTRY                    0x501   ///< error for any registry based access or registry corruption
#define JHI_ERROR_REPOSITORY_NOT_FOUND        0x1000  ///< when cannot find applets repository directory
#define JHI_INTERNAL_ERROR                    0x601   ///< an unexpected internal error happened.
#define JHI_INVALID_BUFFER_SIZE               0x1001  ///< used a buffer that is larger than JHI_BUFFER_MAX
#define JHI_INVALID_COMM_BUFFER               0x1002  ///< JVM_COMM_BUFFER passed to function is invalid

// Install errors
#define JHI_INVALID_INSTALL_FILE              0x1003  ///< the dalp file path is invalid
#define JHI_READ_FROM_FILE_FAILED             0x1004  ///< failed to read DALP file
#define JHI_INVALID_PACKAGE_FORMAT            0x1005  ///< dalp file format is not a valid
#define JHI_FILE_ERROR_COPY                   0x103   ///< applet file could not be copied to repository
#define JHI_INVALID_INIT_BUFFER               0x1006  ///< passed an invalid init buffer to the function
#define JHI_FILE_NOT_FOUND                    JHI_FILE_MISSING_SRC  ///< could not find the specified dalp file
#define JHI_INVALID_FILE_EXTENSION            0x1007  ///< applets package file must end with .dalp extension.
#define JHI_MAX_INSTALLED_APPLETS_REACHED     JHI_JOM_OVERFLOW  ///< exceeds max applets allowed, need to uninstall an applet.
#define JHI_INSTALL_FAILURE_SESSIONS_EXISTS   0x1008  ///< could not install because there are open sessions.
#define JHI_INSTALL_FAILED                    0x1009  ///< no compatible applet was found in the DALP file
#define JHI_SVL_CHECK_FAIL                    0x1040  ///< install failed due to an svl check

// Uninstall errors
#define JHI_DELETE_FROM_REPOSITORY_FAILURE    JHI_FILE_ERROR_DELETE   ///< unable to delete applet DALP file from repository
#define JHI_UNINSTALL_FAILURE_SESSIONS_EXISTS 0x100A  ///< for app uninstallation errors

// Create Session errors
#define JHI_APPLET_NOT_INSTALLED              JHI_APPID_NOT_EXIST ///< trying to create a session of uninstalled applet
#define JHI_MAX_SESSIONS_REACHED              0x100C  ///< exceeds max sessions allowed, need to close a session.
#define JHI_SHARED_SESSION_NOT_SUPPORTED      0x100D  ///< the applet does not support shared sessions.
#define JHI_MAX_SHARED_SESSION_REACHED        0x100E  ///< failed to get session handle due to maximun handles limit.
#define JHI_FIRMWARE_OUT_OF_RESOURCES         0x1018  ///< request causes the VM to exceed its memory quota

// Close Session errors
#define JHI_INVALID_SESSION_HANDLE            0x100F  ///< the session handle is not of an active session.

// Send And Recieve errors
#define JHI_INSUFFICIENT_BUFFER               0x200   ///< buffer overflow - response greater than supplied Rx buffer
#define JHI_APPLET_FATAL                      0x400   ///< This may be a result of uncaught exception or unusual applet error that results in applet being terminated by TL VM.

// Register/Unregister session events
#define JHI_SESSION_NOT_REGISTERED            0x1010  ///< trying to unregister a session that is not registered for events.
#define JHI_SESSION_ALREADY_REGSITERED        0x1011  ///< Registration to an event is done only once.
#define JHI_EVENTS_NOT_SUPPORTED              0x1012  ///< events are not supported for this type of session

// Get Applet Property errors:
#define JHI_APPLET_PROPERTY_NOT_SUPPORTED     0x1013  ///< Rerturned when calling GetAppletProperty with invalid property

// Init errors
#define JHI_SPOOLER_NOT_FOUND                 0x1014  ///< cannot find the spooler file
#define JHI_INVALID_SPOOLER                   0x1015  ///< cannot download spooler / create an instance of the spooler
#define JHI_NO_CONNECTION_TO_FIRMWARE         JHI_COMMS_ERROR   ///< JHI has no connection to the VM

// DLL errors
#define JHI_VM_DLL_FILE_NOT_FOUND             0x1016  ///< VM DLL is missing from the exe path
#define JHI_VM_DLL_VERIFY_FAILED              0x1017  ///< DLL Signature or Publisher name are not valid.

// IAC errors
#define JHI_IAC_SERVER_SESSION_EXIST          0x1020  ///< May occur when trying to create two sessions on an IAC server applet
#define JHI_IAC_SERVER_INTERNAL_SESSIONS_EXIST  0x1021  ///< May occur when trying to close an IAC server applet session that has internal sessions

// Access control errors
#define JHI_MISSING_ACCESS_CONTROL            0x1030

// other errors
#define JHI_APPLET_AUTHENTICATION_FAILURE     JHI_FILE_ERROR_AUTH ///< FW rejected the applet while trying to install it
#define JHI_BAD_APPLET_FORMAT                 0x2001


// -----------------------------------------------------------
// Buffer size limitation is 2MB
// JHI will not accept any buffer with greater size.
//
// Note that this size limitiation does not mark the maximum buffer size an applet can recieve,
// applet max buffer size changes from one applet to another.
//
// This applies for all JHI API function that use buffers such as:
// SendAndRecieve, CreateSession, GetAppletProperty.
// -----------------------------------------------------------
#define JHI_BUFFER_MAX                        2097152


//------------------------------------------------------------
// Applet version macros
//------------------------------------------------------------
// While applet version is represented in a Major.Minor format (i.e. 1.0)
// the VM repersntation of an applet version (that can be obtained using JHI_GetAppletProperty) is as an integer that combine both major and minor version.
// in order to perform the transition between to two representation we offer the following macros:

/*
         Make VM Applet Version (32bit) from a Major.Minor format

         Bits:
                 00-07 - Major
                 08-15 - Minor
                 15-31 - Reserved (All Zero)
*/
#define MK_APPLET_VER(maj, min)               ( (UINT32) \
                                              (maj             & 0x000000FFUL) |  \
                                              ((min << 8)      & 0x0000FF00UL) &  \
                                              (0x0000FFFFUL) )

/* Extract Applet Major Version from a VM integer representation (num) */
#define MAJOR_APPLET_VER(num)                 ((UINT8)  (num & 0x000000FFUL))

/* Extract Applet Minor Version from a VM integer representation (num) */
#define MINOR_APPLET_VER(num)                 ((UINT8) ((num & 0x0000FF00UL) >> 8))

#define APPID_BIN_LENGTH                      16      ///< binary length of applet ID
#define APPID_STR_LENGTH                      32      ///< string length of applet ID (without \0 and separators)

typedef VOID                                  *VM_SESSION_HANDLE;
typedef CHAR8                                 APPID_STR [APPID_STR_LENGTH + 1]; // ANSI string, +1 for '\0'
typedef UINT8                                 APPID_BIN [APPID_BIN_LENGTH];
typedef UINT8                                 JHI_SESSION_ID [APPID_BIN_LENGTH];

//------------------------------------------------------------
// JHI Events
//------------------------------------------------------------

// this enum lists the types of data received by JHI event
typedef enum _JHI_EVENT_DATA_TYPE
{
  JHI_DATA_FROM_APPLET = 0,       // the event raised by an applet session
  JHI_DATA_FROM_SERVICE = 1       // the event raised by JHI service
}JHI_EVENT_DATA_TYPE;

//this struct repersents the data received upon a JHI event
typedef struct {
  UINT32 datalen;                 // byte length of the event data
  UINT8* data;                    // the buffer that contains the event data
  JHI_EVENT_DATA_TYPE dataType;   // the event type
}JHI_EVENT_DATA;

// This is the format for a callback function that is used in order to
// receive session events.
typedef void (*JHI_EventFunc)(JHI_SESSION_HANDLE SessionHandle, JHI_EVENT_DATA EventData);


//------------------------------------------------------------
// JHI Version info.
//------------------------------------------------------------

// this enum lists the communication types that are used
// by JHI in order to communicate with the firmware
typedef enum _JHI_COMMUNICATION_TYPE
{
  JHI_SOCKETS = 0,                // communication by sockets
  JHI_HECI = 1                    // communication by HECI
} JHI_COMMUNICATION_TYPE;

#define VERSION_BUFFER_SIZE 50

// this enum lists the platfom types that are supported by JHI
typedef enum _JHI_PLATFROM_ID
{
  ME = 0,                         // Intel(R) Management Engine (Intel(R) ME)
  SEC = 1,
  CSE = 2,
  INVALID_PLATFORM_ID = -1
} JHI_PLATFROM_ID;

// This enum lists the VM types that are supported by JHI
typedef enum _JHI_VM_TYPE
{
  JHI_VM_TYPE_INVALID       = -1,
  JHI_VM_TYPE_TL            = 0,
  JHI_VM_TYPE_BEIHAI        = 1
} JHI_VM_TYPE;

// Different VM plugin types used by JHI
typedef enum _JHI_PLUGIN_TYPE
{
  JHI_PLUGIN_TYPE_INVALID   = -1,
  JHI_PLUGIN_TYPE_TL        = 0,
  JHI_PLUGIN_TYPE_BEIHAI_V1 = 1,
  JHI_PLUGIN_TYPE_BEIHAI_V2 = 2
} JHI_PLUGIN_TYPE;

// this struct contains information about the JHI service and the
// firmware versions, and additional info
typedef struct
{
  CHAR8                   JhiVersion[VERSION_BUFFER_SIZE];    // the version of the JHI service
  CHAR8                   FwVersion[VERSION_BUFFER_SIZE];     // the version of the firmware
  JHI_COMMUNICATION_TYPE  CommType;                           // the communication type between JHI and the firmware
  JHI_PLATFROM_ID         PlatformId;                         // the platform supported by the JHI service
  JHI_VM_TYPE             VmType;                             // the VM type supported by the JHI service
  UINT8                   JhiVerMajor;                        // Version information of JHI DXE driver
  UINT8                   JhiVerMinor;
  UINT8                   JhiVerHotfix;
  UINT8                   JhiVerBuild;
  UINT8                   FwMajor;                            // Firmware information of JHI DXE driver
  UINT8                   FwMinor;
  UINT8                   FwHotfix;
  UINT8                   FwBuild;
  UINT32                  Reserved[17];                       // reserved bits
} JHI_VERSION_INFO;


//------------------------------------------------------------
// Session info
//------------------------------------------------------------

// this enum lists the states of a session
typedef enum _JHI_SESSION_STATE
{
  JHI_SESSION_STATE_ACTIVE      = 0,                           // the session is active
  JHI_SESSION_STATE_NOT_EXISTS  = 1                            // the session does not exists
} JHI_SESSION_STATE;

// this struct contains information for a given session
typedef struct
{
  JHI_SESSION_STATE state;                                     // the session state
  UINT32            flags;                                     // the flags used when this session created
  UINT32            reserved[20];                              // reserved bits
} JHI_SESSION_INFO;

//------------------------------------------------------------
// Create Session flags
//------------------------------------------------------------
// this enum lists the flags that used when creating a session
//
#define JHI_NO_FLAGS              0                            // no flags to be used
#define JHI_SHARED_SESSION        1                            // create a shared session, or receive a handle for an existing shared session

//------------------------------------------------------------
// Data Buffer
//------------------------------------------------------------
typedef struct
{
  VOID*  buffer;
  UINT32 length ;
} DATA_BUFFER ;


//------------------------------------------------------------
// For Tx and Rx downto the MEI routine
// DON'T ADD MEMBERS IN
//------------------------------------------------------------
typedef struct
{
  DATA_BUFFER TxBuf [1] ;

  //--------------------!!!!!!!!!!!--------------------//
  // Dont add members in between TxBuf[1] & RxBuf[1]   //
  // The code that uses this depends on it             //
  //--------------------!!!!!!!!!!!--------------------//

  DATA_BUFFER RxBuf [1] ;

  // You may add anything here
} JVM_COMM_BUFFER ;


//
// Extern the GUID for protocol users.
//
extern EFI_GUID gJhiProtocolGuid;

//
// Forward reference for ANSI C compatibility
//
typedef struct _ME_JHI_PROTOCOL ME_JHI_PROTOCOL;

//
// Member functions
//
/**
  Initializes the DAL client programming library by allocating resources, establishing
  a session with the ME Firmware through the JHI Service installed in the PC client.
  Typically, this is the first function called by the clients of the JHI interface.
  Context must be NULL and flags set to 0.

  @param[out] Handle              The pointer to JHI handle.
                                  Handle returned by the interface for use by the application
                                  in future references to maintain application related info.
  @param[in]  Context             The pointer to application related context information that
                                  can be returned by interface if necessary.
  @param[in]  Flags               Input parameter used to indicate future conditions.
  @retval JHI_SUCCESS             Initialize JHI core successfully.
  @retval others                  Error code that return from JHI core.
**/
typedef
JHI_RET
(EFIAPI *JHI_INITIALIZE) (
  OUT EFI_HANDLE                  *Handle,
  IN  VOID                        *Context,
  IN  UINT32                      Flags
);

/**
  Uninitializes the DAL client programming library by de-allocating resources and
  closes the connection with host JHI service. Typically, this is the last function
  called by the clients of the JHI interface and is used for cleanup at the end of
  a session. This is a preboot version of JHI_Deinit API.

  @param[in]  Handle              The JHI handle.

  @retval JHI_SUCCESS             Uninitialize JHI core successfully.
  @retval others                  Error code that return from JHI core.
**/
typedef
JHI_RET
(EFIAPI *JHI_UNINIT) (
  IN  EFI_HANDLE                  Handle
  );

/**
  Install an applet file to JHI core. This is a preboot version of JHI_Install2 API.
  This function gets the AppID and the path where the application package is stored
  which are then sent to JOM through JHI service. On successful installation, the
  application along with the manifest is then installed onto the ME through the JHI service.

  @param[in]  Handle              The JHI handle.
  @param[in]  AppId               The applet UUID string without separator characters ('-')
  @param[in]  SrcFile             The file path of the applet.

  @retval JHI_SUCCESS             Install an applet to JHI core successfully.
  @retval others                  Error code that return from JHI core.
**/
typedef
JHI_RET
(EFIAPI *JHI_INSTALL_FILE) (
  IN  EFI_HANDLE                  Handle,
  IN  CHAR8                       *AppId,
  IN  CONST CHAR16                *SrcFile
  );

/**
  Install an applet from content to JHI core. This is a preboot version of JHI_Install3 API.
  This API is similar with JHI_PROTOCOL.InstallFile. This function gets the AppID
  and the contents (AppletBlob and AppletLength) of the application package then
  sent to JOM through JHI service.

  @param[in]  Handle              The JHI handle.
  @param[in]  AppId               The applet UUID string without separator characters ('-')
  @param[in]  AppletBlob          The raw data of the applet.
  @param[in]  AppletLength        The data length of the applet.

  @retval JHI_SUCCESS             Install an applet to JHI core successfully.
  @retval others                  Error code that return from JHI core.
**/
typedef
JHI_RET
(EFIAPI *JHI_INSTALL_CONTENT) (
  IN  EFI_HANDLE                  Handle,
  IN  CHAR8                       *AppId,
  IN  CONST VOID                  *AppletBlob,
  IN  CONST UINT32                AppletLength
  );

/**
  Uninstall an applet from JHI core. This is the interface used to uninstall an
  existing application from the JOM.

  @param[in]  Handle              The JHI handle.
  @param[in]  AppId               The applet UUID string without separator characters ('-')

  @retval JHI_SUCCESS             Uninstall an applet to JHI core successfully.
  @retval others                  Error code that return from JHI core.
**/
typedef
JHI_RET
(EFIAPI *JHI_UNINSTALL) (
  IN  EFI_HANDLE                  Handle,
  IN  CHAR8                       *AppId
  );

/**
  Get applet property from JHI core. This interface used to query one of the
  following properties of an installed applet:
  " applet.name
  " applet.vendor
  " applet.description
  " applet.version
  " security.version
  " applet.flash.quota
  " applet.debug.enable
  " applet.shared.session.support
  " applet.platform

  @param[in]  Handle              The JHI handle.
  @param[in]  AppId               The applet UUID string without separator characters ('-')
  @param[in]  CommBuffer          The pointer to the buffer for information transfer.

  @retval JHI_SUCCESS             Get applet property from JHI core successfully.
  @retval others                  Error code that return from JHI core.
**/
typedef
JHI_RET
(EFIAPI *JHI_GET_APPLET_PROPERTY) (
  IN     EFI_HANDLE               Handle,
  IN     CHAR8                    *AppId,
  IN OUT JVM_COMM_BUFFER          *CommBuffer
  );

/**
  Create a session for an applet. This API function creates a session to a given
  applet (represented by appid) and return a session handle to which used to refer
  to the applet instance that would like to communicate with.

  @param[in]  Handle              The JHI handle.
  @param[in]  AppId               The applet UUID string without separator characters ('-')
  @param[in]  Flags               The flag to create session.
  //
  // Here lists the flags that used when creating a session:
  //
  #define JHI_NO_FLAGS            0 // no flags to be used
  #define JHI_SHARED_SESSION      1 // create a shared session, or receive a handle for an existing shared session
  // Note: for preboot JHI, we won't support multi-thread mechanism. So, there is no shared session, either.
  // In the other words, JHI_NO_FLAGS(0) is the only value that we support for Flags field.

  @param[in]  InitBuffer          The pointer to the buffer for creating session.
                                  Some initialization data that will be passed to
                                  the applet (the applet onInit() function). It can
                                  be set to NULL if no init data is needed by the applet.
  @param[in]  SessionHandle       The pointer to the session handle to be created
                                  and returned.

  @retval JHI_SUCCESS             Create session successfully.
  @retval others                  Error code that return from JHI core.
**/
typedef
JHI_RET
(EFIAPI *JHI_CREATE_SESSION) (
  IN  CONST EFI_HANDLE            Handle,
  IN  CONST CHAR8                 *AppId,
  IN  UINT32                      Flags,
  IN  DATA_BUFFER                 *InitBuffer,
  OUT EFI_HANDLE                  *SessionHandle
  );

/**
  Close a session for an applet. This API function close the session. After the
  function return, SessionHandle value will be not valid to use.

  @param[in]  Handle              The JHI handle.
  @param[in]  SessionHandle       The pointer to the session handle to be closed.

  @retval JHI_SUCCESS             Close session successfully.
  @retval others                  Error code that return from JHI core.
**/
typedef
JHI_RET
(EFIAPI *JHI_CLOSE_SESSION) (
  IN  EFI_HANDLE                  Handle,
  IN  EFI_HANDLE                  *SessionHandle
  );

/**
  This function gets number of active sessions of an installed applet.

  @param[in]  Handle              The JHI handle.
  @param[in]  AppId               The applet UUID string without separator characters ('-')
  @param[in]  SessionsCount       The pointer to the buffer of session count.

  @retval JHI_SUCCESS             Get session count successfully.
  @retval others                  Error code that return from JHI core.
**/
typedef
JHI_RET
(EFIAPI *JHI_GET_SESSIONS_COUNT) (
  IN  EFI_HANDLE                  Handle,
  IN  CHAR8                       *AppId,
  OUT UINT32                      *SessionsCount
  );

/**
  Get session information for a session. This API function returns information of
  a given session. Currently only the session state is available, but this API
  an be extended later to return more info.

  @param[in]  Handle              The JHI handle.
  @param[in]  SessionHandle       The session handle to be queried.
  @param[in]  SessionInfo         The pointer to the buffer of session information.

  @retval JHI_SUCCESS             Get session information successfully.
  @retval others                  Error code that return from JHI core.
**/
typedef
JHI_RET
(EFIAPI *JHI_GET_SESSION_INFO) (
  IN  EFI_HANDLE                  Handle,
  IN  EFI_HANDLE                  SessionHandle,
  OUT JHI_SESSION_INFO            *SessionInfo
  );

/**
  Get version information of JHI core. This function is used in order to get the
  versions of the FW, JHI and other general information such as Communication mode.

  @param[in]  Handle              The JHI handle.
  @param[in]  VersionInfo         The pointer to the buffer of version information.

  @retval JHI_SUCCESS             Get version information successfully.
  @retval others                  Error code that return from JHI core.
**/
typedef
JHI_RET
(EFIAPI *JHI_GET_VERSION_INFO) (
  IN  CONST EFI_HANDLE            Handle,
  OUT JHI_VERSION_INFO            *VersionInfo
  );

/**
  Send/Receive data to/from JHI core. This is a preboot version of JHI_SendAndRecv2 API.
  The interface allows for sending and receiving raw data and in addition a UINT32
  response code. This is an atomic operation from the perspective of the calling application.

  @param[in]  Handle              The JHI handle.
  @param[in]  SessionHandle       The session handle.
  @param[in]  CommandId           The command id that is sent to the applet.
  @param[in]  CommBuffer          I/O communication buffer for sending/receiving raw data.
                                  In case the function returns JHI_INSUFFICIENT_BUFFER
                                  the RxBuf->length will hold the buffer size required
                                  by the applet for the response.

  @param[in]  ResponseCode        The pointer to the buffer of response code.
                                  The response code returned from the applet to
                                  the application by using the SetResponseCode()
                                  method. It can be NULL.

  @retval JHI_SUCCESS             Data transfer successfully.
  @retval others                  Error code that return from JHI core.
**/
typedef
JHI_RET
(EFIAPI *JHI_SEND_ADN_RECEIVE) (
  IN     EFI_HANDLE               Handle,
  IN     EFI_HANDLE               SessionHandle,
  IN     INT32                    CommandId,
  IN OUT JVM_COMM_BUFFER          *CommBuffer,
  OUT    INT32                    *ResponseCode
  );


///
/// Revision
///
#define JHI_PROTOCOL_REVISION  1

/**
  JHI protocol provided for DXE phase
  The interface functions are for JHI APIs to transfer data between host and Intel ME subsystem.
**/
struct _ME_JHI_PROTOCOL {
  UINT8                           Revision;           ///< Structure revision number
  JHI_INITIALIZE                  Initialize;         ///< Initialize JHI DXE driver, allocate resource (JHI_Initialize)
  JHI_UNINIT                      Uninit;             ///< Uninitialized JHI DXE driver, free resource  (JHI_Deinit)
  JHI_INSTALL_FILE                InstallFile;        ///< Download an applet file into ME DAL VM       (JHI_Install2)
  JHI_INSTALL_CONTENT             InstallContent;     ///< Download an applet content into ME DAL VM    (JHI_Install3)
  JHI_UNINSTALL                   Uninstall;          ///< Unload an applet from ME DAL VM              (JHI_Uninstall)
  JHI_GET_APPLET_PROPERTY         GetAppletProperty;  ///< Get information of downloaded applets        (JHI_GetAppletProperty)
  JHI_CREATE_SESSION              CreateSession;      ///< Create a session for a specific applet       (JHI_CreateSession)
  JHI_GET_SESSIONS_COUNT          GetSessionsCount;   ///< Get count of total sessions                  (JHI_GetSessionsCount)
  JHI_CLOSE_SESSION               CloseSession;       ///< End a session for a specific applet          (JHI_CloseSession)
  JHI_GET_SESSION_INFO            GetSessionInfo;     ///< Get information of specific session          (JHI_GetSessionInfo)
  JHI_GET_VERSION_INFO            GetVersionInfo;     ///< Get information of JHI driver                (JHI_GetVersionInfo)
  JHI_SEND_ADN_RECEIVE            SendAndReceive;     ///< Send/receive data to/from a specific applet  (JHI_SendAndRecv2)
};

#endif  // __JHI_PROTOCOL_H__

