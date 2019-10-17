page 75,132
%title "Object Oriented Memory Management System - TASM 3.0"
; Copyright (c) 1991 by Borland International

ifndef MDL
    display "Error: This module requires that you provide a memory model"
    display "    definition on the command line. I.E. /dMDL=SMALL."
    display "Also, /M must be given on the command line to enable multiple"
    display "    passes."
MDL equ <SMALL>
endif

ModuleVersion EQU "0.33"

COMMENT ~

This memory management system shows how to use TASM 3.0 objected oriented
extensions to create a heap management system. Some features of this heap
management system are:
    - Extensive use of objects for the heap manager and also individual
      blocks of memory
    - Extensibility to allow changing the structure of heap blocks without
      drastic changes to the heap manager
    - Ability to mix many different types of blocks in the same heap,
      for example, disk heap objects interspersed with regular memory
      blocks.
    - Extensive optimizations

The memory management system is implemented by several object classes.
All memory accesses are based on requesting a block of memory whose size
is given in paragraphs. Users of the memory system only need to store
segment offsets of the memory blocks that are returned. All memory blocks
can return the offset, where the user may begin storing information,
whenever needed at a later time.

memory_system   is the master heap object. It is responsible for allocating
                a block of memory to be managed as a heap. This block of
                memory may be smaller than the maximum amount of available
                memory, enabling the user of this system to setup multiple
                heaps if desired.

memory_block    is the object that has the methods for the operations of
                individual blocks in the heap. It may be used for blocks
                that are used, or unused. Although extensive checks
                of IsFree are made in routines that are not allowed on used
                blocks of memory, (for example splitting a block apart to
                create a smaller block to satisfy an allocation request),
                there are more specialized blocks objects available to
                handle used blocks and the endblock at the end of the heap.
                Consequently, the _DO_ISFREE_ equate may be disabled, and
                routines within memory_block will rely on the method
                overrides in the memory_usedblock class to filter out calls
                that should not happen to memory_blocks. This alone results
                in a 20% speed increase of the memory manager in the
                set of testing benchmarks!

memory_usedblock is an object that handles the operations for blocks on the
                heap that are in use. It is a descendant of the memory_block
                object. It is not strictly necessary that blocks on the heap
                be retyped as memory_usedblock, (by changing the VMT), but
                it should allow faster operations since the usedblock
                automatically traps out routines that it shouldn't be allowed
                to do, thus eliminating the need to check IsFree.

memory_endblock is a specialized object that is placed at the end of the
                heap. It is a descendant of the memory_usedblock object.
                It should have no size, and is strictly a placemarker so
                that all other blocks will have a next pointer other than
                zero, so they will all be able to use segment arithmetic
                to calculate their sizes.


     Object Hierarchy:

        MEMORY_SYSTEM



        MEMORY_BLOCK
            :
            :
      MEMORY_USEDBLOCK
            :
            :
       MEMORY_ENDBLOCK




For compatibility with future memory_block object descendants, a LockBlock
call should be given for all memory blocks prior to usage, and an UnLockBlock
call should be given whenever the object is free to move about. When a
LockBlock call is given, DS:SI will be set on return to point to an actual
memory address that should be used for operating on the area of memory. The
UnLockBlock call must give this same memory address. UnlockBlock returns
a value in DS:SI that can be used for the next LockBlock call.

The ALLOC operation of the memory_system always locks it's block prior to
returning. Therefore it always returns a real memory pointer. When the memory
area has been initialized, it may be unlocked, and the return of the
UnLockBlock call may be stored for future accesses to the memory region.

This convention can allow implementing a special kind of memory block that
knows how to swap itself to offline storage when it is not in use.
In practice, this system may be implemented by having objects on the heap
that represent unlocked blocks of memory. When this block recieves a lock
call, it creates a region in memory to recieve the memory contents and then
it loads the actual memory contents from offline storage. A pointer to this
new block is returned. Later, when this new block is freed, the old lock
block is informed and the lock block may swap the memory area to disk.

Normal memory_blocks, and memory_usedblocks, do not process the LockBlock or
UnLockBlock calls in any way. So how do blocks that implement swapping come
to be included in the memory system?  A process outside the memory_system,
a caller of memory_system, can implement this. The process calls the
memory_system to give it a block of memory. (This block of memory will
probably be the size of the swapping_block object.) This block of memory
can then be retyped by changing it's VMT. The new VMT will then point to
the method table for a different class of object that implements swapping
of it's memory region. (The outside process might make another call to
the swapping_block object that informs the swapping block how big of an
area it is managing.) As long as the memory_block can respond to normal
requests that the memory_system makes, (it will probably respond with the
methods of the memory_usedblock, while any special messages that it takes
are added to the end of the memory_usedblock VMT), the existance of the
block will not cause any problems. It can transparently handle LockBlock and
UnLockBlock calls by creating and destroying new blocks of memory within
the memory_system that it belongs to, because the outside process would
have passed it a handle to the memory_system, and also any handles or
information that it needs for accessing the offline virtual storage that
it swaps information in and out of.

