.model small
.data
subMsg	db 'This is sub-function',0ah,0dh,0
.code
extrn  _sum:near
extrn  _printf:near
public _show
_show	proc near
	push bp
	mov  bp, sp
	mov  ax, offset subMsg
	push ax
	call _printf
	add  sp, 2
	mov  ax, [bp+4]
	push ax
	call _printf
	add  sp, 2
	mov  ax, 200
	push ax
	mov  ax, 100
	push ax
	call _sum	;(AX)=300
	add  sp, 4
	pop  bp
	ret
_show	endp
_text	ends
	end
