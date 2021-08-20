/** @file  IfrParse.h

 Parser for IFR binary encoding.

 Copyright (c) 2011 - 2017, Intel Corporation. All rights reserved.<BR>

 This program and the accompanying materials are licensed and made available under
 the terms and conditions of the BSD License which accompanies this distribution.
 The full text of the license may be found at
 http://opensource.org/licenses/bsd-license.php

 THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
 WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef _IFR_PARSE_H_
#define _IFR_PARSE_H_

#include "Common.h"
#include <Common/UefiInternalFormRepresentation.h>
#include <Common/MdeModuleHii.h>

//
// Scope for Browser action. It may be Form, FormSet or System level.
//
typedef enum {
  FormLevel,
  FormSetLevel,
  SystemLevel,
  MaxLevel
} BROWSER_SETTING_SCOPE;

///
///Old EFI_IFR_VARSTORE_EFI structure to complible with UEFI 2.3
///
typedef struct _EFI_IFR_VARSTORE_EFI_OLD {
  EFI_IFR_OP_HEADER        Header;
  EFI_VARSTORE_ID          VarStoreId;
  EFI_GUID                 Guid;
  UINT32                   Attributes;
} EFI_IFR_VARSTORE_EFI_OLD;

///
/// The languages used in HII DB
///
typedef enum {
  UQI,
  EN_US,
  ENG
} LANGUAGE;

///
/// Define the structure for the parameters of Uqi and Uqi List
///
typedef struct _FORM_BROWSER_STATEMENT FORM_BROWSER_STATEMENT;

typedef enum {
  ONE_OF,
  NUMERIC,
  CHECKBOX,
  STRING,
  ORDERED_LIST
} QUEST_TYPE;

typedef struct {
  UINT16      *DefaultId;
  UINT64      *PlatformId;
  UINT32      IdNum;
  UINT32      HexNum;
  QUEST_TYPE  Type;
  CHAR16      *Data;
  UINT8       *Value;
  UINT8       *DiffValue;
  UINT32      ScriptsLine;
  FORM_BROWSER_STATEMENT *Question;
} UQI_HEADER;

typedef struct _UQI_PARAM_LIST {
  struct _UQI_PARAM_LIST   *Next;
  UQI_HEADER               Header;
  BOOLEAN                  ParseOrNot;
  BOOLEAN                  SameOrNot;
  BOOLEAN                  ErrorOrNot;
  CHAR8                    *Error;
} UQI_PARAM_LIST;

//
// Incremental size of stack for expression
//
#define EXPRESSION_STACK_SIZE_INCREMENT    0x100

//
// IFR relative definition
//
#define EFI_HII_EXPRESSION_INCONSISTENT_IF   0
#define EFI_HII_EXPRESSION_NO_SUBMIT_IF      1
#define EFI_HII_EXPRESSION_GRAY_OUT_IF       2
#define EFI_HII_EXPRESSION_SUPPRESS_IF       3
#define EFI_HII_EXPRESSION_DISABLE_IF        4
#define EFI_HII_EXPRESSION_VALUE             5
#define EFI_HII_EXPRESSION_RULE              6
#define EFI_HII_EXPRESSION_READ              7
#define EFI_HII_EXPRESSION_WRITE             8
#define EFI_HII_EXPRESSION_WARNING_IF        9

#define EFI_HII_VARSTORE_BUFFER              0
#define EFI_HII_VARSTORE_NAME_VALUE          1
#define EFI_HII_VARSTORE_EFI_VARIABLE        2
#define EFI_HII_VARSTORE_EFI_VARIABLE_BUFFER 3

#define FORM_INCONSISTENT_VALIDATION         0
#define FORM_NO_SUBMIT_VALIDATION            1

typedef struct {
  //
  // HII Data Type
  //
  UINT8               Type;
  //
  // Buffer Data and Length if Type is EFI_IFR_TYPE_BUFFER or EFI_IFR_TYPE_STRING
  //
  UINT8               *Buffer;
  UINT16              BufferLen;
  EFI_IFR_TYPE_VALUE  Value;
} EFI_HII_VALUE;

#define NAME_VALUE_NODE_SIGNATURE  SIGNATURE_32 ('N', 'V', 'S', 'T')

typedef struct {
  UINTN            Signature;
  LIST_ENTRY       Link;
  CHAR16           *Name;
  CHAR16           *Value;
  CHAR16           *EditValue;
} NAME_VALUE_NODE;

#define NAME_VALUE_NODE_FROM_LINK(a)  CR (a, NAME_VALUE_NODE, Link, NAME_VALUE_NODE_SIGNATURE)

#define FORMSET_STORAGE_SIGNATURE  SIGNATURE_32 ('F', 'S', 'T', 'G')

typedef struct {
  UINTN            Signature;
  LIST_ENTRY       Link;

  UINT16           DefaultId[MAX_PLATFORM_DEFAULT_ID_NUM];
  UINT64           PlatformId[MAX_PLATFORM_DEFAULT_ID_NUM];
  UINT32           DefaultPlatformIdNum;
  UINT32           FormSetOrder;

  BOOLEAN          NewEfiVarstore; //EfiVarStore for UEFI 2.31 or not
  BOOLEAN          Skip;           //Flag for sorting out the variables

  UINT8            Type;           // Storage type

  UINT16           VarStoreId;
  EFI_GUID         Guid;

  CHAR16           *Name;          // For EFI_IFR_VARSTORE
  UINT16           Size;
  UINT8            *Buffer;

  LIST_ENTRY       NameValueListHead; // List of NAME_VALUE_NODE

  UINT32           Attributes;     // For EFI_IFR_VARSTORE_EFI: EFI Variable attribute
} FORMSET_STORAGE;

#define FORMSET_STORAGE_FROM_LINK(a)  CR (a, FORMSET_STORAGE, Link, FORMSET_STORAGE_SIGNATURE)

typedef union {
  EFI_STRING_ID         VarName;
  UINT16                VarOffset;
} VAR_STORE_INFO;

#define EXPRESSION_OPCODE_SIGNATURE  SIGNATURE_32 ('E', 'X', 'O', 'P')

typedef struct {
  UINTN             Signature;
  LIST_ENTRY        Link;

  UINT8             Operand;

  UINT8             Format;      // For EFI_IFR_TO_STRING, EFI_IFR_FIND
  UINT8             Flags;       // For EFI_IFR_SPAN
  UINT8             RuleId;      // For EFI_IFR_RULE_REF

  EFI_HII_VALUE     Value;       // For EFI_IFR_EQ_ID_VAL, EFI_IFR_UINT64, EFI_IFR_UINT32, EFI_IFR_UINT16, EFI_IFR_UINT8, EFI_IFR_STRING_REF1

  EFI_QUESTION_ID   QuestionId;  // For EFI_IFR_EQ_ID_ID, EFI_IFR_EQ_ID_VAL_LIST, EFI_IFR_QUESTION_REF1
  EFI_QUESTION_ID   QuestionId2;

  UINT16            ListLength;  // For EFI_IFR_EQ_ID_VAL_LIST
  UINT16            *ValueList;

  EFI_STRING_ID     DevicePath;  // For EFI_IFR_QUESTION_REF3_2, EFI_IFR_QUESTION_REF3_3
  EFI_GUID          Guid;

  FORMSET_STORAGE   *VarStorage; // For EFI_IFR_SET, EFI_IFR_GET
  VAR_STORE_INFO    VarStoreInfo;// For EFI_IFR_SET, EFI_IFR_GET
  UINT8             ValueType;   // For EFI_IFR_SET, EFI_IFR_GET
  UINT8             ValueWidth;  // For EFI_IFR_SET, EFI_IFR_GET
  CHAR16            *ValueName;  // For EFI_IFR_SET, EFI_IFR_GET
  LIST_ENTRY        MapExpressionList;   // nested expressions inside of Map opcode.
} EXPRESSION_OPCODE;

#define EXPRESSION_OPCODE_FROM_LINK(a)  CR (a, EXPRESSION_OPCODE, Link, EXPRESSION_OPCODE_SIGNATURE)

#define FORM_EXPRESSION_SIGNATURE  SIGNATURE_32 ('F', 'E', 'X', 'P')

typedef struct {
  UINTN             Signature;
  LIST_ENTRY        Link;

  UINT8             Type;            // Type for this expression

  UINT8             RuleId;          // For EFI_IFR_RULE only
  EFI_STRING_ID     Error;           // For EFI_IFR_NO_SUBMIT_IF, EFI_IFR_INCONSISTENT_IF only

  EFI_HII_VALUE     Result;          // Expression evaluation result
  UINT8             TimeOut;         // For EFI_IFR_WARNING_IF

  LIST_ENTRY        OpCodeListHead;  // OpCodes consist of this expression (EXPRESSION_OPCODE)
} FORM_EXPRESSION;

#define FORM_EXPRESSION_FROM_LINK(a)  CR (a, FORM_EXPRESSION, Link, FORM_EXPRESSION_SIGNATURE)

#define QUESTION_DEFAULT_SIGNATURE  SIGNATURE_32 ('Q', 'D', 'F', 'T')

typedef struct {
  UINTN               Signature;
  LIST_ENTRY          Link;

  UINT16              DefaultId;
  EFI_HII_VALUE       Value;              // Default value

  FORM_EXPRESSION     *ValueExpression;   // Not-NULL indicates default value is provided by EFI_IFR_VALUE
} QUESTION_DEFAULT;

#define QUESTION_DEFAULT_FROM_LINK(a)  CR (a, QUESTION_DEFAULT, Link, QUESTION_DEFAULT_SIGNATURE)

#define QUESTION_OPTION_SIGNATURE  SIGNATURE_32 ('Q', 'O', 'P', 'T')

typedef struct {
  UINTN               Signature;
  LIST_ENTRY          Link;

  EFI_STRING_ID       Text;
  UINT8               Flags;
  EFI_HII_VALUE       Value;

  FORM_EXPRESSION     *SuppressExpression; // Non-NULL indicates nested inside of SuppressIf
} QUESTION_OPTION;

#define QUESTION_OPTION_FROM_LINK(a)  CR (a, QUESTION_OPTION, Link, QUESTION_OPTION_SIGNATURE)

#define FORM_BROWSER_STATEMENT_SIGNATURE  SIGNATURE_32 ('F', 'S', 'T', 'A')

struct _FORM_BROWSER_STATEMENT {
  UINTN                 Signature;
  LIST_ENTRY            Link;
  UINT8                 Operand;          // The operand (first byte) of this Statement or Question

  UQI_HEADER            Uqi;
  UINT32                FormSetOrder;
  EFI_GUID              Guid;
  UINT8                 Type;           // Storage type
  BOOLEAN               NewEfiVarstore; //EfiVarStore for UEFI 2.31 or not
  UINT32                Attributes;     // For EFI_IFR_VARSTORE_EFI: EFI Variable attribute
  BOOLEAN               QuestionReferToBitField;// Whether the question is stored in a bit field.
  //
  // Statement Header
  //
  EFI_STRING_ID         Prompt;
  EFI_STRING_ID         Help;
  EFI_STRING_ID         TextTwo;          // For EFI_IFR_TEXT

  //
  // Question Header
  //
  EFI_QUESTION_ID       QuestionId;       // The value of zero is reserved
  EFI_VARSTORE_ID       VarStoreId;       // A value of zero indicates no variable storage
  FORMSET_STORAGE       *Storage;
  VAR_STORE_INFO        VarStoreInfo;
  UINT16                StorageWidth;
  UINT16                BitStorageWidth;
  UINT16                BitVarOffset;
  UINT8                 QuestionFlags;
  CHAR16                *VariableName;    // Name/Value or EFI Variable name

  EFI_HII_VALUE         HiiValue;         // Edit copy for checkbox, numberic, oneof
  UINT8                 *BufferValue;     // Edit copy for string, password, orderedlist
  UINT8                 ValueType;        // Data type for orderedlist value array

  //
  // OpCode specific members
  //
  UINT8                 Flags;            // for EFI_IFR_CHECKBOX, EFI_IFR_DATE, EFI_IFR_NUMERIC, EFI_IFR_ONE_OF,
                                          // EFI_IFR_ORDERED_LIST, EFI_IFR_STRING,EFI_IFR_SUBTITLE,EFI_IFR_TIME, EFI_IFR_BANNER
  UINT8                 MaxContainers;    // for EFI_IFR_ORDERED_LIST

  UINT16                BannerLineNumber; // for EFI_IFR_BANNER, 1-based line number

  UINT64                Minimum;          // for EFI_IFR_ONE_OF/EFI_IFR_NUMERIC, it's Min/Max value
  UINT64                Maximum;          // for EFI_IFR_STRING/EFI_IFR_PASSWORD, it's Min/Max length
  UINT64                Step;

  EFI_DEFAULT_ID        DefaultId;        // for EFI_IFR_RESET_BUTTON
  EFI_GUID              RefreshGuid;      // for EFI_IFR_REFRESH_ID

  //
  // Get from IFR parsing
  //
  FORM_EXPRESSION       *ValueExpression;    // nested EFI_IFR_VALUE, provide Question value and indicate Question is ReadOnly
  LIST_ENTRY            DefaultListHead;     // nested EFI_IFR_DEFAULT list (QUESTION_DEFAULT), provide default values
  LIST_ENTRY            OptionListHead;      // nested EFI_IFR_ONE_OF_OPTION list (QUESTION_OPTION)

  EFI_IMAGE_ID          ImageId;             // nested EFI_IFR_IMAGE
  UINT8                 RefreshInterval;     // nested EFI_IFR_REFRESH, refresh interval(in seconds) for Question value, 0 means no refresh
  BOOLEAN               InSubtitle;          // nesting inside of EFI_IFR_SUBTITLE

  LIST_ENTRY            InconsistentListHead;// nested inconsistent expression list (FORM_EXPRESSION)
  LIST_ENTRY            NoSubmitListHead;    // nested nosubmit expression list (FORM_EXPRESSION)
  LIST_ENTRY            WarningListHead;     // nested warning expression list (FORM_EXPRESSION)
  FORM_EXPRESSION       *GrayOutExpression;  // nesting inside of GrayOutIf
  FORM_EXPRESSION       *SuppressExpression; // nesting inside of SuppressIf
  FORM_EXPRESSION       *DisableExpression;  // nesting inside of DisableIf

  FORM_EXPRESSION       *ReadExpression;     // nested EFI_IFR_READ, provide this question value by read expression.
  FORM_EXPRESSION       *WriteExpression;    // nested EFI_IFR_WRITE, evaluate write expression after this question value is set.
};

#define FORM_BROWSER_STATEMENT_FROM_LINK(a)  CR (a, FORM_BROWSER_STATEMENT, Link, FORM_BROWSER_STATEMENT_SIGNATURE)

#define FORM_BROWSER_FORM_SIGNATURE  SIGNATURE_32 ('F', 'F', 'R', 'M')
#define STANDARD_MAP_FORM_TYPE 0x01

typedef struct {
  UINTN             Signature;
  LIST_ENTRY        Link;

  UINT16            FormId;               // FormId of normal form or formmap form.
  EFI_STRING_ID     FormTitle;            // FormTile of normal form, or FormMapMethod title of formmap form.
  UINT16            FormType;             // Specific form type for the different form.

 BOOLEAN            ModalForm;            // Whether this is a modal form.
  LIST_ENTRY        ExpressionListHead;   // List of Expressions (FORM_EXPRESSION)
  LIST_ENTRY        StatementListHead;    // List of Statements and Questions (FORM_BROWSER_STATEMENT)
  FORM_EXPRESSION   *SuppressExpression;  // nesting inside of SuppressIf
} FORM_BROWSER_FORM;

#define FORM_BROWSER_FORM_FROM_LINK(a)  CR (a, FORM_BROWSER_FORM, Link, FORM_BROWSER_FORM_SIGNATURE)

#define FORMSET_DEFAULTSTORE_SIGNATURE  SIGNATURE_32 ('F', 'D', 'F', 'S')

typedef struct {
  UINTN            Signature;
  LIST_ENTRY       Link;

  UINT16           DefaultId;
  EFI_STRING_ID    DefaultName;
} FORMSET_DEFAULTSTORE;

#define STRING_NUMBER 100

typedef struct {
  EFI_STRING_ID    StringId;
  CHAR16           *String;
} STRING_INFO;

typedef struct {
  EFI_STRING_ID    CachedIdNum;
  EFI_STRING_ID    MaxIdNum;
  STRING_INFO      *StringInfoList;
} FORMSET_STRING_LIST;

#define FORMSET_DEFAULTSTORE_FROM_LINK(a)  CR (a, FORMSET_DEFAULTSTORE, Link, FORMSET_DEFAULTSTORE_SIGNATURE)

#define FORM_BROWSER_FORMSET_SIGNATURE  SIGNATURE_32 ('F', 'B', 'F', 'S')

typedef struct {
  UINTN                           Signature;
  LIST_ENTRY                      Link;

  UINT32                          FormSetOrder;

  UINTN                           IfrBinaryLength;
  UINT8                           *IfrBinaryData;
  UINT8                           *UnicodeBinary;

  EFI_GUID                        Guid;
  EFI_STRING_ID                   FormSetTitle;
  EFI_STRING_ID                   Help;
  UINT8                           NumberOfClassGuid;
  EFI_GUID                        ClassGuid[3];         // Up to three ClassGuid
  UINT16                          Class;                // Tiano extended Class code
  UINT16                          SubClass;             // Tiano extended Subclass code

  FORM_BROWSER_STATEMENT          *StatementBuffer;     // Buffer for all Statements and Questions
  EXPRESSION_OPCODE               *ExpressionBuffer;    // Buffer for all Expression OpCode

  LIST_ENTRY                      *StorageListHead;      // Storage list (FORMSET_STORAGE)
  LIST_ENTRY                      DefaultStoreListHead; // DefaultStore list (FORMSET_DEFAULTSTORE)
  LIST_ENTRY                      FormListHead;         // Form list (FORM_BROWSER_FORM)
  LIST_ENTRY                      ExpressionListHead;   // List of Expressions (FORM_EXPRESSION)
  FORMSET_STRING_LIST             EnUsStringList;      // Cache EN_US English list
  FORMSET_STRING_LIST             UqiStringList;       // Cache EN_US English list
} FORM_BROWSER_FORMSET;

#define FORM_BROWSER_FORMSET_FROM_LINK(a)  CR (a, FORM_BROWSER_FORMSET, Link, FORM_BROWSER_FORMSET_SIGNATURE)

///
/// Structure for multi-platform support
///
typedef struct {
  UINT16                 DefaultId[MAX_PLATFORM_DEFAULT_ID_NUM];
  UINT16                 DefaultIdNum;
  UINT64                 PlatformId[MAX_PLATFORM_DEFAULT_ID_NUM];
  UINT16                 PlatformIdNum;
  UINT16                 KeyDefaultId[MAX_PLATFORM_DEFAULT_ID_NUM];
  UINT64                 KeyPlatformId[MAX_PLATFORM_DEFAULT_ID_NUM];
  UINT16                 KeyIdNum;
  FORM_BROWSER_STATEMENT PlatformIdQuestion;
  FORM_BROWSER_STATEMENT *Question;
  UINT16                 PlatformIdWidth;
  UQI_HEADER             Uqi;
  BOOLEAN                MultiPlatformOrNot;
  BOOLEAN                ExistStorageFfsInBfv;
  BOOLEAN                SizeOptimized;
  BOOLEAN                SizeOptimizedParam;
} MULTI_PLATFORM_PARAMETERS;

/**
  Parse the UniString to get the string information.

  @param  CachedStringList  A pointer to cached string list
  @param  UniPackge         A pointer to a Null-terminated Unicode string Array.
  @param  VarDefaultNameId  The string ID.
  @param  Language          The language, en-US UQI or eng.
  @param  VarDefaultName    return the name string.

  @return EFI_SUCCESS       If get the name string successfully
  @return EFI_ABORTED       An error occurred.
  @return EFI_INVALID_PARAMETER

**/
EFI_STATUS
FindDefaultName (
  IN     FORMSET_STRING_LIST *CachedStringList,
  IN     UINT8               *UniPackge,
  IN     UINT16              VarDefaultNameId,
  IN     LANGUAGE            Language,
  IN OUT CHAR16              **VarDefaultName
  );