Of course, it is possible that the memory_system itself might be able to
transparently create these new types of memory_blocks. If the memory_system
is passed a pointer to the init method for a new type of block, then
it would automatically deal with the new type of block. The init method
for memory_blocks requires the size of the block to be passed. Currently
this is set to be the same size as the block that the memory_system
selected.

~
jumps
page
locals @@

; Define the following to enable the optimization of the rover pointer
; to shorten time to find a free heap area.
_USE_ROVER_ =1


; Define the following to enable a freed block to be combined with
; any free block that might be immediately before it.
; Defining this equate causes a tremendous slow down in the deallocation
; process, since a scan for previous must be done for every free operation.
; This scan for previous has to walk the entire memory block chain up to
; the item that is being freed in order to find the previous block and see
; if it is free.
; Logic has been added instead to the alloc routine to combine adjacent
; free blocks that it finds while it is walking forward through the
; chain of memory blocks.
;_COMBINE_PREV_=1

; The PREV pointer for unused blocks is not always accurate, since
; scanprev is not done during dealloc. Do not define the following.
;_DO_SETPREV_ = 1


; Since used blocks have a different VMT pointer than unused blocks,
; routines that are not valid for used blocks, (e.g. setprev and setsize),
; can be trapped out from the default routine in the memory_block object.
; Then those memory block objects can assume that they were called because
; the block is free. If this equate is not defined, it is important that
; all used blocks, (and end blocks), are not left as regular memory_blocks,
; but are instead retyped as what they are by changing the VMT.
;__DO_ISFREE_ = 1


.model MDL,pascal
.code

; Int 21 DOS calls
DOSINT             =   21H
DOSGETMEMBLOCK     =   48H
DOSRELEASEBLOCK    =   49H
DOSRESIZEBLOCK     =   4AH
DOSTERMINATE       =   4CH


; Include the utility macros that ease dealing with
; the Virtual Method Tables.
include vmtutil.inc

IsZero macro reg
       or reg,reg
       endm

; Include the names of routines that handle display of numbers.
include display.inc


; Cause the VMT tables to be defined as a part of this module.
_MAKE_MEMVMT_ = 1
   include mem.inc


PAGE
;************************************ Routines for MEMORY_BLOCK

memory_block_reserved_size proc
         mov  bx,offset @memory_block_used_start
         ret
memory_block_reserved_size endp



; AX has size of block to allocate into the chain.
memory_block_initget proc pascal previousblock:word,nextblock:word

         ret
memory_block_initget endp



memory_block_init proc pascal uses ax,\
                              previousblock:word,nextblock:word,\
                              bsize:word

         ; Set the VMT PTR within this block!
         mov  [ds:si.@Mptr_memory_block],offset @TableAddr_memory_block
;if @CodeSize eq 1
;         mov  word ptr [ds:si.@Mptr_memory_block+2],seg @TableAddr_memory_block
;endif

ifdef _DO_SETPREV_
         mov  ax,[previousbLock]
         mov  word ptr [ds:si.prev],ax
endif

         mov  ax,FREE_BLOCK
         mov  word ptr [ds:si.next],ax
         mov  ax,[nextblock]
         mov  word ptr [ds:si.next2],ax
         mov  ax,[bsize]
         mov  [ds:si.blksize],ax
         xor  ax,ax

         ; Zero out the unused high words
         mov  word ptr [ds:si.next+2],ax
         mov  word ptr [ds:si.next2+2],ax
ifdef _DO_SETPREV_
         mov  word ptr [ds:si.prev+2],ax
endif
         ret
memory_block_init endp



memory_block_deinit proc
         ret
memory_block_deinit endp



; AX has the previous block segment
; If combine is done, DS points to the previous segment.
memory_block_combine proc
ifdef _DO_ISFREE_
         call [ds:si] method memory_block:IsFree
         jnz  @@done
endif

         push cx
         mov  cx,ax   ; Save AX, so we can set it's block to point to the
                      ; next of the DS block.
         call [ds:si] method memory_block:GetNext
         mov  ds,cx
         call [ds:si] method memory_block:SetNext
         ; Also, need to update size of previous block
         ; AX still contains seg of block after one being freed.
         sub  ax,cx
         dec  ax
         call [ds:si] method memory_block:SetSize
         pop  cx

