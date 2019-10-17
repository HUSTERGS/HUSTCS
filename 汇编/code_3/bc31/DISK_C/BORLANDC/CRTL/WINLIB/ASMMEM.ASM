;[]-----------------------------------------------------------------[]
;|      ASMMEM.ASM -- Windows memory suballocator                    |
;[]-----------------------------------------------------------------[]

;
;       C/C++ Run Time Library - Version 5.0
; 
;       Copyright (c) 1991, 1992 by Borland International
;       All Rights Reserved.
; 

    INCLUDE RULES.ASI

    locals

    extrn   __GET_TEMP_BLOCK        :far
    extrn   __RLS_TEMP_BLOCK        :far
    extrn   __SIZ_TEMP_BLOCK        :far
    extrn   ___GetSubAllocClientData:far
    extrn   __WinAllocFlag          :word

Code_Seg@

;=============================================================================
comment @

    Memory is allocated from the heap in large chunks ("pages"), which
    are then sub-allocated. All pages are on a doubly linked list that
    starts at the "page_first" member of the application_block structure.

    Pages are normally allocated to be "DEFAULT_PAGE_SIZE" bytes in size,
    but if a block larger than "DEFAULT_PAGE_SIZE - overhead" needs to be
    allocated, a large enough page will be allocated.

    Every page contains a header at its bottom which contains information
    about its total size, total number of free bytes, and the head of the
    linked list of free blocks. Following the header are all the allocated
    and free blocks, always tightly packed (no gaps) and all starting with
    a block header. The last thing in each page (used as a "sentinel") is
    a minimum-size allocated block.

    A block header consists of the block's size (which is always
    a multiple of 4 and includes the block header); free blocks
    have the low bit set in the size word, so that they can be
    distinguished from user blocks.

    When all blocks in a page are freed, that page will be deallocated if
    possible, with the exception of the first one; the current number of
    allocated pages is kept in the "page_count" member of the
    application_block structure.

    For free blocks, the block size is followed by the offset of the next
    free block in the page. For allocated blocks, the page offset follows.

    The following routines are provided:

        __INITMEM:  initializes the allocator variables

        __GETMEM:   allocates DX:AX bytes, result returned
                    in ES:DI

        __RLSMEM:   frees the memory block at ES:DI

        __STOPMEM:  shuts down the allocator, releasing all memory

@
;=============================================================================

DEFAULT_PAGE_SIZE   equ 4096
RLS_UNUSED_MEM      equ 1

;=============================================================================

page_header STRUC

page_next       dw  ?,?         ; next page
page_prev       dw  ?,?         ; prev page

page_size       dw  ?           ; size of page in bytes
page_free_list  dw  ?           ; head of free list
page_free_count dw  ?           ; size of free area(s) in bytes

page_header ENDS

;-----------------------------------------------------------------------------

block_header    STRUC

block_size  dw  ?       ; first allocated page
block_next  dw  ?       ; next free block

block_header    ENDS

block_alignment equ 4       ; multiple of block_header size!


;-----------------------------------------------------------------------------

TSubAllocClientData struc
  page_first    dd  ?   ;address of first page
  page_count    dw  ?   ;number of allocated pages
TSubAllocClientData ends

;-----------------------------------------------------------------------------

page_overhead   EQU (size page_header + 2)

;=============================================================================

InitApplicationBlock    proc

    ;; Returns with ES:DI pointing to the sub allocation client
    ;; data for this application

    push    dx
    push    ax
    call    ___GetSubAllocClientData
    mov es, dx
    mov di, ax
    pop ax
    pop dx
    ret

InitApplicationBlock    endp

    public  __INITMEM

__INITMEM   proc    far

    push    es
    push    di

    call    InitApplicationBlock
    xor ax, ax
    mov word ptr es:[di].page_first, ax ; no pages allocated
    mov word ptr es:[di].page_first+2, ax
    mov es:[di].page_count, ax

    pop di
    pop es
    ret

