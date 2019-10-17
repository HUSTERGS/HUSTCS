; FILE: MEM.INC
; Copyright (c) 1991 By Borland International, Inc.
page


;
; shrink_memory - The main program should call this routine before
;                initializing any memory system objects. This shrinks
;                the DOS memory block used by the program to the
;                minimum possible size.
;
  global shrink_memory:proc


;****************************************************************
; Memory manager
; This memory manager supports simple allocation
; and deallocation of blocks from memory.
;
;

; This value is used in the NEXT pointer to indicate a FREE block
FREE_BLOCK = 0FFFFH


; Note that the VMT's for the objects in this file must be included in
; one of the .OBJ's of a project. This is accomplished by the MEM.ASM
; module defining the following equate before including this file:
;_MAKE_MEMVMT_ = 1

; Memory_block
;       A memory block is created for each unit on the heap. Memory
;   blocks for unused areas of the heap are larger, and contain more
;   information, than used blocks on the heap. Note that there are
;   derived classes that handle implementing used_blocks.
;
; \/ Not yet implemented
; initget- Handles getting an extra block of memory from DOS, and
;          allocating getting it set up. It does not need to be
;          passed the address of a memory block to init.
;          This is an example of a constructor that even does it's
;          own allocation, as well as setting up of VMT.
;     Arguments:(segments of previous and next blocks)
;     Returns:   AX segment of block that was allocated
;
;
; init   - Handles initializing a block to an unused state.
;          Includes setting the VMT pointer to type the block as a
;          memory_block and it also sets the next pointer and the
;          size. The previous block pointer is unused since the
;          memory system does not always find the previous block out
;          of efficiency considerations.
;     Arguments:(DS:SI instance ptr), (segments of previous and next blocks)
;
;
; deinit - Handles destruction of the memory block. Currently has no
;          function for memory_block or memory_usedblock. No protocol
;          for usage is setup.
;
; memstart - Returns fixed offset within memory blocks that marks the
;            start of information that is only optionally used if the
;            block is empty. This allows descendants to increase the
;            amount of bookkeeping information used in the memory_block
;            for all blocks, free and used.
;            Users of the memory system only need to store segment
;            values of alloced blocks, and they can use this function to
;            fill in the offset if they want.
;            Of course, this behaviour may not be compatible with future
;            memory blocks which might not neccessarily return a constant
;            value for the memstart.
;     Arguments: None
;     Returns:   BX  with fixed offset value
;
;
; Show - Shows whether or not the block is free.
;        If the block is free, additional information concerning the block
;        is printed, including it's next pointer and the size of the free
;        area.
;      Arguments: DS:SI - Address of the memory block
;
;
; MatchNext - Finds the address if the block whose next pointer points
;             to the given block
;      Arguments: DS:SI - Address of memory block
;                 AX    - Segment address of block to find next ptr to.
;      Returns:   AX    - Segment of memory block that points to the
;                            given block with next.
;                         AX=0 if a previous block was not found.
;                 DS:SI - Changed
;
; ScanFree   - If the current block is not free, this routine scans forward
;              until a free block is free
;      Arguments: DS:SI - Address of memory block
;      Returns:   DS:SI - Points to a free block.
;                         DS=0 if no more free blocks
;                 AX - Size of block in paragraphs. 0 if not free.
;                      Size is already adjusted for bookkeeping info.
;
;
; GetNext    - Returns the segment address of the next block.
;      Arguments: DS:SI - Address of memory block
;      Returns:   AX    - Segment of next memory block
;
;
; SetNext    - Sets the pointer to the next block
;      Arguments: DS:SI - Address of memory block
;                 AX    - Segment of next memory block
;      Returns:   None
;
;
ifdef _DO_SETPREV_
; SetPrev  - Sets the pointer to the previous memory block. If the
;            block is in use, this call does nothing.
;      Arguments: DS:SI - Address of memory block
;                 AX    - Segment of prev memroy block
;      Returns:   None
endif
;
; SetSize  - Sets the size field of the memory block. If the
;            block is in use, this call does nothing.
;      Arguments: DS:SI - Address of memory block
;                 AX    - Size of the memory block
;      Returns:   None
;
; IsFree
;      Arguments: DS:SI - Address of the memory block
;      Returns    Z flag set if the block is free.
;
;
; MarkUsed - Marks the block as used. This is done by copying the
;            NEXT2 pointer into NEXT. This will erase the FFFF
;            signature in the NEXT ptr, which will show the
;            block as used. This does nothing if the block is already
;            marked as used.
;
;      Arguments: DS:SI - Address of the memory block
;
; MarkFree - Marks the block as free. This is done by copying the
;            NEXT pointer into NEXT2, and putting 0FFFFH in NEXT.
;            Also the size of the block is calculated and filled in.
;            Also the previous block pointer is filled in.
;
;      Arguments: DS:SI - Address of the memory block
;                 AX    - Previous block
;
; RawBlockSize - Returns the total size in paragraphs of the block,
;                including bookkeeping information. Only works for
;                blocks that are free.
;      Arguments: DS:SI - Address of memory block
;      Returns:   AX
;
; BreakBlock - Breaks a free block in two.
;      Arguments: DS:SI - Address of the memory block
;                 AX    - New desired size of the block, not counting
;                         bookkeeping info.
;      Returns:   AX      Segment address of new free block, if block broken
;                         off, or returns same as original DS if whole block
;                         is used.
;
; Combine - Combines a block with it's previous block, if both are free.
;           The previous block is guaranteed to be free if this is called.
;           Alloc calls this during it's forward walk thru the stack.
;           Blocks that are not free should ignore this call.
;      Arguments: DS:SI - Address of the memory block
;                 AX    - Address of the previous block.
;      Returns:   DS:SI - Address of the previous block if the combine was
;                         done, otherwise they are unchanged.
;
;
; LockBlock - Currently not used. This call should be made before using the
;             contents of a block of memory allocated from the heap. This
;             routine may return a new address to use as a pointer to the
;             actual memory contents.
;             This is automatically called before the ALLOC call terminates.
;
; UnLockBlock - Currently not used. This call should be given the value
;             returned by the UnLockBlock routine.
;
; AllocFail - This method is called for all blocks if an allocation
;             request of the memory system is about to fail. If the
;             block does nothing with this request, it needs to return
;             the Z flag set. If it is able to process this request
;             and cause memory to be freed, or in some other way enable
;             the memory system to possibly succeed, then it can return
;             the zero flag unset, and the memory_system will retry the
;             allocation request.
;             Example: Diskswapping memory blocks could delay actual
;             swap out until they recieve this call. Memory blocks and
;             the controlling swap block should know the location of
;             each other, so they both can respond to the request.
;             Blocks that implement memory swapping might even try to
;             swap out several blocks before returning with the Z flag
;             unset.