/**
  Search the variable list according to the variable Guid and name, and return the pointer
  of that Node.

  @param  HiiObjList       The pointer to the Question
  @param  VarName          The EFI variable name need to be updated to VarList
  @param  Offset           The offset of the variable
  @param  StorageListHead  The pointer to the LIST_ENTRY of Storage
  @param  Vaue             The value in that value offset of the variable
  @param  VarList          The dual pointer of Varlist

  @return EFI_SUCCESS
**/
EFI_STATUS
SearchVarStorage (
  IN     FORM_BROWSER_STATEMENT   *Question,
  IN     CHAR16*                  VarName,
  IN     UINT32                   Offset,
  IN     LIST_ENTRY               *StorageListHead,
  IN OUT CHAR8                    **Value,
  IN OUT FORMSET_STORAGE          **VarList
  );

/**
  Get the string based on the StringId and HII Package List Handle.

  @param  Token                  The String's ID.
  @param  HiiHandle              The package list in the HII database to search for
                                 the specified string.

  @return The output string.

**/
CHAR16 *
GetToken (
  IN  EFI_STRING_ID                Token,
  IN  UINT8                        *UniPackge
  );

/**
  Initialize Statement header members.

  @param  OpCodeData             Pointer of the raw OpCode data.
  @param  FormSet                Pointer of the current FormSe.
  @param  Form                   Pointer of the current Form.

  @return The Statement.

**/
FORM_BROWSER_STATEMENT *
CreateStatement (
  IN UINT8                        *OpCodeData,
  IN OUT FORM_BROWSER_FORMSET     *FormSet,
  IN OUT FORM_BROWSER_FORM        *Form
  );

