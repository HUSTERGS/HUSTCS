;[]-----------------------------------------------------------------[]
;|      NHEAPCHK.ASM                                                 |
;[]-----------------------------------------------------------------[]

;
;       C/C++ Run Time Library - Version 5.0
; 
;       Copyright (c) 1987, 1992 by Borland International
;       All Rights Reserved.
; 

        INCLUDE RULES.ASI

        LOCALS
        INCLUDE _HEAP.INC

IF LPROG
  EXTRADISP     equ     2         ; Allow for FAR returns when getting parms
  DIST          equ     FAR
ELSE
  EXTRADISP     equ     0
  DIST          equ     NEAR
ENDIF

IF LDATA EQ false

;-----------------------------------------------------------------------
; Memory Block Header (near heap)
;-----------------------------------------------------------------------
; Each block in the heap, whether allocated or free, has a header.
; For an allocated block, only the first two fields of the header are
; used. For a free block all eight bytes are used, thus the smallest
; possible block is the size of a free header.
;
; Field       Description
; ---------   ----------------------------------------------------------
; size        total size, in bytes, of this block (+1 if the block is in use)
; prev_real   pointer to the physically previous block in the heap
; prev_free   pointer to the logically previous free block
; next_free   pointer to the logically next free block
;
; Note that the size field is also used to indicate whether the block
; is allocated or free.  A doubly-linked queue is maintained of the
; free blocks and it is important to know that ordering of the blocks
; in this queue is logical rather than physical.  If there is only one
; free block on the heap prev_free and next_free point to itself.
;-----------------------------------------------------------------------
Header          STRUC
bsize           dw      ?
prev_real       dw      ?
prev_free       dw      ?
next_free       dw      ?
                ENDS

;-----------------------------------------------------------------------
; heapinfo structure (near heap)
;-----------------------------------------------------------------------
; Used by the heapwalk function.
; heapwalk accepts a pointer to a struct of this type.
; On entry, the pointer field contains the address of the previous
; memory block in the heap (NULL for the first call).  The next block
; in the heap is then found and its address is stored in the structure
; along with its size, in bytes, and a 'used' flag.
;-----------------------------------------------------------------------
HeapInfo        STRUC
hi_ptr          dw      ?
hi_size         dw      ?
hi_inuse        dw      ?
                ENDS

UsedHeaderSize  EQU     4
FreeHeaderSize  EQU     8

;-----------------------------------------------------------------------
; Only three variables are needed to efficiently manage the heap.
;-----------------------------------------------------------------------
                EXTRN __first:word        ;pointer to the first block
                EXTRN __last:word         ;pointer to the last block
                EXTRN __rover:word        ;pointer to an arbitrary free block


_TEXT           SEGMENT PUBLIC 'CODE'
                ASSUME CS:_TEXT

;-----------------------------------------------------------------------------
; C callable function which checks and verifies the heap.
; Walk through the physical heap and free block queue checking for
; bad links, adjacent free blocks, and sum the free block sizes both
; ways.  If the physical free block sum does not equal the free-block
; queue sum, there is an error.
;
; Args:                 void
; Returns:              _HEAPEMPTY, _HEAPOK, or _HEAPCORRUPT in ax
;-----------------------------------------------------------------------------
                PUBLIC  _heapcheck
_heapcheck      PROC DIST
                push    si
                push    di
                push    bx
                push    cx
                push    dx

                mov     bx,__first              ;bx = first block in heap
                or      bx,bx                   ;is it NULL?
                jz      @@EmptyHeap
                mov     si,[bx.bsize]           ;si = next block after bx
                and     si,0fffeh
                add     si,bx

                xor     cx,cx                   ;cx = size sum of physical free blocks
                mov     dx,cx                   ;dx = size sum of free block queue
@@SearchPhysicalLinks:
                test    BYTE PTR [bx.bsize],01h ;is this block used?
                jnz     @@CheckPhysicalLinks
                add     cx,[bx.bsize]           ;cx += size of this free block
                cmp     bx,[__last]             ;at the end of the heap?
                je      @@QueueCheck
                test    BYTE PTR [si.bsize],01h ;this block should be used
                jz      @@HeapCorrupt           ;Oh nooooo, Mr. Bill!
@@CheckPhysicalLinks:
                cmp     bx,[__last]             ;at the end of the heap?
                je      @@QueueCheck
                cmp     si,bx                   ;check those links!
                jbe     @@HeapCorrupt
                cmp     [bx.bsize],FreeHeaderSize
                jb      @@HeapCorrupt
                cmp     si,[__first]
                jbe     @@HeapCorrupt
                cmp     si,[__last]
                ja      @@HeapCorrupt
                cmp     [si.prev_real],bx
                jne     @@HeapCorrupt
                mov     bx,si                   ;bx = next block in heap
                mov     si,[bx.bsize]           ;si = next block after bx
                and     si,0fffeh
                add     si,bx
                jmp     SHORT @@SearchPhysicalLinks