; Note the size of PREV & NEXT. Because MASM mode makes all symbols
;  be global in scope, if other structures define their own PREV or
;  NEXT pointers, they must be of the same size, and at the same
;  location within the structure. Since other routines may want
;  fullsize NEXT and PREV pointers, this structure defines them to be
;  the same size.... However, a more advanced memory block could
;  make use of the extra word to implement some sort of disk cacheing
;  or other use, especially if lock/unlock system is used for all
;  blocks.
; Note that FindPrev_ is defined to avoid conflict with memory system
;  FindPrev routine.
; Note also show

     global  memory_block_initget:proc
     global  memory_block_init:proc
     global  memory_block_deinit:proc
     global  mb_show:proc
     global  memory_block_reserved_size:proc
     global  mb_findprev:proc
     global  mb_scan:proc
     global  mb_getnext:proc
     global  mb_isfree:proc
     global  mb_setprev:proc
     global  mb_setnext:proc
     global  mb_setsize:proc
     global  mb_rawblocksize:proc
     global  mb_breakblock:proc
     global  memory_block_markused:proc
     global  memory_block_combine:proc
     global  memory_block_markfree:proc
     global  memory_block_lock:proc
     global  memory_block_unlock:proc
     global  memory_block_allocfail:proc

memory_block  STRUC METHOD {
 initget:mptr=memory_block_initget   ;  SI returns seg of allocated block.
 init:mptr=memory_block_init         ;  DS:SI is block.
 virtual deinit:mptr=memory_block_deinit
 virtual show:mptr=mb_show
 virtual memstart:mptr=memory_block_reserved_size
 virtual MatchNext:mptr=mb_findprev
 virtual ScanFree:mptr=mb_scan
 virtual GetNext:mptr=mb_getnext
 virtual IsFree:mptr=mb_isfree
 virtual SetPrev:mptr=mb_setprev
 virtual SetNext:mptr=mb_setnext
 virtual SetSize:mptr=mb_setsize
 virtual RawBlockSize:mptr=mb_rawblocksize
 virtual BreakBlock:mptr=mb_breakblock
 virtual MarkUsed:mptr=memory_block_markused
 virtual Combine:mptr=memory_block_combine
 virtual MarkFree:mptr=memory_block_markfree
 virtual LockBlock:mptr=memory_block_lock
 virtual UnLockBlock:mptr=memory_block_unlock
 virtual AllocFail:mptr=memory_block_allocfail
}

  TBLPTR
  next   dd   ?      ; Segment of the next block in memory.
                     ;  (Only used as a word. High word set to blank in init.)
                     ; FFFF if this block is unused.
                     ; 0000 if this is the last block.

