.386

stack segment use16 stack 
stack ends

data segment use16
data ends

code segment use16
    assume ds:data, cs:code, ss:stack

start:

    mov al, 04h
    out 70h, al
    in al, 71h
    mov ah, 0
    call disp_ax
    mov ah, 4ch
    int 21h

disp_ax proc
    MOV  BX, 16        ;16进制，要除16
    MOV  CX, 4         ;求4位16进制数.
ABC:
    CWD                ;将AX扩展到DX
    DIV  BX
    PUSH DX            ;保存余数到堆栈.
    LOOP ABC
    MOV  CX, 4         ;显示4位.
ASD:
    POP  DX
    CMP  DL, 10
    JB   A48
    ADD  DL, 7
A48:
    ADD  DL, 48
    MOV  AH, 2
    INT  21H           ;输出.
    LOOP ASD
    RET
disp_ax endp

code ends
end start