/**
  Check if the next opcode is the EFI_IFR_EXTEND_OP_VAREQNAME.

  @param OpCodeData     The current opcode.

  @retval TRUE Yes.
  @retval FALSE No.
**/
BOOLEAN
IsNextOpCodeGuidedVarEqName (
  IN UINT8 *OpCodeData
  );

/**
  Initialize Question's members.

  @param  OpCodeData             Pointer of the raw OpCode data.
  @param  FormSet                Pointer of the current FormSet.
  @param  Form                   Pointer of the current Form.

  @return The Question.

**/
FORM_BROWSER_STATEMENT *
CreateQuestion (
  IN UINT8                        *OpCodeData,
  IN OUT FORM_BROWSER_FORMSET     *FormSet,
  IN OUT FORM_BROWSER_FORM        *Form
  );


/**
  Allocate a FORM_EXPRESSION node.

  @param  Form                   The Form associated with this Expression

  @return Pointer to a FORM_EXPRESSION data structure.

**/
FORM_EXPRESSION *
CreateExpression (
  IN OUT FORM_BROWSER_FORM        *Form
  );


/**
  Allocate a FORMSET_STORAGE data structure and insert to FormSet Storage List.

  @param  FormSet                Pointer of the current FormSet

  @return Pointer to a FORMSET_STORAGE data structure.

**/
FORMSET_STORAGE *
CreateStorage (
  IN FORM_BROWSER_FORMSET  *FormSet
  );

