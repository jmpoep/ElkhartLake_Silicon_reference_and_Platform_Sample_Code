;;@file
;   Processor reference code macros.
;
;@copyright
; Copyright (c) 2007 - 2014 Intel Corporation. All rights reserved
; This software and associated documentation (if any) is furnished
; under a license and may only be used or copied in accordance
; with the terms of the license. Except as permitted by the
; license, no part of this software or documentation may be
; reproduced, stored in a retrieval system, or transmitted in any
; form or by any means without the express written consent of
; Intel Corporation.
; This file contains an 'Intel Peripheral Driver' and is uniquely
; identified as "Intel Reference Module" and is licensed for Intel
; CPUs and chipsets under the terms of your license agreement with
; Intel or your vendor. This file may be modified by the user, subject
; to additional terms of the license agreement.
;
;@par Specification Reference:
;;


IFNDEF CRCMACROS_INC
CRCMACROS_INC EQU   1

;----------------------------
; Macro -- CALL_STACK
;
; Purpose: This macro is used to enable a call/return procedure functionality 
;     in a no memory (stackless) environment. Since no memory is available, 
;     the standard stack-based instructions (push, pop, call, return, ret) 
;     cannot be used. 
;
; Step 1: Create a label in the code to be used as the return address
;     Normally the call instruction would push the return address onto the 
;     stack; but no memory exists, so determine the return address using a
;     label.
;
; Step 2: Create a stack inline in the code during compile time
;     Ensure stack is align on dword boundary (use align 4 directive)
;     First dword in this stack is the return address
;     Additional dword values can be optionally added to this stack 
;     (after the return address) as input parameters to the called 
;     routine
;
;     Sample stack 
;     Assumptions: 32-bit flat mode so return address is 32-bit offset 
;     (i.e. segment for the return address is not needed) 
;
;     align 4
;     callStack:
;        ESP + 0 --> dword return address  
;        ESP + 4 --> last dword parameter pushed on the stack
;        ESP + 8 --> first dword parameter pushed on the stack
;
; Step 3: Move the address of the stack into ESP.
;        mov esp, offset CallStack
;
; Step 4: Simulate call by jumping to start address of the called routine
;     jmp   offset of the called routine
;
; Step 5: Use "ret" instruction at end of the called routine
;     ret   ; Routine exit
;
; Advantages:
; (1) Assuming the called routine does not use push or pop instructions, 
;     the called routine can be used in no-memory or memory environment. 
;     In memory environment, "push" instructions is used to put input 
;     parameters onto the stack and the "call" instruction automatically 
;     pushes the return address onto the stack and braches to the called 
;     routine. Stack-based input parameters are retreived from the stack
;     using offsets from ESP. Then at the end of the routine, the "ret"  
;     instruction simply branches to return address pointed at by ESP.
;     In the no memory (stackless) environment, "push" instruction is not
;     usable so the input input paramters are simply placed on the in-line 
;     stack built within the code. The "call" instruction is not usable
;     since it pushes the return address onto the stack. So the return 
;     address is added to theinline stack also. Then a "jmp" instruction
;     is used to branch to the called routine. Stack-based input parameters
;     are retreived from the simulated stack stack using offsets from ESP. 
;     Then at the end of the routine, the "ret" instruction simply branches 
;     to return address pointed at by ESP.
; (2) Under ITP or in a simulated run environment, the "Step Out" feature 
;     can used. The "Step Out" is simply looking for the next "ret" 
;     instruction, so if you advance into a routine you can hit "Step Out"
;     to exit this routine and get back into the calling routine.
; (3) Stack-based input parameters can be used even in no memory environment.
;
; Register Usage:
;     ESP is destroyed
;     All other registers are preserved
;
; Calling routine syntax:
;     CALL_STACK stacklessRoutine
;
; Called routine syntax:
;     [Routine exit]
;     ret
;----------------------------
CALL_STACK  macro RoutineLabel
   local CallStackLabel, ReturnAddressLabel
   
ifndef CALL_STACK_CNT
   CALL_STACK_CNT = 0
endif
   CALL_STACK_CNT = CALL_STACK_CNT +1

CallStackLabel       textequ @CatStr(CallStack,%CALL_STACK_CNT)
ReturnAddressLabel   textequ @CatStr(ReturnAddress,%CALL_STACK_CNT)
@CatStr(ParamCount,%CALL_STACK_CNT) = 0

externdef   RoutineLabel:NEAR32
   mov   esp, offset @CatStr(CallStack,%CALL_STACK_CNT)
   jmp   RoutineLabel

  ; Label for the return address    
@CatStr(ReturnAddress,%CALL_STACK_CNT)::
ENDM

;----------------------------
;----------------------------
MAKE_STACKS  macro
   local CallStackLabel, ReturnAddressLabel
   