@@QueueCheck:
                mov     bx,[__rover]
                or      bx,bx
                jz      @@EvaluateResults
@@QueueLoop:
                mov     ax,[bx.bsize]           ;this block should be free
                test    al,01h                  ;well, is it?
                jnz     @@HeapCorrupt           ;Oh nooooo, Mr. Bill!
                add     dx,ax                   ;dx += size of this block
                cmp     bx,[__first]
                jb      @@HeapCorrupt
                cmp     bx,[__last]
                jae     @@HeapCorrupt
                mov     si,[bx.next_free]       ;si = the next free block
                cmp     si,[__rover]            ;done?
                je      @@EvaluateResults
                cmp     si,bx                   ;check those links!
                je      @@HeapCorrupt
                mov     bx,si
                jmp     SHORT @@QueueLoop
@@EmptyHeap:
                mov     ax,_HEAPEMPTY
                jmp     SHORT @@AllDone

@@EvaluateResults:
                cmp     dx,cx
                jne     @@HeapCorrupt
@@HeapOK:
                mov     ax,_HEAPOK
                jmp     SHORT @@AllDone
@@HeapCorrupt:
                mov     ax,_HEAPCORRUPT
@@AllDone:
                pop     dx
                pop     cx
                pop     bx
                pop     di
                pop     si
                ret
                ENDP

;-----------------------------------------------------------------------------
; C callable function which checks and verifies a node on the heap.
;-----------------------------------------------------------------------------
; Args:                 node to check (stack)
; Returns:              _HEAPCORRUPT, _BADNODE, _FREEENTRY, or _USEDENTRY in ax
;-----------------------------------------------------------------------------
                PUBLIC  _heapchecknode
_heapchecknode  PROC DIST
                push    si
                push    di
                push    bp

                mov     bp,sp

                mov     ax,[bp+8+EXTRADISP]     ;ax = node to find
                sub     ax,UsedHeaderSize

                mov     bx,[__first]            ;bx = first block in heap
                or      bx,bx                   ;is it NULL?
                jz      @@EmptyHeap
                mov     si,[bx.bsize]           ;si = next block after bx
                and     si,0fffeh
                add     si,bx

@@SearchPhysicalLinks:
                cmp     bx,ax
                je      @@Found
                test    BYTE PTR [bx.bsize],01h ;is this block used?
                jnz     @@CheckPhysicalLinks
                cmp     bx,[__last]             ;at the end of the heap?
                je      @@NotFound
                test    BYTE PTR [si.bsize],01h ;this block should be used
                jz      @@HeapCorrupt           ;Oh nooooo, Mr. Bill!
@@CheckPhysicalLinks:
                cmp     bx,[__last]             ;at the end of the heap?
                je      @@NotFound
                cmp     si,bx                   ;check those links!
                jbe     @@HeapCorrupt
                cmp     [bx.bsize],FreeHeaderSize
                jb      @@HeapCorrupt
                cmp     si,[__first]
                jbe     @@HeapCorrupt
                cmp     si,[__last]
                ja      @@HeapCorrupt
                cmp     si,bx
                jbe     @@HeapCorrupt
                cmp     [si.prev_real],bx
                jne     @@HeapCorrupt
                mov     bx,si                   ;bx = next block in heap
                mov     si,[bx.bsize]           ;si = next block after bx
                and     si,0fffeh
                add     si,bx
                jmp     SHORT @@SearchPhysicalLinks
@@EmptyHeap:
                mov     ax,_HEAPEMPTY
                jmp     SHORT @@AllDone
@@HeapCorrupt:
                mov     ax,_HEAPCORRUPT
                jmp     SHORT @@AllDone
@@NotFound:
                mov     ax,_BADNODE
                jmp     SHORT @@AllDone
@@Found:
                test    BYTE PTR [bx.bsize],01
                jnz     @@UsedEntry
@@FreeEntry:
                mov     ax,_FREEENTRY
                jmp     SHORT @@AllDone
@@UsedEntry:
                mov     ax,_USEDENTRY
@@AllDone:
                pop     bp
                pop     di
                pop     si
                ret
                ENDP

;-----------------------------------------------------------------------------
; C callable function which fills the free areas with a given value
;-----------------------------------------------------------------------------
; Args:                 unsigned int, fill value (stack)
; Returns:              _HEAPEMPTY, _HEAPOK, or _HEAPCORRUPT in ax
;-----------------------------------------------------------------------------
                PUBLIC  _heapfillfree