/**
  Free resources of a Expression.

  @param  FormSet                Pointer of the Expression

**/
VOID
DestroyExpression (
  IN FORM_EXPRESSION   *Expression
  );


/**
  Free resources of a storage.

  @param  Storage                Pointer of the storage

**/
VOID
DestroyStorage (
  IN FORMSET_STORAGE   *Storage
  );

/**
  Free resources allocated for all Storage in an LIST_ENTRY.

  @param  FormSet                Pointer of the FormSet

**/
VOID
DestroyAllStorage (
  IN LIST_ENTRY    *StorageEntryListHead
  );

/**
  Free resources of a Statement.

  @param  FormSet                Pointer of the FormSet
  @param  Statement              Pointer of the Statement

**/
VOID
DestroyStatement (
  IN     FORM_BROWSER_FORMSET    *FormSet,
  IN OUT FORM_BROWSER_STATEMENT  *Statement
  );


/**
  Free resources of a Form.

  @param  FormSet                Pointer of the FormSet
  @param  Form                   Pointer of the Form.

**/
VOID
DestroyForm (
  IN     FORM_BROWSER_FORMSET  *FormSet,
  IN OUT FORM_BROWSER_FORM     *Form
  );


/**
  Free resources allocated for a FormSet.

  @param  FormSet                Pointer of the FormSet

**/
VOID
DestroyFormSet (
  IN FORM_BROWSER_FORMSET  *FormSet
  );


