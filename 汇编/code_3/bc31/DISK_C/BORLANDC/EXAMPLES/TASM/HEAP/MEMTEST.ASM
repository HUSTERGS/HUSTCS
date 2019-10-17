page 75,132
%title "Object Oriented Memory Management System - TASM 3.0"
%subttl "Testing/Benchmark module"
; Copyright (c) 1991 By Borland International, Inc.

ifndef MDL
    display "Error: This module requires that you provide a memory model"
    display "    definition on the command line. I.E. /dMDL=SMALL."
    display "Also, /M must be given on the command line to enable multiple"
    display "    passes."

MDL equ <SMALL>

endif



ModuleVersion EQU "0.32"

jumps
page
locals @@

; Things to check:
;   Check the effect of /ML  on generated macros for method calls.


.model MDL,pascal
.stack 1000h
.code

CR  = 0DH
LF  = 0AH

; Int 21 DOS calls
DOSINT             =   21H
DOSRESIZEBLOCK     =   4AH
DOSPRINTSTRING     =   09H
DOSTERMINATE       =   4CH

include vmtutil.inc

; Include the display routines
   include display.inc

; Include definitions of the memory system objects
   include mem.inc


; Create an advanced decendant of the memory_system !

memory_system_advanced STRUC memory_system METHOD \
         init:mptr=memory_system_advanced_init,\
         virtual show:mptr=memory_system_advanced_show
  diskhandle dw ?
memory_system_advanced ends

memory_system_advanced_init proc
        ; Must fill in the VMT pointer
         mov  [ds:si.@Mptr_memory_system],offset @TableAddr_memory_system_advanced
         mov  [ds:si.root],0
         mov  [ds:si.last],0
         mov  [ds:si.rover],0
         mov  [ds:si.freespace],0
         mov  [ds:si.usedspace],0
         ret
memory_system_advanced_init endp

.data
msas_advanced db "Advanced $"
.code
memory_system_advanced_show proc
         push  ds
         mov   ax,@data
         mov   ds,ax
         mov   dx,offset msas_advanced
         mov   ah,DOSPRINTSTRING
         int   21h
         pop   ds
         call  +@Table_memory_system|show
         ret
memory_system_advanced_show endp


; Make the advanced memory system VMT.
MAKE_VMT


.data

; Declare an instance of the memory system. Note that multiple memory
; system instances can be declared and if each is initialized with AX
; other than zero, they each will manage separate heaps.
memory   memory_system {}


memorya  memory_system_advanced {@Mptr_memory_system = @TableAddr_memory_system_advanced}

Psp      dw ?               ; Our PSP
LastSeg  dw seg zzlastseg   ; Segment of the last segment in memory

block1   dw ?
block2   dw ?
block3   dw ?
block4   dw ?
         dw 20000 dup (?)

.code
start_:

     ; Load our data segment
     mov  ax,@data
     mov  ds,ax

     ; Store the original PSP in case it is needed.
     mov  [Psp],es

     ; Have to give up extra memory that we don't need
     ; so the memory system objects can get blocks of memory.
     mov  bx,[LastSeg]
     mov  ax,es
     sub  bx,ax    ; Size of program as a number of segments is in BX
     mov  ah,DOSRESIZEBLOCK
     int  DOSINT


     ; Initialize the memory system
     mov  si,offset memory


comment ~
     ; Only allow memory system to grab 300 paragraphs of memory
     mov  ax,300


     ; Set ES to point to the virtual tables!
     LoadVMTSeg  ES
     call [si] method memory_system:init
     call [si] method memory_system:show

     mov  cx,100
     mov  di,offset block1
t1:
     mov  ax,2
     call [si] method memory_system:alloc
     mov  [di],ax
     add  di,2
     loop t1

     call [si] method memory_system:show
     call CRLF
     call CRLF

     mov  cx,100
     mov  di,offset block1
t2:
     mov  ax,[di]
     call [si] method memory_system:free
     mov  word ptr [di],0
     add  di,2
     loop t2

     call [si] method memory_system:show
     call CRLF
     call CRLF



     mov  ax,90
     call [si] method memory_system:alloc
     mov  [block1],ax
     call [si] method memory_system:show

     mov  ax,90
     call [si] method memory_system:alloc
     mov  [block2],ax
     call [si] method memory_system:show

     mov  ax,90
     call [si] method memory_system:alloc
     mov  [block3],ax
     call [si] method memory_system:show


     mov  ax,[block2]
     call [si] method memory_system:free
     call [si] method memory_system:show

     mov  ax,[block1]
     call [si] method memory_system:free
     call [si] method memory_system:show

     mov  ax,[block3]
     call [si] method memory_system:free
     call [si] method memory_system:show
     call CRLF
     call CRLF

~
     ; Allow memory system to grab all the memory it can
     mov  ax,0


     ; Set ES to point to the virtual tables!
     LoadVMTSeg  ES
     call [si] method memory_system:init
     call [si] method memory_system:show


; Test using memory_system:alloc and memory_block:markfree
blockcount=2000

     ; Get 20 blocks of various sizes
     mov  cx,blockcount
     mov  di,offset block1
again:
     mov  ax,cx
     and  ax,0fh
     cmp  al,0
     jne  again_2
;     call [si] method memory_system:show
again_2:
     inc  ax
     inc  ax
     call [si] method memory_system:alloc
     mov  [di],ax
     inc  di
     inc  di
     loop again

