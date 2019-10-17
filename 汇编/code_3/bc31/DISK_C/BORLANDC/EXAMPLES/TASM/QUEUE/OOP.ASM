;This sample demonstrates the use of objects by using objects to create
;a simple linked-list mailing list.

MODEL SMALL
LOCALS


;** Declare Mailing-List node object **

INCLUDE node.aso				;Pull in node object

mlabel STRUC GLOBAL node METHOD {
  init:dword = InitLabel			;initialize address
  deinit:dword = DeinitLabel			;deinitialize address
  print:word = PrintLabel			;print mailling label
  }
  label_name	db 80 dup (?)			;name
  label_addr1	db 80 dup (?)			;address line 1
  label_addr2	db 80 dup (?)			;address line 2
  label_city	db 80 dup (?)			;city
  label_state	db 2 dup (?)			;state
  label_zip	db 9 dup (?)			;zip code
  label_phone	db 10 dup (?)			;phone number
ENDS

;** Create instance of Mailing-List node virtual method table **

DATASEG

TBLINST

;** Declare Mailing-List object **

INCLUDE list.aso				;Pull in list object

mail STRUC GLOBAL list METHOD {
  print:word = PrintList			;print mailling list
  }
ENDS

;** Create instance of Mailing-List virtual method table **

DATASEG

TBLINST

;** Create instance of Mailing-List

mlist mail {}

CODESEG

	startupcode
	;;...
	mov ax,@data
	mov ds,ax
	mov si,offset mlist
	call ds:si method mail:init uses ds:bx pascal,ds si
	;;...
	mov si,offset mlist
	call ds:si method mail:print uses ds:bx pascal,ds si
	;;...



;** Mailing-List methods **

;Print out the mailling list.

;** Mailing-List methods **

;Print the mailling list
PrintList PROC PASCAL NEAR
ARG @@list:dword
USES dx,bx,es,di
	les di,@@list
	call es:di method mail:first pascal,es di
@@lp:	mov ds,dx
	mov bx,ax
	or ax,dx
	jz @@dn
	call ds:bx method mlabel:print uses cs:si pascal,ds bx
        ; call es:di method mail:next pascal,ds bx
        call ds:bx method mlabel:next pascal,ds bx
        mov ds,dx
        mov bx,ax
	jmp short @@lp
@@dn:	ret
ENDP

;** Mailing-List Node methods **

;Initialize the Node object.
;This is the method "node|init"
InitLabel PROC PASCAL FAR
ARG @@node:dword
USES es,di
	les di,@@node
	call es:di method node:init pascal,es di
	sub ax,ax
	mov es:[di.label_name],al
	mov es:[di.label_addr1],al
	mov es:[di.label_addr2],al
	mov es:[di.label_city],al
	mov es:[di.label_state],al
	mov es:[di.label_phone],al
	ret
ENDP

;Deinitialize the Node object.
;This is the method "node|deinit"
DeinitLabel PROC PASCAL FAR
ARG @@node:dword
USES es,di
	les di,@@node
	call es:di method node:init pascal,es di
	ret
ENDP


;Print a mailing list label
PrintLabel PROC PASCAL NEAR
ARG @@node:dword
USES es,di
	;;<<print the label here>>
	ret
ENDP

END