_heapfillfree   PROC DIST
                push    bp
                mov     bp,sp
                mov     ax,[bp+4+EXTRADISP]

                push    si
                push    di

                cmp     __first,0
                je      @@EmptyHeap

                mov     bx,__rover
                or      bx,bx
                jz      @@HeapOK
                cld
@@QueueLoop:
                mov     cx,[bx.bsize]
                sub     cx,FreeHeaderSize
                shr     cx,1
                lea     di,[bx+8]
                rep
                stosw
                mov     cx,[bx.next_free]       ;cx = next free block
                cmp     cx,[__rover]            ;done?
                je      @@HeapOK
                cmp     bx,cx                   ;check links
                je      @@HeapCorrupt
                or      cx,cx
                jz      @@HeapCorrupt
                mov     bx,cx                   ;get the next free block
                jmp     SHORT @@QueueLoop
@@HeapOK:
                mov     ax,_HEAPOK
                jmp     SHORT @@AllDone
@@EmptyHeap:
                mov     ax,_HEAPEMPTY
                jmp     SHORT @@AllDone
@@HeapCorrupt:
                mov     ax,_HEAPCORRUPT
@@AllDone:
                pop     di
                pop     si
                pop     bp
                ret
                ENDP

;-----------------------------------------------------------------------------
; C callable function which checks the free areas of the heap for a given value
;-----------------------------------------------------------------------------
; Args:                 unsigned int, fill value (stack)
; Returns:              _HEAPOK, _HEAPEMPTY, _BADVALUE, or _HEAPCORRUPT in ax
;-----------------------------------------------------------------------------
                PUBLIC  _heapcheckfree
_heapcheckfree  PROC DIST
                push    bp
                mov     bp,sp
                mov     ax,[bp+4+EXTRADISP]

                push    si
                push    di

                cmp     __first,0
                je      @@EmptyHeap

                mov     bx,__rover
                or      bx,bx
                jz      @@HeapOK
                cld
@@QueueLoop:
                mov     cx,[bx.bsize]
                sub     cx,FreeHeaderSize
                shr     cx,1
                lea     di,[bx+8]
                repe
                scasw
                jnz     @@BadValue
                mov     cx,[bx.next_free]       ;cx = next free block
                cmp     cx,[__rover]            ;done?
                je      @@HeapOK
                cmp     bx,cx                   ;check links
                je      @@HeapCorrupt
                or      cx,cx
                jz      @@HeapCorrupt
                mov     bx,cx                   ;get the next free block
                jmp     SHORT @@QueueLoop
@@HeapOK:
                mov     ax,_HEAPOK
                jmp     SHORT @@AllDone
@@EmptyHeap:
                mov     ax,_HEAPEMPTY
                jmp     SHORT @@AllDone
@@BadValue:
                mov     ax,_BADVALUE
                jmp     SHORT @@AllDone
@@HeapCorrupt:
                mov     ax,_HEAPCORRUPT
@@AllDone:
                pop     di
                pop     si
                pop     bp
                ret
                ENDP

;-----------------------------------------------------------------------------
; C callable function to walk through the heap node by node
;-----------------------------------------------------------------------------
; Args:                 pointer to a heapinfo structure (stack)
; Returns:              _HEAPOK, _HEAPEMPTY, _HEAPEND in ax
;-----------------------------------------------------------------------------
                PUBLIC  _heapwalk
_heapwalk       PROC DIST
                push    bp
                push    si

                mov     bp,sp
                mov     bx,[bp+6+EXTRADISP]     ;bx = address of heapinfo struct
                mov     si,[bx.hi_ptr]          ;si = previous block
                or      si,si                   ;si == NULL?
                je      @@FirstBlock
                sub     si,UsedHeaderSize
                cmp     si,[__last]             ;last block?
                je      @@HeapEnd
@@InnerBlock:
                add     si,[si.bsize]           ;si = next block
                and     si,0fffeh               ;strip 'used' bit
                jmp     SHORT @@SaveInfo
@@FirstBlock:
                mov     si,[__first]
                or      si,si
                jz      @@HeapEmpty
@@SaveInfo:
                mov     [bx.hi_ptr],si
                add     [bx.hi_ptr],UsedHeaderSize
                mov     ax,[si.bsize]
                and     ax,0fffeh               ;strip 'used' bit
                mov     [bx.hi_size],ax
                mov     ax,[si.bsize]
                and     ax,0001h                ;retrieve 'used' bit
                mov     [bx.hi_inuse],ax
@@HeapOK:
                mov     ax,_HEAPOK
                jmp     SHORT @@AllDone
@@HeapEmpty:
                mov     ax,_HEAPEMPTY
                jmp     SHORT @@AllDone
@@HeapEnd:
                mov     ax,_HEAPEND
@@AllDone:
                pop     si
                pop     bp
                ret
                ENDP
                ENDS
ENDIF
                END
