;--------------------------
;-- Define Queue objects --
;--------------------------

MODEL SMALL
LOCALS

;** Define Queue object **

INCLUDE queue.aso

;** Create instance of Queue virtual method table **

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

;** Queue methods **

CODESEG

;Initialize a queue
queue_init PROC PASCAL NEAR
ARG @@queue:dword
USES ds,bx,es,di
	les di,@@queue
	call es:di method list:init uses ds:bx pascal,es di
	lds bx,@@queue
	tblinit ds:bx
	ret
endp

;Dequeue a node from the queue
;This is the virtual method "queue|dequeue"
;Returns pointer to dequeued node in DX:AX
queue_dequeue PROC PASCAL NEAR
ARG @@queue:dword
USES ds,bx,es,di
	les di,@@queue
	call es:di method list:first uses ds:bx pascal,es di
	isnullptr dx,ax
	jz @@dn
	push dx ax
	call es:di method list:remove uses ds:bx pascal,es di,dx ax
	pop ax dx
@@dn:	ret
ENDP

;Insert a node into the Queue object.
;This is an illegal queue operation
;It is included only to disable the inherited linked-list insert method
queue_insert PROC PASCAL NEAR
ARG	@@list:dword,\			;pointer to list object
	@@oldnode:dword,\		;pointer to node to insert after
	@@node:dword			;pointer to new node to insert
	;does nothing.
	ret
ENDP

;Remove a node from a Queue object.
;This is an illegal queue operation
;It is included only to disable the inherited linked-list delete method
queue_delete PROC PASCAL NEAR
ARG	@@list:dword,\			;pointer to list object
	@@node:dword			;pointer to node to delete
	;does nothing.
	ret
ENDP

;Return a pointer to the first or last node in the Queue object
;These are illegal queue operations
;They are included only to disable the inherited linked-list first/last methods.
queue_first label near
queue_last PROC PASCAL NEAR
ARG	@@list:dword			;pointer to list object
	;does nothing.
	ret
ENDP

END