__INITMEM endp

;=============================================================================

    public  __STOPMEM

__STOPMEM   proc    far

    local   ApplicationBlockPtr:dword=STACKFRAMESIZE

    inc     bp
    push    bp
    mov bp, sp
    sub sp, STACKFRAMESIZE

    push    si
    push    di

    push    es
    push    di

    call    InitApplicationBlock
    mov word ptr [ApplicationBlockPtr+2], es
    mov word ptr [ApplicationBlockPtr], di

ifdef   RLS_UNUSED_MEM

    les di, es:[di].page_first
    jmp SHORT stopmem_next
;
; Here ES:DI points to the current page.
;
stopmem_loop:
    push    es:[di].page_next   ; save "next" value
    push    es:[di].page_next+2
;
; Now free the page at ES:DI.
;

    call    __RLS_TEMP_BLOCK  ; free up the page
    pop es      ; restore the saved "next" value
    pop di
;
; Here ES:DI points to the next page to be freed.
;
stopmem_next:
    mov ax, es          ; any more pages?
    or  ax, di
    jnz stopmem_loop

    les di, ApplicationBlockPtr
    mov word ptr es:[di].page_first, ax
    mov word ptr es:[di].page_first+2, ax
    mov es:[di].page_count, ax

    pop di
    pop si
endif

    mov sp, bp
    pop bp
        dec     bp

    ret

__STOPMEM     endp

;=============================================================================
ifdef   DEBUG
;=============================================================================

check_page  proc    near

        mov bx, es:[di].page_free_list
        and bx, bx
        jz  check_done

        mov dx, es:[di].page_size
        add dx, di
check_loop:
        mov si, es:[bx].block_size  ; SI = free block size

        test    si, 1           ; LSB must be set
        jz  bad_size

        dec si          ; get rid of "free" bit

        mov ax, bx
        add ax, si          ; AX = addr of next block

        cmp ax, dx
        ja  bad_size

        mov cx, es:[bx].block_next
        jcxz    check_done

        cmp ax, cx
        ja  bad_size

        mov bx, cx
        jmp check_loop

check_done: ret

bad_size:   int 3
        jmp bad_size

check_page  endp

;------------------------------------------------------------------------------

    public  __CHECK_PAGES

__CHECK_PAGES proc    far

    local   ApplicationBlockPtr:dword=STACKFRAMESIZE

    pushf
    push    ax
    push    bx
    push    cx
    push    dx
    push    si
    push    di

    inc     bp
        push    bp
    mov bp, sp
    sub sp, STACKFRAMESIZE

    call    InitApplicationBlock
    mov word ptr [ApplicationBlockPtr+2], es
    mov word ptr [ApplicationBlockPtr], di

    mov ax, es
    or  ax, di
    jz  @@Exit

    les di, es:[di].page_first
    jmp short check_entry1

check_loop1:
    call    check_page
    les di, dword ptr es:[di].page_next
check_entry1:
    mov dx, es
    or  dx, di
    jnz check_loop1

@@Exit:
    mov sp, bp
    pop bp
        dec     bp

    pop di
    pop si
    pop dx
    pop cx
    pop bx
    pop ax
    popf

    ret

__CHECK_PAGES endp

;=============================================================================
endif
;=============================================================================

    public  __GETMEM

__GETMEM    proc    far

;
; Function __GETMEM: allocate a memory block
;
; Inputs:
;   DX:AX   =   needed block size in bytes
; Outputs:
;       ES:DI   =   allocated block address
;

    local   getmem_size :word, \
        getmem_last :word, \
        ApplicationBlockPtr :dword, \
        applicationSize :dword = STACKFRAMESIZE

    inc     bp
    push    bp
    mov bp, sp
    sub sp, STACKFRAMESIZE