; Mark this offset to be returned as where the caller can start at
; using this block of memory.
@memory_block_used_start  label byte

  ; The following are only for unused blocks
  next2  dd   ?      ; The segment of the next block if this block is unused.
                     ;  (Only used as a word. High word set to blank in init.)
ifdef _DO_SETPREV_
  prev   dd   ?      ; Segment of the previous block.
                     ;  (Only used as a word. High word set to blank in init.)
endif
  blksize  dw   ?    ; Size of the block in paragraphs.
                     ; This should be the size of the allocateable area,
                     ;   (corrected for the bookkeeping area)

memory_block  ends


ifdef _MAKE_MEMVMT_
; Make the VMT for the memory blocks
MAKE_VMT
endif

;mbsize = size @TableAddr_MEMORY_BLOCK


; memory_usedblock
;    When a block of memory on the heap is in use, it's VMT is changed
; so that the block becomes used. The usedblock routines handle returning,
; in a faster way, the results for various block methods. The block
; methods for invalid operations on used blocks are quickly trapped,
; and can even vector to internal_error display routines.
;    While the normal memory_block routines do extensive checking with the
; IsFree method, changing used blocks to this type should speed many
; operations

     global memory_usedblock_init:proc
     global memory_usedblock_getnext:proc
     global memory_usedblock_scan:proc
     global memory_usedblock_isfree:proc
     global memory_usedblock_invalid:proc
     global memory_usedblock_setnext:proc
     global memory_usedblock_markfree:proc
     global memory_usedblock_show:proc
     global memory_usedblock_combine:proc
     global memory_usedblock_lock:proc
     global memory_usedblock_unlock:proc

memory_usedblock  struc memory_block method {
         init:mptr = memory_usedblock_init
         virtual getnext:mptr=memory_usedblock_getnext
         virtual ScanFree:mptr=memory_usedblock_scan
         virtual IsFree:mptr=memory_usedblock_isfree
         virtual SetPrev:mptr=memory_usedblock_invalid
         virtual SetSize:mptr=memory_usedblock_invalid
         virtual SetNext:mptr=memory_usedblock_setnext
         virtual BreakBlock:mptr=memory_usedblock_invalid
         virtual MarkFree:mptr=memory_usedblock_markfree
         virtual MarkUsed:mptr=memory_usedblock_invalid
         virtual show:mptr = memory_usedblock_show
         virtual Combine:mptr=memory_usedblock_combine
         virtual LockBlock:mptr=memory_usedblock_lock
         virtual UnLockBlock:mptr=memory_usedblock_unlock
        }
memory_usedblock  ends


ifdef _MAKE_MEMVMT_
; Make the VMT for the memory usedblocks
MAKE_VMT
endif

; memory_endblock
;    This block is placed at the end of the memory heap. It should
; be only a paragraph in size, just large enough for the bookkeeping
; info of the segment. This allows all other blocks on the heap to
; be guarranteed that a block follows them, and therefore they can all
; use simple segment arithmetic to calculate their size. While the
; size of the memory block can be made a part of the information that
; is stored for the free blocks, used blocks do not have room for this
; information. Since the block does not have access to the last segment
; variable of the heap, the ending block on the heap would have no way
; to calculate it's size if it is used, since the next pointer would
; be zero.   This block handles the whole matter, by appearing to be a
; permanently used block at the end of the heap. Since the next pointer
; is zero, all heapwalks will stop with this block.

     global memory_endblock_init:proc
     global memory_endblock_show:proc
     global memory_endblock_getnext:proc
     global memory_endblock_ignore:proc