@@done:
         ret
memory_block_combine endp



mb_show proc uses ds es dx ax
.data
@@used db "Used$"
@@free db "Free" ;,"$"
@@next2 db " Next2:$"
@@prev db " Prev:$"
@@blksize db " Blksize:$"
.code
         call Show_Bracket
         call [ds:si] method memory_block:IsFree

         ; Put our pointer into   ES:SI
         push ds
         pop  es
         mov  ax,@data
         mov  ds,ax

         ; Print a USED or FREE string
         mov  ah,DOSPRINTSTRING
         jz   @@block_is_free

        ; We should never get here if memory_usedblocks are used.
         mov  dx,offset @@used
         int  DOSINT
         jmp  @@done

@@block_is_free:
         mov  dx,offset @@free

@@show_msg:
         int  DOSINT

        ; mov  ah,DOSPRINTSTRING
        ; mov  dx,offset @@next2
        ; int  DOSINT
         mov  ax,word ptr [es:si.next2]
         call ShowHexWord

ifdef _DO_SETPREV_
         mov  ah,DOSPRINTSTRING
         mov  dx,offset @@prev
         int  DOSINT
         mov  ax,word ptr [es:si.prev]
         call ShowHexWord
endif

         mov  ah,DOSPRINTSTRING
         mov  dx,offset @@blksize
         int  DOSINT
         mov  ax,word ptr [es:si.blksize]
         call ShowHexWord

@@done:
         call Show_Endbracket
         ret
mb_show endp



mb_findprev proc
         local findprevfor:word
         mov  [findprevfor],ax

@@check:
         LoadVMTSeg  es,ax
         call [ds:si] method memory_block:GetNext
         cmp  ax,[findprevfor]
         je   @@previousfound

         IsZero ax
         je   @@noprevious

         ; Load the segment of the next block, and go check it out
         mov  ds,ax
         jmp  @@check

@@previousfound:
         mov ax,ds      ; Store the segment of the current block in AX.
         jmp @@done

@@noprevious:
         xor ax,ax      ;Zero out AX to indicate no previous.
@@done:
         ret
mb_findprev endp



mb_getnext proc
ifdef _DO_ISFREE_
         mov  ax,word ptr [si.next]
         cmp  ax,FREE_BLOCK
         jne  @@done
endif
         mov  ax,word ptr [si.next2]
@@done:
         ret
mb_getnext endp



mb_isfree proc
ifdef _DO_ISFREE_
         cmp word ptr [si.next],FREE_BLOCK
else
         ; All we need to do is set the Z flag!
         cmp ax,ax
endif
         ret
mb_isfree endp



mb_setprev proc
ifdef _DO_SETPREV_
ifdef _DO_ISFREE_
         LoadVMTSeg es,bx
         call [ds:si] method memory_block:IsFree
         jnz  @@1
endif
         mov  word ptr [ds:si.prev],ax
@@1:
endif
         ret
mb_setprev endp



mb_setsize proc
ifdef _DO_ISFREE_
         LoadVMTSeg es,bx
         call [ds:si] method memory_block:IsFree
         jnz  @@1    ; short @memory_block_setsize_done
endif
         mov  word ptr [ds:si.blksize],ax
ifdef _DO_ISFREE_
@@1:
endif
         ret
mb_setsize endp



mb_setnext proc
ifdef _DO_ISFREE_
         LoadVMTSeg es,bx
         call [ds:si] method memory_block:IsFree
         jnz  short @@notfree
endif

         ; If we are here, the block is free.
         mov  word ptr [ds:si.next2],ax
ifdef _DO_ISFREE_
         jmp  short @@done

@@notfree:
         mov  word ptr [ds:si.next],ax
@@done:
endif
         ret
mb_setnext endp



mb_scan proc

;         LoadVMTSeg es,bx

@@check:
         call [ds:si] method memory_block:IsFree
;         cmp word ptr [ds:si.next],FREE_BLOCK  ; See if this block is free
         jz  @@found

         ; It's not free. So go to the next block.
         call [ds:si] method memory_block:GetNext
         IsZero  ax     ; Check for the last block in the chain (next=0?)
         jz  @@done
         mov ds,ax
         jmp @@check

@@found:
         ; Load the size of the current block into AX
         ; Size in paragraphs is    (seg of next block) - (seg of this block)
         mov  ax,ds
         neg  ax
         add  ax,word ptr [ds:si.next2]
         dec  ax       ; Adjust for block bookkeeping information