/**
  Free resources allocated for all FormSet in an LIST_ENTRY.

  @param  FormSet                Pointer of the FormSet

**/
VOID
DestroyAllFormSet (
  IN LIST_ENTRY    *FormSetEntryListHead
  );

/**
  Tell whether this Operand is an Expression OpCode or not

  @param  Operand                Operand of an IFR OpCode.

  @retval TRUE                   This is an Expression OpCode.
  @retval FALSE                  Not an Expression OpCode.

**/
BOOLEAN
IsExpressionOpCode (
  IN UINT8              Operand
  );


/**
  Calculate number of Statemens(Questions) and Expression OpCodes.

  @param  FormSet                The FormSet to be counted.
  @param  NumberOfStatement      Number of Statemens(Questions)
  @param  NumberOfExpression     Number of Expression OpCodes

**/
VOID
CountOpCodes (
  IN      FORM_BROWSER_FORMSET  *FormSet,
  IN OUT  UINT16                *NumberOfStatement,
  IN OUT  UINT16                *NumberOfExpression
  );

/**
  Parse opcodes in the formset IFR binary.

  @param  FormSet                Pointer of the FormSet data structure.

  @retval EFI_SUCCESS            Opcode parse success.
  @retval Other                  Opcode parse fail.

**/
EFI_STATUS
ParseOpCodes (
  IN FORM_BROWSER_FORMSET        *FormSet
  );

/**
  Reset Question to its default value.

  @param  FormSet                The form set.
  @param  Form                   The form.
  @param  Question               The question.
  @param  DefaultId              The default Id.
  @param  DefaultId              The platform Id.

  @retval EFI_SUCCESS            Question is reset to default value.

**/
EFI_STATUS
GetQuestionDefault (
  IN FORM_BROWSER_FORMSET             *FormSet,
  IN FORM_BROWSER_FORM                *Form,
  IN FORM_BROWSER_STATEMENT           *Question,
  IN UINT16                           DefaultId,
  IN UINT64                           PlatformId
  );

/**
  Set the value to the variable of platformId question.

  @param  PlatformId             The form set.

  @retval EFI_SUCCESS            Set successfully.

**/
EFI_STATUS
AssignThePlatformId (
  IN  UINT64   PlatformId
  );