; First check to see if the block is bigger than we can handle with
; the suballocator.  If it is, then we must defer to the underlying
; memory manager (which will return NULL if it can't process the
; request).  We make the assumption, in this implementation, that if
; a block is bigger than we can handle (that is, bigger than 64K
; minus our block_header size), that the offset portion of the
; address returned from the underlying memory manager will be 0.
; Note that this is currently a safe assumption running under MS
; Windows version 3.x.  It probably won't be safe in the future, but
; then, this implementation will have to change anyway.

    ;; save application-specified size because we'll need the unmodified
    ;; size if we defer to the underlying memory manager.
    mov word ptr [applicationSize+2], dx
    mov word ptr [applicationSize], ax

    ;; Don't suballocate blocks if the attributes are different from
    ;; default or GMEM_ZEROINIT.
    mov cx, __WinAllocFlag
    and cx, NOT 40h             ;GMEM_ZEROINIT
    jnz @@GreaterThan64KJmp     ; yes, don't suballocate

    ;; add our block overhead (rounding up the size to a multiple
    ;; of block_alignment and space for the block header.
    add ax, (block_alignment-1) + size block_header
    adc dx, 0
    and al, not (block_alignment-1)
    ;; check for greater than 64K
    cmp dx, 0                   ;greater than 64K?
    jnz @@GreaterThan64KJmp     ; yes
    ;; resulting size is less than 64K
    mov [getmem_size], ax       ;we only handle 16-bit sizes internally

    call    InitApplicationBlock
    mov word ptr [ApplicationBlockPtr+2], es
    mov word ptr [ApplicationBlockPtr], di

    ;; Check to see if our instance data is initialized yet.  If
    ;; not, then use the underlying memory manager.
    mov ax, es
    or  ax, di
    jz  @@GreaterThan64KJmp ;not yet initialized

ifdef   DEBUG
    call    __CHECK_PAGES
endif

    mov ax, [getmem_size]       ;get block size in AX
;
; Now look through all the allocated pages for a big enough free block.
;
getmem_findfree:
    les di, ApplicationBlockPtr
    les di, es:[di].page_first
    jmp SHORT getfree_test

@@GreaterThan64KJmp:
    jmp @@GreaterThan64K

;
; Here if an allocation has been succesfully made; return to the caller.
;
getfree_done:

ifdef   DEBUG
    push    es
    push    di
    call    __CHECK_PAGES
    pop di
    pop es
endif

    jmp @@RealExit
;
; ES:DI points to the current page; first see if the total number of free
; bytes in this page gives us a chance.
;
getfree_loop:
        cmp es:[di].page_free_count, ax
        jb  getfree_next
;
; There is hope; see if we can allocate the block.
;
        call    near ptr find_free_block; try to get enough space ....
        jc  getfree_done
;
; This page was no good, try the next one.
;
getfree_next:
        les di, dword ptr es:[di].page_next
getfree_test:
        mov dx, es
        or  dx, di
        jnz getfree_loop
;
; No luck with free blocks; we'll need to allocate a new page.
;
        mov ax, [getmem_size]
        cmp ax, DEFAULT_PAGE_SIZE - page_overhead
        ja  bigger_page
        mov ax, DEFAULT_PAGE_SIZE
;
; Here to allocate a new page; AX has its size.
;
getmem_allocpage:
        push    ax          ; save page size
getmem_getpage:
        xor dx, dx          ;high half of zie
        call    __GET_TEMP_BLOCK
        mov es, dx
        mov di, ax
;
; Here ES:DI is the newly allocated page.
;
        pop bx          ; restore page size
        mov ax, es
        or  ax, di
        jz  getmem_error
;
; Insert this page at the beginning of the page list.
;
        push    ds
        lds si, ApplicationBlockPtr
        lds si, ds:[si].page_first
        mov es:[di].page_next  , si
        mov es:[di].page_next+2, ds
        mov ax, ds
        or  ax, si
        jz  getmem_first        ; skip if very first page
        mov page_prev  [si], di
        mov page_prev+2[si], es
getmem_first:
        lds si, ApplicationBlockPtr
        inc ds:[si].page_count
;
; The new page is the new first page.
;
        mov word ptr ds:[si].page_first, di
        mov word ptr ds:[si].page_first+2, es

        pop ds

        xor ax, ax

        mov es:[di].page_prev  , ax
        mov es:[di].page_prev+2, ax
;
; Create a fake "0-length" block at the end of the page.
;
        mov es:[di+bx-2], ax
;
; Now initialize the rest of the page header; don't forget to count the
; fake minimum-size block at the very end of the page.
;
        mov es:[di].page_size, bx   ; save page size
        sub bx, page_overhead
        mov es:[di].page_free_count, bx
        lea si, [di+size page_header]
        mov es:[di].page_free_list , si
;
; Create the free block immediately following the page header.
;
        inc bx          ; set "free" bit
        mov es:[si].block_size, bx
        mov es:[si].block_next, ax
;
; Now the page should be all set for the allocation, so that we can simply
; jump to the beginning of this routine.
;
        mov ax, [getmem_size]   ; size expected in AX
        jmp getmem_findfree
;
; Here if a bigger-than-default page is needed; AX = application block size.
;
bigger_page:
        xor dx, dx          ;prepare for overflow check
        add ax, page_overhead + 255 ;add in overhead
        adc dx, 0           ;add in carry
        cmp dx, 0           ;overflow?
        jnz @@GreaterThan64K    ; yes
        xor al, al
        jmp getmem_allocpage

getmem_error:
    jmp short @@Exit

@@GreaterThan64K:
    ;; The requested block size was greater than 64K (or would
    ;; have exceeded 64K if we tacked on our block header).  Call
    ;; the underlying memory manager to allocate the block.
    ;; The unmodified size is in the applicationSize local variable.

    mov dx, word ptr [applicationSize+2]
    mov ax, word ptr [applicationSize]
    call    __GET_TEMP_BLOCK      ;dx:ax is block
    ;; check our assumption that the offset is always 0.  This is
    ;; required by this implementation because we distinguish
    ;; between foreign blocks and our own managed blocks by the
    ;; zero offset.
    or  ax, ax              ;set flags
    jnz @@NonZeroOffset     ;error, non-zero offset
@@Exit:
    mov es, dx
    mov di, ax

@@RealExit:
    mov sp, bp
    pop bp
        dec     bp
    ret

@@NonZeroOffset:
    ;; The assumption that the underlying memory manager always
    ;; returns blocks with zero offsets was invalid.  Free the
    ;; allocated block and act like the allocation failed.

    call    __RLS_TEMP_BLOCK      ;free memory just allocated

    ;; return with NULL pointer
    xor dx, dx
    xor ax, ax
    jmp short @@Exit        ;and return with NULL pointer

__GETMEM     endp

;------------------------------------------------------------------------------

find_free_block proc    near

;
;   This function looks for a big enough free block in a given page;
;   it assumes that the desired number of bytes is smaller than the
;   total number of free bytes in the page.
;
; Inputs:
;     ES:DI =   page header address
;   AX  =   desired block size
;
; Outputs:
;   CF  =   if successful, will be set
;     ES:DI =   if successful, will contain the address of the block
;
        mov bx, es:[di].page_free_list
        lea dx,    [di].page_free_list
;
; In this main loop, ES:DI always points to the page header; ES:BX to the
; current (free) block, and ES:DX to the "next" link of the previous free
; block (in case we need to remove the current block from the singly-linked
; list of free blocks).
;
; Throughout this function, AX is the size we're trying to allocate.
;
ffree_loop:
        mov si, es:[bx].block_size  ; SI = free block size
        dec si          ; get rid of "free" bit
;
; See if the current free block is big enough.
;
        cmp ax, si          ; block big enough ?
        jbe ffree_found
;
; See if the free block is followed by another free block.
;
        mov cx, es:[bx+si].block_size
        test    cl, 1
        jz  ffree_notfree       ; skip if not
;
; Merge the two (consecutive) free blocks into one, and try again.
;
        dec cx          ; get rid of "free" bit
        add es:[bx].block_size, cx  ; new total size
        mov cx, es:[bx+si].block_next
        mov es:[bx].block_next, cx  ; new "next" link value
        jmp ffree_loop
;
; The adjacent block is not free: follow the linked list of free blocks.
;
ffree_notfree:
        lea dx,    [bx].block_next  ; update "last link" address
        mov bx, es:[bx].block_next  ; point to next free block
        or  bx, bx
        jnz ffree_loop      ; continue if more free blocks
;
; No more free blocks --> return with CF cleared (failure).
;
        ret
;
; We've found a free block; see whether it's larger than we need.
;
ffree_found:
        sub es:[di].page_free_count, ax

        mov cx, es:[bx].block_size
        dec cx
        sub cx, ax          ; CX = excess in bytes
        jz  ffree_remove
;
; Free block is larger than we need, shrink it somewhat and return the upper
; part of it as the allocated block.
;
        mov dx, di
        mov di, bx          ; point DI to upper part
        add di, cx
        mov es:[di].block_size, ax  ; set allocated block's size
        mov es:[di].block_next, dx  ; set page offset
        inc cx
        mov es:[bx].block_size, cx  ; new free block size
        add di, size block_header
;
; Return success - set CF.
;
        stc
        ret
;
; The free block is exactly the right size; simply turn it into an allocated
; block.
;
ffree_remove:
        dec es:[bx].block_size  ; get rid of "free" bit
;
; To remove the block from the linked list, we need to update its
; predecessor's "next" link to the address of the next free block.
;
        mov cx, es:[bx].block_next  ; get next free block address
        mov es:[bx].block_next, di  ; set page offset field
        mov di, dx
        mov es:[di], cx     ; update previous block's link
;
; Finally, point ES:DI past the block header and return.
;
        lea di, [bx+size block_header]

        stc
        ret

find_free_block endp

;==============================================================================

    public  __SIZMEM

__SIZMEM    proc    far

; Function __SIZMEM: return the size of the specified block.
;
; Inputs:
;   ES:DI   =   block address
; Outputs:
;   DX:AX   =   size of specified block


ifdef   DEBUG
        push    es
        push    di
        call    __CHECK_PAGES
        pop di
        pop es
endif

    ;; Check to see if the requested block is one of ours
    ;; we do this by checking the offset for 0.  If it is
    ;; non-zero, it is one of ours and we can look up its
    ;; size.  If it is not one of ours, we must ask the
    ;; underlying memory manager what the size is.

    or  di, di      ;check block address offset
    jz  @@NotOurBlock   ; not one of ours

    sub di, size block_header   ; point to block's header

    xor dx, dx          ; ours are all less than 64K
    mov ax, es:[di].block_size  ; get block size
    sub ax, size block_header
    ret

@@NotOurBlock:
    ;; The block is owned by the underlying memory manager.  Ask
    ;; it what its size is.

    call    __SIZ_TEMP_BLOCK      ;dx:ax is block size
    ret

__SIZMEM     endp


    public  __RLSMEM

__RLSMEM    proc    far

;
; Function __RLSMEM: free a memory block.
;
; Inputs:
;      ES:DI    =   block address
; Outputs:
;   none
;

    local   ApplicationBlockPtr :dword = STACKFRAMESIZE

        inc     bp
    push    bp
    mov bp, sp
    sub sp, STACKFRAMESIZE

ifdef   DEBUG
    push    es
    push    di
    call    __CHECK_PAGES
    pop di
    pop es
endif

    ;; Check to see if the requested block is one of ours
    ;; we do this by checking the offset for 0.  If it is
    ;; non-zero, it is one of ours and we can look up its
    ;; size.  If it is not one of ours, we must ask the
    ;; underlying memory manager what the size is.

    or  di, di          ;check block address offset
    jz  @@NotOurBlockJmp    ; not one of ours

    push    es
    push    di
    call    InitApplicationBlock
    mov word ptr [ApplicationBlockPtr+2], es
    mov word ptr [ApplicationBlockPtr], di
    pop di
    pop es

    sub di, size block_header   ; point to block's header

    mov bx, es:[di].block_next  ; get the page address
;
; Here ES:BX points to the page header, ES:DI to the block header.
;
    mov ax, es:[di].block_size  ; update number of free bytes
    add es:[bx].page_free_count, ax

ifdef   RLS_UNUSED_MEM

;
; See if the page is now completely free.
;
    mov ax, es:[bx].page_size
    sub ax, page_overhead
    cmp ax, es:[bx].page_free_count
    je  rlsmem_freepage
rlsmem_freeit:

endif

;
; Change the block into a free block.
;
    inc es:[di].block_size  ; set the "free" bit
;
; Now find the last free block that's in front of this block.
;
    lea dx,    [bx].page_free_list
    mov si, es:[bx].page_free_list
    jmp short rlsmem_next

@@NotOurBlockJmp:
    jmp @@NotOurBlock

rlsmem_loop:
    cmp si, di          ; this free block above new one?
    ja  rlsmem_insert
    lea dx,    [si].block_next
    mov si, es:[si].block_next
;
; See if there are any more free blocks.
;
rlsmem_next:
    or  si, si          ; more free blocks ?
    jnz rlsmem_loop
;
; Here the new free block needs to be inserted after the "next" link at DX,
; the next free block's address is in SI.
;
rlsmem_insert:
    mov es:[di].block_next, si  ; set "next" for new block
    mov si, dx
    mov es:[si], di     ; set predecessor's "next" value

ifdef   DEBUG
    call    __CHECK_PAGES
endif

    jmp short @@ExitRlsMem

ifdef   RLS_UNUSED_MEM

;
; Here if the page is now completely free.
;
rlsmem_freepage:

    push    es
    push    di
    les di, ApplicationBlockPtr
    cmp es:[di].page_count, 1
    pop di
    pop es
    jbe rlsmem_freeit
;
; First remove this page from the linked list.
;
    push    ds
    lds si, dword ptr es:[bx].page_next
    mov ax, ds          ; DS:SI = next page addr
    mov di, es:[bx].page_prev
    mov dx, es:[bx].page_prev+2 ; DX:DI = prev page addr
    or  ax, si
    jz  rlsmem_last
    mov ds:[si].page_prev  , di
    mov ds:[si].page_prev+2, dx
rlsmem_last:
    mov cx, ds
    mov ds, dx
    or  dx, di
    jz  rlsmem_first
    mov ds:[di].page_next  , si
    mov ds:[di].page_next+2, cx
    pop ds
rlsmem_notfirst:
;
; Now free the page memory.
;
    mov di, bx          ; ES:DI = address of page
    call    __RLS_TEMP_BLOCK
;
; We now have fewer pages.
;
    push    es
    push    di
    les di, ApplicationBlockPtr

    dec es:[di].page_count

    pop di
    pop es

    jmp short @@ExitRlsMem
;
; Here if removing the first page.
;
rlsmem_first:

    pop ds

    push    es
    push    di
    les di, ApplicationBlockPtr

    mov word ptr es:[di].page_first, si
    mov word ptr es:[di].page_first+2, cx

    pop di
    pop es

    pop si

    jmp rlsmem_notfirst
endif

    jmp short @@ExitRlsMem

@@NotOurBlock:
    ;; The specified block is not managed by us.  Ask the
    ;; underlying memory manager to free the block.

    call    __RLS_TEMP_BLOCK

@@ExitRlsMem:

    mov sp, bp
    pop bp
    dec bp
    ret

__RLSMEM     endp

;==============================================================================
Code_EndS@
        END