;         mov  ax,[ds:si.blksize]   ; This should produce the same
                                    ; value for free blocks.

@@done:
         ret
mb_scan endp


mb_rawblocksize proc
;         LoadVMTSeg es,bx
         call [ds:si] method memory_block:GetNext
         mov  bx,ds
         sub  ax,bx
         ret
mb_rawblocksize endp



mb_breakblock proc uses ds si
         local desiredsize:word,currentnext:word,newnext:word,currblock:word,\
               newblocksize:word

         mov  [desiredsize],ax
         mov  ax,ds
         mov  [currblock],ax
         mov  [newnext],ax     ; We'll use newnext as the address to return in
                               ; AX.

         ; This routine is only valid for free memory blocks
;         LoadVMTSeg es,bx
ifdef _DO_ISFREE_
         call [ds:si] method memory_block:IsFree
         jnz  @@done
endif

         call [ds:si] method memory_block:RawBlockSize
         mov  bx,ax
         sub  bx,[desiredsize]
         dec  bx     ; Represent bookkeeping information of current block
         dec  bx     ; For bookkeeping information of the new block
         mov  [newblocksize],bx
         cmp  bx,2   ; If less than four paragraphs left over, don't
                     ; do the breakdown.
         jbe  @@done

         ; Get the current next block
         call [ds:si] method memory_block:GetNext
         mov  [currentnext],ax

         ; Calculate the segment of the new block
         mov  ax,ds
         add  ax,[desiredsize]
         inc  ax             ; For the size of our bookkeeping info
         mov  [newnext],ax

         ; Set our next pointer to new block
         call [ds:si] method memory_block:SetNext

         ; Set our size
         mov  ax,[desiredsize]
         call [ds:si] method memory_block:SetSize

         ; Set the new block to point to its neighbors
         mov  ds,[newnext]
         call [ds:si] method memory_block:init pascal,[currblock],[currentnext],[newblocksize]

ifdef _DO_SETPREV_
         ; Set the old next block to point to the new block created just
         ; before it.
         mov  ds,[currentnext]
         call [ds:si] method memory_block:setprev
endif

@@done:
         mov  ax,[newnext]
         ret
mb_breakblock endp



memory_block_markfree proc
ifdef _DO_ISFREE_
         local previous:word

         mov  [previous],ax
         call [ds:si] method memory_block:IsFree
         jz   @@block_is_free_skip

         ; Get the pointer to the next block
         call [ds:si] method memory_block:GetNext

         ; Calculate the size of this block
         push ax

         mov  bx,ax
         mov  ax,ds
         sub  bx,ax
         dec  bx      ; For the bookkeeping area

         pop  ax
         call [ds:si] method memory_block:init  pascal,[previous],ax,bx

@@block_is_free_skip:
endif
         ret
memory_block_markfree endp



memory_block_markused proc
ifdef _DO_ISFREE_
         call [ds:si] method memory_block:IsFree
         jnz  @@done
endif
         mov  ax,word ptr [ds:si.next2]
         mov  word ptr [ds:si.next],ax
         mov  ax,word ptr [ds:si.next2+2]
         mov  word ptr [ds:si.next+2],ax

         ; Change the block type to be a used block.
         ; Do this by changing the VMT!
         mov  [ds:si.@Mptr_memory_block],offset @TableAddr_memory_usedblock
;if @CodeSize eq 1
;         mov  word ptr [ds:si.@Mptr_memory_block+2],seg @TableAddr_memory_usedblock
;endif
@@done:
         ret
memory_block_markused endp



memory_block_lock proc

         ret
memory_block_lock endp



memory_block_unlock proc

         ret
memory_block_unlock endp


memory_block_allocfail proc
         ret
memory_block_allocfail endp


page
;***** Routines for  MEMORY_USEDBLOCK


memory_usedblock_markfree proc
         local previous:word

         mov  [previous],ax
ifdef _DO_ISFREE_
         call [ds:si] method memory_block:IsFree
         jz   @@block_is_free_skip
endif

         ; Get the pointer to the next block
         call [ds:si] method memory_block:GetNext

         ; Calculate the size of this block
         push ax

         mov  bx,ax
         mov  ax,ds
         sub  bx,ax
         dec  bx      ; For the bookkeeping area

         pop  ax
         call [ds:si] method memory_block:init  pascal,[previous],ax,bx

@@block_is_free_skip:
         ret
memory_usedblock_markfree endp


memory_usedblock_combine proc
         ret    ;Can't do a combine with a used block. So ignore it!
