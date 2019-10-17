;--------------------------
;-- Define Stack objects --
;--------------------------

MODEL SMALL
LOCALS

;** Define Stack object **

INCLUDE stack.aso

;** Create instance of stack virtual method table **

DATASEG

TBLINST

;** Define some macros for use by the methods **
;** These are used by the methods for storing and loading double registers **

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

;** stack methods **

CODESEG

;Pop a node from the stack
;This is the virtual method "stack|pop"
;Returns pointer to the poped node in DX:AX
stack_pop PROC PASCAL NEAR
ARG @@stack:dword
USES ds,bx,es,di
	mov ax,@Data
	mov ds,ax
	les di,@@stack
	call es:di method list:last uses ds:bx pascal,es di
	isnullptr dx ax
	jz @@dn
	push dx ax
	call es:di method list:remove uses ds:bx pascal,es di,dx ax
	pop ax dx
@@dn:	ret
ENDP

;Insert a node into the Stack object.
;This is an illegal stack operation
;It is included only to disable the inherited linked-list insert method
stack_insert PROC PASCAL NEAR
ARG	@@list:dword,\			;pointer to list object
	@@oldnode:dword,\		;pointer to node to insert after
	@@node:dword			;pointer to new node to insert
	;does nothing.
	ret
ENDP

;Remove a node from a Stack object.
;This is an illegal stack operation
;It is included only to disable the inherited linked-list delete method
stack_delete PROC PASCAL NEAR
ARG	@@list:dword,\			;pointer to list object
	@@node:dword			;pointer to node to delete
	;does nothing.
	ret
ENDP

;Return a pointer to the first or last node in the Stack object
;These are illegal stack operations
;They are included only to disable the inherited linked-list first/last methods.
stack_first label near
stack_last PROC PASCAL NEAR
ARG	@@list:dword			;pointer to list object
	;does nothing.
	ret
ENDP

END