;     call [si] method memory_system:show
;     call CRLF
;     call CRLF

     xor  si,si
     ; Now free up half of them
     mov  cx,blockcount/2
     mov  di,offset block1
again_3:
     mov  ax,cx
     and  ax,0fh
     cmp  al,0
     jne  again_4
;     call [si] method memory_system:show
again_4:
     mov  ax,[di]
     mov  word ptr [di],0
     cmp  ax,0
     je   again_5
     push ds
     mov  ds,ax
     call [si] method memory_block:MarkFree
     pop  ds
again_5:
     add  di,4
     loop again_3

;     call [si] method memory_system:show
;     call CRLF
;     call CRLF

     ; Now free up all the rest
     mov  cx,blockcount
     mov  di,offset block1
again_6:
     mov  ax,cx
     and  ax,0fh
     cmp  al,0
     jne  again_7
;     call [si] method memory_system:show
again_7:
     mov  ax,[di]
     mov  word ptr [di],0
     cmp  ax,0
     je   again_8
     push ds
     mov  ds,ax
     call [si] method memory_block:MarkFree
     pop  ds

again_8:
     add  di,2
     loop again_6

;     call [si] method memory_system:show
;     call CRLF
;     call CRLF

     mov  si,offset memory
     ; Now allocate 13 very large blocks
     mov  cx,13
     mov  di,offset block1
final:
     mov  ax,2000
     call [si] method memory_system:alloc
     mov  [di],ax
     add  di,2
     loop final


;     call [si] method memory_system:show
;     call CRLF
;     call CRLF

     xor  si,si
     mov  cx,13
     mov  di,offset block1
final2:
     mov  ax,[di]
     push ds
     mov  ds,ax
     call [si] method memory_block:MarkFree
     pop  ds
     add  di,2
     loop final2


     mov  si,offset memory
      ; Now allocate 15 larger blocks
     mov  cx,15
     mov  di,offset block1
final3:
     mov  ax,2500
     call [si] method memory_system:alloc
     mov  [di],ax
     add  di,2
     loop final3


;     call [si] method memory_system:show
;     call CRLF
;     call CRLF

     xor  si,si
     mov  cx,15
     mov  di,offset block1
final4:
     mov  ax,[di]
     cmp  ax,0
     jz   final4b
     push ds
     mov  ds,ax
     call [si] method memory_block:MarkFree
     pop  ds
final4b:
     add  di,2
     loop final4

     mov  si,offset memory
 
comment ~
; Test using memory_system:alloc and memory_system:free
blockcount=2000

     ; Get 20 blocks of various sizes
     mov  cx,blockcount
     mov  di,offset block1
again:
     mov  ax,cx
     and  ax,0fh
     cmp  al,0
     jne  again_2
;     call [si] method memory_system:show
again_2:
     inc  ax
     inc  ax
     call [si] method memory_system:alloc
     mov  [di],ax
     inc  di
     inc  di
     loop again

;     call [si] method memory_system:show
;     call CRLF
;     call CRLF

     ; Now free up half of them
     mov  cx,blockcount/2
     mov  di,offset block1
again_3:
     mov  ax,cx
     and  ax,0fh
     cmp  al,0
     jne  again_4
;     call [si] method memory_system:show
again_4:
     mov  ax,[di]
     mov  word ptr [di],0
     cmp  ax,0
     je   again_5
     call [si] method memory_system:free
again_5:
     add  di,4
     loop again_3

;     call [si] method memory_system:show
;     call CRLF
;     call CRLF

     ; Now free up all the rest
     mov  cx,blockcount
     mov  di,offset block1
again_6:
     mov  ax,cx
     and  ax,0fh
     cmp  al,0
     jne  again_7
;     call [si] method memory_system:show
again_7:
     mov  ax,[di]
     mov  word ptr [di],0
     cmp  ax,0
     je   again_8
     call [si] method memory_system:free
again_8:
     add  di,2
     loop again_6

;     call [si] method memory_system:show
;     call CRLF
;     call CRLF

     ; Now allocate 13 very large blocks
     mov  cx,13
     mov  di,offset block1
final:
     mov  ax,2000
     call [si] method memory_system:alloc
     mov  [di],ax
     add  di,2
     loop final


;     call [si] method memory_system:show
;     call CRLF
;     call CRLF

     mov  cx,13
     mov  di,offset block1
final2:
     mov  ax,[di]
     call [si] method memory_system:free
     add  di,2
     loop final2


     ; Now allocate 15 larger blocks
     mov  cx,15
     mov  di,offset block1
final3:
     mov  ax,2500
     call [si] method memory_system:alloc
     mov  [di],ax
     add  di,2
     loop final3


;     call [si] method memory_system:show
;     call CRLF
;     call CRLF

     mov  cx,15
     mov  di,offset block1
final4:
     mov  ax,[di]
     call [si] method memory_system:free
     add  di,2
     loop final4

~
     call [si] method memory_system:show
     call CRLF
     call CRLF
     call [si] method memory_system:freeall
     call [si] method memory_system:show
     call CRLF
     call CRLF

     ; Try the same calls with the advanced memory system object
     mov  si,seg memorya
     mov  ds,si
     mov  si,offset memorya

     ; Set ES to point to the virtual tables!
     LoadVMTSeg  ES,BX
     call [si] method memory_system_advanced:init
     call [si] method memory_system_advanced:show
     call [si] method memory_system_advanced:freeall
     mov  ah,DOSTERMINATE
     int  DOSINT

@curseg ends

zzlastseg segment

zzlastseg ends

end start_