memory_usedblock_combine endp



memory_usedblock_setnext proc
         mov  word ptr [ds:si.next],ax
         ret
memory_usedblock_setnext endp



memory_usedblock_invalid proc
         ret
memory_usedblock_invalid endp



memory_usedblock_isfree proc uses ax
         mov  ax,1    ; Set the Z flag to zero!
         IsZero ax
         ret
memory_usedblock_isfree endp



memory_usedblock_scan proc
         ; This block is not free, so quickly pass the call
         ; along to the next object in this chain!
         mov   ax,word ptr [ds:si.next]
         mov   ds,ax
         IsZero ax   ; Check for zero, meaning end of the line!
         jz    @@done

         ; Use a jump, instead of
         ; call  [ds:si] method memory_usedblock:ScanFree
         ; so that we eliminate overflowing the stack during this routine.
         MOV   BX,[([DS :SI ]).@Mptr_memory_block]
;if @CodeSize eq 1
;         MOV   ES,word ptr [([DS :SI ]).@Mptr_memory_block+2]
;endif
         jmp   [(@Table_memory_usedblock PTR ES:BX).ScanFree]

@@done:
         ret
memory_usedblock_scan endp



memory_usedblock_getnext proc
         mov  ax,word ptr [ds:si.next]
         ret
memory_usedblock_getnext endp



memory_usedblock_init proc
         ; Set the VMT PTR within this block!
         mov  [ds:si.@Mptr_memory_block],offset @TableAddr_memory_usedblock
         ret
memory_usedblock_init endp



memory_usedblock_show proc uses ds es dx ax
.data
@@type db "USED$"
@@next db " Next:$"
.code
         call Show_Bracket
         push ds
         pop  es
         mov  ax,@data
         mov  ds,ax
         mov  dx,offset @@type
         mov  ah,DOSPRINTSTRING
         int  DOSINT

         mov  ah,DOSPRINTSTRING
         mov  dx,offset @@next
         int  DOSINT
         mov  ax,word ptr [es:si.next]
         call ShowHexWord

         call Show_Endbracket
         ret
memory_usedblock_show endp



memory_usedblock_lock proc

         ret
memory_usedblock_lock endp



memory_usedblock_unlock proc

         ret
memory_usedblock_unlock endp




page
;***** Routines for   MEMORY_ENDBLOCK


memory_endblock_ignore proc
         ret
memory_endblock_ignore endp



memory_endblock_getnext proc
         xor ax,ax
         ret
memory_endblock_getnext endp



memory_endblock_init proc
         ; Set the VMT PTR within this block!
         mov  [ds:si.@Mptr_memory_block],offset @TableAddr_memory_endblock
;if @CodeSize eq 1
;         mov  word ptr [ds:si.@Mptr_memory_block],seg @TableAddr_memory_endblock
;endif
         xor  ax,ax
         mov  word ptr [ds:si.next],ax
         mov  word ptr [ds:si.next+2],ax
         ret
memory_endblock_init endp


memory_endblock_show proc uses ds dx ax
.data
@@end db "END$"
.code
         call Show_Bracket
         mov  ax,@data
         mov  ds,ax
         mov  dx,offset @@end
         mov  ah,DOSPRINTSTRING
         int  DOSINT

         call Show_Endbracket
         ret
memory_endblock_show endp





page
;***** Routines for   MEMORY_SYSTEM


memory_system_init proc uses es ds si bx
         local endblockseg:word

         ; Fill in the VMT for the memory system
         mov  [ds:si.@Mptr_memory_system],offset @TableAddr_memory_system

         ; Get a block of memory.
         mov  bx,ax              ; Get the desired size, unless it is zero,
                                 ; then get the largest possible block.
         or   bx,bx
         jnz  @Memory_system_init_Alloc

         dec  bx   ;mov  bx,0FFFFh          ; Go for largest possible
@Memory_system_init_Alloc:
         mov  [ds:si.blocksize],bx
         mov  ah,DOSGETMEMBLOCK
         int  DOSINT

         ; Need to handle fail here!  (Carryflag set, and BX with size of
         ;                              largest block available. )
         jnc  AllocSuccess

         ; Check the high bit of blocksize to see
         ; if we can get a different size.
         ; Note that if we come here a second time, it is because DOS
         ; said a certain size was available, and then it wouldn't give
         ; it when requested. The high bit wont be set on the second call.
         TESTFLAG [ds:si.blocksize],8000h
         jz   AllocFailed

         ; BX has size of largest block available. Go get it if it is NZ.
         or   bx,bx
         jnz  @Memory_system_init_Alloc    ; Jump back and get it if there
                                           ; is some available.
