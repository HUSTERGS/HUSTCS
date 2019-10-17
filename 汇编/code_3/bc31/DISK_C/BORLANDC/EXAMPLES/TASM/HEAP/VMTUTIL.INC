; File: VMTUTIL.INC
;Copyright (c) 1991 By Borland International, Inc.

;********** VMT Utilities *************
; Setup area for the VMT segments
if (@CodeSize eq 0)

;*** Handle VMT utilities for small code model programs.

    vmtseg macro   ; Macro to switch to where the VMT's are stored
    .code
           endm

    @vmtseg = @code

    LoadVMTSeg macro reg,tempreg
               push cs
               pop  es
    endm

    mptr equ <word>
else

;*** Handle VMT utilities for large and huge code models

    ; Declare a separate segment for the VMT's
    vmt_seg segment public
    vmt_seg ends

    vmtseg macro

    vmt_seg segment
           endm

    @vmtseg   = vmt_seg

    LoadVMTSeg_ macro reg,tempreg
    ifidni <reg>,<tempreg>
               mov   reg,@vmtseg
    else
               mov   tempreg,@vmtseg
               mov   reg,tempreg
    endif
    endm

    LoadVMTSeg  macro reg,tempreg
    ifb    <tempreg>
               push  bx
              ; Use BX as the temp since it is destroyed during the call!
               LoadVMTSeg_ reg,bx
               pop   bx
    else
               LoadVMTSeg_ reg,tempreg
    endif
               endm

    mptr equ <dword>
endif


MAKE_VMT   macro
vmtseg
TBLINST     ; Create the virtual table for the memory_block
ends
.code
           endm