memory_endblock  struc memory_usedblock method {
         init:mptr = memory_endblock_init
         virtual getnext:mptr = memory_endblock_getnext
         virtual show:mptr = memory_endblock_show
         virtual RawBlockSize:mptr=memory_endblock_getnext
         virtual LockBlock:mptr=memory_endblock_ignore
         virtual UnLockBlock:mptr=memory_endblock_ignore
         }
memory_endblock  ends


ifdef _MAKE_MEMVMT_
; Make the VMT for the memory endblocks
MAKE_VMT
endif


;  MEMORY_SYSTEM
;
;  init -  Handles setting up a block of memory for memory allocation
;          management.
;      Arguments: DS:SI - Address of memory system object
;                 AX    - 0 - Allocate maximum block.
;                         other - Size of desired block
;                         High-bit of AX  - If 1 - Allow smaller block
;                                           If 0 - Fail if not enough memory
;      Returns:   Memory block initialized.
;                 DS:SI unchanged.
;                 AX is size of actual block. (Note that maximum allocateable
;                       size is a paragraph less than this value because of
;                       memory_block bookkeeping.)
;
;
; alloc - Allocates an area in the memory block.
;      Arguments: DS:SI - Address of memory system object
;                 AX    - Size in bytes of area to allocate
;      Returns:   AX is segment of memory block
;                 BX is the offset into the memory block
;                 DS:SI unchanged
;                 If no block can be allocated, then AX is zero, and
;                 BX is the size of the largest block.
;
;
; free -   Frees an allocated area
;      Arguments: DS:SI - Address of the memory system object
;                 AX    - Segment of area to be freed
;      Returns:   None
;
;
; blockofs - Returns fixed offset within memory blocks that marks the
;            start of information that is only optionally used if the
;            block is empty. This allows descendants to increase the
;            amount of bookkeeping information used in the memory_block
;            for all blocks, free and used.
;            Users of the memory system only need to store segment
;            values of alloced blocks, and they can use this function to
;            fill in the offset if they want.
;     Arguments: AX  Segment of block to find this value for
;                    (If AX=0, then root block's blockofs is returned.)
;     Returns:   AX  with fixed offset value
;
;
; resetrover - Makes rover point at the root block. This causes the
;            next alloc call to use the earliest possible free
;            block in the heap.
;
;
;
; show - Displays global status information for the memory_system, and
;       then calls the show method for each of the individual memory
;       blocks.
;
;
; freeall - Frees all blocks on the heap.
;
;***** Lower Level Calls:
;
;  FindPrev - Finds the address if the block current to the previous block.
;      Arguments: DS:SI - Address of memory system
;                 AX    - Segment address of block to find previous for
;      Returns:   AX    - Segment of previous memory block
;                         AX=0 if a previous block was not found.
;                 DS:SI - Unchanged

; This is the global memory system manager object.

     global memory_system_init:proc
     global memory_system_deinit:proc
     global memory_system_show:proc
     global memory_system_alloc:proc
     global memory_system_free:proc
     global memory_system_blockofs:proc
     global memory_system_freeall:proc
     global memory_system_resetrover:proc
     global memory_system_findprev:proc

memory_system STRUC METHOD {
         init:mptr = memory_system_init
         virtual deinit:mptr=memory_system_deinit
         virtual show:mptr=memory_system_show
         virtual alloc:mptr=memory_system_alloc
         virtual free:mptr=memory_system_free
         blockofs:mptr=memory_system_blockofs
         virtual freeall:mptr=memory_system_freeall
         virtual resetrover:mptr=memory_system_resetrover
         virtual FindPrev:mptr=memory_system_findprev
       }
  TBLPTR

  blocksize dw ?     ; Size of the block of memory managed by this
                     ; memory system manager.
  root   dw   ?      ; The first block of memory
  last   dw   ?      ; The last block of memory
  rover  dw   ?      ; Moves through memory

  freespace dw ?     ; Remembers the amount of free space total in paragraphs
  usedspace dw ?     ; Remembers the amount of used memory in paragraphs
memory_system ends
;mssize = size @TableAddr_MEMORY_system

ifdef _MAKE_MEMVMT_
; Make the VMT for the memory endblocks
MAKE_VMT
endif