/**
  Save Question Value to edit copy(cached).

  @param  FormSet                FormSet data structure.
  @param  Form                   Form data structure.
  @param  Question               Pointer to the Question.
  @param  DefaultId              The default Id.
  @param  DefaultId              The platform Id.

  @retval EFI_SUCCESS            The function completed successfully.

**/
EFI_STATUS
SetQuestionValue (
  IN FORM_BROWSER_FORMSET             *FormSet,
  IN FORM_BROWSER_FORM                *Form,
  IN OUT FORM_BROWSER_STATEMENT       *Question,
  IN UINT16                           DefaultId,
  IN UINT64                           PlatformId
  );


/**
  Reset Questions to their default value in a Form, Formset or System.

  @param  FormSet                FormSet data structure.
  @param  Form                   Form data structure.
  @param  DefaultId              The default Id
  @param  PlatformId             The platform Id
  @param  SettingScope           Setting Scope for Default action.

  @retval EFI_SUCCESS            The function completed successfully.
  @retval EFI_UNSUPPORTED        Unsupport SettingScope.

**/
EFI_STATUS
ExtractDefault (
  IN FORM_BROWSER_FORMSET             *FormSet,
  IN FORM_BROWSER_FORM                *Form,
  IN UINT16                           DefaultId,
  IN UINT64                           PlatformId,
  IN BROWSER_SETTING_SCOPE            SettingScope
  );

/**
  Get Value for given Name from a NameValue Storage.

  @param  Storage                The NameValue Storage.
  @param  Name                   The Name.
  @param  Value                  The retured Value.

  @retval EFI_SUCCESS            Value found for given Name.
  @retval EFI_NOT_FOUND          No such Name found in NameValue storage.

**/
EFI_STATUS
GetValueByName (
  IN FORMSET_STORAGE         *Storage,
  IN CHAR16                  *Name,
  IN OUT CHAR16              **Value
  );

/**
  Grow size of the stack.

  This is an internal function.

  @param  Stack                  On input: old stack; On output: new stack
  @param  StackPtr               On input: old stack pointer; On output: new stack
                                 pointer
  @param  StackEnd               On input: old stack end; On output: new stack end

  @retval EFI_SUCCESS            Grow stack success.
  @retval EFI_OUT_OF_RESOURCES   No enough memory for stack space.

**/
EFI_STATUS
GrowStack (
  IN OUT EFI_HII_VALUE  **Stack,
  IN OUT EFI_HII_VALUE  **StackPtr,
  IN OUT EFI_HII_VALUE  **StackEnd
  );

/**
  Push an element onto the Boolean Stack.

  @param  Stack                  On input: old stack; On output: new stack
  @param  StackPtr               On input: old stack pointer; On output: new stack
                                 pointer
  @param  StackEnd               On input: old stack end; On output: new stack end
  @param  Data                   Data to push.

  @retval EFI_SUCCESS            Push stack success.

**/
EFI_STATUS
PushStack (
  IN OUT EFI_HII_VALUE       **Stack,
  IN OUT EFI_HII_VALUE       **StackPtr,
  IN OUT EFI_HII_VALUE       **StackEnd,
  IN EFI_HII_VALUE           *Data
  );

/**
  Pop an element from the stack.

  @param  Stack                  On input: old stack
  @param  StackPtr               On input: old stack pointer; On output: new stack pointer
  @param  Data                   Data to pop.

  @retval EFI_SUCCESS            The value was popped onto the stack.
  @retval EFI_ACCESS_DENIED      The pop operation underflowed the stack

**/
EFI_STATUS
PopStack (
  IN  EFI_HII_VALUE          *Stack,
  IN OUT EFI_HII_VALUE       **StackPtr,
  OUT EFI_HII_VALUE          *Data
  );


/**
  Reset stack pointer to begin of the stack.

**/
VOID
ResetCurrentExpressionStack (
  VOID
  );


/**
  Push current expression onto the Stack

  @param  Pointer                Pointer to current expression.

  @retval EFI_SUCCESS            The value was pushed onto the stack.
  @retval EFI_OUT_OF_RESOURCES   There is not enough system memory to grow the stack.

**/
EFI_STATUS
PushCurrentExpression (
  IN VOID  *Pointer
  );


/**
  Pop current expression from the Stack

  @param  Pointer                Pointer to current expression to be pop.

  @retval EFI_SUCCESS            The value was pushed onto the stack.
  @retval EFI_OUT_OF_RESOURCES   There is not enough system memory to grow the stack.

**/
EFI_STATUS
PopCurrentExpression (
  OUT VOID    **Pointer
  );

/**
  Reset stack pointer to begin of the stack.

**/
VOID
ResetMapExpressionListStack (
  VOID
  );


/**
  Push the list of map expression onto the Stack

  @param  Pointer                Pointer to the list of map expression to be pushed.

  @retval EFI_SUCCESS            The value was pushed onto the stack.
  @retval EFI_OUT_OF_RESOURCES   There is not enough system memory to grow the stack.

**/
EFI_STATUS
PushMapExpressionList (
  IN VOID  *Pointer
  );


/**
  Pop the list of map expression from the Stack

  @param  Pointer                Pointer to the list of map expression to be pop.

  @retval EFI_SUCCESS            The value was pushed onto the stack.
  @retval EFI_OUT_OF_RESOURCES   There is not enough system memory to grow the stack.

**/
EFI_STATUS
PopMapExpressionList (
  OUT VOID    **Pointer
  );

/**
  Reset stack pointer to begin of the stack.

**/
VOID
ResetScopeStack (
  VOID
  );


/**
  Push an Operand onto the Stack

  @param  Operand                Operand to push.

  @retval EFI_SUCCESS            The value was pushed onto the stack.
  @retval EFI_OUT_OF_RESOURCES   There is not enough system memory to grow the
                                 stack.

**/
EFI_STATUS
PushScope (
  IN UINT8   Operand
  );


