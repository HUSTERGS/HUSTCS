;--------------------------------
;-- Define Linked-List objects --
;--------------------------------

MODEL SMALL
LOCALS

;** Define Linked-List object **

INCLUDE list.aso
INCLUDE node.aso

;** Create instance of Linked-List virtual method table **

DATASEG

TBLINST

;** Define some macros for use by the methods **
;** These are used by the methods for storing and loading double registers **

;Load two 16-bit registers from an address in specified segment
loadptr macro r2,r1, addr
	mov r2,word ptr [addr+2]
	mov r1,word ptr [addr]
	endm

;Store two 16-bit registers to an address in specified segment
storeptr macro addr, r2,r1
	mov word ptr [addr+2],r2
	mov word ptr [addr],r1
	endm

;Check to see if two 16-bit registers are both set to 0
;(r1 cannot be ax)
isnullptr macro r2,r1
	ifdifi <r1>,<ax>
	  mov ax,r2
	  or ax,r1
	else
	  push bx
	  push r2
	  pop bx
	  or bx,ax
	  pop bx
	endif
	endm

;** Linked-List methods **

CODESEG

;Construct a Linked-List object
;This is the method "list|construct"
;This must be a static method.
;Returns DX:AX pointing to linked-list object, null if none.
;Object is allocated but not yet initialized.
list_construct PROC PASCAL FAR
USES ds
	;-- Allocate the Linked-List object --
	mov bx,list_size
	mov ah,48h
	int 21h
	jc @@err
	mov dx,ax
	sub ax,ax
	ret
@@err:	sub dx,dx
	sub ax,ax
	ret
ENDP


;Destroy a Linked-List object.
;This is the method "list|destroy"
list_destroy PROC PASCAL FAR
ARG @@list:dword
	;-- deallocate memory for list --
	mov es,word ptr @@list+2
	mov ah,49h
	int 21h
	ret
ENDP

;Initialize a Linked-List object.
;This is the method "list|init"
;This must be a static method!
list_init PROC PASCAL FAR
ARG @@list:dword
USES ds,bx
	lds bx,@@list
	;-- Initialize any virtual method table for the object at ds:bx --
	TBLINIT ds:bx
	;-- Initialize the object's data --
	sub ax,ax
	storeptr ds:bx.list_head, ax,ax
	storeptr ds:bx.list_tail, ax,ax
	ret
ENDP

;Deinitialize a Linked-List object.
;This is the method "list|deinit"
list_deinit PROC PASCAL FAR
ARG @@list:dword
	;does nothing.
	ret
ENDP


;Insert a node into the Linked-List object.
;This is the method "list|insert".
list_insert PROC PASCAL NEAR
ARG	@@list:dword,\			;Pointer to list object
	@@new:dword,\			;Pointer to new node to insert
	@@old:dword			;Pointer to node to insert before
USES ds,es,bx,cx,dx,si,di

	les di,@@new				;es:di = new
	lds si,@@old				;ds:si = old
	;-- First, adjust backward links --
	isnullptr ds,si				;old = null?
	jz @@a
	;-- there is an old node to insert before
	loadptr dx,bx,ds:si.node_prev		;prev <- old.prev
	storeptr ds:si.node_prev,es,di		;old.prev <- new
	jmp short @@b
@@a:	;-- there is no old node to insert before - insert at end
	push ds si				;(save old)
	 lds si,@@list				;(get list object)
	 loadptr dx,bx,ds:si.list_tail		;prev <- tail
	 storeptr ds:si.list_tail,es,di		;tail <- new
	pop si ds				;(recall old)
@@b:	;-- Next, adjust forward links --
	isnullptr dx,bx				;prev = null?
	jz @@c
	;-- there is a prev node to insert after
	push ds					;(save old)
	 mov ds,dx				;(ds:bx = prev)
	 storeptr ds:bx.node_next,es,di		;prev.next <- new
	pop ds					;(recall old)
	jmp short @@d
@@c:	;-- there is no prev node to insert after - insert at start
	push ds si				;(save old)
	 lds si,@@list				;(ds:si = list object)
	 storeptr ds:si.list_head,es,di		;head <- new
	pop si ds				;(recall old)
@@d:	;-- Finally set pointers in this node
	storeptr es:di.node_prev,dx,bx		;new.prev <- prev
	storeptr es:di.node_next,ds,si		;new.next <- old
	ret
ENDP

;Append a node at the end of a Linked-List object.
;This is the virtual method "list|append".
list_append PROC PASCAL NEAR
ARG	@@list:dword,\
	@@new:dword
USES ds,bx,es,di
	mov ax,@Data
	mov ds,ax
	les di,@@list
	sub ax,ax
	call es:di method list:insert uses ds:bx pascal,es di,@@new,ax ax
	ret
ENDP

;Remove a node from a Linked-List object.
;This is the virtual method "list|remove"
;This simply unlinks the node from the list; the node itself must be
;delete by calling the node|deinit method.
list_delete PROC PASCAL NEAR
ARG	@@list:dword,\			;pointer to linked-list object
	@@node:dword			;pointer to node to delete
USES ds,es,si,di

	lds si,@@node			;ds:si = node
	les di,ds:[si.node_prev]	;es:di = prev
	lds si,ds:[si.node_next]	;ds:si = next
	;-- First change next node's previous pointer
	isnullptr ds,si			;next = 0?
	jz @@a				; yes - skip
	storeptr ds:si.node_prev,es,di	;  no - next.prev <- prev
	jmp short @@b			;	and skip...
@@a:	push ds si			;(save next)
	lds si,@@list			;(list object)
	storeptr ds:si.list_tail,es,di	;tail <- prev
	pop si ds			;(recall next)
@@b:	;-- Now change previous node's next pointer
	isnullptr es,di			;prev = 0?
	jz @@c				; yes - skip
	storeptr es:di.node_next,ds,si	;  no - prev.next <- next
	jmp short @@d			;	and done...
@@c:	lds di,@@list			;(list object)
	storeptr ds:di.list_head,ds,si	;head <- next
@@d:	ret
ENDP

;Return a pointer to the first node in the list
;This is the virtual method "list|first"
;Returns DX:AX pointing to first node in list (null if none)
list_first PROC PASCAL NEAR
ARG	@@list:dword			;pointer to linked-list object
USES ds,si
	lds si,@@list
	loadptr dx,ax, ds:si.list_head
	ret
ENDP

;Return a pointer to the last node in the list
;This is the virtual method "list|last"
;Pass:	pointer to object
;Ret:	DX:AX points to last node in list (null if none)
list_last PROC PASCAL NEAR
ARG	@@list:dword			;pointer to linked-list object
USES ds,si
	lds si,@@list
	loadptr dx,ax, ds:si.list_tail
	ret
ENDP

END