AllocFailed:
         mov  [ds:si.blocksize],0
         jmp  @Memory_system_init_done

AllocSuccess:
         ; Success:  Carryflag clear, and AX initial segment of allocated block

         mov  [si.root],ax     ; Segment of start of block still in AX!

         mov  [si.rover],ax

         ; Load the size of the block into BX
         mov  bx,[ds:si.blocksize]
         dec  bx     ; For bookkeeping
         dec  bx     ; For the endblock

         ; Calculate in CX the segment of the endblock
         mov  cx,bx
         inc  cx     ; For bookkeeping for first block
         add  cx,ax  ; To get segment
         mov  [endblockseg],cx
         mov  [si.last],cx


         ; Save the address of the memory system, so we
         ; can call constructor for the memory block.
         push ds
         push si

         ; Load the pointer to the block into DS:SI
         mov  ds,ax
         xor  si,si
         xor  ax,ax   ; For pushing zeros for prev & next blocks

;         ; Need to set the VMT for the memory block before calling init!
;         ; This is only needed if INIT routine is in the VMT!
;         mov  [ds:si.@Mptr_memory_block],offset @TableAddr_memory_block

         LoadVMTSeg ES
         call [ds:si] method memory_block:init pascal, ax,cx,bx

         ; Now make an endblock
         mov  ds,[endblockseg]
         call [ds:si] method memory_endblock:init


         ; Restore pointre to the memory system
         pop  si
         pop  ds

@Memory_system_init_done:
         mov  [ds:si.usedspace],0
         mov  ax,[ds:si.blocksize]
         dec  ax    ; Bookkeeping for the first block
         dec  ax    ; Bookkeeping for the end block
         mov  [ds:si.freespace],ax
         dec  [ds:si.freespace]
         ret
memory_system_init endp



memory_system_deinit proc
        ; Return the memory to DOS.
         mov  es,[ds:si.root]
         mov  ah,DOSRELEASEBLOCK
         int  DOSINT
         ret
memory_system_deinit endp



memory_system_resetrover proc
         mov  bx,[ds:si.root]
         mov  [ds:si.rover],root
         ret
memory_system_resetrover endp



.data
mss_initial  db "Memory System Show:",CR,LF
             db "System at:$"
mss_root     db "  Root block at:$"
mss_last     db "  Last block at:$"
mss_rover    db " Rover block at:$"
mss_free     db "      Freespace:$"
mss_used     db "      Usedspace:$"
mss_blocks   db "Blocks at:$"
mss_no_blks  db "No blocks in heap.$"
.code
memory_system_show   proc uses ax dx es ds
         ; Move pointer to the memory system from DS:SI, to ES:SI
         push  ds
         pop   es
         ; Now load pointer to our messages
         mov   dx,@data
         mov   ds,dx
         ; Show the location of the memory system
         mov   dx,offset mss_initial
         mov   ah,DOSPRINTSTRING
         int   DOSINT
         mov   ax,es
         call  ShowHexWord
         mov   dl,':'
         mov   al,DOSPRINTCHAR
         int   DOSINT
         mov   ax,si
         call  ShowHexWord
         call  CRLF

         ; Show the internal variables of the memory system
         mov   dx,offset mss_root
         mov   ah,DOSPRINTSTRING
         int   DOSINT
         mov   ax,[es:si.root]
         call  ShowHexWord
         call  CRLF
         mov   dx,offset mss_last
         mov   ah,DOSPRINTSTRING
         int   DOSINT
         mov   ax,[es:si.last]
         call  ShowHexWord
         call  CRLF
         mov   dx,offset mss_rover
         mov   ah,DOSPRINTSTRING
         int   DOSINT
         mov   ax,[es:si.rover]
         call  ShowHexWord
         call  CRLF
         mov   dx,offset mss_free
         mov   ah,DOSPRINTSTRING
         int   DOSINT
         mov   ax,[es:si.freespace]
         call  ShowHexWord
         call  CRLF
         mov   dx,offset mss_used
         mov   ah,DOSPRINTSTRING
         int   DOSINT
         mov   ax,[es:si.usedspace]
         call  ShowHexWord
         call  CRLF

         ; Save pointer to the memory system
         push  es
         push  si
         mov   ax,[es:si.root]
         xor   si,si

         ; Check for empty chain
         cmp   ax,0
         jz    mss_no_blocks

         push  ax

         ; Now we need to walk the chain
         mov   dx,offset mss_blocks
         mov   ah,DOSPRINTSTRING
         int   DOSINT

         pop   ax


