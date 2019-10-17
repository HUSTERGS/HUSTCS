PUBLIC  _BUFA,_convert
EXTRN  _INVAL:WORD
.386
DATA    SEGMENT  USE16
_BUFA    DB 15 DUP(0)
DATA    ENDS
STACK1   SEGMENT  USE16 STACK
        DB  1000 DUP(0)
STACK1   ENDS
_TEXT    SEGMENT  USE16  PUBLIC 'CODE'
		ASSUME CS:_TEXT,DS:DATA,SS:STACK1
_convert  PROC  NEAR
		PUSH  EAX
		PUSH  EBX
		PUSH  SI
		PUSH  DS
		MOVZX EAX,_INVAL
		MOV   EBX,16            ;转成16进制形式显示
		MOV   SI,DATA
		MOV   DS,SI
		LEA   SI,_BUFA
		CALL  RADIX_R
		MOV   BYTE PTR [SI],'H'
		POP   DS
		POP   SI
		POP   EBX
		POP   EAX
		RET
_convert  ENDP

RADIX_R   PROC  NEAR
		PUSH  CX
		PUSH  EDX
		XOR   CX,CX
LOP1:   XOR   EDX,EDX
		DIV   EBX
		PUSH  DX
		INC   CX
		OR    EAX,EAX
		JNZ   LOP1
LOP2:   POP   AX
		CMP   AL,10
		JB    L1
		ADD   AL,7
L1:     ADD   AL,30H
		MOV   [SI],AL
		INC   SI                   ;指针指向下一个单元
		DEC   CX
		JNZ   LOP2
		POP   EDX
		POP   CX
		RET
RADIX_R   ENDP
_TEXT   ENDS
END