align 4
CALL_STACKS_START:
count = 1
; Hard-coded call stack created directly in code 
   REPEAT   CALL_STACK_CNT
CallStackLabel       textequ @CatStr(CallStack,%count)   
@CatStr(CallStack,%count)::
ReturnAddressLabel   textequ @CatStr(ReturnAddress,%count)
   DD    offset @CatStr(ReturnAddress,%count)
ParamCountLabel      textequ @CatStr(ParamCount,%count)    
if @CatStr(ParamCount,%count) GE 1
ParamLabel           textequ @CatStr(ParamValue,%count)    
   DD    @CatStr(ParamValue,%count)
endif
   count = count + 1
   ENDM

CALL_STACKS_SIZE  EQU $ - CALL_STACKS_START
   
ENDM

;----------------------------
;Macro -- CALL_STACK_PARAM
;
; Purpose: This macro is used to enable a call/return procedure functionality 
;     in a no memory (stackless) environment. Since no memory is available, 
;     the standard stack-based instructions (push, pop, call, return, ret) 
;     cannot be used. 
;
; Step 1: Create a label in the code to be used as the return address
;     Normally the call instruction would push the return address onto the 
;     stack; but no memory exists, so determine the return address using a
;     label.
; Step 2: Create a stack inline in the code during compile time
;     Ensure stack is align on dword boundary (use align 4 directive)
;     First dword in this stack is the return address
;     Additional dword values can be optionally added to this stack 
;     (after the return address) as input parameters to the called 
;     routine
;
;     Sample stack 
;     Assumptions: 32-bit flat mode so return address is 32-bit offset 
;     (i.e. segment for the return address is not needed) 
;
;     align 4
;     callStack:
;        ESP + 0 --> dword return address  
;        ESP + 4 --> last dword parameter pushed on the stack
;        ESP + 8 --> first dword parameter pushed on the stack
;
; Step 3: Move the address of the stack into ESP.
;        mov esp, offset CallStack
;
; Step 4: Simulate call by jumping to start address of the called routine
;     jmp   offset of the called routine
;
; Step 5: Use "ret" instruction at end of the called routine
;     ret   ; Routine exit
;
; Advantages:
; (1) Assuming the called routine does not use push or pop instructions, 
;     the called routine can be used in no-memory or memory environment. 
;     In memory environment, "push" instructions is used to put input 
;     parameters onto the stack and the "call" instruction automatically 
;     pushes the return address onto the stack and braches to the called 
;     routine. Stack-based input parameters are retreived from the stack
;     using offsets from ESP. Then at the end of the routine, the "ret"  
;     instruction simply branches to return address pointed at by ESP.
;     In the no memory (stackless) environment, "push" instruction is not
;     usable so the input input paramters are simply placed on the in-line 
;     stack built within the code. The "call" instruction is not usable
;     since it pushes the return address onto the stack. So the return 
;     address is added to theinline stack also. Then a "jmp" instruction
;     is used to branch to the called routine. Stack-based input parameters
;     are retreived from the simulated stack stack using offsets from ESP. 
;     Then at the end of the routine, the "ret" instruction simply branches 
;     to return address pointed at by ESP.
; (2) Under ITP or in a simulated run environment, the "Step Out" feature 
;     can used. The "Step Out" is simply looking for the next "ret" 
;     instruction, so if you advance into a routine you can hit "Step Out"
;     to exit this routine and get back into the calling routine.
; (3) Stack-based input parameters can be used even in no memory environment.
;
; Register Usage:
;     ESP is destroyed
;     All other registers are preserved
;
; Calling routine syntax:
;     CALL_STACK_PARAM stacklessRoutine, param
;
; Called routine syntax:
;     [Routine entry]
;     Using a local stack frame to simplify the changes to this routine
;     param TEXTEQU <dword ptr [esp+4]>
;     mov   eax, param

;     [Routine exit]
;     ret
;----------------------------
CALL_STACK_PARAM  macro RoutineLabel, Param
   local CallStackLabel, ReturnAddressLabel
   
ifndef CALL_STACK_CNT
   CALL_STACK_CNT = 0
endif
   CALL_STACK_CNT = CALL_STACK_CNT +1

CallStackLabel       textequ @CatStr(CallStack,%CALL_STACK_CNT)
ReturnAddressLabel   textequ @CatStr(ReturnAddress,%CALL_STACK_CNT)

@CatStr(ParamCount,%CALL_STACK_CNT) = 1
@CatStr(ParamValue,%CALL_STACK_CNT) = Param

externdef   RoutineLabel:NEAR32
   mov   esp, offset @CatStr(CallStack,%CALL_STACK_CNT)
   jmp   RoutineLabel

  ; Label for the return address    
@CatStr(ReturnAddress,%CALL_STACK_CNT)::
ENDM


ENDIF    ;IFNDEF CRCMACROS_INC