mss_show_block:
         mov   ds,ax
         call  ShowHexWord

         LoadVMTSeg ES,AX
         call  [ds:si] method memory_block:show

         call  [ds:si] method memory_block:GetNext
         ; See if it is the last block
         IsZero ax
         jz    mss_show_block_done
         push  ax
         mov   ah,DOSPRINTCHAR
         mov   dl,','
         int   DOSINT
         pop   ax
         jmp   mss_show_block

; Branch here if this heap system is still empty
mss_no_blocks:
         mov   dx,offset mss_no_blks
         mov   ah,DOSPRINTSTRING
         int   DOSINT

mss_show_block_done:
         pop   si
         pop   es

         call  CRLF

         ret
memory_system_show   endp



memory_system_freeall   proc
         mov  ax,[si.root]
@@free_another:
         ; If it is the end block, dont try to free it.
         cmp  ax,[ds:si.last]
         jz   @@done
         push ax
         call [ds:si] method memory_system:free
         pop  ax
         push ds
         push si
         mov  ds,ax
         xor  si,si
         call [ds:si] method memory_block:GetNext
         IsZero ax
         pop  si
         pop  ds
         jnz  @@free_another
@@done:
         ret
memory_system_freeall   endp



memory_system_findprev  proc uses ds si
;         local systemseg:word,systemofs:word,findprevfor:word
;         mov  [systemseg],ds
;         mov  [systemofs],si
;         mov  [findprevfor],ax

         ; Check if this block is the root block
         cmp  ax,[si.root]
         jz   @memory_system_findprev_atroot

         ; Make pointer to first block in memory system
         mov  ds,[si.root]
         xor  si,si

         call [si] method memory_block:MatchNext
         cmp  ax,0
         jne  @memory_system_findprev_done

         ; The block wasn't found!

@memory_system_findprev_atroot:

@memory_system_findprev_done:
;         mov ds,[systemseg]
;         mov si,[systemofs]
         ret
memory_system_findprev  endp



memory_system_blockofs proc uses ds si
         cmp  ax,0
         jne  @memory_system_blockofs_getit
         mov  ax,[ds:si.root]  ; Get the root and use it's offset since
                               ; no segment was passed in
@memory_system_blockofs_getit:
         mov  ds,ax
         xor  si,si
         call [ds:si] method memory_block:memstart
         ret
memory_system_blockofs endp



memory_system_alloc proc uses ds si
         local allocsize:word,\
               allocblock:word,\
               largest:word,\      ; The size of the largest block encountered
               largestseg:word,\
               newfree:word,\
               rootscan:word,\
               memsysaddr:dword

         mov  [largest],0
         mov  [rootscan],0

         mov  word ptr [memsysaddr],si
         mov  word ptr [memsysaddr+2],ds

         mov  [allocsize],ax
ifdef _USE_ROVER_
         mov  ax,[ds:si.rover]
else
         mov  ax,[ds:si.root]
endif
         mov  ds,ax
@@scan:
         xor  si,si
         call [ds:si] method memory_block:ScanFree
         ; Check if there is enough room in this free block
         cmp  ax,[largest]
         jbe  @@scan_2
         mov  [largest],ax
         mov  [largestseg],ds
@@scan_2:
         cmp  ax,[allocsize]
         ja   @@found
         mov  ax,ds
         IsZero ax
         je   @@no_more_blocks
         call [ds:si] method memory_block:GetNext
         IsZero ax
         je   @@no_more_blocks


         ; The following block may also be free. Try to combine them.
         ; Swap DS and AX
         mov  bx,ds   ; DS has the previous block!
         mov  ds,ax
         mov  ax,bx   ; Make sure AX has the previous block
         call [ds:si] method memory_block:Combine

         jmp  @@scan

         ; No more blocks to scan!
@@no_more_blocks:
ifdef _USE_ROVER_
         ; Scan again from the root, because a big enough
         ; block could be prior to rover.
         cmp  [rootscan],0
         jne  @@scan_root

         inc  [rootscan]
         lds  si,dword ptr [memsysaddr]
         mov  ax,[ds:si.root]

         ; Check to see that rover wasn't already pointing at the root
         cmp  ax,[ds:si.rover]
         je   @@scan_root

         mov  ds,ax
         jmp  @@scan

@@scan_root:
endif
         ; Set rover to point to this new largest memory block,
         ; because combines might have invalidated the rover pointer.
         lds  si,dword ptr [memsysaddr]
         mov  ax,[largestseg]
         mov  [ds:si.rover],ax
         xor  ax,ax
         mov  bx,[largest]
         jmp  @@done

