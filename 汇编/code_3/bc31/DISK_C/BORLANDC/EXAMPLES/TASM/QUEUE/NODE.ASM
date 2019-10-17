;-------------------------------------
;-- Define Linked-List Node objects --
;-------------------------------------

MODEL SMALL
LOCALS

;This object is designed to be inherited by any actual data object that is
;placed in the Linked-List, on the Queue or the Stack defined in this module.

;** Define Linked-List Node object **

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

;** Linked-List Node methods **

CODESEG

;Construct (allocate space for) the Node object
;This is the method "node|construct"
;This must be a static method
;Returns AX:BX pointing to allocated but uinitialized node (null if none).
node_construct PROC PASCAL FAR
ARG @@size:word
USES es
	;-- Allocate memory for the node --
	mov bx,@@size
	add bx,15
	shr bx,4
	mov ah,48h
	int 21h
	jc @@err
	sub bx,bx
	ret
@@err:	sub ax,ax
	sub bx,bx
	ret
ENDP

;Destroy the Node object
;This is the method "node|destroy"
node_destroy PROC PASCAL FAR
ARG @@node:dword
USES es
	;-- deallocate memory for the node --
	mov es,word ptr @@node+2
	mov ah,49h
	int 21h
	ret
ENDP

;Initialize the Node object.
;This is the method "node|init"
node_init PROC PASCAL FAR
ARG @@node:dword
USES ds,bx
	lds bx,@@node
	;-- Initialize any virtual method table for the object at ds:bx --
	TBLINIT ds:bx
	;-- Initialize the object's data --
	sub ax,ax
	mov word ptr ds:[bx.node_next],ax
	mov word ptr ds:[bx.node_next+2],ax
	mov word ptr ds:[bx.node_prev],ax
	mov word ptr ds:[bx.node_prev+2],ax
	ret
ENDP

;Deinitialize the Node object.
;This is the method "node|deinit"
node_deinit PROC PASCAL FAR
ARG @@node:dword
	;does nothing.
	ret
ENDP

;Advance to the next node in the linked-list of node objects.
;This is the method "node|next"
;Returns DX:AX pointing to next node, null if none.
node_adv PROC PASCAL NEAR
ARG @@node:dword
USES ds,si
	lds si,@@node
	loadptr dx,ax, ds:si.node_next
	ret
ENDP

;Backup to the previous node in the linked-list of node objects.
;This is the method "node|prev"
;Returns DX:AX pointing to previous node, null if none.
node_back PROC PASCAL NEAR
ARG @@node:dword
USES ds,si
	lds si,@@node
	loadptr dx,ax, ds:si.node_prev
	ret
ENDP

END