/**
  Pop an Operand from the Stack

  @param  Operand                Operand to pop.

  @retval EFI_SUCCESS            The value was pushed onto the stack.
  @retval EFI_OUT_OF_RESOURCES   There is not enough system memory to grow the
                                 stack.

**/
EFI_STATUS
PopScope (
  OUT UINT8     *Operand
  );


/**
  Push an Expression value onto the Stack

  @param  Value                  Expression value to push.

  @retval EFI_SUCCESS            The value was pushed onto the stack.
  @retval EFI_OUT_OF_RESOURCES   There is not enough system memory to grow the
                                 stack.

**/
EFI_STATUS
PushExpression (
  IN EFI_HII_VALUE  *Value
  );


/**
  Pop an Expression value from the stack.

  @param  Value                  Expression value to pop.

  @retval EFI_SUCCESS            The value was popped onto the stack.
  @retval EFI_ACCESS_DENIED      The pop operation underflowed the stack

**/
EFI_STATUS
PopExpression (
  OUT EFI_HII_VALUE  *Value
  );

/**
  Get current stack offset from stack start.

  @return Stack offset to stack start.
**/
UINTN
SaveExpressionEvaluationStackOffset (
  );

/**
  Restore stack offset based on input stack offset

  @param  StackOffset  Offset to stack start.

**/
VOID
RestoreExpressionEvaluationStackOffset (
  UINTN StackOffset
  );

/**
  Get Form given its FormId.

  @param  FormSet                The formset which contains this form.
  @param  FormId                 Id of this form.

  @retval Pointer                The form.
  @retval NULL                   Specified Form is not found in the formset.

**/
FORM_BROWSER_FORM *
IdToForm (
  IN FORM_BROWSER_FORMSET  *FormSet,
  IN UINT16                FormId
);


/**
  Search a Question in Form scope using its QuestionId.

  @param  Form                   The form which contains this Question.
  @param  QuestionId             Id of this Question.

  @retval Pointer                The Question.
  @retval NULL                   Specified Question not found in the form.

**/
FORM_BROWSER_STATEMENT *
IdToQuestion2 (
  IN FORM_BROWSER_FORM  *Form,
  IN UINT16             QuestionId
  );


/**
  Search a Question in Formset scope using its QuestionId.

  @param  FormSet                The formset which contains this form.
  @param  Form                   The form which contains this Question.
  @param  QuestionId             Id of this Question.

  @retval Pointer                The Question.
  @retval NULL                   Specified Question not found in the form.

**/
FORM_BROWSER_STATEMENT *
IdToQuestion (
  IN FORM_BROWSER_FORMSET  *FormSet,
  IN FORM_BROWSER_FORM     *Form,
  IN UINT16                QuestionId
  );


/**
  Get Expression given its RuleId.

  @param  Form                   The form which contains this Expression.
  @param  RuleId                 Id of this Expression.

  @retval Pointer                The Expression.
  @retval NULL                   Specified Expression not found in the form.

**/
FORM_EXPRESSION *
RuleIdToExpression (
  IN FORM_BROWSER_FORM  *Form,
  IN UINT8              RuleId
  );

/**
  Convert the input Unicode character to upper.

  @param String  Th Unicode character to be converted.

**/
VOID
IfrStrToUpper (
  IN CHAR16                   *String
  );

/**
  Evaluate opcode EFI_IFR_TO_STRING.

  @param  FormSet                Formset which contains this opcode.
  @param  Format                 String format in EFI_IFR_TO_STRING.
  @param  Result                 Evaluation result for this opcode.

  @retval EFI_SUCCESS            Opcode evaluation success.
  @retval Other                  Opcode evaluation failed.

**/
EFI_STATUS
IfrToString (
  IN FORM_BROWSER_FORMSET  *FormSet,
  IN UINT8                 Format,
  OUT  EFI_HII_VALUE       *Result
  );

/**
  Evaluate opcode EFI_IFR_TO_UINT.

  @param  FormSet                Formset which contains this opcode.
  @param  Result                 Evaluation result for this opcode.

  @retval EFI_SUCCESS            Opcode evaluation success.
  @retval Other                  Opcode evaluation failed.

**/
EFI_STATUS
IfrToUint (
  IN FORM_BROWSER_FORMSET  *FormSet,
  OUT  EFI_HII_VALUE       *Result
  );

/**
  Evaluate opcode EFI_IFR_CATENATE.

  @param  FormSet                Formset which contains this opcode.
  @param  Result                 Evaluation result for this opcode.

  @retval EFI_SUCCESS            Opcode evaluation success.
  @retval Other                  Opcode evaluation failed.

**/
EFI_STATUS
IfrCatenate (
  IN FORM_BROWSER_FORMSET  *FormSet,
  OUT  EFI_HII_VALUE       *Result
  );

/**
  Evaluate opcode EFI_IFR_MATCH.

  @param  FormSet                Formset which contains this opcode.
  @param  Result                 Evaluation result for this opcode.

  @retval EFI_SUCCESS            Opcode evaluation success.
  @retval Other                  Opcode evaluation failed.

**/
EFI_STATUS
IfrMatch (
  IN FORM_BROWSER_FORMSET  *FormSet,
  OUT  EFI_HII_VALUE       *Result
  );