@@found:
         mov  [allocblock],ds
         ; See how much is leftover in the block after the memory needed
         ; for this alloc call is taken out
         mov  ax,[allocsize]
         call [ds:si] method memory_block:BreakBlock
ifdef _USE_ROVER_
         mov  [newfree],ax
endif
         ; Mark the block as used!
         call [ds:si] method memory_block:MarkUsed
         call [ds:si] method memory_block:LockBlock
         call [ds:si] method memory_block:memstart
         push bx

         ; If enough area was leftover, the extra area has been
         ; broken off to make a separate block.
         lds  si,dword ptr [memsysaddr]
ifdef _USE_ROVER_
         ; Update rover
         mov  ax,[newfree]
         mov  [ds:si.rover],ax
endif

         mov  ax,[allocblock]
         pop  bx
;         call [ds:si] method memory_block:memstart
@@done:
         ret
memory_system_alloc endp



memory_system_free proc uses ds si bx
         local prevblock:word,\  ; Address of the block previous to this one
               freeblock:word,\  ; Address of block that is being freed
               systemaddr:dword

         mov  word ptr [systemaddr],si
         mov  word ptr [systemaddr+2],ds
         mov  [freeblock],ax

         cmp  ax,0
         jz   @@done

         ; Check the block to make sure that it is not already free
         ; Note that an invalid block address here will likely hang the
         ; memory manager, since the VMT will not be valid.
         mov  ds,ax
         xor  si,si
ifdef _DO_ISFREE_
         call [ds:si] method memory_block:IsFree
         jz   @@done
endif
         call [ds:si] method memory_block:UnLockBlock

         lds  si,dword ptr [systemaddr]
         mov  ax,[freeblock]
         cmp  ax,[ds:si.root]
         je   @@free_root      ; Special routine to free the root block

ifdef _COMBINE_PREVIOUS_
         ; Prior to freeing the block, get the address of
         ; the previous block. If no previous block is found,
         ; then this is a bogus FREE request and will be ignored.
         call [ds:si] method memory_system:findprev
         IsZero ax   ; Check for zero.
         jz   @@done

         ; There is a previous block
         mov  [prevblock],ax
endif

         ; Mark the current block as free.
         mov  ds,[freeblock]
         xor  si,si
         call [ds:si] method memory_block:MarkFree

ifdef _COMBINE_PREVIOUS_
         mov  ds,[prevblock]
         xor  si,si
         call [ds:si] method memory_block:IsFree
         mov  ds,[freeblock]
         jnz  @@try_combine_next
else
         jmp  @@try_combine_next
endif

@@combine_previous:
         ; The previous block is free, therefore it can be combined with
         ; this one. Set the previous block to point to our next block.
         call [ds:si] method memory_block:GetNext
         mov  ds,[prevblock]
         call [ds:si] method memory_block:SetNext
         ; Also, need to update size of previous block
         ; AX still contains seg of block after one being freed.
         mov  bx,ds
         sub  ax,bx
         dec  ax
         call [ds:si] method memory_block:SetSize
         mov  [freeblock],ds
         jmp  @@try_combine_next

@@free_root:
         ; At this point we only have to worry is if the block following
         ; a free block so it can be combined with this one.
         ; AX is the block to free.
         mov  ds,ax
         xor  si,si
         xor  ax,ax     ; Because there is not previous block
         call [ds:si] method memory_block:MarkFree

@@try_combine_next:
         call [ds:si] method memory_block:GetNext
         mov  ds,ax
         call [ds:si] method memory_block:IsFree
         jnz  @@No_more_combine
         mov  ax,[freeblock]
         mov  [prevblock],ax
         jmp  @@combine_previous

@@No_more_combine:
ifdef _USE_ROVER_
        ; Just in case the rover might have pointed to a block that was
        ; combined with another, set rover to the start of the new
        ; free block that was created.
         lds  si,dword ptr [systemaddr]
         mov  bx,[freeblock]
         mov  [ds:si.rover],bx
endif


@@done:
         ret
memory_system_free endp


.data
LastSeg dw seg zzlastseg


.code
shrink_memory proc
     ; Have to give up extra memory that we don't need
     ; so the memory system objects can get blocks of memory.
     mov  bx,[LastSeg]
     mov  ax,es
     sub  bx,ax    ; Size of program as a number of segments is in BX
     mov  ah,DOSRESIZEBLOCK
     int  DOSINT

         ret
shrink_memory endp



zzlastseg segment

zzlastseg ends

end