/**
  Evaluate opcode EFI_IFR_FIND.

  @param  FormSet                Formset which contains this opcode.
  @param  Format                 Case sensitive or insensitive.
  @param  Result                 Evaluation result for this opcode.

  @retval EFI_SUCCESS            Opcode evaluation success.
  @retval Other                  Opcode evaluation failed.

**/
EFI_STATUS
IfrFind (
  IN FORM_BROWSER_FORMSET  *FormSet,
  IN UINT8                 Format,
  OUT  EFI_HII_VALUE       *Result
  );


/**
  Evaluate opcode EFI_IFR_MID.

  @param  FormSet                Formset which contains this opcode.
  @param  Result                 Evaluation result for this opcode.

  @retval EFI_SUCCESS            Opcode evaluation success.
  @retval Other                  Opcode evaluation failed.

**/
EFI_STATUS
IfrMid (
  IN FORM_BROWSER_FORMSET  *FormSet,
  OUT  EFI_HII_VALUE       *Result
  );

/**
  Evaluate opcode EFI_IFR_TOKEN.

  @param  FormSet                Formset which contains this opcode.
  @param  Result                 Evaluation result for this opcode.

  @retval EFI_SUCCESS            Opcode evaluation success.
  @retval Other                  Opcode evaluation failed.

**/
EFI_STATUS
IfrToken (
  IN FORM_BROWSER_FORMSET  *FormSet,
  OUT  EFI_HII_VALUE       *Result
  );


/**
  Evaluate opcode EFI_IFR_SPAN.

  @param  FormSet                Formset which contains this opcode.
  @param  Flags                  FIRST_MATCHING or FIRST_NON_MATCHING.
  @param  Result                 Evaluation result for this opcode.

  @retval EFI_SUCCESS            Opcode evaluation success.
  @retval Other                  Opcode evaluation failed.

**/
EFI_STATUS
IfrSpan (
  IN FORM_BROWSER_FORMSET  *FormSet,
  IN UINT8                 Flags,
  OUT  EFI_HII_VALUE       *Result
  );


/**
  Zero extend integer/boolean/date/time to UINT64 for comparing.

  @param  Value                  HII Value to be converted.

**/
VOID
ExtendValueToU64 (
  IN  EFI_HII_VALUE   *Value
  );


/**
  Compare two Hii value.

  @param  Value1                 Expression value to compare on left-hand.
  @param  Value2                 Expression value to compare on right-hand.

  @retval EFI_INVALID_PARAMETER  Could not perform compare on two values.
  @retval 0                      Two operators equal.
  @return Positive value if Value1 is greater than Value2.
  @retval Negative value if Value1 is less than Value2.

**/
INTN
CompareHiiValue (
  IN  EFI_HII_VALUE        *Value1,
  IN  EFI_HII_VALUE        *Value2,
  IN FORM_BROWSER_FORMSET  *FormSet
  );

/**
  Evaluate the result of a HII expression.

  If Expression is NULL, then ASSERT.

  @param  FormSet                FormSet associated with this expression.
  @param  Form                   Form associated with this expression.
  @param  Expression             Expression to be evaluated.
  @param  ConstantExpression     The pointer to the flag of constant expression. If constant, will return TRUE.

  @retval EFI_SUCCESS            The expression evaluated successfuly
  @retval EFI_NOT_FOUND          The Question which referenced by a QuestionId
                                 could not be found.
  @retval EFI_OUT_OF_RESOURCES   There is not enough system memory to grow the
                                 stack.
  @retval EFI_ACCESS_DENIED      The pop operation underflowed the stack
  @retval EFI_INVALID_PARAMETER  Syntax error with the Expression

**/
EFI_STATUS
EvaluateExpression (
  IN FORM_BROWSER_FORMSET  *FormSet,
  IN FORM_BROWSER_FORM     *Form,
  IN OUT FORM_EXPRESSION   *Expression,
  IN OUT BOOLEAN           *ConstantExpression
  );

/**
  Compare two Uqi parameters

  @param UqiParm1       The pointer to the first Uqi parameter.
  @param UqiParm2       The pointer to the second Uqi parameter.

  @retval TRUE          If these two Uqi parameters are the same, return TRUE;
  @return FALSE         Otherwise, return FALSE;
**/
BOOLEAN
CompareUqiHeader (
  IN  CONST UQI_HEADER  *UqiParm1,
  IN  CONST UQI_HEADER  *UqiParm2
  );


/**
  Print all ONE_OF ORDER_LIST NUMERIC STRING and CHECKBOX in all fromsets.

  @param Formset        The pointer to the entry of the fromset list
  @param Formset        The pointer to the entry of the storage list

  @retval EFI_SUCCESS   It was complete successfully
  @return EFI_ABORTED   An error occurred
**/
EFI_STATUS
PrintInfoInAllFormset (
  IN LIST_ENTRY      *FormSetEntryListHead,
  IN LIST_ENTRY      *StorageEntryListHead
  );

 /**
  Get the question value with bit field from the buffer.

  @param  Question        The question refer to bit field.
  @param  Buffer          The buffer which the question value get from.
  @param  Value           Retun the value.

**/
VOID
GetBitsQuestionValue(
  IN  FORM_BROWSER_STATEMENT *Question,
  IN  UINT8                  *Buffer,
  OUT UINT32                 *Value
  );

/**
  Set the question value with bit field to the buffer.

  @param  Question        The question refer to bit field.
  @param  Buffer          The buffer which the question value set to.
  @param  Value           The value need to set.

**/
VOID
SetBitsQuestionValue (
  IN FORM_BROWSER_STATEMENT *Question,
  IN UINT8                  *Buffer,
  IN UINT32                 Value
  );

#endif
